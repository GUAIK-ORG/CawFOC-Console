#ifndef LABELINPUT_H
#define LABELINPUT_H

#include <QWidget>
#include <QLineEdit>

class LabelInput : public QWidget
{
    Q_OBJECT
public:
    explicit LabelInput(QString text, QWidget *parent = nullptr);
    void setText(const QString& text);
    QString text();


protected:


private:
    QLineEdit *m_edit;

signals:
    void textChanged(const QString& text);
};

#endif // LABELINPUT_H
