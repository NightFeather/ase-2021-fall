#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_context(new PageContext)
{
    ui->setupUi(this);
    ui->welcompage->setContext(m_context);
    connect(m_context, &PageContext::routeChanged, this, &MainWindow::routeChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::routeChanged(QString route)
{
    auto segs = route.split("/");
    if(segs.at(1) == "browse") {
        this->ui->stackedWidget->setCurrentIndex(1);
    } else if(segs.at(1) == "create") {
        this->ui->stackedWidget->setCurrentIndex(2);
    } else if(segs.at(1) == "openlast") {
        this->ui->stackedWidget->setCurrentIndex(2);
    }
}
