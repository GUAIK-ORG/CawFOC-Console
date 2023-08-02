#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QtEndian>
#include <QDataStream>

typedef enum _PACK_TYPE {
    UNKNOWN =0x0,
    UPDATE_PARAMS,
    SEND_DATAS,
} PACK_TYPE;

#pragma pack(1)
typedef struct _BYTE_PACKET_HEAD {
    char magic[4];      // 用于识别封包起使位置
    quint32 length;     // 封包总长度
    quint16 type;       // 封包类型
    quint16 version;    // 版本
} BYTE_PACKET_HEAD;
#pragma pack()

// 协议常量定义
#define BYTE_PACKET_HEAD_SIZE ((int)sizeof(BYTE_PACKET_HEAD))
#define BYTE_PACKET_HEAD_VERSION ((quint16)0x0101)
#define BYTE_PACKET_HEAD_MAGIC "FOC!"

// 计算协议结构体字段偏移量
#define BYTE_PACKET_HEAD_LENGTH_OFFSET offsetof(BYTE_PACKET_HEAD, length)
#define BYTE_PACKET_HEAD_TYPE_OFFSET offsetof(BYTE_PACKET_HEAD, type)
#define BYTE_PACKET_HEAD_VERSION_OFFSET offsetof(BYTE_PACKET_HEAD, version)

// 解包数据头
bool unpack_head(const char* ptr, BYTE_PACKET_HEAD* head);

// 打包数据头
void pack_head(quint32 length, quint16 type, QByteArray* dst);

#endif // PROTOCOL_H
