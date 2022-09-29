#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "colorconverterclass.h"
#include "mainwindow.h"

class Widget : public QWidget
{
    Q_OBJECT
    friend class ColorConverterClass;
    friend class MainWindow;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void showStatus();
    void clearStatus();

private:

    ColorConverterClass* converter;

    QLabel *lbl_11, *lbl_12, *lbl_13, *lbl_14;
    QLabel *lbl_21, *lbl_22, *lbl_23, *lbl_24;
    QLabel *lbl_31, *lbl_32, *lbl_33, *lbl_34;

    QComboBox  *col1;
    QComboBox  *col2;
    QComboBox  *col3;

    QPushButton *pal;
    QGridLayout *grid;

    QGridLayout *grid1;
    QGridLayout *grid2;
    QGridLayout *grid3;

    QGroupBox *box1;
    QGroupBox *box2;
    QGroupBox *box3;

    QVBoxLayout *mainLayout;

    QDoubleSpinBox *colName1_1;
    QDoubleSpinBox *colName1_2;
    QDoubleSpinBox *colName1_3;
    QDoubleSpinBox *colName1_4;

    QDoubleSpinBox *colName2_1;
    QDoubleSpinBox *colName2_2;
    QDoubleSpinBox *colName2_3;
    QDoubleSpinBox *colName2_4;

    QDoubleSpinBox *colName3_1;
    QDoubleSpinBox *colName3_2;
    QDoubleSpinBox *colName3_3;
    QDoubleSpinBox *colName3_4;

    QTableWidget *colShow;
    QTableWidgetItem *colCell;

    QBrush brush;

    int oldMod1, oldMod2, oldMod3;

    QFont *font;


    void blockSpinBoxesSignals(bool bl);

    void lblSettings(QLabel *&lbl1, QLabel *&lbl2, QLabel *&lbl3, QLabel *&lbl4);
    void gridFill(QGridLayout *gr, QLabel *lbl1, QLabel *lbl2, QLabel *lbl3, QLabel *lbl4,
                  QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3, QDoubleSpinBox* spBx4);
    void spinBoxSettings(QDoubleSpinBox *&spBx);
    void comboBoxSettings(QComboBox *&bx);

    int repeatModelsCheck(QComboBox *inspected, QComboBox *bx1, QComboBox *bx2);
    void copyRepeatModel(QDoubleSpinBox* insBox1, QDoubleSpinBox* insBox2, QDoubleSpinBox* insBox3, QDoubleSpinBox* insBox4,
                         QDoubleSpinBox* copyBx1, QDoubleSpinBox* copyBx2, QDoubleSpinBox* copyBx3, QDoubleSpinBox* copyBx4);

    void setCurrentLabels(int mode, QLabel *lbl1, QLabel *lbl2, QLabel *lbl3);

    void convertModChanges(int &oldMod, int newMode, QDoubleSpinBox* sender1, QDoubleSpinBox* sender2, QDoubleSpinBox* sender3,
                           QDoubleSpinBox* sender4, QDoubleSpinBox* receiver1, QDoubleSpinBox* receiver2,
                           QDoubleSpinBox* receiver3, QDoubleSpinBox* receiver4);
    void convertFromMod1SpinBoxes();
    void convertFromMod2SpinBoxes();
    void convertFromMod3SpinBoxes();

    void convertToColor(int mode, QDoubleSpinBox* spBox1, QDoubleSpinBox* spBox2, QDoubleSpinBox* spBox3,
                        QDoubleSpinBox* spBox4);

    void convertFromBrushToModel(int mod, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3, QDoubleSpinBox* spBx4);

    void repaint();

private slots:
    void setCurrentBrushCol();

    void MOD1_Changed();
    void MOD2_Changed();
    void MOD3_Changed();

    void spBx1_1Changed();
    void spBx1_2Changed();
    void spBx1_3Changed();
    void spBx1_4Changed();

    void spBx2_1Changed();
    void spBx2_2Changed();
    void spBx2_3Changed();
    void spBx2_4Changed();

    void spBx3_1Changed();
    void spBx3_2Changed();
    void spBx3_3Changed();
    void spBx3_4Changed();
};
#endif // WIDGET_H
