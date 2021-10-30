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
        context()->gotoPage("/browse");
    }
}

void LandingWidget::gotoCreator()
{
    if(context() != nullptr) {
        PageContext ctx("/editor");
        auto args = ctx.args();
        args.insert("action", "new");
        ctx.setArgs(args);
        context()->gotoPage(ctx);
    }
}

void LandingWidget::gotoEditor()
{
    if(context() != nullptr) {
        PageContext ctx("/editor");
        auto args = ctx.args();
        args.insert("action", "open");
        args.insert("id", "_last");
        ctx.setArgs(args);
        context()->gotoPage(ctx);
    }
}
