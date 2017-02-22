#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QStatusBar>

#include "mandelbrot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    Mandelbrot *canvas;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;

    QLabel *label1, *label2, *label3;
    QComboBox *combo1, *combo2;
    QSpinBox *threshold;
    QStatusBar *status;

    QStringList *colors;

};

#endif // WIDGET_H
