/**
 * @file main.cpp
 * @brief Główna funkcja programu.
 */

#include <iostream>
#include <thread>
#include <chrono>
#include "SensorReader.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <regex>
#include <termios.h>
#include <QApplication>
#include "MainWindow.h"

/**
 * @brief Wyświetla pasek ładowania w terminalu.
 * 
 */

/**
 * @brief Główna funkcja programu.
 * 
 * Inicjalizuje obiekt SensorReader, otwiera port szeregowy i uruchamia aplikację Qt.
 * 
 * @param argc Liczba argumentów wiersza poleceń.
 * @param argv Tablica argumentów wiersza poleceń.
 * @return int Kod wyjścia programu.
 */
int main(int argc, char *argv[]) {

    const char* portname = "/dev/ttyUSB0";
    SensorReader reader(portname);

    if (!reader.openPort()) {
        return 1;
    }

    QApplication app(argc, argv);
    MainWindow mainWindow(&reader);
    mainWindow.show();

    return app.exec();
}
