#include "mainwidget.h"
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include <QGroupBox>

#include <QScreen>
#include <QDebug>
#include "protocol/protocol.h"

// UI界面
QWidget* MainWidget::makeLeftUI() {
    QWidget *widget = new QWidget();
    widget->setFixedWidth(250);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    QLabel *titleLabel = new QLabel("🦉 CawFOC-Console");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setFixedHeight(50);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QGroupBox *angleGroup = new QGroupBox("Angle");
    QGroupBox *velocityGroup = new QGroupBox("Velocity");
    QGroupBox *currentGroup = new QGroupBox("Current");

    QVBoxLayout *angleLayout = new QVBoxLayout();
    m_angle = new LabelInput("angle: ");
    m_angleP = new LabelInput("P: ");
    m_angleI = new LabelInput("I: ");
    m_angleD = new LabelInput("D: ");
    angleLayout->addWidget(m_angle);
    angleLayout->addWidget(m_angleP);
    angleLayout->addWidget(m_angleI);
    angleLayout->addWidget(m_angleD);
    angleGroup->setLayout(angleLayout);

    connect(m_angle, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].angle = text.toFloat();
    });
    connect(m_angleP, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].angleP = text.toFloat();
    });
    connect(m_angleI, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].angleI = text.toFloat();
    });
    connect(m_angleD, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].angleD = text.toFloat();
    });

    QVBoxLayout *velocityLayout = new QVBoxLayout();
    m_velocity = new LabelInput("velocity: ");
    m_velocityP = new LabelInput("P: ");
    m_velocityI = new LabelInput("I: ");
    m_velocityD = new LabelInput("D: ");
    velocityLayout->addWidget(m_velocity);
    velocityLayout->addWidget(m_velocityP);
    velocityLayout->addWidget(m_velocityI);
    velocityLayout->addWidget(m_velocityD);
    velocityGroup->setLayout(velocityLayout);

    connect(m_velocity, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].velocity = text.toFloat();
    });
    connect(m_velocityP, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].velocityP = text.toFloat();
    });
    connect(m_velocityI, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].velocityI = text.toFloat();
    });
    connect(m_velocityD, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].velocityD = text.toFloat();
    });

    QVBoxLayout *currentLayout = new QVBoxLayout();
    m_currentP = new LabelInput("P: ");
    m_currentI = new LabelInput("I: ");
    m_currentD = new LabelInput("D: ");
    currentLayout->addWidget(m_currentP);
    currentLayout->addWidget(m_currentI);
    currentLayout->addWidget(m_currentD);
    currentGroup->setLayout(currentLayout);

    connect(m_currentP, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].currentP = text.toFloat();
    });
    connect(m_currentI, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].currentI = text.toFloat();
    });
    connect(m_currentD, &LabelInput::textChanged, [=](const QString& text){
        m_params.params[m_params.motor].currentD = text.toFloat();
    });


    QHBoxLayout *serialSelecterLayout = new QHBoxLayout();
    QLabel *serialSelecterLabel = new QLabel("Serial selection:");
    m_serialSelecter = new QComboBox();
    m_openSerialButton = new QPushButton("OPEN");
    m_openSerialButton->setFixedWidth(50);
    serialSelecterLayout->addWidget(m_serialSelecter);
    serialSelecterLayout->addWidget(m_openSerialButton);

    connect(m_openSerialButton, &QPushButton::clicked, [=](){
        if (m_serial->open(m_serialSelecter->currentText())) {
            m_serialSelecter->setEnabled(false);
            m_openSerialButton->setEnabled(false);
        } else {
            qDebug() << "serial open filed";
        }
    });


    QLabel *motorSelecterLabel = new QLabel("Motor selection:");
    m_motorSelecter = new QComboBox();
    m_motorSelecter->addItem("Motor#A");
    m_motorSelecter->addItem("Motor#B");

    connect(m_motorSelecter,  (void(QComboBox::*)(int))&QComboBox::currentIndexChanged, [=](int index){
        m_params.motor = index;
        loadParams();
    });

    QLabel *modeSelecterLabel = new QLabel("Mode selection:");
    m_modeSelecter = new QComboBox();
    m_modeSelecter->addItem("Angle Mode");
    m_modeSelecter->addItem("Velocity Mode");

    connect(m_modeSelecter,  (void(QComboBox::*)(int))&QComboBox::currentIndexChanged, [=](int index){
        m_params.params[m_params.motor].mode = index;
    });

    QHBoxLayout *readWriteLayout = new QHBoxLayout();
    m_readParamsButton = new QPushButton("READ");
    m_writeParamsButton = new QPushButton("WRITE");
    readWriteLayout->addWidget(m_readParamsButton);
    readWriteLayout->addWidget(m_writeParamsButton);

    QHBoxLayout *startStopLayout = new QHBoxLayout();
    m_startButton = new QPushButton("START");
    m_stopButton = new QPushButton("STOP");
    startStopLayout->addWidget(m_startButton);
    startStopLayout->addWidget(m_stopButton);

    connect(m_startButton, &QPushButton::clicked, [=](){
        m_params.params[m_params.motor].state = 1;
        QByteArray body;
        pack_params(m_params, &body);
        QByteArray head;
        pack_head(sizeof(PARAMS_T), UPDATE_PARAMS, &head);
        m_serial->write(head);
        m_serial->write(body);
    });
    connect(m_stopButton, &QPushButton::clicked, [=](){
        m_params.params[m_params.motor].state = 0;
        QByteArray body;
        pack_params(m_params, &body);
        QByteArray head;
        pack_head(sizeof(PARAMS_T), UPDATE_PARAMS, &head);
        m_serial->write(head);
        m_serial->write(body);
    });

    m_updateParamsButton = new QPushButton("🛠 Update params");
    m_updateParamsButton->setFixedHeight(30);
    connect(m_updateParamsButton, &QPushButton::clicked, [=](){
        QByteArray body;
        pack_params(m_params, &body);
        QByteArray head;
        pack_head(sizeof(PARAMS_T), UPDATE_PARAMS, &head);
        m_serial->write(head);
        m_serial->write(body);
    });

    layout->addWidget(titleLabel);
    layout->addSpacing(30);
    layout->addWidget(serialSelecterLabel);
    layout->addLayout(serialSelecterLayout);
    layout->addSpacing(10);
    layout->addLayout(readWriteLayout);
    layout->addSpacing(10);
    layout->addWidget(motorSelecterLabel);
    layout->addWidget(m_motorSelecter);
    layout->addSpacing(10);
    layout->addWidget(modeSelecterLabel);
    layout->addWidget(m_modeSelecter);
    layout->addSpacing(10);
    layout->addWidget(angleGroup);
    layout->addSpacing(10);
    layout->addWidget(velocityGroup);
    layout->addSpacing(10);
    layout->addWidget(currentGroup);
    layout->addSpacing(10);
    layout->addLayout(startStopLayout);
    layout->addWidget(m_updateParamsButton);
    layout->addStretch();

    widget->setLayout(layout);

    return widget;
}

QWidget* MainWidget::makeRightUI() {
    QWidget *widget = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    m_angleChart = new Chart();
    m_angleChart->addGraph("Motor#A", Qt::green);
    m_angleChart->addGraph("Motor#B", Qt::red);
    m_angleChart->yAxis->setRange(-5, 5);

    m_velocityChart = new Chart();
    m_velocityChart->addGraph("Motor#A", Qt::green);
    m_velocityChart->addGraph("Motor#B", Qt::red);
    m_velocityChart->yAxis->setRange(-50, 50);

    m_motorACurrentChart = new Chart();
    m_motorACurrentChart->addGraph("Phase#A", Qt::green);
    m_motorACurrentChart->addGraph("Phase#B", Qt::red);
    m_motorACurrentChart->addGraph("Phase#C", Qt::yellow);

    m_motorBCurrentChart = new Chart();
    m_motorBCurrentChart->addGraph("Phase#A", Qt::green);
    m_motorBCurrentChart->addGraph("Phase#B", Qt::red);
    m_motorBCurrentChart->addGraph("Phase#C", Qt::yellow);

    m_angleChart->setYAxisLabel("Angle");
    m_velocityChart->setYAxisLabel("Velocity");
    m_motorACurrentChart->setYAxisLabel("Motor [A] Current");
    m_motorBCurrentChart->setYAxisLabel("Motor [B] Current");

    layout->addWidget(m_angleChart);
    layout->addWidget(m_velocityChart);
    layout->addWidget(m_motorACurrentChart);
    layout->addWidget(m_motorBCurrentChart);
//    layout->addStretch();
    widget->setLayout(layout);
    return widget;
}

void MainWidget::loadParams()
{
    m_motorSelecter->setCurrentIndex(m_params.motor);
    m_modeSelecter->setCurrentIndex(m_params.params[m_params.motor].mode);
    m_angle->setText(QString::asprintf("%f", m_params.params[m_params.motor].angle));
    m_angleP->setText(QString::asprintf("%f", m_params.params[m_params.motor].angleP));
    m_angleI->setText(QString::asprintf("%f", m_params.params[m_params.motor].angleI));
    m_angleD->setText(QString::asprintf("%f", m_params.params[m_params.motor].angleD));

    m_velocity->setText(QString::asprintf("%f", m_params.params[m_params.motor].velocity));
    m_velocityP->setText(QString::asprintf("%f", m_params.params[m_params.motor].velocityP));
    m_velocityI->setText(QString::asprintf("%f", m_params.params[m_params.motor].velocityI));
    m_velocityD->setText(QString::asprintf("%f", m_params.params[m_params.motor].velocityD));

    m_currentP->setText(QString::asprintf("%f", m_params.params[m_params.motor].currentP));
    m_currentI->setText(QString::asprintf("%f", m_params.params[m_params.motor].currentI));
    m_currentD->setText(QString::asprintf("%f", m_params.params[m_params.motor].currentD));
}


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(1000, 800);
    setWindowTitle("GUAIK-ORG");

    QScreen *screen = qApp->primaryScreen();
    move(screen->size().width() / 2.0 - this->width() / 2.0,
         screen->size().height() / 2.0 - this->height() / 2.0);

    memset(&m_params, 0, sizeof(PARAMS_T));

    // 配置总体布局
    QHBoxLayout *rootLayout = new QHBoxLayout();
    rootLayout->setSpacing(0);
    rootLayout->setMargin(0);

    rootLayout->addWidget(makeLeftUI());
    rootLayout->addWidget(makeRightUI());

    m_ds = new DataSource();
    connect(m_ds, &DataSource::parseDataFinish, this, &MainWidget::onParseDataFinish);

    m_serial = new Serial();
    m_serial->updateItems();
    m_serialSelecter->addItems(m_serial->getItems().keys());
    connect(m_serial, &Serial::recvData, m_ds, &DataSource::onRecvData);


    loadParams();

    this->setLayout(rootLayout);
}

MainWidget::~MainWidget()
{
}

// 重写paintEvent函数用来自定义主窗体背景色
void MainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QColor color(30, 30, 30);
    painter.setBrush(color);
    painter.drawRect(this->rect());
}

void MainWidget::onParseDataFinish(const DATAS_T &data)
{
    for (int i=0; i<2; i++) {
        m_angleChart->addData(i, fmod(data.datas[i].angle, 3.141592654));
        m_velocityChart->addData(i, data.datas[i].velocity);
    }
    m_angleChart->stepX();
    m_velocityChart->stepX();
    m_angleChart->xScroll();
    m_velocityChart->xScroll();
    m_angleChart->replot(QCustomPlot::rpQueuedReplot);
    m_velocityChart->replot(QCustomPlot::rpQueuedReplot);
}

