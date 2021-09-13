#ifndef SHADOWLAYER_H
#define SHADOWLAYER_H

#include <QPair>
#include <QPixmap>
#include <QPoint>
#include <QWidget>

class ShadowLayer : public QWidget
{
    Q_OBJECT
public:
    explicit ShadowLayer(QWidget* parent = nullptr);

    const QPixmap& capture_pic() const;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
signals:
    void capture_over(QPixmap pic);

private:
    QPair<QPoint, QPoint> m_rectAngle;
    bool m_isPressing;
    QPixmap m_pic;
    QPixmap m_capture_pic;
};

#endif // SHADOWLAYER_H
