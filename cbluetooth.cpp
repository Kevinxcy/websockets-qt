#include "cbluetooth.h"

#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>

#include <QMessageBox>

cbluetooth::cbluetooth(QObject *parent) : QObject(parent)
{
    lplocalDevice = new QBluetoothLocalDevice;
    lpdiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    connect(lpdiscoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(DiscovereddeviceNotify(QBluetoothDeviceInfo)));

    connect(lpdiscoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));


    connect(lplocalDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing)),
        this, SLOT(pairingDone(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));

    lpdiscoveryAgent->start();
}

cbluetooth::~cbluetooth()
{

}

void cbluetooth::DiscovereddeviceNotify(const QBluetoothDeviceInfo &info)
{
    if (!info.name().isEmpty())
    {
        QBluetoothLocalDevice::Pairing pairingStatus = lplocalDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            emit sig_add_blu_info(info.address().toString(), info.name(), true);
        else
            emit sig_add_blu_info(info.address().toString(), info.name(), false);
        //this->blueinfo_map.insert(info.address().toString(), info.name());
    }

    QMessageBox::about(nullptr, info.address().toString(), info.name());
    //QMessageBox()
}

void cbluetooth::pairingDone(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired )
    {
        //pair success
    }
    else
    {
        //pair failed
    }
}

void cbluetooth::scanFinished()
{

}
