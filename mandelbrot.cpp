#include "mandelbrot.h"
#include <QImage>
#include <QRgb>

Mandelbrot::Mandelbrot(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(QSize(400, 400));

}


void Mandelbrot::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    int w = this->width();
    int h = this->height();

    int threshold = 16;
    complex<double> za(-2.1, -1.5);
    complex<double> ze(0.8, 1.5);

    double diffReal = ze.real() - za.real();
    double diffImag = ze.imag() - za.imag();

    double ratioZs = diffReal/diffImag; // 2
    double ratioIg = w/h;

    double factorWidth, factorHeight;
    double offsetW, offsetH = 0;
    if (ratioIg < ratioZs) {
        factorWidth = factorHeight = diffReal/w;
        offsetH = (h - w)/h;
    }
    else {
        factorWidth = factorHeight = diffImag/h;
        offsetW = (w - h)/w;
    }

    //double factorWidth = diffReal / w;
    //double factorHeight = diffImag / h;

    complex<double> **canvas = new complex<double>*[h];
    QImage image(w, h, QImage::Format_RGB32);

    double colorScaleFactor;
    for (int i = 0; i < h; i++) {
        canvas[i] = new complex<double>[w];
        for (int j = 0; j < w; j++) {
            canvas[i][j] = complex<double>(za.real()+(double) j*factorWidth + offsetW, za.imag()+(double) i*factorHeight + offsetH);
            colorScaleFactor = calculateColorScaleFactor(canvas[i][j], threshold);

            if (colorScaleFactor == 0) {
                image.setPixel(j, h-i-1, qRgb(0, 0, 0));
            }
            else {
                image.setPixel(j, h-i-1, qRgb(255 * colorScaleFactor, 0, 255 - 255 * colorScaleFactor));
            }
        }
    }

    QPainter painter(this);
    painter.drawImage(0, 0, image);
    delete canvas;
}

double Mandelbrot::calculateColorScaleFactor(complex<double> c, int n) {
    double scaleFactor;
    int k = 0;
    complex<double> tmp = (0, 0);
    for (int i = 1; i < n; i++) {
        tmp = zFunctionStep(tmp, c);
        if (norm(tmp) > 2) {
            k = i;
            break;
        }
    }
    scaleFactor = (double) k / (double) n;
    return scaleFactor;
}

complex<double> Mandelbrot::zFunctionStep(complex<double> zn, complex<double> c) {
    return c += (zn * zn);
}

complex<double> Mandelbrot::zFunction(int n, complex<double> c) {
    if (n <= 0) {
        return complex<double>(0.0, 0.0);
    }
    else {
        n--;
        return c += norm(zFunction(n, c));
    }
}
