/* AtCore Test Client
    Copyright (C) <2016>

    Authors:
        Patrick José Pereira <patrickjp@kde.org>
        Lays Rodrigues <lays.rodrigues@kde.org>
        Chris Rizzitello <rizzitello@kde.org>
        Tomaz Canabrava <tcanabrava@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <QMainWindow>
#include <QSerialPort>

#include "atcore.h"
#include "commandwidget.h"
#include "logwidget.h"
#include "movementwidget.h"
#include "plotwidget.h"
#include "printwidget.h"
#include "sdwidget.h"
#include "statuswidget.h"
#include "temperaturewidget.h"

class SerialLayer;

class  MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

public slots:
    /**
     * @brief Check temperature
     *
     * @param  sensorType : type of sensor
     * @param  number     : index of sensor
     * @param  temp       : temperature
     */
    void checkTemperature(uint sensorType, uint number, float temp);

private slots:
    //ButtonEvents

    /**
     * @brief Connect Button Clicked will connect or disconnect based on printer state
     */
    void connectPBClicked();

    /**
     * @brief Print Button Clicked, can also pause /resue print based on printer state
     */
    void printPBClicked();

    /**
     * @brief printerStateChanged Catch and proccess printer state commands
     * @param state: new printer state
     */
    void printerStateChanged(AtCore::STATES state);

    /**
     * @brief show/hide dock titlebars
     * @param checked: True if shown
     */
    void toggleDockTitles(bool checked);

    /**
     * @brief Toggle disable state of dangerous docks
     * Command, Sd Card, Movement, Temperature Controls and Printing docks
     * @param disabled: True if items are disabled.
     */
    void setDangeriousDocksDisabled(bool disabled);

private:
    AtCore *core;
    // Define max number of fans
    static int fanCount;

    void closeEvent(QCloseEvent *event) override;
    /**
     * @brief Locate serial port
     *
     */
    void locateSerialPort(const QStringList &ports);

    /**
     * @brief pluginCB index changed
     */
    void pluginCBChanged(const QString &currentText);

    /**
     * @brief setupActions for KXMLGui
     */
    void setupActions();

    /**
     * @brief Populate comboboxes
     */
    void populateCBs();

    /**
     * @brief Gui Changes for when sd card mount status has changed.
     */
    void sdChanged(bool mounted);

    //UI Functions

    /**
     * @brief Create The Menubar
     */
    void initMenu();

    /**
     * @brief Create StatusBar
     */
    void initStatusBar();

    /**
     * @brief Create Main Widgets.
     */
    void initWidgets();

//Private GUI Items
    //menuView is global to allow for docks to be added / removed.
    QMenu *menuView = nullptr;
    //Status Bar Items
    StatusWidget *statusWidget = nullptr;
    //Docks
    void makeLogDock();
    QDockWidget *logDock = nullptr;
    LogWidget *logWidget = nullptr;

    void makeTempTimelineDock();
    QDockWidget *tempTimelineDock = nullptr;
    PlotWidget *plotWidget = nullptr;

    void makeCommandDock();
    QDockWidget *commandDock = nullptr;
    CommandWidget *commandWidget = nullptr;

    void makePrintDock();
    QDockWidget *printDock = nullptr;
    PrintWidget *printWidget = nullptr;

    void makeConnectDock();
    QDockWidget *connectDock = nullptr;
    QComboBox *comboPort = nullptr;
    QComboBox *comboBAUD = nullptr;
    QComboBox *comboPlugin = nullptr;
    QPushButton *buttonConnect = nullptr;
    QCheckBox *cbReset = nullptr;

    void makeMoveDock();
    QDockWidget *moveDock = nullptr;
    MovementWidget *movementWidget = nullptr;

    void makeTempControlsDock();
    QDockWidget *tempControlsDock = nullptr;
    TemperatureWidget *temperatureWidget = nullptr;

    void makeSdDock();
    QDockWidget *sdDock = nullptr;
    SdWidget *sdWidget = nullptr;
};
