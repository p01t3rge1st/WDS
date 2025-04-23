QT += core gui widgets charts

TEMPLATE = app
TARGET = SensorReaderApp

CONFIG += c++11

# Ścieżki do plików źródłowych
SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/SensorReader.cpp

HEADERS += \
    src/MainWindow.h \
    src/SensorReader.h

# Ścieżka do folderu z nagłówkami (jeśli chcesz dodać osobny `include/`, dodaj go tutaj)
INCLUDEPATH += src

# Katalog wyjściowy i tymczasowe pliki
DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui

# Biblioteki Qt (zwykle nie trzeba ręcznie dodawać LIBS dla Qt, qmake sam to załatwia)
# LIBS += -L/usr/lib/x86_64-linux-gnu -lQt5Widgets -lQt5Core -lQt5Gui


