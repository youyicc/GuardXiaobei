#ifndef GUARDXIAOBEI_H
#define GUARDXIAOBEI_H

#include <QLabel>
#include <QBrush>
#include <QDialog>
#include <QScreen>
#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QGuiApplication>

class GuardXiaobei : public QDialog
{
    Q_OBJECT

private:
    int radius;
    QPoint last;
    int currentAngle;
    QRect geometry;

private:
    QLabel* lab_Value;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

private:
    void DrawLineEllipse(QPainter&,int,QColor);
    void DrawConicalGradientFullArc(QPainter&,int,QColor);
    void DrawConicalGradientArc(QPainter&,int,QColor,QColor);
    void DrawRadialGradientArc(QPainter&,int,QColor,QColor);

public:
    GuardXiaobei(QWidget *parent = nullptr);
    ~GuardXiaobei();

public:
    void SetCurrentValue(int);                      //设置进度条当前值
};
#endif
