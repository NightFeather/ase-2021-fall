#include "landingwidget.h"
#include "ui_landingwidget.h"

LandingWidget::LandingWidget(QWidget *parent) :
    PageWidget(parent, nullptr),
    ui(new Ui::LandingWidget)
{
    ui->setupUi(this);
    connect(ui->browse_button, &QAbstractButton::clicked, this, &LandingWidget::gotoBrowser);
    connect(ui->new_button, &QAbstractButton::clicked, this, &LandingWidget::gotoCreator);
    connect(ui->openlast_button, &QAbstractButton::clicked, this, &LandingWidget::gotoEditor);
}

LandingWidget::~LandingWidget()
{
    delete ui;
}

void LandingWidget::gotoBrowser()
{
    if(context() != nullptr) {
        context()->setCurrent("/browse");
    }
}

void LandingWidget::gotoCreator()
{
    if(context() != nullptr) {
        context()->setCurrent("/create");
    }
}

void LandingWidget::gotoEditor()
{
    if(context() != nullptr) {
        context()->setCurrent("/openlast");
    }
}
