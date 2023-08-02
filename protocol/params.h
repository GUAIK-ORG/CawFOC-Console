#ifndef PARAMS_H
#define PARAMS_H

#include <QObject>

#pragma pack(1)
typedef struct {
    quint16 mode;
    quint16 state;
    float angle;
    float angleP;
    float angleI;
    float angleD;
    float velocity;
    float velocityP;
    float velocityI;
    float velocityD;
    float currentP;
    float currentI;
    float currentD;
} MOTOR_PARAM_T;
#pragma pack()

#pragma pack(1)
typedef struct {
    quint16 motor;
    MOTOR_PARAM_T params[2];
} PARAMS_T;
#pragma pack()

void pack_params(const PARAMS_T& src, QByteArray *dst);

#endif // PARAMS_H
