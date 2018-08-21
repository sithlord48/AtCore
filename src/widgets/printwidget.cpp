/* AtCore Test Client
    Copyright (C) <2018>
    Author: Chris Rizzitello - rizzitello@kde.org

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
#include "printwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

PrintWidget::PrintWidget(bool showAllControls, QWidget *parent) :
    QWidget(parent)
{
    auto mainLayout = new QVBoxLayout;
    QPushButton *newButton = nullptr;
    QLabel *newLabel = nullptr;
    QHBoxLayout *hBoxLayout = nullptr;
    if (showAllControls) {
        buttonPrint = new QPushButton(tr("Print File"));
        connect(buttonPrint, &QPushButton::clicked, this, [this] {
            emit printPressed();
        });

        newButton = new QPushButton(tr("Emergency Stop"));
        connect(newButton, &QPushButton::clicked, this, [this] {
            emit emergencyStopPressed();
        });

        hBoxLayout = new QHBoxLayout;
        hBoxLayout->addWidget(buttonPrint);
        hBoxLayout->addWidget(newButton);
        mainLayout->addLayout(hBoxLayout);

        newLabel = new QLabel(tr("On Pause:"));

        linePostPause = new QLineEdit;
        linePostPause->setPlaceholderText(QStringLiteral("G91,G0 Z1,G90,G1 X0 Y195"));

        hBoxLayout = new QHBoxLayout;
        hBoxLayout->addWidget(newLabel);
        hBoxLayout->addWidget(linePostPause);
        mainLayout->addLayout(hBoxLayout);
    }

    newLabel = new QLabel(tr("Printer Speed"));
    sbPrintSpeed = new QSpinBox;
    sbPrintSpeed->setRange(1, 300);
    sbPrintSpeed->setValue(100);
    sbPrintSpeed->setSuffix(QStringLiteral("%"));

    newButton = new QPushButton(tr("Set"));
    connect(newButton, &QPushButton::clicked, this, [this] {
        emit printSpeedChanged(sbPrintSpeed->value());
    });

    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(newLabel, 60);
    hBoxLayout->addWidget(sbPrintSpeed, 20);
    hBoxLayout->addWidget(newButton, 20);
    mainLayout->addLayout(hBoxLayout);

    newLabel = new QLabel(tr("Flow Rate"));
    sbFlowRate = new QSpinBox;
    sbFlowRate->setRange(1, 300);
    sbFlowRate->setValue(100);
    sbFlowRate->setSuffix(QStringLiteral("%"));

    newButton = new QPushButton(tr("Set"));
    connect(newButton, &QPushButton::clicked, this, [this] {
        emit flowRateChanged(sbFlowRate->value());
    });
    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(newLabel, 60);
    hBoxLayout->addWidget(sbFlowRate, 20);
    hBoxLayout->addWidget(newButton, 20);
    mainLayout->addLayout(hBoxLayout);

    comboFanSelect = new QComboBox;
    sbFanSpeed = new QSpinBox;
    sbFanSpeed->setRange(0, 100);
    sbFanSpeed->setSuffix(QStringLiteral("%"));

    newButton = new QPushButton(tr("Set"));
    connect(newButton, &QPushButton::clicked, this, [this] {
        emit fanSpeedChanged(sbFanSpeed->value(), comboFanSelect->currentIndex());
    });

    hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(comboFanSelect, 60);
    hBoxLayout->addWidget(sbFanSpeed, 20);
    hBoxLayout->addWidget(newButton, 20);
    mainLayout->addLayout(hBoxLayout);

    setLayout(mainLayout);
}

QString PrintWidget::postPauseCommand(void) const
{
    return linePostPause->text();
}

void PrintWidget::setPrintText(const QString &text)
{
    buttonPrint->setText(text);
}

void PrintWidget::updateFanCount(const int count)
{
    for (int i = 0; i < count; i++) {
        comboFanSelect->insertItem(i, tr("Fan %1 speed").arg(i));
    }
}
