#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QObject>
#include <QFile>

class Attachment : public QObject
{
    Q_OBJECT
public:
    explicit Attachment(QObject *parent = nullptr);

    virtual QFile* getFile() = 0;
signals:

};

#endif // ATTACHMENT_H
