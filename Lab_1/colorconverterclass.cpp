#include "colorconverterclass.h"

ColorConverterClass::ColorConverterClass(){}

bool ColorConverterClass::rgbRangeCheck(double r, double g, double b)
{
    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
        return false;
    return true;
}

bool ColorConverterClass::cmykRangeCheck(double c, double m, double y, double k)
{
    if (c < 0 || m < 0 || y < 0 || k < 0 ||  c > 100 || m > 100 || y > 100 || k > 100)
        return false;
    return true;
}

bool ColorConverterClass::hsv_hslRangeCheck(double h, double s, double vl)
{
    if (h < 0 || s < 0 || vl < 0 || h > 360 || s > 100 || vl > 100)
        return false;
    return true;
}

bool ColorConverterClass::xyzRangeCheck(double x, double y, double z)
{
    if (x < 0 || y < 0 || z < 0 || x > 95.047 || y > 100 || z > 108.883)
        return false;
    return true;
}

bool ColorConverterClass::labRangeCheck(double l, double a, double b)
{
    if (l < 0 || a < -128 || b < -128 || l > 100 || a > 128 || b > 128)
        return false;
    return true;
}




bool ColorConverterClass::ConvertFromRGBToCMYK(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                                               QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3, QDoubleSpinBox* new4)
{
    double r = old1->value();
    double g = old2->value();
    double b = old3->value();

    double k = qMin(qMin(1 - r/255.0, 1 - g/255.0), 1 - b/255.0);
    double c, m, y;
    if (k != 1)
    {
        c = (1 - r/255.0 - k)/(1 - k);
        m = (1 - g/255.0 - k)/(1 - k);
        y = (1 - b/255.0 - k)/(1 - k);
    }
    else
    {
        c = 0;
        m = 0;
        y = 0;
    }


    k *= 100;
    c *= 100;
    m *= 100;
    y *= 100;

    new1->setRange(0, 100);
    new2->setRange(0, 100);
    new3->setRange(0, 100);
    new4->setRange(0, 100);

    new1->setValue(c);
    new2->setValue(m);
    new3->setValue(y);
    new4->setValue(k);

    return cmykRangeCheck(c, m, y, k);
}

bool ColorConverterClass::ConvertFromRGBToHSV(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3)
{
    QColor col;
    double r = old1->value();
    double g = old2->value();
    double b = old3->value();
    col.setRgbF(r/255, g/255, b/255);

    new1->setRange(0, 360);
    new2->setRange(0, 100);
    new3->setRange(0, 100);

    float h, s, v;
    col.getHsvF(&h, &s, &v);
    h *= 360;
    s *= 100;
    v *= 100;

    new1->setValue(h);
    new2->setValue(s);
    new3->setValue(v);

    return hsv_hslRangeCheck(h, s, v);
}

bool ColorConverterClass::ConvertFromRGBToHSL(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3)
{
    QColor col;
    double r = old1->value();
    double g = old2->value();
    double b = old3->value();
    col.setRgbF(r/255, g/255, b/255);

    new1->setRange(0, 360);
    new2->setRange(0, 100);
    new3->setRange(0, 100);

    float h, s, l;
    col.getHslF(&h, &s, &l);
    h *= 360;
    s *= 100;
    l *= 100;

    new1->setValue(h);
    new2->setValue(s);
    new3->setValue(l);

    return hsv_hslRangeCheck(h, s, l);
}

double ColorConverterClass::FunctionRGBToXYZ(double x)
{
    if (x >= 0.04045)
    {
        x += 0.055;
        x /= 1.055;
        x = pow(x, 2.4);
    }
    else
        x/=12.92;
    return x;
}

bool ColorConverterClass::ConvertFromRGBToXYZ(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3)
{
    double r = old1->value();
    double g = old2->value();
    double b = old3->value();

    double rn = FunctionRGBToXYZ(r/255)*100;
    double gn = FunctionRGBToXYZ(g/255)*100;
    double bn = FunctionRGBToXYZ(b/255)*100;

    double x,y,z;
    x = rn * 0.412453 + gn * 0.357580 + bn * 0.180423;
    y = rn * 0.212671 + gn * 0.715160 + bn * 0.072169;
    z = rn * 0.019334 + gn * 0.119193 + bn * 0.950227;

    new1->setRange(0, 95.047);
    new2->setRange(0, 100);
    new3->setRange(0, 108.883);

    new1->setValue(x);
    new2->setValue(y);
    new3->setValue(z);

    return xyzRangeCheck(x, y, z);
}

bool ColorConverterClass::ConvertFromRGBToLAB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3)
{
    bool bl = ConvertFromRGBToXYZ(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromXYZToLAB(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromXYZToLAB(new1, new2, new3, new1, new2, new3);
    return bl;
}






bool ColorConverterClass::ConvertFromCMYKToRGB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *old4,
                                               QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    double c = old1->value();
    double m = old2->value();
    double y = old3->value();
    double k = old4->value();

    double r = 255 * (1 - c/100) * (1 - k/100);
    double g = 255 * (1 - m/100) * (1 - k/100);
    double b = 255 * (1 - y/100) * (1 - k/100);

    new1->setRange(0, 255);
    new2->setRange(0, 255);
    new3->setRange(0, 255);

    new1->setValue(r);
    new2->setValue(g);
    new3->setValue(b);

    return rgbRangeCheck(r, g, b);
}

bool ColorConverterClass::ConvertFromCMYKToHSV(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *old4,
                                               QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    QColor col;
    double c = old1->value();
    double m = old2->value();
    double y = old3->value();
    double k = old4->value();
    col.setCmykF(c/100, m/100, y/100, k/100);

    new1->setRange(0, 360);
    new2->setRange(0, 100);
    new3->setRange(0, 100);

    float h, s, v;
    col.getHsvF(&h, &s, &v);
    h *= 360;
    s *= 100;
    v *= 100;

    new1->setValue(h);
    new2->setValue(s);
    new3->setValue(v);

    return hsv_hslRangeCheck(h, s, v);
}

bool ColorConverterClass::ConvertFromCMYKToHSL(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *old4,
                                               QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    QColor col;
    double c = old1->value();
    double m = old2->value();
    double y = old3->value();
    double k = old4->value();
    col.setCmykF(c/100, m/100, y/100, k/100);

    new1->setRange(0, 360);
    new2->setRange(0, 100);
    new3->setRange(0, 100);

    float h, s, l;
    col.getHslF(&h, &s, &l);
    h *= 360;
    s *= 100;
    l *= 100;

    new1->setValue(h);
    new2->setValue(s);
    new3->setValue(l);

    return hsv_hslRangeCheck(h, s, l);
}

bool ColorConverterClass::ConvertFromCMYKToXYZ(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *old4,
                                               QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromCMYKToRGB(old1, old2, old3, old4, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToXYZ(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToXYZ(new1, new2, new3,  new1, new2, new3);
    return bl;
}

bool ColorConverterClass::ConvertFromCMYKToLAB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *old4,
                                               QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromCMYKToRGB(old1, old2, old3, old4, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToLAB(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToLAB(new1, new2, new3,  new1, new2, new3);
    return bl;
}






bool ColorConverterClass::ConvertFromHSVToRGB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    QColor col;
    double h = old1->value();
    double s = old2->value();
    double v = old3->value();
    col.setHsvF(h/360, s/100, v/100);

    new1->setRange(0, 255);
    new2->setRange(0, 255);
    new3->setRange(0, 255);

    float r, g, b;
    col.getRgbF(&r, &g, &b);
    r *= 255;
    g *= 255;
    b *= 255;

    new1->setValue(r);
    new2->setValue(g);
    new3->setValue(b);

    return rgbRangeCheck(r, g, b);
}

bool ColorConverterClass::ConvertFromHSVToCMYK(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                               QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3, QDoubleSpinBox *new4)
{
    QColor col;
    double h = old1->value();
    double s = old2->value();
    double v = old3->value();
    col.setHsvF(h/360, s/100, v/100);

    new1->setRange(0, 100);
    new2->setRange(0, 100);
    new3->setRange(0, 100);
    new4->setRange(0, 100);

    float c, m, y, k;
    col.getCmykF(&c, &m, &y, &k);
    c *= 100;
    m *= 100;
    y *= 100;
    k *= 100;

    new1->setValue(c);
    new2->setValue(m);
    new3->setValue(y);
    new4->setValue(k);

    return cmykRangeCheck(c, m, y, k);
}

bool ColorConverterClass::ConvertFromHSVToHSL(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    QColor col;
    double h = old1->value();
    double s = old2->value();
    double v = old3->value();
    col.setHsvF(h/360, s/100, v/100);

    new1->setRange(0, 360);
    new2->setRange(0, 100);
    new3->setRange(0, 100);

    float hn, sn, ln;
    col.getHslF(&hn, &sn, &ln);
    hn *= 360;
    sn *= 100;
    ln *= 100;

    new1->setValue(hn);
    new2->setValue(sn);
    new3->setValue(ln);

    return hsv_hslRangeCheck(hn, sn, ln);
}

bool ColorConverterClass::ConvertFromHSVToXYZ(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromHSVToRGB(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToXYZ(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToXYZ(new1, new2, new3,  new1, new2, new3);
    return bl;
}

bool ColorConverterClass::ConvertFromHSVToLAB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromHSVToRGB(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToLAB(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToLAB(new1, new2, new3,  new1, new2, new3);
    return bl;
}






bool ColorConverterClass::ConvertFromHSLToRGB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    QColor col;
    double h = old1->value();
    double s = old2->value();
    double l = old3->value();
    col.setHslF(h/360, s/100, l/100);

    new1->setRange(0, 255);
    new2->setRange(0, 255);
    new3->setRange(0, 255);

    float r, g, b;
    col.getRgbF(&r, &g, &b);
    r *= 255;
    g *= 255;
    b *= 255;

    new1->setValue(r);
    new2->setValue(g);
    new3->setValue(b);

    return rgbRangeCheck(r, g, b);
}

bool ColorConverterClass::ConvertFromHSLToCMYK(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                               QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3, QDoubleSpinBox *new4)
{
    QColor col;
    double h = old1->value();
    double s = old2->value();
    double l = old3->value();
    col.setHslF(h/360, s/100, l/100);

    new1->setRange(0, 100);
    new2->setRange(0, 100);
    new3->setRange(0, 100);
    new4->setRange(0, 100);

    float c, m, y, k;
    col.getCmykF(&c, &m, &y, &k);
    c *= 100;
    m *= 100;
    y *= 100;
    k *= 100;

    new1->setValue(c);
    new2->setValue(m);
    new3->setValue(y);
    new4->setValue(k);

    return cmykRangeCheck(c, m, y, k);
}

bool ColorConverterClass::ConvertFromHSLToHSV(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    QColor col;
    double h = old1->value();
    double s = old2->value();
    double l = old3->value();
    col.setHslF(h/360, s/100, l/100);

    new1->setRange(0, 360);
    new2->setRange(0, 100);
    new3->setRange(0, 100);

    float hn, sn, vn;
    col.getHsvF(&hn, &sn, &vn);
    hn *= 360;
    sn *= 100;
    vn *= 100;

    new1->setValue(hn);
    new2->setValue(sn);
    new3->setValue(vn);

    return hsv_hslRangeCheck(hn, sn, vn);
}

bool ColorConverterClass::ConvertFromHSLToXYZ(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromHSLToRGB(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToXYZ(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToXYZ(new1, new2, new3,  new1, new2, new3);
    return bl;
}

bool ColorConverterClass::ConvertFromHSLToLAB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3,
                                              QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromHSLToRGB(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToLAB(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToLAB(new1, new2, new3,  new1, new2, new3);
    return bl;
}






double ColorConverterClass::FunctionXYZToRGB(double x)
{
    if (x >= 0.0031308)
        x = 1.055 * pow(x, 1/2.4) - 0.055;
    else
        x *= 12.92;
    return x;
}

bool ColorConverterClass::ConvertFromXYZToRGB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    double x = old1->value()/100;
    double y = old2->value()/100;
    double z = old3->value()/100;

    double r = 3.2406*x - 1.5372*y - 0.4986*z;
    double g = (-0.9689)*x + 1.8758 *y + 0.0415*z;
    double b = 0.0557 *x - 0.2040*y + 1.0570*z;

    r = FunctionXYZToRGB(r) * 255;
    g = FunctionXYZToRGB(g) * 255;
    b = FunctionXYZToRGB(b) * 255;

    new1->setRange(0, 255);
    new2->setRange(0, 255);
    new3->setRange(0, 255);

    new1->setValue(r);
    new2->setValue(g);
    new3->setValue(b);

    return rgbRangeCheck(r, g, b);
}

bool ColorConverterClass::ConvertFromXYZToCMYK(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3, QDoubleSpinBox *new4)
{
    bool bl = ConvertFromXYZToRGB(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToCMYK(new1, new2, new3,  new1, new2, new3, new4);
    else
        ConvertFromRGBToCMYK(new1, new2, new3,  new1, new2, new3, new4);
    return bl;
}

bool ColorConverterClass::ConvertFromXYZToHSV(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromXYZToRGB(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToHSV(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToHSV(new1, new2, new3,  new1, new2, new3);
    return bl;
}

bool ColorConverterClass::ConvertFromXYZToHSL(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromXYZToRGB(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromRGBToHSL(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromRGBToHSL(new1, new2, new3,  new1, new2, new3);
    return bl;
}

double ColorConverterClass::FunctionXYZToLAB(double x)
{
    if (x >= 0.008856)
        x = pow(x, 1.0/3.0);
    else
        x = 7.787*x + 16.0/116.0;
    return x;
}

bool ColorConverterClass::ConvertFromXYZToLAB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    double x = old1->value();
    double y = old2->value();
    double z = old3->value();

    double xWhite = 95.047;
    double yWhite = 100;
    double zWhite = 108.883;

    double l = 116 * FunctionXYZToLAB(y/yWhite) - 16;
    double a = 500 * (FunctionXYZToLAB(x/xWhite) - FunctionXYZToLAB(y/yWhite));
    double b = 200 * (FunctionXYZToLAB(y/yWhite) - FunctionXYZToLAB(z/zWhite));

    new1->setRange(0, 100);
    new2->setRange(-128, 128);
    new3->setRange(-128, 128);

    new1->setValue(l);
    new2->setValue(a);
    new3->setValue(b);

    return labRangeCheck(l, a, b);
}






bool ColorConverterClass::ConvertFromLABToRGB(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromLABToXYZ(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromXYZToRGB(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromXYZToRGB(new1, new2, new3,  new1, new2, new3);
    return bl;
}

bool ColorConverterClass::ConvertFromLABToCMYK(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3, QDoubleSpinBox *new4)
{
    bool bl = ConvertFromLABToXYZ(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromXYZToCMYK(new1, new2, new3,  new1, new2, new3, new4);
    else
        ConvertFromXYZToCMYK(new1, new2, new3,  new1, new2, new3, new4);
    return bl;
}

bool ColorConverterClass::ConvertFromLABToHSV(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromLABToXYZ(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromXYZToHSV(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromXYZToHSV(new1, new2, new3,  new1, new2, new3);
    return bl;
}

bool ColorConverterClass::ConvertFromLABToHSL(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    bool bl = ConvertFromLABToXYZ(old1, old2, old3, new1, new2, new3);
    if (bl)
        bl = ConvertFromXYZToHSL(new1, new2, new3,  new1, new2, new3);
    else
        ConvertFromXYZToHSL(new1, new2, new3,  new1, new2, new3);
    return bl;
}

double ColorConverterClass::FunctionLABToXYZ(double x)
{
    if (pow(x, 3.0) >= 0.008856)
        x = pow(x, 3.0);
    else
        x = (x - 16.0/116.0) / 7.787;
    return x;
}

bool ColorConverterClass::ConvertFromLABToXYZ(QDoubleSpinBox *old1, QDoubleSpinBox *old2, QDoubleSpinBox *old3, QDoubleSpinBox *new1, QDoubleSpinBox *new2, QDoubleSpinBox *new3)
{
    double l = old1->value();
    double a = old2->value();
    double b = old3->value();

    double xWhite = 95.047;
    double yWhite = 100;
    double zWhite = 108.883;

    double x = FunctionLABToXYZ(a/500.0 + (l + 16)/116.0) * xWhite;
    double y = FunctionLABToXYZ((l + 16)/116.0) * yWhite;
    double z = FunctionLABToXYZ((l + 16)/116.0 - b/200.0) * zWhite;

    new1->setRange(0, 95.047);
    new2->setRange(0, 100);
    new3->setRange(0, 108.883);

    new1->setValue(x);
    new2->setValue(y);
    new3->setValue(z);

    return xyzRangeCheck(x, y, z);
}






bool ColorConverterClass::ConvertFromRGBToColor(double r, double g, double b, QBrush &brush)
{
    QColor col;
    col.setRgbF(r/255, g/255, b/255);
    brush.setColor(col);
    return true;
}

bool ColorConverterClass::ConvertFromCMYKToColor(double c, double m, double y, double k, QBrush &brush)
{
    QColor col;
    col.setCmykF(c/100, m/100, y/100, k/100);
    brush.setColor(col);
    return true;
}

bool ColorConverterClass::ConvertFromHSVToColor(double h, double s, double v, QBrush &brush)
{
    QColor col;
    col.setHsvF(h/360, s/100, v/100);
    brush.setColor(col);
    return true;
}

bool ColorConverterClass::ConvertFromHSLToColor(double h, double s, double l, QBrush &brush)
{
    QColor col;
    col.setHslF(h/360, s/100, l/100);
    brush.setColor(col);
    return true;
}

bool ColorConverterClass::ConvertFromXYZToColor(double x, double y, double z, QBrush &brush)
{
    double r = 3.2406*x - 1.5372*y - 0.4986*z;
    double g = (-0.9689)*x + 1.8758 *y + 0.0415*z;
    double b = 0.0557 *x - 0.2040*y + 1.0570*z;

    r = FunctionXYZToRGB(r) * 255;
    g = FunctionXYZToRGB(g) * 255;
    b = FunctionXYZToRGB(b) * 255;

    ConvertFromRGBToColor(r, g, b, brush);

    return rgbRangeCheck(r, g, b);
}

bool ColorConverterClass::ConvertFromLABToColor(double l, double a, double b, QBrush &brush)
{
    double xWhite = 95.047;
    double yWhite = 100;
    double zWhite = 108.883;

    double x = FunctionLABToXYZ(a/500.0 + (l + 16)/116.0) * xWhite;
    double y = FunctionLABToXYZ((l + 16)/116.0) * yWhite;
    double z = FunctionLABToXYZ((l + 16)/116.0 - b/200.0) * zWhite;

    ConvertFromXYZToColor(x, y, z, brush);

    return xyzRangeCheck(x, y, z);
}






bool ColorConverterClass::ConvertFromColorToRGB(QBrush &brush, QDoubleSpinBox *spBx1, QDoubleSpinBox *spBx2,
                                                QDoubleSpinBox *spBx3)
{
    float r, g, b;
    brush.color().getRgbF(&r, &g, &b);

    spBx1->setValue(r*255);
    spBx2->setValue(g*255);
    spBx3->setValue(b*255);

    return rgbRangeCheck(r*255, g*255, b*255);
}

bool ColorConverterClass::ConvertFromColorToCMYK(QBrush &brush, QDoubleSpinBox *spBx1, QDoubleSpinBox *spBx2,
                                                 QDoubleSpinBox *spBx3, QDoubleSpinBox *spBx4)
{
    float c, m, y, k;
    brush.color().getCmykF(&c, &m, &y, &k);

    spBx1->setValue(c*100);
    spBx2->setValue(m*100);
    spBx3->setValue(y*100);
    spBx4->setValue(k*100);

    return cmykRangeCheck(c*100, m*100, y*100, k*100);
}

bool ColorConverterClass::ConvertFromColorToHSV(QBrush &brush, QDoubleSpinBox *spBx1, QDoubleSpinBox *spBx2,
                                                QDoubleSpinBox *spBx3)
{
    float h, s, v;
    brush.color().getHsvF(&h, &s, &v);

    spBx1->setValue(h*360);
    spBx2->setValue(s*100);
    spBx3->setValue(v*100);

    return hsv_hslRangeCheck(h*360, s*100, v*100);
}

bool ColorConverterClass::ConvertFromColorToHSL(QBrush &brush, QDoubleSpinBox *spBx1, QDoubleSpinBox *spBx2,
                                                QDoubleSpinBox *spBx3)
{
    float h, s, l;
    brush.color().getHslF(&h, &s, &l);

    spBx1->setValue(h*360);
    spBx2->setValue(s*100);
    spBx3->setValue(l*100);

    return hsv_hslRangeCheck(h*360, s*100, l*100);
}

bool ColorConverterClass::ConvertFromColorToXYZ(QBrush &brush, QDoubleSpinBox *spBx1, QDoubleSpinBox *spBx2,
                                                QDoubleSpinBox *spBx3)
{
    spBx1->setRange(0, 255);
    spBx2->setRange(0, 255);
    spBx3->setRange(0, 255);

    ConvertFromColorToRGB(brush, spBx1, spBx2, spBx3);
    return ConvertFromRGBToXYZ(spBx1, spBx2, spBx3, spBx1, spBx2, spBx3);
}

bool ColorConverterClass::ConvertFromColorToLAB(QBrush &brush, QDoubleSpinBox *spBx1, QDoubleSpinBox *spBx2,
                                                QDoubleSpinBox *spBx3)
{
    spBx1->setRange(0, 255);
    spBx2->setRange(0, 255);
    spBx3->setRange(0, 255);

    ConvertFromColorToRGB(brush, spBx1, spBx2, spBx3);
    return ConvertFromRGBToLAB(spBx1, spBx2, spBx3, spBx1, spBx2, spBx3);
}
