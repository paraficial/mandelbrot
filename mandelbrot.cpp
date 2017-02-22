#include "mandelbrot.h"

Mandelbrot::Mandelbrot(QWidget *parent) : QWidget(parent)
{
    int w = 800, h = 800;
    setMinimumSize(QSize(w, h));
    za = complex<double>(-2.1, -1.5);
    ze = complex<double>(0.8, 1.5);
    factorWidth = 1.0;
    factorHeight = 1.0;
    threshold = 0;

    image = new QImage(w, h, QImage::Format_RGB32);
}

Mandelbrot::~Mandelbrot() {
}


void Mandelbrot::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    int w = this->width();
    int h = this->height();
    image = new QImage(w, h, QImage::Format_RGB32);

    double diffReal = ze.real() - za.real();
    double diffImag = ze.imag() - za.imag();

    double ratioZs = diffReal/diffImag; // 2
    double ratioIg = w/h;

    double offsetW, offsetH = 0;

    if (ratioIg < ratioZs) {
        factorWidth = factorHeight = diffReal/w;
        offsetH = ((za.imag() + h * factorHeight) - ze.imag())/2;
    }
    else {
        factorWidth = factorHeight = diffImag/h;
        offsetW = ((za.real() + w * factorWidth) - ze.real())/2;
    }

    complex<double> **canvas = new complex<double>*[h];

    double colorScaleFactor;
    for (int i = 0; i < h; i++) {
        canvas[i] = new complex<double>[w];
        for (int j = 0; j < w; j++) {
            canvas[i][j] = complex<double>(za.real()+(double) j * factorWidth - offsetW, za.imag()+(double) i * factorHeight - offsetH);
            colorScaleFactor = calculateColorScaleFactor(canvas[i][j], threshold);

            if (colorScaleFactor == 0) {
                image->setPixel(j, h-i-1, qRgb(0, 0, 0));
            }
            else {
                image->setPixel(j, h-i-1, qRgb(255 * colorScaleFactor, 0, 255 - 155 * colorScaleFactor));
            }
        }
    }

    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    delete canvas;
}

double Mandelbrot::calculateColorScaleFactor(complex<double> c, int n) {
    double scaleFactor;
    int k = 0;
    complex<double> tmp(0, 0);
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

void Mandelbrot::wheelEvent(QWheelEvent *e) {
    double diffReal = ze.real() - za.real();
    double diffImag = ze.imag() - za.imag();
    double middleReal = za.real() + (diffReal/2);
    double middleImag = za.imag() + (diffImag/2);

    int val = e->delta();
    QPoint position = e->pos();
    int x = position.rx();
    int y = position.ry();
    double xReal = za.real() + x * factorWidth;
    double yImag = za.imag() + y * factorHeight;

    complex<double> shift(0.4 * abs(xReal - middleReal),
                          0.4 * -abs(yImag - middleImag));

    complex<double> add(0.1*diffReal, 0.1*diffImag);
    if (val > 0) {
        if (xReal < middleReal) {
            za.real() -= shift.real();
            ze.real() -= shift.real();
        }
        else {
            za.real() += shift.real();
            ze.real() += shift.real();
        }
        if (yImag < middleImag) {
            za.imag() -= shift.imag();
            ze.imag() -= shift.imag();
        }
        else {
            za.imag() += shift.imag();
            ze.imag() += shift.imag();
        }
        za.operator +=(add);
        ze.operator -=(add);
    }
    else {
        if (xReal < middleReal) {
            za.real() -= shift.real();
            ze.real() -= shift.real();
        }
        else {
            za.real() += shift.real();
            ze.real() += shift.real();
        }
        if (yImag < middleImag) {
            za.imag() -= shift.imag();
            ze.imag() -= shift.imag();
        }
        else {
            za.imag() += shift.imag();
            ze.imag() += shift.imag();
        }
        za.operator -=(add);
        ze.operator +=(add);
    }
    update();
}

void Mandelbrot::changeThreshold(int n) {
    threshold = n;
    update();
}
