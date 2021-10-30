#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include "navcontext.h"

class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr, NavContext *context = nullptr);

    virtual bool handle(const QHash<QString, QVariant>&);

    NavContext *context() const;
    void setContext(NavContext *newContext);

signals:
    void contextChanged();

private:
    NavContext* m_context;
};

#endif // PAGEWIDGET_H
