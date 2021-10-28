#include "browserwidget.h"
#include "ui_browserwidget.h"

BrowserWidget::BrowserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrowserWidget)
{
    ui->setupUi(this);
}

BrowserWidget::~BrowserWidget()
{
    delete ui;
}
