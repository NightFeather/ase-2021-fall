#ifndef STORAGEBACKEND_H
#define STORAGEBACKEND_H

#include <QObject>

class StorageBackend : public QObject
{
    Q_OBJECT
public:
    explicit StorageBackend(QObject *parent = nullptr);

signals:

};

template<typename T> class TypedStorageBackend : public StorageBackend {
};

#endif // STORAGEBACKEND_H
