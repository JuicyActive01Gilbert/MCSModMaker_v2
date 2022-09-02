#ifndef CREATEAVATARMAINWIN_H
#define CREATEAVATARMAINWIN_H

#include "ui_createavatarmainwin.h"
#include <QWidget>

class Tool_JsonManager;
class CreateAvatarMainWin : public QWidget,public Ui_CreateAvatarMainWin
{
    Q_OBJECT

public:
    explicit CreateAvatarMainWin(QWidget *parent = nullptr);
    ~CreateAvatarMainWin();
public slots:
    void iniData();
    void iniSysData();

protected slots:
    void onOpenSysData();
    void onOpenData();
    void onDeleteData();
    void onNewData();

protected:
    void initialize();
    QVariantMap readDatas(const QString &path);
    void displayCombobox(QComboBox *pCombox,QVariantMap &map,QList<int> &values);
    void showDataWgt(const QVariantMap &map);
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    QVariantMap m_datasSys;
    QVariantMap m_datas;
    QList<int> m_DataIndexSys;
    QList<int> m_DataIndex;

};

#endif // CREATEAVATARMAINWIN_H
