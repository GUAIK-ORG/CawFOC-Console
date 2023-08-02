#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "chart/chart.h"
#include "widgets/labelinput.h"
#include <QPushButton>
#include <QComboBox>
#include "serial.h"
#include "datasource.h"
#include "protocol/params.h"
#include "protocol/datas.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QWidget* makeLeftUI();
    QWidget* makeRightUI();

private:
    PARAMS_T m_params;

    Serial *m_serial;
    DataSource *m_ds;

    Chart *m_angleChart;
    Chart *m_velocityChart;
    Chart *m_motorACurrentChart;
    Chart *m_motorBCurrentChart;

    QComboBox *m_serialSelecter;

    QComboBox *m_motorSelecter;
    QComboBox *m_modeSelecter;

    QPushButton *m_readParamsButton;
    QPushButton *m_writeParamsButton;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QPushButton *m_openSerialButton;
    QPushButton *m_updateParamsButton;

    LabelInput *m_angle;
    LabelInput *m_angleP;
    LabelInput *m_angleI;
    LabelInput *m_angleD;

    LabelInput *m_velocity;
    LabelInput *m_velocityP;
    LabelInput *m_velocityI;
    LabelInput *m_velocityD;

    LabelInput *m_currentP;
    LabelInput *m_currentI;
    LabelInput *m_currentD;

private:
    void loadParams();          // 将Params中的数据更新到界面

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void onParseDataFinish(const DATAS_T& data);
};
#endif // MAINWIDGET_H
