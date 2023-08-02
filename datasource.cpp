#include "datasource.h"
#include <QDebug>
#include "protocol/protocol.h"


DataSource::DataSource(QObject *parent) : QObject(parent)
{

}

void DataSource::onRecvData(const QByteArray &data)
{
    QMutexLocker _(&m_mutex);
    m_buffer.push_back(data);
    while (m_buffer.size() > BYTE_PACKET_HEAD_SIZE) {
        int index = m_buffer.indexOf(BYTE_PACKET_HEAD_MAGIC);
        if (index == -1) {
            m_buffer.clear();
            return;
        }
        m_buffer.remove(0, index);
        BYTE_PACKET_HEAD head;
        if (!unpack_head(m_buffer.data(), &head)) {
            m_buffer.remove(0, BYTE_PACKET_HEAD_SIZE);
            continue;
        }
        if (static_cast<quint32>(m_buffer.size()) < head.length) return;
        if (head.type == PACK_TYPE::SEND_DATAS) {
            parseData(m_buffer.data() + BYTE_PACKET_HEAD_SIZE, head.length - BYTE_PACKET_HEAD_SIZE);
        }
        m_buffer.remove(0, head.length);
    }
}

void DataSource::parseData(const char *ptr, quint32 length)
{
    DATAS_T datas;
    memcpy(&datas, ptr, length);
    unpack_datas(&datas);
    emit parseDataFinish(datas);
//    qDebug() << datas.datas[1].angle << " - " << datas.datas[1].velocity << "@" << length;
}
