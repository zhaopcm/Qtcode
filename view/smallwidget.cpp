#include "smallwidget.h"

#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

smallwidget::smallwidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox *box = new QSpinBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal, this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(box);
    layout->addWidget(slider);

    //官方推荐方式处理重载信号
    //connect(box, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);
    //第二种方式
    //connect(box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), slider, &QSlider::setValue);
    //第三种方式
    void (QSpinBox::*send_value)(int) = &QSpinBox::valueChanged;
    connect(box, send_value, slider, &QSlider::setValue);
    connect(slider, &QSlider::valueChanged, box, &QSpinBox::setValue);

    //调用样式表
}
