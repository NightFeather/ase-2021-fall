#include "notemanager.h"
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>
#include <QSqlRecord>

NoteManager::NoteManager(QObject *parent) : QObject(parent)
{
    m_backend.connect(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/Notes");

    QDir d;
    if(!d.exists(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation))) {
        d.mkpath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    }
    d.setPath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    if(!d.exists("NoteApp")) { d.mkdir("NoteApp"); }
    d.cd("NoteApp");

    auto fp = d.filePath("notes_indexes");
    m_indexdb = QSqlDatabase::addDatabase("QSQLITE", fp);
    m_indexdb.open();

    m_indexdb.exec(
        "CREATE TABLE IF NOT EXISTS main"
        "(nid TEXT PRIMARY KEY, path TEXT, location TEXT, when TEXT)"
    ).exec();

    m_indexdb.exec("CREATE INDEX IF NOT EXISTS idx_location ON main ( location )").exec();
    m_indexdb.exec("CREATE INDEX IF NOT EXISTS idx_when ON main ( when )").exec();

    m_indexdb.exec(QString("CREATE TABLE IF NOT EXISTS persons"
                           "(person TEXT PRIMARY KEY, nid TEXT)"
                           )).exec();
}

NoteManager::NoteManager(const QString &base, QObject *parent) : QObject(parent)
{
    m_backend.connect(base);

    QDir d;
    if(!d.exists(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation))) {
        d.mkpath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    }
    d.cd(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    if(!d.exists("NoteApp")) { d.mkdir("NoteApp"); }
    d.cd("NoteApp");

    auto fp = d.filePath("notes_indexes");
    m_indexdb = QSqlDatabase::addDatabase("QSQLITE", fp);
    m_indexdb.open();

    m_indexdb.exec(
        "CREATE TABLE IF NOT EXISTS main"
        "(nid TEXT PRIMARY KEY, path TEXT, location TEXT, when TEXT)"
    );

    m_indexdb.exec("CREATE INDEX IF NOT EXISTS idx_location ON main ( location )");
    m_indexdb.exec("CREATE INDEX IF NOT EXISTS idx_when ON main ( when )");

    m_indexdb.exec(QString("CREATE TABLE IF NOT EXISTS persons"
                           "(person TEXT PRIMARY KEY, nid TEXT)"
                           ));
}

Note* NoteManager::get(QUuid id)
{
    if(id.isNull()) { return nullptr; }

    auto query = m_indexdb.exec(
          QString("SELECT path from main where nid = '%1'").arg(id.toString())
    );

    if(query.size() <= 0) { return nullptr; }

    auto path = query.record().value("path").toString();

    if(path.isEmpty()) { return nullptr; } // WTF

    Note* note = new Note;

    auto res = m_backend.read(path, "props.json");
    auto props = QJsonDocument::fromJson(res).object().toVariantMap();

    note->setId(props["id"].toUuid());
    note->setTitle(props["title"].toString());
    note->setWhen(props["when"].toDateTime());
    note->setLocation(props["location"].toString());
    note->setPersons(props["persons"].toStringList());

    note->setBody(m_backend.read(path, "body"));

    return note;
}

QList<Note*> NoteManager::find(const QString &, const QString &)
{
    return QList<Note*>();
}

QList<Note*> NoteManager::find(const QDate & date)
{
    auto dpath = date.toString("yyyy/MM/dd");
    QList<Note*> notes;

    for(auto& dir: m_backend.list(dpath)) {

        QString path = dir.filePath();
        Note* note = new Note;

        auto res = m_backend.read(path, "props.json");
        auto props = QJsonDocument::fromJson(res).object().toVariantMap();

        note->setId(props["id"].toUuid());
        note->setTitle(props["title"].toString());
        note->setWhen(props["when"].toDateTime());
        note->setLocation(props["location"].toString());
        note->setPersons(props["persons"].toStringList());

        note->setBody(m_backend.read(path, "body"));

        notes.append(note);
    }
    return notes;
}

QList<Note*> NoteManager::find(const QDate &from, const QDate &to)
{
    QList<Note*> notes;
    QDate i = from;
    while(i < to) {
        notes.append(find(i));
        i = i.addDays(1);
    }
    return notes;
}

bool NoteManager::index(Note *note)
{
    QSqlQuery query1("INSERT INTO main (nid, path, location, when) VALUES (?, ?, ?, ?)", m_indexdb);
    query1.bindValue(0, note->id().toString());
    query1.bindValue(1, makepath(note));
    query1.bindValue(2, note->location());
    query1.bindValue(3, note->when());

    QSqlQuery query2("INSERT INTO persons (person, nid) VALUES (?, ?)", m_indexdb);
    query2.addBindValue(note->persons());
    auto repeated = QStringList();
    {
        auto i = note->persons().length();
        while(--i) { repeated.append(note->id().toString()); }
    }
    query2.addBindValue(repeated);

    return query1.exec() && query2.execBatch();
}

bool NoteManager::indexAll()
{
    QList<QFileInfo> pending;

    pending.append(m_backend.list("."));
    while(!pending.isEmpty()) {
        auto item = pending.first();
        pending.pop_front();

    }
    return false;
}

bool NoteManager::save(Note *note)
{
    QVariantMap props;
    QJsonDocument doc;

    if(note->id().isNull()) {
        note->setId(QUuid::createUuid());
        note->setTimestamp(QDateTime::currentDateTime());
    }

    QString path = makepath(note);

    props["id"] = note->id();
    props["title"] = note->title();
    props["when"] = note->when();
    props["location"] = note->location();
    props["persons"] = note->persons();

    doc.setObject(QJsonObject::fromVariantMap(props));

    return m_backend.write(path, "props.json", doc.toJson()) &&
            m_backend.write(path, "body", note->body().toUtf8());
}

bool NoteManager::remove(Note *)
{

    return false;
}

QString NoteManager::makepath(Note *note)
{
    auto path = QString("%1/%2");
    path = path.arg(note->timestamp().toString("yyyy/MM/dd"));
    path = path.arg(note->title().toHtmlEscaped());
    return path;
}
