#ifndef COLORCONVERTERCLASS_H
#define COLORCONVERTERCLASS_H

#include <QtWidgets>
#include <QtMath>
#include "widget.h"

class ColorConverterClass: public QWidget
{
    Q_OBJECT
    friend class Widget;
private:
    ColorConverterClass();

    bool rgbRangeCheck(double r, double g, double b);
    bool cmykRangeCheck(double c, double m, double y, double k);
    bool hsv_hslRangeCheck(double h, double s, double vl);
    bool xyzRangeCheck(double x, double y, double z);
    bool labRangeCheck(double l, double a, double b);


    bool ConvertFromRGBToCMYK(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3, QDoubleSpinBox* new4);
    bool ConvertFromRGBToHSV(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromRGBToHSL(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    double FunctionRGBToXYZ(double x);
    bool ConvertFromRGBToXYZ(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromRGBToLAB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);


    bool ConvertFromCMYKToRGB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3, QDoubleSpinBox* old4,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromCMYKToHSV(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3, QDoubleSpinBox* old4,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromCMYKToHSL(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3, QDoubleSpinBox* old4,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromCMYKToXYZ(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3, QDoubleSpinBox* old4,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromCMYKToLAB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3, QDoubleSpinBox* old4,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);


    bool ConvertFromHSVToRGB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromHSVToCMYK(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3, QDoubleSpinBox* new4);
    bool ConvertFromHSVToHSL(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromHSVToXYZ(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromHSVToLAB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);


    bool ConvertFromHSLToRGB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromHSLToCMYK(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3, QDoubleSpinBox* new4);
    bool ConvertFromHSLToHSV(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromHSLToXYZ(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromHSLToLAB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);


    double FunctionXYZToRGB(double x);
    bool ConvertFromXYZToRGB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromXYZToCMYK(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3, QDoubleSpinBox* new4);
    bool ConvertFromXYZToHSV(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromXYZToHSL(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    double FunctionXYZToLAB(double x);
    bool ConvertFromXYZToLAB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);


    bool ConvertFromLABToRGB(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromLABToCMYK(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                              QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3, QDoubleSpinBox* new4);
    bool ConvertFromLABToHSV(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    bool ConvertFromLABToHSL(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);
    double FunctionLABToXYZ(double x);
    bool ConvertFromLABToXYZ(QDoubleSpinBox* old1, QDoubleSpinBox* old2, QDoubleSpinBox* old3,
                             QDoubleSpinBox* new1, QDoubleSpinBox* new2, QDoubleSpinBox* new3);


    bool ConvertFromRGBToColor(double r, double g, double b, QBrush &brush);
    bool ConvertFromCMYKToColor(double c, double m, double y, double k, QBrush &brush);
    bool ConvertFromHSVToColor(double h, double s, double v, QBrush &brush);
    bool ConvertFromHSLToColor(double h, double s, double l, QBrush &brush);
    bool ConvertFromXYZToColor(double x, double y, double z, QBrush &brush);
    bool ConvertFromLABToColor(double l, double a, double b, QBrush &brush);


    bool ConvertFromColorToRGB(QBrush &brush, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3);
    bool ConvertFromColorToCMYK(QBrush &brush, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3,
                                QDoubleSpinBox* spBx4);
    bool ConvertFromColorToHSV(QBrush &brush, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3);
    bool ConvertFromColorToHSL(QBrush &brush, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3);
    bool ConvertFromColorToXYZ(QBrush &brush, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3);
    bool ConvertFromColorToLAB(QBrush &brush, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3);
};

#endif // COLORCONVERTERCLASS_H
