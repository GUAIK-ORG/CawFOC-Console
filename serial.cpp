#include "serial.h"
#include <QSerialPortInfo>
#include <QDebug>

Serial::Serial(QObject *parent) : QObject(parent)
{
    m_serial = new QSerialPort();
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    connect(m_serial, &QSerialPort::readyRead, this, &Serial::onReadyRead);
}

void Serial::updateItems()
{
    QSerialPort tmpSerial;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        tmpSerial.setPort(info);
        if (tmpSerial.open(QIODevice::ReadWrite)) {
            m_serialItems.insert(QString("[%1] %2").arg(info.portName()).arg(info.description()), info.portName());
            qDebug() << info.portName();
            tmpSerial.close();
        }
    }
}

const QMap<QString, QString> &Serial::getItems()
{
    return m_serialItems;
}

bool Serial::open(const QString& name)
{
    if (m_serial->isOpen() || !m_serialItems.contains(name)) {
        return false;
    }
    m_serial->setPortName(m_serialItems[name]);
    return m_serial->open(QIODevice::ReadWrite);
}

void Serial::close()
{
    if (m_serial->isOpen()) {
        m_serial->close();
    }
}

void Serial::write(const QByteArray &data)
{
    m_serial->write(data);
}

void Serial::onReadyRead()
{
    emit recvData(m_serial->readAll());
}
