#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include <QObject>
#include <QStack>
#include "pagecontext.h"

class NavContext : public QObject
{
    Q_OBJECT
public:
    explicit NavContext(QObject *parent = nullptr);

    const PageContext& currentPage() const;
    void replacePage(const QString& newCurrent);
    void gotoPage(const QString &);
    void replacePage(const PageContext& newCurrent);
    void gotoPage(const PageContext &);
    void backPage();

    const QStack<PageContext> &history() const;

signals:
    void routeChanged(PageContext);

private:
    QStack<PageContext> m_history;
};

#endif // PAGECONTROLLER_H
