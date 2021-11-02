#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <datatypes/note.h>
#include "filesystembackend.h"

class NoteManager : public QObject
{
    Q_OBJECT
public:
    explicit NoteManager(QObject *parent = nullptr);
    NoteManager(const QString& base, QObject* parent = nullptr);

    Note* get(QUuid);                           // get by id
    QList<Note*> find(const QString&, const QString&);  // search by field
    QList<Note*> find(const QDate&);                    // search by date
    QList<Note*> find(const QDate&, const QDate&);      // search by range

    bool index(Note*);
    bool indexAll();
    bool save(Note*);
    bool remove(Note*);

    static QString makepath(Note*);
signals:

private:
    FilesystemBackend m_backend;
    QSqlDatabase m_indexdb;
};

#endif // NOTEMANAGER_H
