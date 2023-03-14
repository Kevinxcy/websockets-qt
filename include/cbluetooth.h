#ifndef CBLUETOOTH_H
#define CBLUETOOTH_H

#include <qbluetoothlocaldevice.h>
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

//add git use, good luck ！co...............................................
#include <string>
#include <vector>
#include <QObject>
#include <QMap>

class cbluetooth : public QObject
{
    Q_OBJECT
public:
    explicit cbluetooth(QObject *parent = nullptr);
    ~cbluetooth();

signals:
    void sig_add_blu_info(const QString &stradr, const QString &strname, bool bpair);

public slots:
    void DiscovereddeviceNotify(const QBluetoothDeviceInfo&);
    void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);

private slots:
    //void startScan();
    void scanFinished();
    //void hostModeStateChanged(QBluetoothLocalDevice::HostMode);

private:
    QBluetoothDeviceDiscoveryAgent *lpdiscoveryAgent ={nullptr};
    QBluetoothLocalDevice *lplocalDevice ={nullptr};

    QMap<QString, QString> blueinfo_map;
};

#endif // CBLUETOOTH_H
