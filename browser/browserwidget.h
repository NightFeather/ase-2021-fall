#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>

namespace Ui {
class BrowserWidget;
}

class BrowserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BrowserWidget(QWidget *parent = nullptr);
    ~BrowserWidget();

private:
    Ui::BrowserWidget *ui;
};

#endif // BROWSERWIDGET_H
