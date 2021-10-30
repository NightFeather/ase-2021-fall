#include "note.h"

Note::Note(QObject *parent) : QObject(parent)
{

}

Note::Note(const Note &other)
    : m_id(other.m_id)
    , m_title(other.m_title)
    , m_persons(other.m_persons)
    , m_location(other.m_location)
    , m_body(other.m_body)
    , m_timestamp(other.m_timestamp)
    , m_attachments(other.m_attachments)
{
}

Note::Note(Note && other)
    : m_id(std::move(other.m_id))
    , m_title(std::move(other.m_title))
    , m_persons(std::move(other.m_persons))
    , m_location(std::move(other.m_location))
    , m_body(std::move(other.m_body))
    , m_timestamp(std::move(other.m_timestamp))
    , m_attachments(std::move(other.m_attachments))
{

}

const QUuid &Note::id() const
{
    return m_id;
}

void Note::setId(const QUuid &newId)
{
    m_id = newId;
}

const QString &Note::title() const
{
    return m_title;
}

void Note::setTitle(const QString &newTitle)
{
    m_title = newTitle;
}

const QStringList &Note::persons() const
{
    return m_persons;
}

void Note::setPersons(const QStringList &newPersons)
{
    m_persons = newPersons;
}

const QString &Note::location() const
{
    return m_location;
}

void Note::setLocation(const QString &newLocation)
{
    m_location = newLocation;
}

const QDateTime &Note::timestamp() const
{
    return m_timestamp;
}

void Note::setTimestamp(const QDateTime &newTimestamp)
{
    m_timestamp = newTimestamp;
}

const QList<Attachment *> &Note::attachments() const
{
    return m_attachments;
}

void Note::setAttachments(const QList<Attachment *> &newAttachments)
{
    m_attachments = newAttachments;
}

const QString &Note::body() const
{
    return m_body;
}

void Note::setBody(const QString &newBody)
{
    m_body = newBody;
}
