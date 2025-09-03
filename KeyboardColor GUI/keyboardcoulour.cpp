#include "keyboardcoulour.h"
#include "./ui_keyboardcoulour.h"
#include <QDir>
#include <QIcon>
#include <filesystem>
//#include <QtAwesome.h>
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

    connect(ui->breathePushButton, &QPushButton::clicked, this, &KeyboardCoulour::setBreathe);
    connect(ui->colourTfPushButton, &QPushButton::clicked, this, &KeyboardCoulour::setColourTF);
    connect(ui->stopPushButton, &QPushButton::clicked, this, &KeyboardCoulour::stopAnimation);
    connect(ui->staticPushButton, &QPushButton::clicked, this, &KeyboardCoulour::setStatic);
    setColourTF();
    this->setWindowIcon(QIcon(":icons/logo2.png"));
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

void KeyboardCoulour::stopAnimation()
{
    if (this->process->state() == QProcess::Running) {
        ui->staticPushButton->setStyleSheet("background-color : #22223b");
        ui->staticPushButton->setEnabled(true);

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
    this->animation = "breathe";
    ui->staticPushButton->setStyleSheet("background-color : #22223b");
    ui->staticPushButton->setEnabled(true);
    ui->colourTfPushButton->setEnabled(true);
    ui->colourTfPushButton->setStyleSheet("background-color: #22223b;");
    ui->breathePushButton->setEnabled(false);
    ui->breathePushButton->setStyleSheet("background-color: gray;");
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
