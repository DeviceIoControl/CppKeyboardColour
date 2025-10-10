//Created by BenRango

#include "keyboardcoulour.h"
#include "ui_keyboardcoulour.h"
#include <QDir>
#include <QIcon>
#include <filesystem>

KeyboardCoulour::KeyboardCoulour(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KeyboardCoulour)
{
    this->process = new QProcess(this);
    ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/favicon.ico")); 
    trayIcon->setToolTip("KeyboardColor");

    QMenu *trayMenu = new QMenu(this);
    QAction *restoreAction = new QAction("Ouvrir", this);
    QAction *quitAction = new QAction("Quitter", this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);


    trayMenu->addAction(restoreAction);
    trayMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayMenu);

    connect(trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::DoubleClick) {
            this->showNormal();
        }
    });

    trayIcon->show();
//  QtAwesome* awesome = new QtAwesome(this);
//  awesome->initFontAwesome();

//  ui->breathePushButton->setIcon(awesome->icon(fa::tint));
//  ui->colourTfPushButton->setIcon(awesome->icon(fa::exchangalt));
//  ui->runPushButton->setIcon(awesome->icon(fa::playcircle));
//  ui->stopPushButton->setIcon(awesome->icon(fa::stopcircle));

    connect(ui->redPushButton, &QPushButton::clicked, this, [this]() {
        setColour("red");
    });

    connect(ui->bluePushButton, &QPushButton::clicked, this, [this]() {
        setColour("blue");
    });

    connect(ui->greenPushButton, &QPushButton::clicked, this, [this]() {
        setColour("green");
    });
    connect(ui->cyanPushButton, &QPushButton::clicked, this, [this]() {
        setColour("cyan");
    });
    connect(ui->grayPushButton, &QPushButton::clicked, this, [this]() {
        setColour("gray");
    });
    connect(ui->greenPushButton, &QPushButton::clicked, this, [this]() {
        setColour("green");
    });
    connect(ui->breathePushButton, &QPushButton::clicked, this, &KeyboardCoulour::setBreathe);
    connect(ui->colourTfPushButton, &QPushButton::clicked, this, &KeyboardCoulour::setColourTF);
    connect(ui->stopPushButton, &QPushButton::clicked, this, &KeyboardCoulour::stopAnimation);
    connect(ui->staticPushButton, &QPushButton::clicked, this, &KeyboardCoulour::setStatic);
    setColourTF();
    this->setWindowIcon(QIcon(":icons/logo2.png"));
    this->colour = "none";
}


void KeyboardCoulour::setAnimation()
{
    if (this->process->state() == QProcess::Running) {
        this->process->kill();
        this->process->waitForFinished(1000);
    }

    QString current_path = QString::fromStdString(std::filesystem::current_path().string());
    current_path = current_path.replace("\\", "/");
    QDir dir(current_path);
    dir.cdUp();
    dir.cd("Build");
    qDebug() <<"dir = "<< dir;
    QString CKD_path = dir.filePath("CLEVO_KeyboardColour.exe");
    CKD_path = CKD_path.replace("\\", "/");
    qDebug() <<"CKD_path = "<< CKD_path;

    QString commande =  "\"" + CKD_path + "\""+ " theme " + this->animation;

    //this->process->setStandardOutputProcessChannelMode(QProcess::MergedChannels);
    //this->process->setReadChannel(QProcess::MergedChannels);

    this->process->start(commande);

    if (this->process->state() == QProcess::Running) {
        qDebug() << "Animation is running : " << commande;
    } else {
        qDebug() << "Failed to run the animation .";
        qDebug() << "Error : " << this->process->errorString();
    }
}
void KeyboardCoulour::setColour(QString colour){
    ui->breathePushButton->setStyleSheet("background-color: #22223b;");
    ui->breathePushButton->setEnabled(true);
    this->colour = "red";
    ui->selectedColorLabel->setText("Couleur s\303\251lectionn\303\251e : " + colour);
    this->animation = "singlecolour " + colour;
}
void KeyboardCoulour::stopAnimation()
{
    if (this->process->state() == QProcess::Running) {
        ui->staticPushButton->setStyleSheet("background-color : #22223b");
        ui->staticPushButton->setEnabled(true);
        this->colour = "none";
        ui->colourTfPushButton->setStyleSheet("background-color : #22223b");
        ui->colourTfPushButton->setEnabled(true);

        ui->breathePushButton->setStyleSheet("background-color: #22223b;");
        ui->breathePushButton->setEnabled(true);

        this->process->kill();
        qDebug() << "Animation stopped.";
    }
}

void KeyboardCoulour::changeAnimation(QString animation)
{
    this->animation = animation;
    return;
}
void KeyboardCoulour::setColourTF()
{
    this->animation = "colourtransform";
    this->colour == "none";
    ui->breathePushButton->setEnabled(true);
    ui->breathePushButton->setStyleSheet("background-color: #22223b;");
    ui->staticPushButton->setStyleSheet("background-color : #22223b");
    ui->staticPushButton->setEnabled(true);
    ui->colourTfPushButton->setEnabled(false);
    ui->colourTfPushButton->setStyleSheet("background-color: gray;");
    setAnimation();
    return;
}
void KeyboardCoulour::setStatic()
{

    this->colour == "none";
    if (this->process->state() == QProcess::Running) {
        ui->colourTfPushButton->setEnabled(true);
        ui->breathePushButton->setEnabled(true);
        ui->breathePushButton->setStyleSheet("background-color: #22223b;");
        this->process->kill();
        qDebug() << "Animation arrêtée.";
    }
    ui->staticPushButton->setStyleSheet("background-color : gray");
    ui->staticPushButton->setEnabled(false);
    ui->breathePushButton->setEnabled(true);
    ui->breathePushButton->setStyleSheet("background-color: #22223b;");
    ui->colourTfPushButton->setEnabled(true);
    ui->colourTfPushButton->setStyleSheet("background-color: #22223b;");
    return;
}
void KeyboardCoulour::setBreathe()
{
    if (this->colour != "none" || !this->colour.isEmpty()){
        this->animation = "singlebreathe "+ this->colour;
    }
    else{
        this->animation = "freshbreathe";
        ui->breathePushButton->setEnabled(false);
        ui->breathePushButton->setStyleSheet("background-color: gray;");
    }
    ui->staticPushButton->setStyleSheet("background-color : #22223b");
    ui->staticPushButton->setEnabled(true);
    ui->colourTfPushButton->setEnabled(true);
    ui->colourTfPushButton->setStyleSheet("background-color: #22223b;");
    setAnimation();
    return;
}

void KeyboardCoulour::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}
KeyboardCoulour::~KeyboardCoulour()
{
    delete ui;
}
