#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "navigate/navcontext.h"
#include "landing/landingwidget.h"
#include "browser/browserwidget.h"
#include "editor/editorwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void routeChanged(const PageContext &);

private:
    Ui::MainWindow *ui;
    NavContext* m_context;
};
#endif // MAINWINDOW_H
