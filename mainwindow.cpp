#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_context(new NavContext)
{
    ui->setupUi(this);
    ui->welcompage->setContext(m_context);
    ui->backBtn->setVisible(false);

    qRegisterMetaType<PageContext>("PageContext");

    connect(m_context, &NavContext::routeChanged, this, &MainWindow::routeChanged);
    connect(ui->backBtn, &QToolButton::clicked, m_context, &NavContext::backPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::routeChanged(const PageContext& page)
{
    auto route = page.path();
    auto segs = route.split("/");
    if(route == "/") {
        this->ui->stackedWidget->setCurrentIndex(0);
    } else if(segs.length() > 1) {
        if(segs.at(1) == "browse") {
            this->ui->stackedWidget->setCurrentIndex(1);
        } else if(segs.at(1) == "create") {
            this->ui->stackedWidget->setCurrentIndex(2);
        } else if(segs.at(1) == "editor") {
            this->ui->stackedWidget->setCurrentIndex(2);
        } else {
            qWarning() << QString("Try navigating to invalid route %1.").arg(route) << Qt::endl;
        }
    } else {
        qWarning() << QString("Try navigating to invalid route %1.").arg(route) << Qt::endl;
    }
    ui->backBtn->setVisible(m_context->history().length() > 1);
    ui->title->setText(m_context->currentPage().title());
}
