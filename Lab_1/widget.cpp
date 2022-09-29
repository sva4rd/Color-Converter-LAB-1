#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent): QWidget(parent)
{
    converter = new ColorConverterClass();

    font = new QFont;
    font->setBold(true);

    oldMod1 = 1;
    oldMod2 = 1;
    oldMod3 = 1;

    spinBoxSettings(colName1_1);
    spinBoxSettings(colName1_2);
    spinBoxSettings(colName1_3);
    spinBoxSettings(colName1_4);

    spinBoxSettings(colName2_1);
    spinBoxSettings(colName2_2);
    spinBoxSettings(colName2_3);
    spinBoxSettings(colName2_4);

    spinBoxSettings(colName3_1);
    spinBoxSettings(colName3_2);
    spinBoxSettings(colName3_3);
    spinBoxSettings(colName3_4);

    colName1_4->hide();
    colName2_4->hide();
    colName3_4->hide();

    comboBoxSettings(col1);
    comboBoxSettings(col2);
    comboBoxSettings(col3);

    pal = new QPushButton(this);
    pal->setText("PICK COLOR");

    colCell = new QTableWidgetItem();

    colShow = new QTableWidget(1,1);

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    repaint();

    colShow->verticalHeader()->setVisible(false);
    colShow->horizontalHeader()->setVisible(false);
    colShow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    colShow->setSelectionMode(QAbstractItemView::NoSelection);
    colShow->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    QHeaderView* header = colShow->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    QHeaderView* header2 = colShow->verticalHeader();
    header2->setSectionResizeMode(QHeaderView::Stretch);


    connect(pal, &QPushButton::clicked, this, &Widget::setCurrentBrushCol);

    connect(col1, &QComboBox::currentTextChanged, this, &Widget::MOD1_Changed);
    connect(col2, &QComboBox::currentTextChanged, this, &Widget::MOD2_Changed);
    connect(col3, &QComboBox::currentTextChanged, this, &Widget::MOD3_Changed);

    connect(colName1_1, &QDoubleSpinBox::valueChanged, this, &Widget::spBx1_1Changed);
    connect(colName1_2, &QDoubleSpinBox::valueChanged, this, &Widget::spBx1_2Changed);
    connect(colName1_3, &QDoubleSpinBox::valueChanged, this, &Widget::spBx1_3Changed);
    connect(colName1_4, &QDoubleSpinBox::valueChanged, this, &Widget::spBx1_4Changed);

    connect(colName2_1, &QDoubleSpinBox::valueChanged, this, &Widget::spBx2_1Changed);
    connect(colName2_2, &QDoubleSpinBox::valueChanged, this, &Widget::spBx2_2Changed);
    connect(colName2_3, &QDoubleSpinBox::valueChanged, this, &Widget::spBx2_3Changed);
    connect(colName2_4, &QDoubleSpinBox::valueChanged, this, &Widget::spBx2_4Changed);

    connect(colName3_1, &QDoubleSpinBox::valueChanged, this, &Widget::spBx3_1Changed);
    connect(colName3_2, &QDoubleSpinBox::valueChanged, this, &Widget::spBx3_2Changed);
    connect(colName3_3, &QDoubleSpinBox::valueChanged, this, &Widget::spBx3_3Changed);
    connect(colName3_4, &QDoubleSpinBox::valueChanged, this, &Widget::spBx3_4Changed);



    lblSettings(lbl_11, lbl_12, lbl_13, lbl_14);
    lblSettings(lbl_21, lbl_22, lbl_23, lbl_24);
    lblSettings(lbl_31, lbl_32, lbl_33, lbl_34);

    lbl_14->hide();
    lbl_24->hide();
    lbl_34->hide();

    grid1 = new QGridLayout;
    grid2 = new QGridLayout;
    grid3 = new QGridLayout;

    mainLayout = new QVBoxLayout(this);

    gridFill(grid1, lbl_11, lbl_12, lbl_13, lbl_14, colName1_1, colName1_2, colName1_3, colName1_4);
    gridFill(grid2, lbl_21, lbl_22, lbl_23, lbl_24, colName2_1, colName2_2, colName2_3, colName2_4);
    gridFill(grid3, lbl_31, lbl_32, lbl_33, lbl_34, colName3_1, colName3_2, colName3_3, colName3_4);

    box1 = new QGroupBox;
    box2 = new QGroupBox;
    box3 = new QGroupBox;

    box1->setLayout(grid1);
    box2->setLayout(grid2);
    box3->setLayout(grid3);

    grid = new QGridLayout;

    grid->addWidget(pal, 0, 1);
    grid->addWidget(col1, 1, 0);
    grid->addWidget(col2, 1, 1);
    grid->addWidget(col3, 1, 2);
    grid->addWidget(box1, 2, 0);
    grid->addWidget(box2, 2, 1);
    grid->addWidget(box3, 2, 2);

    mainLayout->addWidget(colShow);
    mainLayout->addLayout(grid);
}

void Widget::setCurrentBrushCol()
{
    QColor col = QColorDialog::getColor(brush.color());
    if(col.isValid())
        brush.setColor(col);
    repaint();
    convertFromBrushToModel(col1->currentData().toInt(), colName1_1, colName1_2, colName1_3, colName1_4);
    convertFromBrushToModel(col2->currentData().toInt(), colName2_1, colName2_2, colName2_3, colName2_4);
    convertFromBrushToModel(col3->currentData().toInt(), colName3_1, colName3_2, colName3_3, colName3_4);
}

void Widget::repaint()
{
    colCell->setBackground(brush);
    colShow->setItem(0, 0, new QTableWidgetItem(*colCell));
}

void Widget::MOD1_Changed()
{
    emit clearStatus();

    blockSpinBoxesSignals(true);

    if (oldMod1 == col1->currentData().toInt())
        return;

    if (oldMod1 == 2)
    {
        colName1_4->hide();
        lbl_14->hide();
    }

    int repMod = repeatModelsCheck(col1, col2, col3);
    if (repMod == 1)
    {
        copyRepeatModel(colName1_1, colName1_2, colName1_3, colName1_4, colName2_1, colName2_2, colName2_3, colName2_4);
        oldMod1 = col1->currentData().toInt();
    }

    else if (repMod == 2)
    {
        copyRepeatModel(colName1_1, colName1_2, colName1_3, colName1_4, colName3_1, colName3_2, colName3_3, colName3_4);
        oldMod1 = col1->currentData().toInt();
    }

    else
        convertModChanges(oldMod1, col1->currentData().toInt(), colName1_1, colName1_2, colName1_3, colName1_4,
                          colName1_1, colName1_2, colName1_3, colName1_4);

    if (oldMod1 == 2)
    {
        colName1_4->show();
        lbl_14->show();
    }

    blockSpinBoxesSignals(false);

    setCurrentLabels(col1->currentData().toInt(), lbl_11, lbl_12, lbl_13);
}

void Widget::MOD2_Changed()
{
    emit clearStatus();

    blockSpinBoxesSignals(true);

    if (oldMod2 == col2->currentData().toInt())
        return;

    if (oldMod2 == 2)
    {
        colName2_4->hide();
        lbl_24->hide();
    }

    int repMod = repeatModelsCheck(col2, col1, col3);
    if (repMod == 1)
    {
        copyRepeatModel(colName2_1, colName2_2, colName2_3, colName2_4, colName1_1, colName1_2, colName1_3, colName1_4);
        oldMod2 = col2->currentData().toInt();
    }

    else if (repMod == 2)
    {
        copyRepeatModel(colName2_1, colName2_2, colName2_3, colName2_4, colName3_1, colName3_2, colName3_3, colName3_4);
        oldMod2 = col2->currentData().toInt();
    }

    else
        convertModChanges(oldMod2, col2->currentData().toInt(), colName2_1, colName2_2, colName2_3, colName2_4,
                          colName2_1, colName2_2, colName2_3, colName2_4);

    if (oldMod2 == 2)
    {
        colName2_4->show();
        lbl_24->show();
    }

    blockSpinBoxesSignals(false);

    setCurrentLabels(col2->currentData().toInt(), lbl_21, lbl_22, lbl_23);
}

void Widget::MOD3_Changed()
{
    emit clearStatus();

    blockSpinBoxesSignals(true);

    if (oldMod3 == col3->currentData().toInt())
        return;

    if (oldMod3 == 2)
    {
        colName3_4->hide();
        lbl_34->hide();
    }

    int repMod = repeatModelsCheck(col3, col1, col2);
    if (repMod == 1)
    {
        copyRepeatModel(colName3_1, colName3_2, colName3_3, colName3_4, colName1_1, colName1_2, colName1_3, colName1_4);
        oldMod3 = col3->currentData().toInt();
    }

    else if (repMod == 2)
    {
        copyRepeatModel(colName3_1, colName3_2, colName3_3, colName3_4, colName2_1, colName2_2, colName2_3, colName2_4);
        oldMod3 = col3->currentData().toInt();
    }

    else
        convertModChanges(oldMod3, col3->currentData().toInt(), colName3_1, colName3_2, colName3_3, colName3_4,
                          colName3_1, colName3_2, colName3_3, colName3_4);

    if (oldMod3 == 2)
    {
        colName3_4->show();
        lbl_34->show();
    }

    blockSpinBoxesSignals(false);

    setCurrentLabels(col3->currentData().toInt(), lbl_31, lbl_32, lbl_33);
}



void Widget::spBx1_1Changed()
{
    convertFromMod1SpinBoxes();
}

void Widget::spBx1_2Changed()
{
    convertFromMod1SpinBoxes();
}

void Widget::spBx1_3Changed()
{
    convertFromMod1SpinBoxes();
}

void Widget::spBx1_4Changed()
{
    convertFromMod1SpinBoxes();
}



void Widget::spBx2_1Changed()
{
    convertFromMod2SpinBoxes();
}

void Widget::spBx2_2Changed()
{
    convertFromMod2SpinBoxes();
}

void Widget::spBx2_3Changed()
{
    convertFromMod2SpinBoxes();
}

void Widget::spBx2_4Changed()
{
    convertFromMod2SpinBoxes();
}



void Widget::spBx3_1Changed()
{
    convertFromMod3SpinBoxes();
}

void Widget::spBx3_2Changed()
{
    convertFromMod3SpinBoxes();
}

void Widget::spBx3_3Changed()
{
    convertFromMod3SpinBoxes();
}

void Widget::spBx3_4Changed()
{
    convertFromMod3SpinBoxes();
}



Widget::~Widget()
{
    delete converter;
}

void Widget::blockSpinBoxesSignals(bool bl)
{
    colName1_1->blockSignals(bl);
    colName1_2->blockSignals(bl);
    colName1_3->blockSignals(bl);
    colName1_4->blockSignals(bl);

    colName2_1->blockSignals(bl);
    colName2_2->blockSignals(bl);
    colName2_3->blockSignals(bl);
    colName2_4->blockSignals(bl);

    colName3_1->blockSignals(bl);
    colName3_2->blockSignals(bl);
    colName3_3->blockSignals(bl);
    colName3_4->blockSignals(bl);
}

void Widget::lblSettings(QLabel *&lbl1, QLabel *&lbl2, QLabel *&lbl3, QLabel *&lbl4)
{
    lbl1 = new QLabel("R:", this);
    lbl2 = new QLabel("G:", this);
    lbl3 = new QLabel("B:", this);
    lbl4 = new QLabel("K:", this);

    lbl1->setAlignment(Qt::AlignCenter);
    lbl2->setAlignment(Qt::AlignCenter);
    lbl3->setAlignment(Qt::AlignCenter);
    lbl4->setAlignment(Qt::AlignCenter);
}

void Widget::gridFill(QGridLayout *gr, QLabel *lbl1, QLabel *lbl2, QLabel *lbl3, QLabel *lbl4, QDoubleSpinBox *spBx1, QDoubleSpinBox *spBx2, QDoubleSpinBox *spBx3, QDoubleSpinBox *spBx4)
{
    gr->addWidget(lbl1, 1, 0);
    gr->addWidget(lbl2, 2, 0);
    gr->addWidget(lbl3, 3, 0);
    gr->addWidget(lbl4, 4, 0);
    gr->addWidget(spBx1, 1, 1, 1, 9);
    gr->addWidget(spBx2, 2, 1, 1, 9);
    gr->addWidget(spBx3, 3, 1, 1, 9);
    gr->addWidget(spBx4, 4, 1, 1, 9);
}

void Widget::spinBoxSettings(QDoubleSpinBox *&spBx)
{
    spBx = new QDoubleSpinBox(this);
    spBx->setDecimals(3);
    spBx->setRange(0, 255);
}

void Widget::comboBoxSettings(QComboBox *&bx)
{
    bx = new QComboBox(this);
    bx->addItem("RGB", QVariant(1));
    bx->addItem("CMYK", QVariant(2));
    bx->addItem("HSV", QVariant(3));
    bx->addItem("HSL", QVariant(4));
    bx->addItem("XYZ", QVariant(5));
    bx->addItem("LAB", QVariant(6));
}

int Widget::repeatModelsCheck(QComboBox *inspected, QComboBox *bx1, QComboBox *bx2)
{
    if (inspected->currentData().toInt() == bx1->currentData().toInt())
        return 1;
    else if (inspected->currentData().toInt() == bx2->currentData().toInt())
        return 2;
    else
        return 0;
}

void Widget::copyRepeatModel(QDoubleSpinBox *insBox1, QDoubleSpinBox *insBox2, QDoubleSpinBox *insBox3, QDoubleSpinBox *insBox4,
                             QDoubleSpinBox *copyBx1, QDoubleSpinBox *copyBx2, QDoubleSpinBox *copyBx3, QDoubleSpinBox *copyBx4)
{
    insBox1->setRange(copyBx1->minimum(), copyBx1->maximum());
    insBox2->setRange(copyBx2->minimum(), copyBx2->maximum());
    insBox3->setRange(copyBx3->minimum(), copyBx3->maximum());
    insBox4->setRange(copyBx4->minimum(), copyBx4->maximum());

    insBox1->setValue(copyBx1->value());
    insBox2->setValue(copyBx2->value());
    insBox3->setValue(copyBx3->value());
    insBox4->setValue(copyBx4->value());
}

void Widget::setCurrentLabels(int mode, QLabel *lbl1, QLabel *lbl2, QLabel *lbl3)
{
    switch(mode)
    {
    case 1:
    {
        lbl1->setText("R:");
        lbl2->setText("G:");
        lbl3->setText("B:");
        break;
    }
    case 2:
    {
        lbl1->setText("C:");
        lbl2->setText("M:");
        lbl3->setText("Y:");
        break;
    }
    case 3:
    {
        lbl1->setText("H:");
        lbl2->setText("S:");
        lbl3->setText("V:");
        break;
    }
    case 4:
    {
        lbl1->setText("H:");
        lbl2->setText("S:");
        lbl3->setText("L:");
        break;
    }
    case 5:
    {
        lbl1->setText("X:");
        lbl2->setText("Y:");
        lbl3->setText("Z:");
        break;
    }
    case 6:
    {
        lbl1->setText("L:");
        lbl2->setText("A:");
        lbl3->setText("B:");
        break;
    }
    }
}



void Widget::convertModChanges(int &oldMod, int newMod, QDoubleSpinBox *sender1, QDoubleSpinBox *sender2,
                               QDoubleSpinBox *sender3, QDoubleSpinBox *sender4, QDoubleSpinBox *receiver1,
                               QDoubleSpinBox *receiver2, QDoubleSpinBox *receiver3, QDoubleSpinBox *receiver4)
{
    bool correct = true;
    if(oldMod == 1)
    {
        switch(newMod)
        {
        case 2:
        {
            correct = converter->ConvertFromRGBToCMYK(sender1, sender2, sender3,
                                                      receiver1, receiver2, receiver3, receiver4);
            oldMod = 2;
            break;
        }
        case 3:
        {
            correct = converter->ConvertFromRGBToHSV(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 3;
            break;
        }
        case 4:
        {
            correct = converter->ConvertFromRGBToHSL(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 4;
            break;
        }
        case 5:
        {
            correct = converter->ConvertFromRGBToXYZ(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 5;
            break;
        }
        case 6:
        {
            correct = converter->ConvertFromRGBToLAB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 6;
            break;
        }
        default:
            break;
        }
    }


    else if(oldMod == 2)
    {
        switch(newMod)
        {
        case 1:
        {
            correct = converter->ConvertFromCMYKToRGB(sender1, sender2, sender3, sender4,
                                                      receiver1, receiver2, receiver3);
            oldMod = 1;
            break;
        }
        case 3:
        {
            correct = converter->ConvertFromCMYKToHSV(sender1, sender2, sender3,sender4,
                                                      receiver1, receiver2, receiver3);
            oldMod = 3;
            break;
        }
        case 4:
        {
            correct = converter->ConvertFromCMYKToHSL(sender1, sender2, sender3, sender4,
                                                      receiver1, receiver2, receiver3);
            oldMod = 4;
            break;
        }
        case 5:
        {
            correct = converter->ConvertFromCMYKToXYZ(sender1, sender2, sender3, sender4,
                                                      receiver1, receiver2, receiver3);
            oldMod = 5;
            break;
        }
        case 6:
        {
            correct = converter->ConvertFromCMYKToLAB(sender1, sender2, sender3, sender4,
                                                      receiver1, receiver2, receiver3);
            oldMod = 6;
            break;
        }
        default:
            break;
        }
    }


    else if(oldMod == 3)
    {
        switch(newMod)
        {
        case 1:
        {
            correct = converter->ConvertFromHSVToRGB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 1;
            break;
        }
        case 2:
        {
            correct = converter->ConvertFromHSVToCMYK(sender1, sender2, sender3,
                                                      receiver1, receiver2, receiver3, receiver4);
            oldMod = 2;
            break;
        }
        case 4:
        {
            correct = converter->ConvertFromHSVToHSL(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 4;
            break;
        }
        case 5:
        {
            correct = converter->ConvertFromHSVToXYZ(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 5;
            break;
        }
        case 6:
        {
            correct = converter->ConvertFromHSVToLAB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 6;
            break;
        }
        default:
            break;
        }
    }


    else if(oldMod == 4)
    {
        switch(newMod)
        {
        case 1:
        {
            correct = converter->ConvertFromHSLToRGB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 1;
            break;
        }
        case 2:
        {
            correct = converter->ConvertFromHSLToCMYK(sender1, sender2, sender3,
                                                      receiver1, receiver2, receiver3, receiver4);
            oldMod = 2;
            break;
        }
        case 3:
        {
            correct = converter->ConvertFromHSLToHSV(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 3;
            break;
        }
        case 5:
        {
            correct = converter->ConvertFromHSLToXYZ(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 5;
            break;
        }
        case 6:
        {
            correct = converter->ConvertFromHSLToLAB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 6;
            break;
        }
        default:
            break;
        }
    }


    else if(oldMod == 5)
    {
        switch(newMod)
        {
        case 1:
        {
            correct = converter->ConvertFromXYZToRGB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 1;
            break;
        }
        case 2:
        {
            correct = converter->ConvertFromXYZToCMYK(sender1, sender2, sender3,
                                                      receiver1, receiver2, receiver3, receiver4);
            oldMod = 2;
            break;
        }
        case 3:
        {
            correct = converter->ConvertFromXYZToHSV(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 3;
            break;
        }
        case 4:
        {
            correct = converter->ConvertFromXYZToHSL(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 4;
            break;
        }
        case 6:
        {
            correct = converter->ConvertFromXYZToLAB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 6;
            break;
        }
        default:
            break;
        }
    }


    else if(oldMod == 6)
    {
        switch(newMod)
        {
        case 1:
        {
            correct = converter->ConvertFromLABToRGB(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 1;
            break;
        }
        case 2:
        {
            correct = converter->ConvertFromLABToCMYK(sender1, sender2, sender3,
                                                      receiver1, receiver2, receiver3, receiver4);
            oldMod = 2;
            break;
        }
        case 3:
        {
            correct = converter->ConvertFromLABToHSV(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 3;
            break;
        }
        case 4:
        {
            correct = converter->ConvertFromLABToHSL(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 4;
            break;
        }
        case 5:
        {
            correct = converter->ConvertFromLABToXYZ(sender1, sender2, sender3,
                                                     receiver1, receiver2, receiver3);
            oldMod = 5;
            break;
        }
        default:
            break;
        }
    }

    if (!correct)
        emit showStatus();
}



void Widget::convertFromMod1SpinBoxes()
{
    emit clearStatus();

    blockSpinBoxesSignals(true);

    if (repeatModelsCheck(col2, col1, col1) != 0)
        copyRepeatModel(colName2_1, colName2_2, colName2_3, colName2_4, colName1_1, colName1_2, colName1_3, colName1_4);
    else
    {
        int oldMode = col1->currentData().toInt();
        int newMode = col2->currentData().toInt();
        convertModChanges(oldMode, newMode, colName1_1, colName1_2, colName1_3, colName1_4,
                          colName2_1, colName2_2, colName2_3, colName2_4);
    }

    int repMode = repeatModelsCheck(col3, col1, col2);

    if (repMode == 1)
        copyRepeatModel(colName3_1, colName3_2, colName3_3, colName3_4, colName1_1, colName1_2, colName1_3, colName1_4);
    else if (repMode == 2)
        copyRepeatModel(colName3_1, colName3_2, colName3_3, colName3_4, colName2_1, colName2_2, colName2_3, colName2_4);
    else
    {
        int oldMode = col1->currentData().toInt();
        int newMode = col3->currentData().toInt();
        convertModChanges(oldMode, newMode, colName1_1, colName1_2, colName1_3, colName1_4,
                          colName3_1, colName3_2, colName3_3, colName3_4);
    }

    convertToColor(col1->currentData().toInt(), colName1_1, colName1_2, colName1_3, colName1_4);
    repaint();

    blockSpinBoxesSignals(false);
}

void Widget::convertFromMod2SpinBoxes()
{
    emit clearStatus();

    blockSpinBoxesSignals(true);

    if (repeatModelsCheck(col1, col2, col2) != 0)
        copyRepeatModel(colName1_1, colName1_2, colName1_3, colName1_4, colName2_1, colName2_2, colName2_3, colName2_4);
    else
    {
        int oldMode = col2->currentData().toInt();
        int newMode = col1->currentData().toInt();
        convertModChanges(oldMode, newMode, colName2_1, colName2_2, colName2_3, colName2_4,
                          colName1_1, colName1_2, colName1_3, colName1_4);
    }

    int repMode = repeatModelsCheck(col3, col1, col2);

    if (repMode == 1)
        copyRepeatModel(colName3_1, colName3_2, colName3_3, colName3_4, colName1_1, colName1_2, colName1_3, colName1_4);
    else if (repMode == 2)
        copyRepeatModel(colName3_1, colName3_2, colName3_3, colName3_4, colName2_1, colName2_2, colName2_3, colName2_4);
    else
    {
        int oldMode = col2->currentData().toInt();
        int newMode = col3->currentData().toInt();
        convertModChanges(oldMode, newMode, colName2_1, colName2_2, colName2_3, colName2_4,
                          colName3_1, colName3_2, colName3_3, colName3_4);
    }

    convertToColor(col2->currentData().toInt(), colName2_1, colName2_2, colName2_3, colName2_4);
    repaint();

    blockSpinBoxesSignals(false);
}

void Widget::convertFromMod3SpinBoxes()
{
    emit clearStatus();

    blockSpinBoxesSignals(true);

    if (repeatModelsCheck(col1, col3, col3) != 0)
        copyRepeatModel(colName1_1, colName1_2, colName1_3, colName1_4, colName3_1, colName3_2, colName3_3, colName3_4);
    else
    {
        int oldMode = col3->currentData().toInt();
        int newMode = col1->currentData().toInt();
        convertModChanges(oldMode, newMode, colName3_1, colName3_2, colName3_3, colName3_4,
                          colName1_1, colName1_2, colName1_3, colName1_4);
    }

    int repMode = repeatModelsCheck(col2, col1, col3);

    if (repMode == 1)
        copyRepeatModel(colName2_1, colName2_2, colName2_3, colName2_4, colName1_1, colName1_2, colName1_3, colName1_4);
    else if (repMode == 2)
        copyRepeatModel(colName2_1, colName2_2, colName2_3, colName2_4, colName3_1, colName3_2, colName3_3, colName3_4);
    else
    {
        int oldMode = col3->currentData().toInt();
        int newMode = col2->currentData().toInt();
        convertModChanges(oldMode, newMode, colName3_1, colName3_2, colName3_3, colName3_4,
                          colName2_1, colName2_2, colName2_3, colName2_4);
    }

    convertToColor(col3->currentData().toInt(), colName3_1, colName3_2, colName3_3, colName3_4);
    repaint();

    blockSpinBoxesSignals(false);
}

void Widget::convertToColor(int mode, QDoubleSpinBox *spBox1, QDoubleSpinBox *spBox2, QDoubleSpinBox *spBox3,
                            QDoubleSpinBox *spBox4)
{
    switch(mode)
    {
    case 1:
    {
        converter->ConvertFromRGBToColor(spBox1->value(), spBox2->value(), spBox3->value(), brush);
        break;
    }
    case 2:
    {
        converter->ConvertFromCMYKToColor(spBox1->value(), spBox2->value(), spBox3->value(), spBox4->value(), brush);
        break;
    }
    case 3:
    {
        converter->ConvertFromHSVToColor(spBox1->value(), spBox2->value(), spBox3->value(), brush);
        break;
    }
    case 4:
    {
        converter->ConvertFromHSLToColor(spBox1->value(), spBox2->value(), spBox3->value(), brush);
        break;
    }
    case 5:
    {
        converter->ConvertFromXYZToColor(spBox1->value(), spBox2->value(), spBox3->value(), brush);
        break;
    }
    case 6:
    {
        converter->ConvertFromLABToColor(spBox1->value(), spBox2->value(), spBox3->value(), brush);
        break;
    }
    }
}

void Widget::convertFromBrushToModel(int mod, QDoubleSpinBox* spBx1, QDoubleSpinBox* spBx2, QDoubleSpinBox* spBx3,
                                     QDoubleSpinBox* spBx4)
{
    blockSpinBoxesSignals(true);
    switch(mod)
    {
    case 1:
    {
        converter->ConvertFromColorToRGB(brush, spBx1, spBx2, spBx3);
        break;
    }
    case 2:
    {
        converter->ConvertFromColorToCMYK(brush, spBx1, spBx2, spBx3, spBx4);
        break;
    }
    case 3:
    {
        converter->ConvertFromColorToHSV(brush, spBx1, spBx2, spBx3);
        break;
    }
    case 4:
    {
        converter->ConvertFromColorToHSL(brush, spBx1, spBx2, spBx3);
        break;
    }
    case 5:
    {
        converter->ConvertFromColorToXYZ(brush, spBx1, spBx2, spBx3);
        break;
    }
    case 6:
    {
        converter->ConvertFromColorToLAB(brush, spBx1, spBx2, spBx3);
        break;
    }
    }
    blockSpinBoxesSignals(false);
}
