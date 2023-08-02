#include "chart.h"
#include <QDebug>
#include <QApplication>

Chart::Chart(QWidget *parent)
    : QCustomPlot{parent}
{
    this->setMinimumHeight(200);
    setOpenGl(false);

    setLocale(QLocale(QLocale::English,QLocale::UnitedKingdom));

    m_xStep = 1;
    m_xCnt = 0.0;
    m_xMaxPoints = 500;

//    addGraph();
//    graph(0)->setPen(QPen(Qt::green, 1));
//    graph(0)->setName("Motor#A");

//    addGraph();
//    graph(1)->setPen(QPen(Qt::red, 1));
//    graph(1)->setName("Motor#B");

//    graph(0)->setPen(QPen(Qt::green));
//    xAxis->setRange(0, m_xMaxPoints);
//    yAxis->setRange(-3, 3);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(0x2e, 0x36, 0x48));
    plotGradient.setColorAt(1, QColor(0x2e, 0x36, 0x48));
    setBackground(plotGradient);      // 设置背景颜色

    xAxis->setBasePen(QPen(Qt::white, 1));  // 轴线的画笔
    xAxis->setTickPen(QPen(Qt::white, 1));  // 轴刻度线的画笔
    xAxis->setSubTickPen(QPen(Qt::white, 1)); // 轴子刻度线的画笔
    xAxis->setTickLabelColor(Qt::white);  // 轴刻度文字颜色
    xAxis->setLabelColor(Qt::white);   // 轴标签颜色
    xAxis->setTickLengthIn(3);       // 轴线内刻度的长度
    xAxis->setTickLengthOut(5);      // 轴线外刻度的长度
    xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    yAxis->setBasePen(QPen(Qt::white, 1));  // 轴线的画笔
    yAxis->setTickPen(QPen(Qt::white, 1));  // 轴刻度线的画笔
    yAxis->setSubTickPen(QPen(Qt::white, 1)); // 轴子刻度线的画笔
    yAxis->setTickLabelColor(Qt::white);  // 轴刻度文字颜色
    yAxis->setLabelColor(Qt::white);   // 轴标签颜色
    yAxis->setTickLengthIn(3);       // 轴线内刻度的长度
    yAxis->setTickLengthOut(5);      // 轴线外刻度的长度
    yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    // 每条网格对应一个刻度
    xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));     // 网格线(对应刻度)画笔
    yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine)); // 子网格线(对应子刻度)画笔
//    yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    xAxis->grid()->setSubGridVisible(false);     // 显示子网格线
    yAxis->grid()->setSubGridVisible(false);
//    xAxis->grid()->setZeroLinePen(QPen(Qt::red));   // 设置刻度为0时的网格线的画笔
//    yAxis->grid()->setZeroLinePen(QPen(Qt::red));

//    xAxis->setLabel("Date");
//    yAxis->setLabel("Random wobbly lines value");
    legend->setVisible(true);
    legend->setBrush(QColor(0x0,0x0,0x0,150));
    legend->setTextColor(QColor(0xff,0xff,0xff));
}

void Chart::setXAxisLabel(const QString &label)
{
    xAxis->setLabel(label);
}

void Chart::setYAxisLabel(const QString &label)
{
    yAxis->setLabel(label);
}

void Chart::addGraph(const QString &label,QColor color)
{
    QCustomPlot::addGraph();
    graph(graphCount() - 1)->setPen(QPen(color, 1));
    graph(graphCount() - 1)->setName(label);
}

void Chart::addData(quint32 graphId, double num)
{
    graph(graphId)->addData(m_xCnt, num);
}

void Chart::setXMaxPoints(quint32 size)
{
    m_xMaxPoints = size;
}

void Chart::xScroll()
{
    if (graph(0)->dataCount() > m_xMaxPoints) {
        xAxis->setRange(graph(0)->dataCount() - m_xMaxPoints, graph(0)->dataCount());
    } else {
        xAxis->setRange(0, m_xMaxPoints);
    }
}

void Chart::stepX()
{
    m_xCnt += m_xStep;
}

