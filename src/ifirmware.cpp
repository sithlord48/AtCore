/* AtCore
    Copyright (C) <2016>

    Authors:
        Tomaz Canabrava <tcanabrava@kde.org>
        Patrick José Pereira <patrickelectric@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ifirmware.h"
#include "temperature.h"
#include "atcore.h"

struct IFirmwarePrivate {
    AtCore *parent;
};

IFirmware::IFirmware()
    : d(new IFirmwarePrivate)
{
}

void IFirmware::init(AtCore *parent)
{
    d->parent = parent;
    connect(d->parent, &AtCore::receivedMessage, this, &IFirmware::checkCommand);
}

AtCore *IFirmware::core() const
{
    return d->parent;
}

IFirmware::~IFirmware()
{
}

void IFirmware::checkCommand(const QByteArray &lastMessage)
{
    validateCommand(QString::fromLatin1(lastMessage));
}

