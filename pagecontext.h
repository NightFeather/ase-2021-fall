#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include <QObject>

class PageContext : public QObject
{
    Q_OBJECT
public:
    explicit PageContext(QObject *parent = nullptr);

    QString current() const;
    void setCurrent(const QString& newCurrent);

signals:
    void routeChanged(QString);

private:
    QString m_current;
};

#endif // PAGECONTROLLER_H
