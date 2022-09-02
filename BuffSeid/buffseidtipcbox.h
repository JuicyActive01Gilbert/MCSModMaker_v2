#ifndef BUFFSEIDTIPCBOX_H
#define BUFFSEIDTIPCBOX_H

#include <QWidget>
#include <QComboBox>

class BuffSeidTipCBox : public QComboBox
{
    Q_OBJECT
public:
    explicit BuffSeidTipCBox(QWidget *parent = nullptr);
    ~BuffSeidTipCBox();

    void initialize();
signals:

};

#endif // BUFFSEIDTIPCBOX_H
