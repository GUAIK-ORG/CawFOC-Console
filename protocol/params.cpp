#include "params.h"
#include <QDataStream>
#include <QtEndian>


void pack_params(const PARAMS_T& src, QByteArray *dst) {
    quint16 motor = qToBigEndian<quint16>(src.motor);
    QDataStream stream(dst, QIODevice::WriteOnly);
    stream.writeRawData((char*)(&motor), sizeof(quint16));
    for (int i=0; i<2; i++) {
        quint16 mode = qToBigEndian<quint16>(src.params[i].mode);
        stream.writeRawData((char*)(&mode), sizeof(quint16));
        quint16 state = qToBigEndian<quint16>(src.params[i].state);
        stream.writeRawData((char*)(&state), sizeof(quint16));

        float angle = qToBigEndian<float>(src.params[i].angle);
        stream.writeRawData((char*)(&angle), sizeof(float));

        float angleP = qToBigEndian<float>(src.params[i].angleP);
        stream.writeRawData((char*)(&angleP), sizeof(float));

        float angleI = qToBigEndian<float>(src.params[i].angleI);
        stream.writeRawData((char*)(&angleI), sizeof(float));

        float angleD = qToBigEndian<float>(src.params[i].angleD);
        stream.writeRawData((char*)(&angleD), sizeof(float));

        float velocity = qToBigEndian<float>(src.params[i].velocity);
        stream.writeRawData((char*)(&velocity), sizeof(float));

        float velocityP = qToBigEndian<float>(src.params[i].velocityP);
        stream.writeRawData((char*)(&velocityP), sizeof(float));

        float velocityI = qToBigEndian<float>(src.params[i].velocityI);
        stream.writeRawData((char*)(&velocityI), sizeof(float));

        float velocityD = qToBigEndian<float>(src.params[i].velocityD);
        stream.writeRawData((char*)(&velocityD), sizeof(float));

        float currentP = qToBigEndian<float>(src.params[i].currentP);
        stream.writeRawData((char*)(&currentP), sizeof(float));

        float currentI = qToBigEndian<float>(src.params[i].currentI);
        stream.writeRawData((char*)(&currentI), sizeof(float));

        float currentD = qToBigEndian<float>(src.params[i].currentD);
        stream.writeRawData((char*)(&currentD), sizeof(float));
    }
}
