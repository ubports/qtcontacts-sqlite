/*
 * Copyright (C) 2013 Jolla Ltd. <andrew.den.exter@jollamobile.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#ifndef CONTACTREADER_H
#define CONTACTREADER_H

#include "contactid_p.h"
#include "contactsdatabase.h"

#include <QContact>
#include <QContactCollection>
#include <QContactManager>

#include <QSqlDatabase>
#include <QSqlQuery>

QTCONTACTS_USE_NAMESPACE

class ContactReader
{
public:
    ContactReader(ContactsDatabase &database, const QString &managerUri);
    virtual ~ContactReader();

    QContactManager::Error readCollections();

    QContactManager::Error readContacts(
            const QString &table,
            QList<QContact> *contacts,
            const QContactFilter &filter,
            const QList<QContactSortOrder> &order,
            const QContactFetchHint &fetchHint);

    QContactManager::Error readContacts(
            const QString &table,
            QList<QContact> *contacts,
            const QList<QContactId> &contactIds,
            const QContactFetchHint &fetchHint);

    QContactManager::Error readContacts(
            const QString &table,
            QList<QContact> *contacts,
            const QList<quint32> &databaseIds,
            const QContactFetchHint &fetchHint,
            bool relaxConstraints = false);

    QContactManager::Error readContactIds(
            QList<QContactId> *contactIds,
            const QContactFilter &filter,
            const QList<QContactSortOrder> &order);

    QContactManager::Error getIdentity(
            ContactsDatabase::Identity identity, QContactId *contactId);

    QContactManager::Error readRelationships(
            QList<QContactRelationship> *relationships,
            const QString &type,
            const QContactId &first,
            const QContactId &second);

    bool fetchOOB(const QString &scope, const QStringList &keys, QMap<QString, QVariant> *values);

    bool fetchOOBKeys(const QString &scope, QStringList *keys);

protected:
    QContactManager::Error readDeletedContactIds(
            QList<QContactId> *contactIds,
            const QContactFilter &filter);

    QContactManager::Error queryContacts(
            const QString &table, QList<QContact> *contacts, const QContactFetchHint &fetchHint, bool relaxConstraints = false);
    QContactManager::Error queryContacts(
            const QString &table, QList<QContact> *contacts, const QContactFetchHint &fetchHint, bool relaxConstraints, QSqlQuery &query, QSqlQuery &relationshipQuery);

    virtual void collectionsAvailable(const QList<QContactCollection> &collections);
    virtual void contactsAvailable(const QList<QContact> &contacts);
    virtual void contactIdsAvailable(const QList<QContactId> &contactIds);

private:
    ContactsDatabase &m_database;
    QString m_managerUri;
};

#endif
