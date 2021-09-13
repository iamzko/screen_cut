#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseDoubleClickEvent(QMouseEvent* event);

private slots:
    void on_actionScreen_Cut_triggered();

    void on_actionClear_triggered();

    void on_actionShadow_Layer_triggered();
    void on_show_capture_pic(QPixmap pic);

    void on_actiontest1_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
