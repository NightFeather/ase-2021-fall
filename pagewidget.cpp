#include "pagewidget.h"

PageWidget::PageWidget(QWidget *parent, PageContext* context) : QWidget(parent), m_context(context)
{

}

PageContext *PageWidget::context() const
{
    return m_context;
}

void PageWidget::setContext(PageContext *newContext)
{
    if (m_context == newContext)
        return;
    m_context = newContext;
    emit contextChanged();
}
