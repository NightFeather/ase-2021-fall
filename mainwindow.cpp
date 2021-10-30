#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <datatypes/attachment.h>
#include <datatypes/note.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_context(new NavContext)
{
    ui->setupUi(this);
    ui->welcompage->setContext(m_context);
    ui->editor->setContext(m_context);
    ui->backBtn->setVisible(false);

    qRegisterMetaType<PageContext>("PageContext");
    qRegisterMetaType<Note>("Note");
    qRegisterMetaType<Attachment>("Attachment");

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
        ui->stackedWidget->setCurrentIndex(0);
    } else if(segs.length() > 1) {
        if(segs.at(1) == "browse") {
            ui->stackedWidget->setCurrentIndex(1);
        } else if(segs.at(1) == "editor") {
            ui->editor->handle(page.args());
            ui->stackedWidget->setCurrentIndex(2);
        } else {
            qWarning() << QString("Try navigating to invalid route %1.").arg(route) << Qt::endl;
        }
    } else {
        qWarning() << QString("Try navigating to invalid route %1.").arg(route) << Qt::endl;
    }
    ui->backBtn->setVisible(m_context->history().length() > 1);
    ui->title->setText(m_context->currentPage().title());
}
