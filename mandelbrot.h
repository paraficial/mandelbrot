#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <QWidget>
#include <QPainter>

#include <complex>
#include <iostream>
using namespace std;

class Mandelbrot : public QWidget
{
    Q_OBJECT
public:
    explicit Mandelbrot(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    complex<double> zFunction(int, complex<double>);
    double calculateColorScaleFactor(complex<double>, int);
    complex<double> zFunctionStep(complex<double>, complex<double>);

signals:

public slots:
};

#endif // MANDELBROT_H
