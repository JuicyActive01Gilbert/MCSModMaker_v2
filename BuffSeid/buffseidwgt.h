#ifndef BUFFSEIDWGT_H
#define BUFFSEIDWGT_H

#include "ui_buffseidwgt.h"
#include <QWidget>

class Tool_JsonManager;
class BuffSeidWgt : public QWidget,public Ui_BuffSeidWgt
{
    Q_OBJECT

public:
    explicit BuffSeidWgt(QWidget *parent = nullptr);
    ~BuffSeidWgt();
    void setSeidList(QStringList text,int buffid);

protected slots:
    void onSeidChange(int index);
    void onOK();
protected:
    void initialize();
    void displayData();
private:
    int m_buffID = 0;
    QVariantMap m_seidTips;
    Tool_JsonManager *m_pJsonMgr = nullptr;

};

#endif // BUFFSEIDWGT_H
