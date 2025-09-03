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
"       background-color: #1a1a2e;\n"
"       color: #e0e0f0;\n"
"   }\n"
"   \n"
"   /* Styles des boutons d'animation (cartes) */\n"
"   QPushButton {\n"
"       background-color: #22223b;\n"
"       border: 2px solid transparent;\n"
"       border-radius: 15px;\n"
"       padding: 30px;\n"
"       color: #e0e0f0;\n"
"       font-family: 'Verdana';\n"
"       font-weight: 600;\n"
"       text-align: center;\n"
"   }\n"
"   QPushButton:hover {\n"
"       border: 2px solid #e94560;\n"
"   }\n"
"   QPushButton:checked {\n"
"       border: 2px solid #007bff;\n"
"   }\n"
"   \n"
"   /* Styles des boutons d'action */\n"
"   QPushButton#runPushButton {\n"
"       background-color: #2ecc71;\n"
"       color: white;\n"
"       font-size: 16px;\n"
"       border-radius: 8px;\n"
"       padding: 10px 20px;\n"
"   }\n"
"   QPushButton#stopPushButton {\n"
"       background-color: #e74c3c;\n"
"       color: white;\n"
"       font-size: 16px;\n"
"       bo"
                        "rder-radius: 8px;\n"
"       padding: 10px 20px;\n"
"   }\n"
"\n"
"   /* Style du QLabel (titre) */\n"
"   QLabel {\n"
"       font: 24pt \"Verdana\";\n"
"       font-weight: 600;\n"
"       color: #e94560;\n"
"   }\n"
"   \n"
"   /* Style de la barre lat\303\251rale */\n"
"   QWidget#sidebar {\n"
"       background-color: #22223b;\n"
"       border-right: 1px solid #3b3a4d;\n"
"   }\n"
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
        colourTfPushButton->setText(QCoreApplication::translate("KeyboardCoulour", "Coulour Transform", nullptr));
        staticPushButton->setText(QCoreApplication::translate("KeyboardCoulour", "Static Colours", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KeyboardCoulour: public Ui_KeyboardCoulour {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARDCOULOUR_H
