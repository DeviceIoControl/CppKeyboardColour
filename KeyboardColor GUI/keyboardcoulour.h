//Created by BenRango

#ifndef KEYBOARDCOULOUR_H
#define KEYBOARDCOULOUR_H
#include <QProcess>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class KeyboardCoulour;
}
QT_END_NAMESPACE

class KeyboardCoulour : public QMainWindow
{
    Q_OBJECT



    public:
        KeyboardCoulour(QWidget *parent = nullptr);
        void setBreathe();
        void setColour(QString colour);
        void setColourTF();
        void setStatic();
        void setAnimation();
        void stopAnimation();
        void changeAnimation(QString);
        ~KeyboardCoulour();

    protected:
    void closeEvent(QCloseEvent *event) override;

    private:
        QSystemTrayIcon *trayIcon;
        QProcess *process;
        Ui::KeyboardCoulour *ui;
        QString animation;
        QString colour;
};
#endif // KEYBOARDCOULOUR_H
