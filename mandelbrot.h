#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <QWidget>
#include <QPainter>
#include <QWheelEvent>
#include <QImage>
#include <QRgb>

#include <complex>
#include <iostream>
using namespace std;

class Mandelbrot : public QWidget
{
    Q_OBJECT

public:
    explicit Mandelbrot(QWidget *parent = 0);
    ~Mandelbrot();
    void paintEvent(QPaintEvent*);
    complex<double> zFunction(int, complex<double>);
    double calculateColorScaleFactor(complex<double>, int);
    complex<double> zFunctionStep(complex<double>, complex<double>);

private:
    int threshold;
    complex<double> za;
    complex<double> ze;
    double factorWidth;
    double factorHeight;
    QImage *image;
    void wheelEvent(QWheelEvent *e);

signals:

public slots:
    void changeThreshold(int);
};

#endif // MANDELBROT_H
