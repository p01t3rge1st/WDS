#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include "SensorReader.h"

/**
 * @class MainWindow
 * @brief Klasa reprezentująca główne okno aplikacji.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy MainWindow.
     * @param reader Wskaźnik do obiektu SensorReader.
     * @param parent Wskaźnik do obiektu nadrzędnego (domyślnie nullptr).
     */
    explicit MainWindow(SensorReader* reader, QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Aktualizuje dane z czujników i wyświetla je w interfejsie.
     */
    void updateSensorData();

private:
    QLabel* co2Label; ///< Etykieta wyświetlająca poziom CO2.
    QLabel* co2TempLabel; ///< Etykieta wyświetlająca temperaturę CO2.
    QLabel* co2HumLabel; ///< Etykieta wyświetlająca wilgotność CO2.
    QLabel* pm1Label; ///< Etykieta wyświetlająca poziom PM1.0.
    QLabel* pm25Label; ///< Etykieta wyświetlająca poziom PM2.5.
    QLabel* pm10Label; ///< Etykieta wyświetlająca poziom PM10.
    QLabel* radiationLabel; ///< Etykieta wyświetlająca poziom promieniowania.
    QLabel* radiationDoseLabel; ///< Etykieta wyświetlająca dawkę promieniowania na godzinę.
    QLabel* co2StatusLabel; ///< Etykieta wyświetlająca status CO2.
    QLabel* pmStatusLabel; ///< Etykieta wyświetlająca status PM.
    QLabel* radiationStatusLabel; ///< Etykieta wyświetlająca status promieniowania.

    QTimer* timer; ///< Timer do cyklicznej aktualizacji danych.
    SensorReader* sensorReader; ///< Wskaźnik do obiektu SensorReader.
};

#endif
