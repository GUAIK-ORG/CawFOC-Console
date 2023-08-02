#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QStringList>
#include <QMap>
#include <QMutex>

class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = nullptr);
    void updateItems();
    const QMap<QString, QString>& getItems();

    bool open(const QString& name);
    void close();

    void write(const QByteArray& data);

private:
    QSerialPort *m_serial;
    QMap<QString, QString> m_serialItems;

signals:
    void recvData(const QByteArray& data);
private slots:
    void onReadyRead();

};

#endif // SERIAL_H
