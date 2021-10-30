#include "attachment.h"

Attachment::Attachment(QObject *parent) : QObject(parent),
  m_id(), m_type(), m_title(), m_desc()
{

}

Attachment::Attachment(const QString &type, QObject *parent) : QObject(parent),
    m_type(type), m_title("No title"), m_desc("No Description")
{

}

Attachment::Attachment(const Attachment &other) :
     m_id(other.m_id), m_type(other.m_type), m_title(other.m_title), m_desc(other.m_desc)
{

}

const QString &Attachment::type() const
{
    return m_type;
}

const QString &Attachment::title() const
{
    return m_title;
}

void Attachment::setTitle(const QString &newTitle)
{
    m_title = newTitle;
}

const QString &Attachment::desc() const
{
    return m_desc;
}

void Attachment::setDesc(const QString &newDesc)
{
    m_desc = newDesc;
}

const QPixmap *Attachment::preview()
{
    return new QPixmap(":/images/nopreview.png");
}

bool Attachment::editable() const
{
    return false;
}

bool Attachment::hasPreview() const
{
    return true;
}

const QUuid &Attachment::id() const
{
    return m_id;
}

bool Attachment::operator==(const Attachment &other) const {
    return other.m_id == m_id && other.m_type == m_type;
}
