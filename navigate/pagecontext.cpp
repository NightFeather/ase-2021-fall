#include "pagecontext.h"

PageContext::PageContext(QObject *parent) : QObject(parent),
    m_path("/"), m_title(""), m_args()
{

}

PageContext::PageContext(const QString &path, QObject *parent) : QObject(parent),
    m_path(path), m_title(path), m_args()
{

}

PageContext::PageContext(const QString &path, const QString &title, QObject *parent) : QObject(parent),
    m_path(path), m_title(title), m_args()
{

}

PageContext::PageContext(const PageContext& other) : QObject(nullptr),
    m_path(other.m_path), m_title(other.m_title), m_args(other.m_args){

}

bool PageContext::operator==(const PageContext & other) const {
    return other.m_path == m_path;
}

PageContext& PageContext::operator=(const PageContext& other) {
    this->m_path = other.m_path;
    this->m_title = other.m_title;
    this->m_args = other.m_args;
    return *this;
}

const QString &PageContext::title() const
{
    return m_title;
}

void PageContext::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

const QString &PageContext::path() const
{
    return m_path;
}

const QHash<QString, QVariant> &PageContext::args() const
{
    return m_args;
}

void PageContext::setArgs(const QHash<QString, QVariant> &newArgs)
{
    m_args = newArgs;
}
