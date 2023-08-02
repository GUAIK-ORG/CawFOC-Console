#include "protocol.h"

#include <QDebug>

// 解包数据头
bool unpack_head(const char* ptr, BYTE_PACKET_HEAD* head) {
    memcpy(head->magic, ptr, 4);
    if (memcmp(head->magic, BYTE_PACKET_HEAD_MAGIC, 4) != 0) return false;
    head->length = qFromBigEndian<quint32>(ptr + BYTE_PACKET_HEAD_LENGTH_OFFSET);
    head->type = qFromBigEndian<quint16>(ptr + BYTE_PACKET_HEAD_TYPE_OFFSET);
    head->version = qFromBigEndian<quint16>(ptr + BYTE_PACKET_HEAD_VERSION_OFFSET);
    if (head->version != BYTE_PACKET_HEAD_VERSION) return false;
    return true;
}

// 打包数据头
void pack_head(quint32 length, quint16 type, QByteArray* dst) {
    length = qToBigEndian<quint32>(length + sizeof(BYTE_PACKET_HEAD));
    type = qToBigEndian<quint16>(type);
    quint16 version = qToBigEndian<quint16>(BYTE_PACKET_HEAD_VERSION);
    QDataStream stream(dst, QIODevice::WriteOnly);
    stream.writeRawData(BYTE_PACKET_HEAD_MAGIC, 4);
    stream.writeRawData((char*)(&length), sizeof(quint32));
    stream.writeRawData((char*)(&type), sizeof(quint16));
    stream.writeRawData((char*)(&version), sizeof(quint16));
}
