#include "pagewidget.h"

PageWidget::PageWidget(QWidget *parent, NavContext* context) : QWidget(parent), m_context(context)
{

}

bool PageWidget::handle(const QHash<QString, QVariant> &)
{
    return true;
}

NavContext *PageWidget::context() const
{
    return m_context;
}

void PageWidget::setContext(NavContext *newContext)
{
    if (m_context == newContext)
        return;
    m_context = newContext;
    emit contextChanged();
}
