#ifndef DATAS_H
#define DATAS_H

#include <QObject>

#pragma pack(1)
typedef struct {
  float angle;
  float velocity;
  float current[3];
} MOTOR_DATA_T;
#pragma pack()

#pragma pack(1)
typedef struct {
  MOTOR_DATA_T datas[2];
} DATAS_T;
#pragma pack()

void unpack_datas(DATAS_T* datas);

#endif // DATAS_H
