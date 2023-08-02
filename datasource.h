#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QByteArray>
#include <QMutex>
#include "protocol/datas.h"

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

signals:
    void parseDataFinish(const DATAS_T& datas);
public slots:
    void onRecvData(const QByteArray& data);

private:
    QMutex m_mutex;
    QByteArray m_buffer;

    void parseData(const char* ptr, quint32 length);

};

#endif // DATASOURCE_H
