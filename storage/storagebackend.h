#ifndef STORAGEBACKEND_H
#define STORAGEBACKEND_H

#include <QObject>

class StorageBackend : public QObject
{
    Q_OBJECT
public:
    explicit StorageBackend(QObject *parent = nullptr);

    virtual bool connect(const QString&) = 0;
    virtual void close() = 0;

protected:
    const QString &uri() const;
    void setUri(const QString &newUri);
    bool opened() const;
    void setOpened(bool newOpened);

signals:


private:
    QString m_uri;
    bool m_opened;
};

#endif // STORAGEBACKEND_H
