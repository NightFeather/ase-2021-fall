#include "filesystembackend.h"

FilesystemBackend::FilesystemBackend(QObject *parent) : StorageBackend(parent)
{

}


bool FilesystemBackend::connect(const QString &uri)
{
    QDir d;
    setUri(uri);

    if(!d.exists(uri)) {
        d.mkpath(uri);
    }

    if(d.exists(uri)) {
        d.setPath(uri);
        m_base = d;
        setOpened(true);
        return true;
    } else {
        return false;
    }
}

void FilesystemBackend::close()
{
    setOpened(false);
}

QFileInfoList FilesystemBackend::list(const QString &path)
{
    QDir d(m_base);
    if(d.cd(path)) {
        return d.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::DirsFirst|QDir::Name);
    }
    return QFileInfoList();
}

bool FilesystemBackend::open(const QString &pkey, bool autoCreate)
{
    QDir d(m_base);
    if(d.exists(pkey)) { return true; }
    if(autoCreate && d.mkpath(pkey)) { return true; }
    return false;
}

bool FilesystemBackend::rename(const QString &src, const QString &dst, bool overwrite)
{
    QDir d(m_base);
    if(!d.exists(src)) { return false; }
    if(d.exists(dst)) {
        if(!overwrite) { return false; }
        d.rmpath(dst);
    }

    // make sure parents exists
    d.mkpath(dst);
    d.rmdir(dst);

    d.rename(src, dst);

    return true;
}

bool FilesystemBackend::remove(const QString &pkey)
{
    QDir d(m_base);
    if(d.exists(pkey)) {
        return d.rmpath(pkey);
    }
    return false;
}

size_t FilesystemBackend::write(const QString &pkey, const QString &field, const QByteArray &value)
{
    QDir d(m_base);
    if(!d.exists(pkey)) { d.mkpath(pkey); }
    if(d.cd(pkey)) {
        QFile f(d.filePath(field));
        if(f.open(QFile::ReadWrite)) {
            return f.write(value);
        }
    }
    return 0;
}

QByteArray FilesystemBackend::read(const QString &pkey, const QString &field)
{
    QDir d(m_base);
    if(d.cd(pkey)) {
        QFile f(d.filePath(field));
        if(f.open(QFile::ReadWrite)) {
            return f.readAll();
        }
    }
    return QByteArray();
}
