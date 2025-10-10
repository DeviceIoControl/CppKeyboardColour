//Created by BenRango

#include <windows.h>
#include <QApplication>
#include <QMessageBox>

#include "keyboardcoulour.h"

int main(int argc, char *argv[])
{
    const char *mutexName = "votre_app_unique_mutex_3A4B5C6D";

    HANDLE hMutex = CreateMutexA(nullptr, TRUE, mutexName);

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        QMessageBox::warning(nullptr, "Application déjà en cours d'exécution",
            "Une instance de l'application est déjà en cours d'exécution.");
        CloseHandle(hMutex);
        return 0;
    }
    QApplication a(argc, argv);
    KeyboardCoulour w;
    w.show();
    return a.exec();
}
