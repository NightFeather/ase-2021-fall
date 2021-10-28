#include "pagecontext.h"

PageContext::PageContext(QObject *parent) : QObject(parent), m_current("/")
{

}

QString PageContext::current() const
{
    return m_current;
}

void PageContext::setCurrent(const QString& newCurrent)
{
    if(m_current != newCurrent)
        emit routeChanged(newCurrent);

    m_current = newCurrent;
}
