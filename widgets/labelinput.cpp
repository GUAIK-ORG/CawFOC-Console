#include "labelinput.h"
#include <QHBoxLayout>
#include <QLabel>

LabelInput::LabelInput(QString text, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    QLabel *label = new QLabel(text);
    label->setFixedWidth(80);
    label->setAlignment(Qt::AlignRight);
    m_edit = new QLineEdit();
    m_edit->setAlignment(Qt::AlignCenter);

    layout->addWidget(label);
    layout->addWidget(m_edit);

    connect(m_edit, &QLineEdit::textChanged, [=](const QString& text){
        emit textChanged(text);
    });


    setLayout(layout);
}

void LabelInput::setText(const QString &text)
{
    m_edit->setText(text);
}

QString LabelInput::text()
{
    return m_edit->text();
}

