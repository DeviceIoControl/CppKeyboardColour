cmake_minimum_required(VERSION 3.16)

project(KeyboardColor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Ne faites qu'un seul appel à find_package
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    keyboardcoulour.cpp
    keyboardcoulour.h
    keyboardcoulour.ui
)

# 2. Utilisez qt_add_executable pour Qt 6
# C'est la méthode recommandée.
qt_add_executable(KeyboardColor
    ${PROJECT_SOURCES}
    resources.qrc
)

# 3. Liez la cible à la librairie Qt Widgets
# La commande qt_add_executable inclut déjà les options de liaison nécessaires.
# La ligne ci-dessous est tout ce dont vous avez besoin.
target_link_libraries(KeyboardColor PRIVATE Qt6::Widgets)

# 4. Gérer l'icône de l'application
# Assurez-vous que votre fichier d'icône est présent.
set(ICON_FILE_NAME "votre_logo.ico") # Pour Windows
set_target_properties(KeyboardColor PROPERTIES
    WIN32_EXECUTABLE FALSE
    WIN32_ICON "${ICON_FILE_NAME}"
)

# 5. Pas besoin de 'if(QT_VERSION_MAJOR EQUAL 6)' ou de 'qt_finalize_executable'
# La commande qt_add_executable le fait pour vous.
# Enlever le bloc 'if(QT_VERSION_MAJOR EQUAL 6)' et le `qt_finalize_executable`.