#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "shadowlayer.h"
#include <QClipboard>
#include <QFuture>
#include <QMouseEvent>
#include <QPixmap>
#include <QScreen>
#include <QThread>
#include <QtConcurrent/QtConcurrentRun>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setScaledContents(true);
    //    ui->scrollArea->setWidget(ui->label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    auto ori_size = ui->label->size();
    if (event->button() == Qt::LeftButton) {
        ui->label->resize(ori_size * 2);
        ui->scrollAreaWidgetContents->resize(ori_size * 2);
    } else if (event->button() == Qt::RightButton) {
        ui->label->resize(ori_size / 2);
        ui->scrollAreaWidgetContents->resize(ori_size / 2);
    }
}

void MainWindow::on_actionScreen_Cut_triggered()
{
    this->hide();
    QThread::sleep(1);
    //    auto pic = QPixmap::grabWindow(QApplication::desktop()->winId());
    //    auto pic = QGuiApplication::primaryScreen()->grabWindow();
    auto pic = QGuiApplication::screenAt(QCursor::pos())->grabWindow();
    ui->label->resize(pic.size());
    ui->scrollAreaWidgetContents->resize(pic.size());
    ui->label->setPixmap(pic);
    auto clipboard = QApplication::clipboard();
    clipboard->setPixmap(pic);
    this->show();
}
void MainWindow::on_actionClear_triggered()
{
    ui->label->clear();
}

void MainWindow::on_actionShadow_Layer_triggered()
{
    ShadowLayer* shadow = new ShadowLayer();
    connect(shadow, &ShadowLayer::capture_over, this, &MainWindow::on_show_capture_pic);
    shadow->showFullScreen();
}

void MainWindow::on_show_capture_pic(QPixmap pic)
{
    ui->label->setPixmap(pic);
}

void MainWindow::on_actiontest1_triggered()
{
    int i = 0;
    QFuture<int> test;
    auto result = QtConcurrent::run([&](int p) {p = i++;return p; }, 10).then([&](int p) { i = p++ + i;return p; }).then([&](int p) {p = i++;qDebug() << "p:" << p;return p; });

    qDebug() << "i:" << i;
    qDebug() << result.result();
}
