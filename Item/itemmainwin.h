#ifndef ITEMMAINWIN_H
#define ITEMMAINWIN_H

#include "ui_itemmainwin.h"
#include <QWidget>

class Tool_JsonManager;
class ItemMainWin : public QWidget,public Ui_ItemMainWin
{
    Q_OBJECT

public:
    explicit ItemMainWin(QWidget *parent = nullptr);
    ~ItemMainWin();

public slots:
    void iniData();
    void iniSysData();

protected slots:
    void onOpenSysSkill();
    void onOpenSkill();
    void onDeleteSkill();
    void onNewSkill();

protected:
    void initialize();
    QVariantMap readItems(const QStringList &paths);
    void displayCombobox(QComboBox *pCombox,QVariantMap &map,QList<int> &values);
    void showDataWgt(const QVariantMap &map);
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    QList<int> m_itemIndexSys;
    QList<int> m_itemIndex;

};

#endif // ITEMMAINWIN_H
