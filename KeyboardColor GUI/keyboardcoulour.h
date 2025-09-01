#ifndef KEYBOARDCOULOUR_H
#define KEYBOARDCOULOUR_H
#include <QProcess>
#include <QMainWindow>

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
        void setColourTF();
        void setStatic();
        void setAnimation();
        void stopAnimation();
        void changeAnimation(QString);
        ~KeyboardCoulour();

    private:
        QProcess *process;
        Ui::KeyboardCoulour *ui;
        QString animation;
};
#endif // KEYBOARDCOULOUR_H
