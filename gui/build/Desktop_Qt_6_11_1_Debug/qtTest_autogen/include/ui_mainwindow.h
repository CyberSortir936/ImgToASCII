/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *PixelRatio;
    QSpacerItem *horizontalSpacer_3;
    QSlider *PixelSlider;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLineEdit *filePath;
    QPushButton *BrowseButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *InvertCheck;
    QCheckBox *EdgesCheck;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QComboBox *AccentDropDown;
    QComboBox *ColorSchemeDropDown;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *SaveButton;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_5;
    QLabel *label_5;
    QLineEdit *CustomAccent;
    QLabel *label_6;
    QLineEdit *CustomBack;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(441, 425);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(20, 91, 391, 52));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        PixelRatio = new QLineEdit(gridLayoutWidget_2);
        PixelRatio->setObjectName("PixelRatio");

        gridLayout_2->addWidget(PixelRatio, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        PixelSlider = new QSlider(gridLayoutWidget_2);
        PixelSlider->setObjectName("PixelSlider");
        PixelSlider->setMaximumSize(QSize(140, 15));
        PixelSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(PixelSlider, 1, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(20, 21, 391, 61));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget_3);
        label->setObjectName("label");

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        filePath = new QLineEdit(gridLayoutWidget_3);
        filePath->setObjectName("filePath");

        gridLayout_3->addWidget(filePath, 1, 0, 1, 1);

        BrowseButton = new QPushButton(gridLayoutWidget_3);
        BrowseButton->setObjectName("BrowseButton");

        gridLayout_3->addWidget(BrowseButton, 1, 1, 1, 1);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 151, 391, 54));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        InvertCheck = new QCheckBox(verticalLayoutWidget);
        InvertCheck->setObjectName("InvertCheck");

        verticalLayout->addWidget(InvertCheck);

        EdgesCheck = new QCheckBox(verticalLayoutWidget);
        EdgesCheck->setObjectName("EdgesCheck");

        verticalLayout->addWidget(EdgesCheck);

        gridLayoutWidget_4 = new QWidget(centralwidget);
        gridLayoutWidget_4->setObjectName("gridLayoutWidget_4");
        gridLayoutWidget_4->setGeometry(QRect(20, 211, 391, 71));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        AccentDropDown = new QComboBox(gridLayoutWidget_4);
        AccentDropDown->addItem(QString());
        AccentDropDown->addItem(QString());
        AccentDropDown->addItem(QString());
        AccentDropDown->addItem(QString());
        AccentDropDown->addItem(QString());
        AccentDropDown->addItem(QString());
        AccentDropDown->setObjectName("AccentDropDown");

        gridLayout_4->addWidget(AccentDropDown, 1, 0, 1, 1);

        ColorSchemeDropDown = new QComboBox(gridLayoutWidget_4);
        ColorSchemeDropDown->addItem(QString());
        ColorSchemeDropDown->addItem(QString());
        ColorSchemeDropDown->addItem(QString());
        ColorSchemeDropDown->addItem(QString());
        ColorSchemeDropDown->addItem(QString());
        ColorSchemeDropDown->addItem(QString());
        ColorSchemeDropDown->addItem(QString());
        ColorSchemeDropDown->setObjectName("ColorSchemeDropDown");

        gridLayout_4->addWidget(ColorSchemeDropDown, 0, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget_4);
        label_3->setObjectName("label_3");

        gridLayout_4->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget_4);
        label_4->setObjectName("label_4");

        gridLayout_4->addWidget(label_4, 1, 1, 1, 1);

        SaveButton = new QPushButton(centralwidget);
        SaveButton->setObjectName("SaveButton");
        SaveButton->setGeometry(QRect(340, 390, 86, 26));
        gridLayoutWidget_5 = new QWidget(centralwidget);
        gridLayoutWidget_5->setObjectName("gridLayoutWidget_5");
        gridLayoutWidget_5->setGeometry(QRect(20, 290, 391, 71));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(gridLayoutWidget_5);
        label_5->setObjectName("label_5");

        gridLayout_5->addWidget(label_5, 0, 1, 1, 1);

        CustomAccent = new QLineEdit(gridLayoutWidget_5);
        CustomAccent->setObjectName("CustomAccent");

        gridLayout_5->addWidget(CustomAccent, 1, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_5);
        label_6->setObjectName("label_6");

        gridLayout_5->addWidget(label_6, 1, 1, 1, 1);

        CustomBack = new QLineEdit(gridLayoutWidget_5);
        CustomBack->setObjectName("CustomBack");

        gridLayout_5->addWidget(CustomBack, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Character to pixel ratio", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Input File", nullptr));
        BrowseButton->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        InvertCheck->setText(QCoreApplication::translate("MainWindow", "Invert Colors", nullptr));
        EdgesCheck->setText(QCoreApplication::translate("MainWindow", "Draw Edges Only", nullptr));
        AccentDropDown->setItemText(0, QCoreApplication::translate("MainWindow", "Red", nullptr));
        AccentDropDown->setItemText(1, QCoreApplication::translate("MainWindow", "Green", nullptr));
        AccentDropDown->setItemText(2, QCoreApplication::translate("MainWindow", "Yellow", nullptr));
        AccentDropDown->setItemText(3, QCoreApplication::translate("MainWindow", "Blue", nullptr));
        AccentDropDown->setItemText(4, QCoreApplication::translate("MainWindow", "Purple", nullptr));
        AccentDropDown->setItemText(5, QCoreApplication::translate("MainWindow", "White", nullptr));

        ColorSchemeDropDown->setItemText(0, QCoreApplication::translate("MainWindow", "Gruvbox", nullptr));
        ColorSchemeDropDown->setItemText(1, QCoreApplication::translate("MainWindow", "Everforest", nullptr));
        ColorSchemeDropDown->setItemText(2, QCoreApplication::translate("MainWindow", "Nord", nullptr));
        ColorSchemeDropDown->setItemText(3, QCoreApplication::translate("MainWindow", "Kanagawa", nullptr));
        ColorSchemeDropDown->setItemText(4, QCoreApplication::translate("MainWindow", "Catppuccin", nullptr));
        ColorSchemeDropDown->setItemText(5, QCoreApplication::translate("MainWindow", "Dracula", nullptr));
        ColorSchemeDropDown->setItemText(6, QCoreApplication::translate("MainWindow", "Custom", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Color Scheme", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Accent", nullptr));
        SaveButton->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Background", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Accent", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
