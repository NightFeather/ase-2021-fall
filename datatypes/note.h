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
    Note(const Note&);
    Note(Note&&);

    const QUuid &id() const;
    void setId(const QUuid &newId);
    const QString &title() const;
    void setTitle(const QString &newTitle);
    const QStringList &persons() const;
    void setPersons(const QStringList &newPersons);
    const QString &location() const;
    void setLocation(const QString &newLocation);
    const QDateTime &when() const;
    void setWhen(const QDateTime &newWhen);
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
    QDateTime m_when;
    QList<Attachment*> m_attachments;
};

Q_DECLARE_METATYPE(Note);

#endif // NOTE_H
