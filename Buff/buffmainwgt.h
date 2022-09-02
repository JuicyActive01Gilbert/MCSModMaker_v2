#ifndef BUFFMAINWGT_H
#define BUFFMAINWGT_H

#include "ui_buffmainwgt.h"
#include <QWidget>


class Tool_JsonManager;
class BuffMainWgt : public QWidget,public Ui_BuffMainWgt
{
    Q_OBJECT

public:
    explicit BuffMainWgt(QWidget *parent = nullptr);
    ~BuffMainWgt();

    void iniSysBuffs();
public slots:
    void iniBuffs();
protected slots:
    void onOpenBuff_Sys();
    void onOpenBuff();
    void onNewBuff();
    void onDeleteBuff();

protected:
    void initialize();

    QStringList getStringList(const QVariantList &list);
    void showBuffWgt(const QVariantMap &map);
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;

};

#endif // BUFFMAINWGT_H
