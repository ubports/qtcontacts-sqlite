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

#include "contactsengine.h"
#include "contactid_p.h"
#include <QContactManagerEngineFactory>

#include <QtDebug>

QTCONTACTS_USE_NAMESPACE

class ContactsFactory : public QContactManagerEngineFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QContactManagerEngineFactoryInterface" FILE "plugin.json")

public:
    ContactsFactory();

    QContactManagerEngine *engine(
            const QMap<QString, QString> &parameters, QContactManager::Error* error);
    QString managerName() const;
#ifndef NEW_QTPIM
    QContactEngineId *createContactEngineId(
            const QMap<QString, QString> &parameters, const QString &engineIdString) const;
#endif
};


ContactsFactory::ContactsFactory()
{
}

QContactManagerEngine *ContactsFactory::engine(
        const QMap<QString, QString> &parameters, QContactManager::Error* error)
{
    ContactsEngine *engine = new ContactsEngine(managerName(), parameters);
    QContactManager::Error err = engine->open();
    if (error)
        *error = err;
    if (err != QContactManager::NoError) {
        delete engine;
        return 0;
    } else {
        return engine;
    }
}

QString ContactsFactory::managerName() const
{
    return QString::fromLatin1("org.nemomobile.contacts.sqlite");
}

#ifndef NEW_QTPIM
QContactEngineId *ContactsFactory::createContactEngineId(
        const QMap<QString, QString> &parameters, const QString &engineIdString) const
{
    Q_UNUSED(parameters)
    return new ContactId(engineIdString);
}
#endif

#include "contactsplugin.moc"
