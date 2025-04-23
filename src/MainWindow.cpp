#include "MainWindow.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "SensorReader.h"
#include <QApplication>
#include <QTimer>
#include <QFrame>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

/**
 * @brief Stałe progowe dla interpretacji danych.
 */
const int HIGH_CO2 = 1200; ///< Poziom CO2 (ppm), powyżej którego jakość powietrza jest uznawana za złą.
const int HIGH_PM1 = 25;   ///< Poziom PM1.0 (µg/m³), powyżej którego jakość powietrza jest uznawana za złą.
const int HIGH_PM25 = 25;  ///< Poziom PM2.5 (µg/m³), powyżej którego jakość powietrza jest uznawana za złą.
const int HIGH_PM10 = 50;  ///< Poziom PM10 (µg/m³), powyżej którego jakość powietrza jest uznawana za złą.
const int HIGH_RADIATION = 30; ///< Liczba CPM, powyżej której poziom promieniowania jest uznawany za podwyższony.
const float CPS_PER_USV = 0.0037; ///< Przelicznik CPM na µSv/h.

MainWindow::MainWindow(SensorReader* reader, QWidget *parent)
    : QMainWindow(parent), sensorReader(reader)
{
    co2Label = new QLabel("--", this);
    co2TempLabel = new QLabel("--", this);
    co2HumLabel = new QLabel("--", this);
    pm1Label = new QLabel("--", this);
    pm25Label = new QLabel("--", this);
    pm10Label = new QLabel("--", this);
    radiationLabel = new QLabel("--", this);
    radiationDoseLabel = new QLabel("--", this);

    co2StatusLabel = new QLabel("--", this);
    pmStatusLabel = new QLabel("--", this);
    radiationStatusLabel = new QLabel("--", this);

    QGridLayout* sensorDataLayout = new QGridLayout();
    sensorDataLayout->addWidget(new QLabel("CO2 (Dwutlenek Węgla):", this), 0, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(co2Label, 0, 1, Qt::AlignLeft);
    sensorDataLayout->addWidget(new QLabel("Temperatura:", this), 1, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(co2TempLabel, 1, 1, Qt::AlignLeft);
    sensorDataLayout->addWidget(new QLabel("Wilogtność:", this), 2, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(co2HumLabel, 2, 1, Qt::AlignLeft);
    sensorDataLayout->addWidget(new QLabel("Pył zawieszony PM1.0:", this), 3, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(pm1Label, 3, 1, Qt::AlignLeft);
    sensorDataLayout->addWidget(new QLabel("Pył zawieszony PM2.5:", this), 4, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(pm25Label, 4, 1, Qt::AlignLeft);
    sensorDataLayout->addWidget(new QLabel("Pył zawieszony PM10:", this), 5, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(pm10Label, 5, 1, Qt::AlignLeft);
    sensorDataLayout->addWidget(new QLabel("Zliczenia det. Geiger Mullera:", this), 6, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(radiationLabel, 6, 1, Qt::AlignLeft);
    sensorDataLayout->addWidget(new QLabel("Dawka przyjęta na godzinę:", this), 7, 0, Qt::AlignRight);
    sensorDataLayout->addWidget(radiationDoseLabel, 7, 1, Qt::AlignLeft);

    QFrame* sensorDataFrame = new QFrame(this);
    sensorDataFrame->setLayout(sensorDataLayout);
    sensorDataFrame->setFrameStyle(QFrame::Box | QFrame::Raised);
    sensorDataFrame->setLineWidth(2);

    QGridLayout* interpretationLayout = new QGridLayout();
    interpretationLayout->addWidget(new QLabel("CO2 Status:", this), 0, 0, Qt::AlignRight);
    interpretationLayout->addWidget(co2StatusLabel, 0, 1, Qt::AlignLeft);
    interpretationLayout->addWidget(new QLabel("PM Status:", this), 1, 0, Qt::AlignRight);
    interpretationLayout->addWidget(pmStatusLabel, 1, 1, Qt::AlignLeft);
    interpretationLayout->addWidget(new QLabel("Prom. Status:", this), 2, 0, Qt::AlignRight);
    interpretationLayout->addWidget(radiationStatusLabel, 2, 1, Qt::AlignLeft);

    QFrame* interpretationFrame = new QFrame(this);
    interpretationFrame->setLayout(interpretationLayout);
    interpretationFrame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    interpretationFrame->setLineWidth(2);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel("Interpretacja danych:", this));
    mainLayout->addWidget(interpretationFrame);
    mainLayout->addWidget(new QLabel("Dane z czujników:", this));
    mainLayout->addWidget(sensorDataFrame);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSensorData);
    timer->start(1000);
}

/**
 * @brief Destruktor klasy MainWindow.
 */
MainWindow::~MainWindow()
{
}

/**
 * @brief Aktualizuje dane z czujników i wyświetla je w interfejsie.
 */
void MainWindow::updateSensorData()
{
    if (sensorReader->readData()) {
        SensorData data = sensorReader->getData();

        co2Label->setText(QString::number(data.co2) + " ppm");
        co2TempLabel->setText(QString::number(data.co2_temp) + " C");
        co2HumLabel->setText(QString::number(data.co2_hum) + " %");
        pm1Label->setText(QString::number(data.pm1) + " ppm");
        pm25Label->setText(QString::number(data.pm25) + " ppm");
        pm10Label->setText(QString::number(data.pm10) + " ppm");
        radiationLabel->setText(QString::number(data.radiation) + " imp/min");
        radiationDoseLabel->setText(QString::number(data.radiation * CPS_PER_USV) + " uSv/h");

        QString co2Status = (data.co2 > HIGH_CO2) ? "Wysoki poziom CO2!" : "Akceptowalny poziom CO2";
        QString pmStatus = (data.pm1 > HIGH_PM1 || data.pm25 > HIGH_PM25 || data.pm10 > HIGH_PM10) ? "Wysokie zanieczyszczenie!" : "Niskie zanieczyszczenie powietrza";
        QString radiationStatus = (data.radiation > HIGH_RADIATION) ? "Podwyższony poziom promieniowania!" : "Naturalny poziom promieniowania";

        co2StatusLabel->setText(co2Status);
        pmStatusLabel->setText(pmStatus);
        radiationStatusLabel->setText(radiationStatus);
    }
}
