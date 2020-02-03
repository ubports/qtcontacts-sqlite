/*
 * Copyright (C) 2020 UBports Foundation
 * Author(s): Alberto Mardegan <mardy@users.sourceforge.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <qcontact.h>
#include <qcontactcollectionid.h>
#include <qcontactmanager.h>
#include <qversitcontactimporter.h>
#include <qversitdocument.h>
#include <qversitreader.h>

class EdsReader {
public:
    EdsReader(const QString &filePath):
        m_db(QSqlDatabase::addDatabase("QSQLITE", "eds"))
    {
        m_db.setDatabaseName(filePath);
        if (!m_db.open()) {
            qCritical() << "Cannot open DB file" << filePath;
        }

        m_query = QSqlQuery(m_db);
        m_query.exec("SELECT vcard FROM 'folder_id'");
    }

    bool next() {
        return m_query.next();
    }

    QByteArray vCard() const {
        return m_query.value(0).toByteArray();
    }

private:
    QSqlDatabase m_db;
    QSqlQuery m_query;
};

class Importer {
public:
    Importer(const QByteArray &localCollectionId):
        m_manager("org.nemomobile.contacts.sqlite"),
        m_collectionId(m_manager.managerUri(), localCollectionId),
        m_numCards(0)
    {
    }

    void addVCard(const QByteArray &vcard) {
        m_vcards += "\r\n" + vcard;
        m_numCards++;
        if (m_numCards % 20 == 0) { // save every 20 vcards
            importVCards();
        }
    }

    bool importVCards() {
        QtVersit::QVersitReader reader(m_vcards);
        reader.startReading();
        reader.waitForFinished();
        if (Q_UNLIKELY(reader.error() != QtVersit::QVersitReader::NoError)) {
            qWarning() << "Error reading VCARD:" << reader.error();
        }
        bool ok = m_importer.importDocuments(reader.results());

        QMap<int, QContactManager::Error> errorMap;
        QList<QContact> contacts = m_importer.contacts();
        if (!m_collectionId.isNull()) {
            for (QContact &contact: contacts) {
                contact.setCollectionId(m_collectionId);
            }
        }
        ok &= m_manager.saveContacts(&contacts, &errorMap);
        if (Q_UNLIKELY(!errorMap.isEmpty())) {
            qWarning() << "Errors importing contacts:" << errorMap;
        }

        return ok;
    }

private:
    QContactManager m_manager;
    QContactCollectionId m_collectionId;
    QtVersit::QVersitContactImporter m_importer;
    int m_numCards;
    QByteArray m_vcards;
};

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    EdsReader edsReader(app.arguments()[1]);

    QByteArray collectionId = app.arguments().count() > 2 ?
        app.arguments()[2].toUtf8() : QByteArray();
    Importer importer(collectionId);

    while (edsReader.next()) {
        importer.addVCard(edsReader.vCard());
    }

    bool ok = importer.importVCards();
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
