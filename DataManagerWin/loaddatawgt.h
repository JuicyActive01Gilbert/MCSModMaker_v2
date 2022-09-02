#ifndef LOADDATAWGT_H
#define LOADDATAWGT_H

#include "ui_loaddatawgt.h"
#include <QWidget>


class LoadDataWgt : public QWidget,public Ui_LoadDataWgt
{
    Q_OBJECT

public:
    explicit LoadDataWgt(QWidget *parent = nullptr);
    ~LoadDataWgt();

    void setData(const QVariantMap &data);
    QString getFlag();

protected slots:
    void onDelete();
signals:
    void pressData(QString flag);
    void deleteData(QString flag);
protected:
    void initialize();

    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    void paintEvent(QPaintEvent *event);

private:
    QVariantMap m_data;
    bool m_isHover  = false;
    QString m_flag;

};

#endif // LOADDATAWGT_H
