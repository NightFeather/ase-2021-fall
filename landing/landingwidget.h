#ifndef LANDINGWIDGET_H
#define LANDINGWIDGET_H

#include <QWidget>
#include "pagewidget.h"

namespace Ui {
class LandingWidget;
}

class LandingWidget : public PageWidget
{
    Q_OBJECT

public:
    explicit LandingWidget(QWidget *parent = nullptr);
    ~LandingWidget();

public slots:
    void gotoBrowser();
    void gotoCreator();
    void gotoEditor();

private:
    Ui::LandingWidget *ui;
};

#endif // LANDINGWIDGET_H
