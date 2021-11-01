#include "filesystembackend.h"

FilesystemBackend::FilesystemBackend(QObject *parent) : StorageBackend(parent)
{

}


bool FilesystemBackend::connect(const QString &uri)
{
    QDir d;
    setUri(uri);

    if(!d.exists(uri)) {
        if(d.mkpath(uri)) {
            d.setPath(uri);
            m_base = d;
        }
        return false;
    }

    setOpened(true);
    return true;
}

void FilesystemBackend::close()
{
    setOpened(false);
}

bool FilesystemBackend::open(const QString &pkey)
{
    QDir d(m_base);
    return d.cd(pkey);
}

bool FilesystemBackend::create(const QString &pkey)
{
    QDir d(m_base);
    if(!d.cd(pkey)) {
        if(d.mkpath(pkey)) {
            return true;
        }
    }
    return false;
}

bool FilesystemBackend::remove(const QString &pkey)
{
    QDir d(m_base);
    if(d.cd(pkey)) {
        return d.removeRecursively();
    }
    return false;
}

size_t FilesystemBackend::write(const QString &pkey, const QString &field, const QByteArray &value)
{

}

QByteArray FilesystemBackend::read(const QString &pkey, const QString &field)
{

}
