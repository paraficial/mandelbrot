#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    canvas = new Mandelbrot();
    hbox = new QHBoxLayout(this);
    vbox = new QVBoxLayout();

    label1 = new QLabel("Threshold: ", this);
    label2 = new QLabel("Gradient: ", this);
    label3 = new QLabel("", this);

    colors = new QStringList();
    colors->append("Blue");
    colors->append("Green");
    colors->append("Red");
    colors->append("Yellow");

    combo1 = new QComboBox();
    combo1->addItems(*colors);
    combo2 = new QComboBox();
    combo2->addItems(*colors);

    threshold = new QSpinBox();

    status = new QStatusBar();

    vbox->addWidget(label1);
    vbox->addWidget(threshold);
    vbox->addWidget(label2);
    vbox->addWidget(combo1);
    vbox->addWidget(combo2);
    vbox->addWidget(label3, 1, Qt::AlignBottom);

    hbox->addWidget(canvas, 1);
    hbox->addLayout(vbox);

    hbox->setMargin(1);

    setLayout(hbox);
}

Widget::~Widget()
{
    delete ui;
}
