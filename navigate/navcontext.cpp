#include "navcontext.h"

NavContext::NavContext(QObject *parent) : QObject(parent), m_history()
{
    m_history.push(PageContext());
}

const PageContext &NavContext::currentPage() const
{
    return m_history.top();
}

void NavContext::replacePage(const QString& newCurrent)
{
    return replacePage(PageContext(newCurrent));
}

void NavContext::gotoPage(const QString& next)
{
    return gotoPage(PageContext(next));
}

void NavContext::replacePage(const PageContext& newCurrent)
{
    if(currentPage() != newCurrent)
        emit routeChanged(newCurrent);

    m_history.pop();
    m_history.push(newCurrent);
}

void NavContext::gotoPage(const PageContext& next)
{
    if(currentPage() == next) { return; }
    m_history.push(next);
    emit routeChanged(next);
}

void NavContext::backPage()
{
    if(history().length() <= 1) { return; }
    m_history.pop();
    emit routeChanged(currentPage());
}

const QStack<PageContext> &NavContext::history() const
{
    return m_history;
}
