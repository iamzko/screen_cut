#include "shadowlayer.h"
#include <QApplication>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QScreen>
#include <QtDebug>

ShadowLayer::ShadowLayer(QWidget* parent)
    : QWidget(parent)
    , m_isPressing(false)
{
    setWindowFlag(Qt::FramelessWindowHint);
    //    QPalette palette = this->palette();
    //    palette.setColor(QPalette::Window, QColor(0, 0, 0, 0));
    //    this->setPalette(palette);
    setWindowOpacity(1); //设置透明度，1为不透明，0为完全透明
    setMouseTracking(true); //设置鼠标追踪
    m_pic = QGuiApplication::primaryScreen()->grabWindow();
    update();
    //    auto screen = QGuiApplication::primaryScreen();
    //    this->setGeometry(screen->availableGeometry());
}

void ShadowLayer::mousePressEvent(QMouseEvent* event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        close();
    } else {
        m_isPressing = true;
        qDebug() << m_isPressing;
    }
}

void ShadowLayer::mouseReleaseEvent(QMouseEvent* event)
{
    m_isPressing = false;
    m_capture_pic = m_pic.copy(m_rectAngle.first.x(), m_rectAngle.first.y(), m_rectAngle.second.x() - m_rectAngle.first.x(), m_rectAngle.second.y() - m_rectAngle.first.y());
    emit capture_over(m_capture_pic);
    qDebug() << m_isPressing;
    close();
}

void ShadowLayer::paintEvent(QPaintEvent* event)
{
    if (m_isPressing) {
        QPainter p(this);
        p.drawPixmap(this->rect(), m_pic);
        QPen pen(QColor(0, 255, 0));
        pen.setWidth(3);
        p.setPen(Qt::NoPen);
        p.setBrush(QBrush(QColor(160, 160, 160, 100)));
        p.drawRect(this->rect());

        //        p.drawRect(this->rect().x(), this->rect().y(), this->rect().width(), m_rectAngle.first.y() - this->rect().y());
        //        p.drawRect(this->rect().x(), m_rectAngle.first.y(), m_rectAngle.first.x() - this->rect().x(), m_rectAngle.second.y() - m_rectAngle.first.y());
        //        p.drawRect(m_rectAngle.second.x(), m_rectAngle.first.y(), this->rect().width() - m_rectAngle.second.x(), m_rectAngle.second.y() - m_rectAngle.first.y());
        //        p.drawRect(this->rect().x(), m_rectAngle.second.y(), this->rect().width(), this->rect().height() - m_rectAngle.second.y());
        p.setBrush(QBrush(QColor(0, 0, 0, 0)));
        p.drawPixmap(m_rectAngle.first.x(), m_rectAngle.first.y(), m_rectAngle.second.x() - m_rectAngle.first.x(), m_rectAngle.second.y() - m_rectAngle.first.y(), m_pic.copy(m_rectAngle.first.x(), m_rectAngle.first.y(), m_rectAngle.second.x() - m_rectAngle.first.x(), m_rectAngle.second.y() - m_rectAngle.first.y()));
        p.setBrush(Qt::NoBrush);

        p.setPen(pen);
        qDebug() << m_rectAngle.first.x() << "," << m_rectAngle.first.y() << "," << m_rectAngle.second.x() << "," << m_rectAngle.second.y();
        p.drawText(QRect(m_rectAngle.first.x(), m_rectAngle.first.y() - 20, 200, 20), QString::fromUtf8(u8"%1,%2;%3,%4").arg(m_rectAngle.first.x()).arg(m_rectAngle.first.y()).arg(m_rectAngle.second.x()).arg(m_rectAngle.second.y()));

        p.drawRect(m_rectAngle.first.x(), m_rectAngle.first.y(), m_rectAngle.second.x() - m_rectAngle.first.x(), m_rectAngle.second.y() - m_rectAngle.first.y());
    } else {
        QPainter p(this);
        //        p.setBrush(QBrush(QColor(160, 160, 160, 100)));
        //        p.drawRect(this->rect());
        p.drawPixmap(this->rect(), m_pic);
        p.setBrush(QBrush(QColor(160, 160, 160, 100)));
        p.drawRect(this->rect());
    }
}

void ShadowLayer::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isPressing) {
        m_rectAngle.second = event->pos();
        update();
    } else {
        m_rectAngle.first = event->pos();
    }
}
