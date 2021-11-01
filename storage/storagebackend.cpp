#include "storagebackend.h"

StorageBackend::StorageBackend(QObject *parent) : QObject(parent)
{

}

const QString &StorageBackend::uri() const
{
    return m_uri;
}

void StorageBackend::setUri(const QString &newUri)
{
    m_uri = newUri;
}

bool StorageBackend::opened() const
{
    return m_opened;
}

void StorageBackend::setOpened(bool newOpened)
{
    m_opened = newOpened;
}
