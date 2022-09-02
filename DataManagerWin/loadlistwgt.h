#ifndef LOADLISTWGT_H
#define LOADLISTWGT_H

#include <QWidget>
#include <QVBoxLayout>
#include "loaddatawgt.h"

class LoadListWgt : public QWidget
{
    Q_OBJECT
public:
    explicit LoadListWgt(QWidget *parent = nullptr);
    ~LoadListWgt();

public slots:
    void setDatas(QVariantMap map);
    void addData(const QVariantMap &data);
    void removeData(QString flag);
    int maxIndex();

    void clearDatas();
signals:
    void clickedData(QVariantMap data);
    void loadMod();
protected slots:
    void onDataClick(QString flag);
protected:
    void initialize();
    void updateUIs();
    void addEmpty(QVariantMap map);
    void saveData();
private:
    QVector<LoadDataWgt*> m_vecLoadDataWgts;
    QVBoxLayout *m_pLayout = nullptr;
    QVariantMap m_datas;
    QList<int> m_indices;
};

#endif // LOADLISTWGT_H
