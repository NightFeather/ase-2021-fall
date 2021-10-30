#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QUuid>
#include <QDateTime>
#include "attachment.h"

class Note : public QObject
{
    Q_OBJECT
public:
    explicit Note(QObject *parent = nullptr);

    const QUuid &id() const;
    void setId(const QUuid &newId);
    const QString &title() const;
    void setTitle(const QString &newTitle);
    const QStringList &persons() const;
    void setPersons(const QStringList &newPersons);
    const QString &location() const;
    void setLocation(const QString &newLocation);
    const QDateTime &timestamp() const;
    void setTimestamp(const QDateTime &newTimestamp);
    const QList<Attachment *> &attachments() const;
    void setAttachments(const QList<Attachment *> &newAttachments);

    const QString &body() const;
    void setBody(const QString &newBody);

signals:

private:
    QUuid m_id;
    QString m_title;
    QStringList m_persons;
    QString m_location;
    QString m_body;
    QDateTime m_timestamp;
    QList<Attachment*> m_attachments;
};

#endif // NOTE_H
