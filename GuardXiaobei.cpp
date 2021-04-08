#include "GuardXiaobei.h"

GuardXiaobei::GuardXiaobei(QWidget *parent)
    : QDialog(parent)
{
    //设置窗口大小
    setFixedSize(70,70);
    //去掉标题栏 设置置顶 去掉任务栏图标
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|
                   Qt::WindowCloseButtonHint|Qt::WindowStaysOnTopHint);
    //获取主屏尺寸 设置位置
    QScreen *primaryScreen=QGuiApplication::primaryScreen();
    if(primaryScreen==nullptr)
        return;
    geometry=primaryScreen->availableGeometry();
    this->move(geometry.width()-100,geometry.height()*0.6);
    //初始化变量
    radius=34;
    currentAngle=0;
    last=QPoint(0,0);
    //设置窗口背景透明
    setAttribute(Qt::WA_TranslucentBackground, true);
    try {
        //初始化控件
        lab_Value=new QLabel();
        QLabel *lab_Unit=new QLabel();
        QLabel *lab_NetSpeed=new QLabel();
        QHBoxLayout* valueLayout=new QHBoxLayout();
        QVBoxLayout* mainLayout=new QVBoxLayout();
        //设置控件样式
        lab_Value->setFont(QFont("宋体",18));
        //设置控件文字
        lab_Value->setText("0");
        lab_Unit->setText("%");
        lab_NetSpeed->setText("0K/s");
        //设置控件文字对齐方式
        lab_Value->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
        lab_Unit->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
        lab_NetSpeed->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        lab_Value->setFixedHeight(40);
        lab_Unit->setFixedHeight(36);
        //设置布局
        valueLayout->setMargin(0);
        valueLayout->setSpacing(0);
        valueLayout->addStretch(1);
        valueLayout->addWidget(lab_Value);
        valueLayout->addWidget(lab_Unit);
        valueLayout->addStretch(1);
        mainLayout->setMargin(0);
        mainLayout->setSpacing(0);
        mainLayout->addLayout(valueLayout,3);
        mainLayout->addWidget(lab_NetSpeed,2);
        setLayout(mainLayout);
    } catch (...) {}
}

GuardXiaobei::~GuardXiaobei()
{}

void GuardXiaobei::SetCurrentValue(int value)
{
    lab_Value->setText(QString("%1").arg(value));
    currentAngle=-(value/100.0)*360+90;
    update();
}

void GuardXiaobei::mousePressEvent(QMouseEvent *e)
{
    last = e->globalPos();
}

void GuardXiaobei::mouseMoveEvent(QMouseEvent *e)
{
    if((last.x()==0)&&(last.y()==0))
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    this->move(x()+dx, y()+dy);
}

void GuardXiaobei::mouseReleaseEvent(QMouseEvent *e)
{
    if((last.x()==0)&&(last.y()==0))
        return;
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    this->move(x() + dx, y() + dy);
}

void GuardXiaobei::mouseDoubleClickEvent(QMouseEvent*)
{
    SetCurrentValue(qrand()%100);
}

void GuardXiaobei::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //启动反锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    //将画笔中心点移动到窗体中心
    painter.translate(this->width()/2,this->height()/2);
    //绘制外圆环
    DrawLineEllipse(painter,radius,QColor(230,230,230,100));
    //绘制中圆环
    DrawConicalGradientFullArc(painter,radius-1,QColor(255,255,255,50));
    //绘制进度条圆环
    DrawConicalGradientArc(painter,radius-1,QColor(86,229,108),QColor(255,0,0));
    //绘制内圆环
    DrawLineEllipse(painter,radius-6,QColor(21,207,96,150));
    //绘制中遮罩
    DrawConicalGradientFullArc(painter,radius-6,QColor(230,230,230));
    //绘制一个锥形渐变
    DrawRadialGradientArc(painter,radius-7,QColor(21,207,96,80),QColor(230,230,230));
}

void GuardXiaobei::DrawLineEllipse(QPainter& painter,int r,QColor color)
{
    QBrush brush(color);
    painter.setPen(QPen(brush,1,Qt::SolidLine));
    painter.drawEllipse(-r,-r,r<<1,r<<1);
}

void GuardXiaobei::DrawConicalGradientFullArc(QPainter& painter,int r,QColor color)
{
    QConicalGradient conicalGradient(QPointF(0, 0), 90);
    conicalGradient.setColorAt(0, color);
    conicalGradient.setColorAt(1.0, color);
    painter.setBrush(conicalGradient);
    painter.drawEllipse(QPoint(0,0),r,r);
}

void GuardXiaobei::DrawConicalGradientArc(QPainter& painter,int r,QColor startColor,QColor endColor)
{
    // 渐变色
    QConicalGradient conicalGradient(QPointF(0, 0), 90);
    conicalGradient.setColorAt(0,endColor);
    conicalGradient.setColorAt(1.0, startColor);
    painter.setBrush(conicalGradient);
    QRectF rect(-r,-r,r<<1,r<<1);
    QPainterPath path;
    path.arcTo(rect,currentAngle,90-currentAngle);
    painter.setPen(Qt::NoPen);
    painter.drawPath(path);
}

void GuardXiaobei::DrawRadialGradientArc(QPainter& painter,int r,QColor startColor,QColor endColor)
{
    QRadialGradient radialGradient(0,0,r,0,0);
    radialGradient.setColorAt(0.7,endColor);
    radialGradient.setColorAt(1,startColor);
    painter.setBrush(radialGradient);
    painter.drawEllipse(-r,-r,r<<1,r<<1);
}
