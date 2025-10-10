/********************************************************************************
** Form generated from reading UI file 'keyboardcoulour.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARDCOULOUR_H
#define UI_KEYBOARDCOULOUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyboardCoulour
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *sidebar;
    QVBoxLayout *verticalLayout;
    QLabel *appTitleLabel;
    QSpacerItem *verticalSpacer;
    QWidget *mainContent;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *headerLayout;
    QLabel *effectsLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *stopPushButton;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *animationsGrid;
    QPushButton *breathePushButton;
    QPushButton *colourTfPushButton;
    QPushButton *staticPushButton;
    QLabel *selectColorLabel;
    QGridLayout *colorButtonsGrid;
    QPushButton *redPushButton;
    QPushButton *greenPushButton;
    QPushButton *bluePushButton;
    QPushButton *yellowPushButton;
    QPushButton *cyanPushButton;
    QPushButton *magentaPushButton;
    QPushButton *whitePushButton;
    QPushButton *blackPushButton;
    QPushButton *orangePushButton;
    QPushButton *purplePushButton;
    QPushButton *pinkPushButton;
    QPushButton *brownPushButton;
    QPushButton *grayPushButton;
    QPushButton *limePushButton;
    QPushButton *goldPushButton;
    QPushButton *silverPushButton;
    QLabel *selectedColorLabel;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *KeyboardCoulour)
    {
        if (KeyboardCoulour->objectName().isEmpty())
            KeyboardCoulour->setObjectName("KeyboardCoulour");
        KeyboardCoulour->resize(1164, 600);
        KeyboardCoulour->setStyleSheet(QString::fromUtf8("\n"
"   /* Variables de style */\n"
"   QWidget#centralwidget {\n"
"        background-color: #1a1a2e;\n"
"        color: #e0e0f0;\n"
"   }\n"
"   \n"
"   /* Styles des boutons d'animation (cartes) */\n"
"   QPushButton {\n"
"        background-color: #22223b;\n"
"        border: 2px solid transparent;\n"
"        border-radius: 15px;\n"
"        padding: 30px;\n"
"        color: #e0e0f0;\n"
"        font-family: 'Verdana';\n"
"        font-weight: 600;\n"
"        text-align: center;\n"
"   }\n"
"   QPushButton:hover {\n"
"        border: 2px solid #e94560;\n"
"   }\n"
"   QPushButton:checked {\n"
"        border: 2px solid #007bff;\n"
"   }\n"
"   \n"
"   /* Styles des boutons d'action */\n"
"   QPushButton#runPushButton {\n"
"        background-color: #2ecc71;\n"
"        color: white;\n"
"        font-size: 16px;\n"
"        border-radius: 8px;\n"
"        padding: 10px 20px;\n"
"   }\n"
"   QPushButton#stopPushButton {\n"
"        background-color: #e74c3c;\n"
"        color: white;\n"
"        font-size:"
                        " 16px;\n"
"        border-radius: 8px;\n"
"        padding: 10px 20px;\n"
"   }\n"
"\n"
"   /* Style du QLabel (titre) */\n"
"   QLabel {\n"
"        font: 24pt \"Verdana\";\n"
"        font-weight: 600;\n"
"        color: #e94560;\n"
"   }\n"
"   \n"
"   /* Style de la barre lat\303\251rale */\n"
"   QWidget#sidebar {\n"
"        background-color: #22223b;\n"
"        border-right: 1px solid #3b3a4d;\n"
"   }\n"
"\n"
"   /* Style des boutons de couleur */\n"
"   .colorButton {\n"
"       min-width: 50px;\n"
"       min-height: 50px;\n"
"       max-width: 50px;\n"
"       max-height: 50px;\n"
"       border-radius: 25px;\n"
"       padding: 0;\n"
"   }\n"
"   /* Styles des couleurs individuelles */\n"
"   QPushButton#redPushButton { background-color: rgb(255, 0, 0); }\n"
"   QPushButton#greenPushButton { background-color: rgb(0, 255, 0); }\n"
"   QPushButton#bluePushButton { background-color: rgb(0, 0, 255); }\n"
"   QPushButton#yellowPushButton { background-color: rgb(255, 255, 0); }\n"
"   QPushButton#cyanPu"
                        "shButton { background-color: rgb(0, 255, 255); }\n"
"   QPushButton#magentaPushButton { background-color: rgb(255, 0, 255); }\n"
"   QPushButton#whitePushButton { background-color: rgb(255, 255, 255); }\n"
"   QPushButton#blackPushButton { background-color: rgb(0, 0, 0); }\n"
"   QPushButton#orangePushButton { background-color: rgb(255, 165, 0); }\n"
"   QPushButton#purplePushButton { background-color: rgb(128, 0, 128); }\n"
"   QPushButton#pinkPushButton { background-color: rgb(255, 192, 203); }\n"
"   QPushButton#brownPushButton { background-color: rgb(165, 42, 42); }\n"
"   QPushButton#grayPushButton { background-color: rgb(128, 128, 128); }\n"
"   QPushButton#limePushButton { background-color: rgb(50, 205, 50); }\n"
"   QPushButton#goldPushButton { background-color: rgb(255, 215, 0); }\n"
"   QPushButton#silverPushButton { background-color: rgb(192, 192, 192); }\n"
"   "));
        centralwidget = new QWidget(KeyboardCoulour);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebar = new QWidget(centralwidget);
        sidebar->setObjectName("sidebar");
        verticalLayout = new QVBoxLayout(sidebar);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, 30, 30, 30);
        appTitleLabel = new QLabel(sidebar);
        appTitleLabel->setObjectName("appTitleLabel");

        verticalLayout->addWidget(appTitleLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(sidebar);

        mainContent = new QWidget(centralwidget);
        mainContent->setObjectName("mainContent");
        mainContent->setStyleSheet(QString::fromUtf8("padding: 40px;"));
        verticalLayout_2 = new QVBoxLayout(mainContent);
        verticalLayout_2->setSpacing(40);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(40, 40, 40, 40);
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        effectsLabel = new QLabel(mainContent);
        effectsLabel->setObjectName("effectsLabel");
        effectsLabel->setStyleSheet(QString::fromUtf8("font-size: 1.6rem; font-weight: 600; color: #e0e0f0;"));

        headerLayout->addWidget(effectsLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        stopPushButton = new QPushButton(mainContent);
        stopPushButton->setObjectName("stopPushButton");
        stopPushButton->setMaximumSize(QSize(16777215, 70));
        stopPushButton->setStyleSheet(QString::fromUtf8("padding: 5px 8px;\n"
"width : 80px;\n"
"margin-left : 30px"));

        headerLayout->addWidget(stopPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(headerLayout);

        animationsGrid = new QGridLayout();
        animationsGrid->setSpacing(20);
        animationsGrid->setObjectName("animationsGrid");
        breathePushButton = new QPushButton(mainContent);
        breathePushButton->setObjectName("breathePushButton");

        animationsGrid->addWidget(breathePushButton, 0, 0, 1, 1);

        colourTfPushButton = new QPushButton(mainContent);
        colourTfPushButton->setObjectName("colourTfPushButton");

        animationsGrid->addWidget(colourTfPushButton, 0, 1, 1, 1);

        staticPushButton = new QPushButton(mainContent);
        staticPushButton->setObjectName("staticPushButton");

        animationsGrid->addWidget(staticPushButton, 0, 2, 1, 1);

        selectColorLabel = new QLabel(mainContent);
        selectColorLabel->setObjectName("selectColorLabel");
        selectColorLabel->setStyleSheet(QString::fromUtf8("font-size: 14pt; color: #e0e0f0; margin-bottom: 10px;"));

        animationsGrid->addWidget(selectColorLabel, 1, 0, 1, 3);

        colorButtonsGrid = new QGridLayout();
        colorButtonsGrid->setSpacing(10);
        colorButtonsGrid->setObjectName("colorButtonsGrid");
        redPushButton = new QPushButton(mainContent);
        redPushButton->setObjectName("redPushButton");

        colorButtonsGrid->addWidget(redPushButton, 0, 0, 1, 1);

        greenPushButton = new QPushButton(mainContent);
        greenPushButton->setObjectName("greenPushButton");

        colorButtonsGrid->addWidget(greenPushButton, 0, 1, 1, 1);

        bluePushButton = new QPushButton(mainContent);
        bluePushButton->setObjectName("bluePushButton");

        colorButtonsGrid->addWidget(bluePushButton, 0, 2, 1, 1);

        yellowPushButton = new QPushButton(mainContent);
        yellowPushButton->setObjectName("yellowPushButton");

        colorButtonsGrid->addWidget(yellowPushButton, 0, 3, 1, 1);

        cyanPushButton = new QPushButton(mainContent);
        cyanPushButton->setObjectName("cyanPushButton");

        colorButtonsGrid->addWidget(cyanPushButton, 0, 4, 1, 1);

        magentaPushButton = new QPushButton(mainContent);
        magentaPushButton->setObjectName("magentaPushButton");

        colorButtonsGrid->addWidget(magentaPushButton, 0, 5, 1, 1);

        whitePushButton = new QPushButton(mainContent);
        whitePushButton->setObjectName("whitePushButton");

        colorButtonsGrid->addWidget(whitePushButton, 0, 6, 1, 1);

        blackPushButton = new QPushButton(mainContent);
        blackPushButton->setObjectName("blackPushButton");

        colorButtonsGrid->addWidget(blackPushButton, 0, 7, 1, 1);

        orangePushButton = new QPushButton(mainContent);
        orangePushButton->setObjectName("orangePushButton");

        colorButtonsGrid->addWidget(orangePushButton, 1, 0, 1, 1);

        purplePushButton = new QPushButton(mainContent);
        purplePushButton->setObjectName("purplePushButton");

        colorButtonsGrid->addWidget(purplePushButton, 1, 1, 1, 1);

        pinkPushButton = new QPushButton(mainContent);
        pinkPushButton->setObjectName("pinkPushButton");

        colorButtonsGrid->addWidget(pinkPushButton, 1, 2, 1, 1);

        brownPushButton = new QPushButton(mainContent);
        brownPushButton->setObjectName("brownPushButton");

        colorButtonsGrid->addWidget(brownPushButton, 1, 3, 1, 1);

        grayPushButton = new QPushButton(mainContent);
        grayPushButton->setObjectName("grayPushButton");

        colorButtonsGrid->addWidget(grayPushButton, 1, 4, 1, 1);

        limePushButton = new QPushButton(mainContent);
        limePushButton->setObjectName("limePushButton");

        colorButtonsGrid->addWidget(limePushButton, 1, 5, 1, 1);

        goldPushButton = new QPushButton(mainContent);
        goldPushButton->setObjectName("goldPushButton");

        colorButtonsGrid->addWidget(goldPushButton, 1, 6, 1, 1);

        silverPushButton = new QPushButton(mainContent);
        silverPushButton->setObjectName("silverPushButton");

        colorButtonsGrid->addWidget(silverPushButton, 1, 7, 1, 1);


        animationsGrid->addLayout(colorButtonsGrid, 2, 0, 1, 3);

        selectedColorLabel = new QLabel(mainContent);
        selectedColorLabel->setObjectName("selectedColorLabel");
        selectedColorLabel->setStyleSheet(QString::fromUtf8("font-size: 14pt; color: #e94560;"));

        animationsGrid->addWidget(selectedColorLabel, 3, 0, 1, 3);


        verticalLayout_2->addLayout(animationsGrid);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(mainContent);

        KeyboardCoulour->setCentralWidget(centralwidget);
        menubar = new QMenuBar(KeyboardCoulour);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1164, 21));
        KeyboardCoulour->setMenuBar(menubar);
        statusbar = new QStatusBar(KeyboardCoulour);
        statusbar->setObjectName("statusbar");
        KeyboardCoulour->setStatusBar(statusbar);

        retranslateUi(KeyboardCoulour);

        QMetaObject::connectSlotsByName(KeyboardCoulour);
    } // setupUi

    void retranslateUi(QMainWindow *KeyboardCoulour)
    {
        KeyboardCoulour->setWindowTitle(QCoreApplication::translate("KeyboardCoulour", "Keyboard Colour Controller", nullptr));
        appTitleLabel->setText(QCoreApplication::translate("KeyboardCoulour", "Keyboard Colour", nullptr));
        effectsLabel->setText(QCoreApplication::translate("KeyboardCoulour", "Lighting Effects", nullptr));
        stopPushButton->setText(QCoreApplication::translate("KeyboardCoulour", "Stop", nullptr));
        breathePushButton->setText(QCoreApplication::translate("KeyboardCoulour", "Breathe", nullptr));
        colourTfPushButton->setText(QCoreApplication::translate("KeyboardCoulour", "Colour Transform", nullptr));
        staticPushButton->setText(QCoreApplication::translate("KeyboardCoulour", "Static Colours", nullptr));
        selectColorLabel->setText(QCoreApplication::translate("KeyboardCoulour", "Select a color for Breathe:", nullptr));
        selectedColorLabel->setText(QCoreApplication::translate("KeyboardCoulour", "Selected Color: None", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KeyboardCoulour: public Ui_KeyboardCoulour {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARDCOULOUR_H
