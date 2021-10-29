#ifndef PAGECONTEXT_H
#define PAGECONTEXT_H

#include <QObject>
#include <QHash>

class PageContext : public QObject
{
    Q_OBJECT
public:
    explicit PageContext(QObject *parent = nullptr);
    explicit PageContext(const QString &path, QObject *parent = nullptr);
    explicit PageContext(const QString &path, const QString &title, QObject *parent = nullptr);

    PageContext(const PageContext&);
    bool operator==(const PageContext&) const;
    PageContext& operator=(const PageContext&);

    const QString &title() const;
    void setTitle(const QString &newTitle);
    const QString &path() const;
    QHash<QString, QString> &args();

signals:
    void titleChanged();

private:
    QString m_path;
    QString m_title;
    QHash<QString, QString> m_args;
};

Q_DECLARE_METATYPE(PageContext);

#endif // PAGECONTEXT_H
