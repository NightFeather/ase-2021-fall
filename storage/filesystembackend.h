#ifndef FILESYSTEMBACKEND_H
#define FILESYSTEMBACKEND_H

#include "storagebackend.h"
#include <QObject>
#include <QDir>

class FilesystemBackend : public StorageBackend
{
public:
    explicit FilesystemBackend(QObject *parent = nullptr);

public:
    virtual bool connect(const QString&) override;
    virtual void close() override;

    bool open(const QString&);
    bool create(const QString&); // create model directory
    bool remove(const QString&);

    size_t write(const QString&, const QString&, const QByteArray&); // write single entity
    QByteArray read(const QString&, const QString&); // read single entity

private:
    QDir m_base;
};

#endif // FILESYSTEMBACKEND_H
