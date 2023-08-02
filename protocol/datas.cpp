#include "datas.h"
#include <QtEndian>

void unpack_datas(DATAS_T* datas) {
    for (int i=0; i<2; i++) {
        datas->datas[i].angle = qFromBigEndian<float>(datas->datas[i].angle);
        datas->datas[i].velocity = qFromBigEndian<float>(datas->datas[i].velocity);
        datas->datas[i].current[0] = qFromBigEndian<float>(datas->datas[i].current[0]);
        datas->datas[i].current[1] = qFromBigEndian<float>(datas->datas[i].current[1]);
        datas->datas[i].current[2] = qFromBigEndian<float>(datas->datas[i].current[2]);
    }
}
