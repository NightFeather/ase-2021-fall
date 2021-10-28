#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include "pagecontext.h"

class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr, PageContext *context = nullptr);

    PageContext *context() const;
    void setContext(PageContext *newContext);

signals:
    void contextChanged();

private:
    PageContext* m_context;
};

#endif // PAGEWIDGET_H
