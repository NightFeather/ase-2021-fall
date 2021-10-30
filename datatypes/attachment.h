#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include <QObject>
#include <QFile>
#include <QPixmap>
#include <QUuid>

class Attachment : public QObject
{
    Q_OBJECT
public:
    explicit Attachment(QObject *parent = nullptr);
    explicit Attachment(const QString& type, QObject *parent = nullptr);
    Attachment(const Attachment&);

    const QString &type() const;
    const QString &title() const;
    void setTitle(const QString &newTitle);
    const QString &desc() const;
    void setDesc(const QString &newDesc);
    virtual const QPixmap* preview();

    bool operator==(const Attachment&) const;

    bool editable() const;
    bool hasPreview() const;

    const QUuid &id() const;

signals:

private:
    QUuid m_id;
    QString m_type;
    QString m_title;
    QString m_desc;
};

Q_DECLARE_METATYPE(Attachment);

#endif // ATTACHMENT_H
