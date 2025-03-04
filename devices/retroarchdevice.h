#ifndef RETROARCHDEVICE_H
#define RETROARCHDEVICE_H

#include "../adevice.h"
#include "../rommapping/rominfo.h"

#include <QObject>
#include <QUdpSocket>
#include <qtimer.h>


class RetroArchDevice : public ADevice
{
    Q_OBJECT
public:
    RetroArchDevice(QUdpSocket* sock, QString raVersion, QString gameName, int bSize, bool snesMemoryMap, bool snesLoromMap);

    // ADevice interface
public:
    void fileCommand(SD2Snes::opcode op, QVector<QByteArray> args);
    void fileCommand(SD2Snes::opcode op, QByteArray args);
    void controlCommand(SD2Snes::opcode op, QByteArray args);
    void putFile(QByteArray name, unsigned int size);
    void getAddrCommand(SD2Snes::space space, unsigned int addr, unsigned int size);
    void getAddrCommand(SD2Snes::space space, QList<QPair<unsigned int, quint8> > &args);
    void putAddrCommand(SD2Snes::space space, unsigned int addr0, unsigned int size);
    void putAddrCommand(SD2Snes::space space, QList<QPair<unsigned int, quint8> > &args);
    void putAddrCommand(SD2Snes::space space, unsigned char flags, unsigned int addr, unsigned int size);
    void sendCommand(SD2Snes::opcode opcode, SD2Snes::space space, unsigned char flags, const QByteArray &arg, const QByteArray arg2);
    void infoCommand();
    void writeData(QByteArray data);
    bool canAttach();
    QString name() const;
    bool hasFileCommands();
    bool hasControlCommands();
    USB2SnesInfo parseInfo(const QByteArray &data);
    QList<ADevice::FileInfos> parseLSCommand(QByteArray &dataI);


public slots:
    bool open();
    void close();

private slots:
    void    onUdpReadyRead();
    void    timedCommandDone();

private:
    QUdpSocket*  m_sock;
    QByteArray   dataToWrite;
    QTimer*      m_timer;
    QString      m_raVersion;
    QString      m_gameName;
    bool         bigGet;
    unsigned int sizeBigGet;
    unsigned int sizeRequested;
    unsigned int sizePrevBigGet;
    unsigned int addrBigGet;
    unsigned int lastRCRSize;
    unsigned int sizePut;
    unsigned int sizeWritten;
    bool         checkingRetroarch;
    bool         checkingInfo;
    bool         hasSnesMemoryMap;
    bool         hasSnesLoromMap;
    QByteArray   checkReturnedValue;
    rom_infos*   c_rom_infos;
    void         read_core_ram(unsigned int addr, unsigned int size);
    int          addr_to_addr(unsigned int addr);
    unsigned int blockSize;
    QString      m_uuid;

signals:
    void    checkReturned();
};

#endif // RETROARCHDEVICE_H
