#ifndef AFFIXMAINWIN_H
#define AFFIXMAINWIN_H

#include "ui_affixmainwin.h"
#include <QWidget>


class Tool_JsonManager;
class AffixMainWin : public QWidget,public Ui_AffixMainWin
{
    Q_OBJECT

public:
    explicit AffixMainWin(QWidget *parent = nullptr);
    ~AffixMainWin();

public slots:
    void iniAffix();
    void iniSysAffix();
protected slots:
    void onOpenSys();
    void onOpenMy();
    void onDelete();
    void onNew();
protected:
    void initialize();
    void loadAffixComboBox(QVariantMap map,QComboBox *pCbox);
    void showDataWgt(const QVariantMap &map);
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    QVariantMap m_dataSys;
    QVariantMap m_data;

};

#endif // AFFIXMAINWIN_H
