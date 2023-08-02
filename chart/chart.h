#ifndef CHART_H
#define CHART_H

#include <QObject>
#include "qcustomplot.h"
#include <QVector>
#include <QColor>
#include <QMutex>

class Chart : public QCustomPlot
{
    Q_OBJECT
public:
    explicit Chart(QWidget *parent = nullptr);
    void setXAxisLabel(const QString& label);
    void setYAxisLabel(const QString& label);
    void addGraph(const QString& label, QColor color);
    void addData(quint32 graphId, double num);
    void setXMaxPoints(quint32 size);
    void xScroll();
    void stepX();

private:
    QVector<QVector<double>> m_arrChs;
    QVector<QCPGraph*> m_graphs;
    QMutex m_mutex;
    double m_xStep;
    double m_xCnt;
    int m_xMaxPoints;

signals:

};

#endif // CHART_H
