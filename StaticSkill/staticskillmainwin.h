#ifndef STATICSKILLMAINWIN_H
#define STATICSKILLMAINWIN_H

#include "ui_staticskillmainwin.h"
#include <QWidget>


class Tool_JsonManager;
class StaticSkillMainWin : public QWidget,public Ui_StaticSkillMainWin
{
    Q_OBJECT

public:
    explicit StaticSkillMainWin(QWidget *parent = nullptr);
    ~StaticSkillMainWin();

public slots:
    void iniSkill();
    void iniSysSkill();

protected slots:
    void onOpenSysSkill();
    void onOpenSkill();
    void onDeleteSkill();
    void onNewSkill();

protected:
    void initialize();
    QVariantMap readSkills(const QString &path);
    void displayCombobox(QComboBox *pCombox,QVariantMap &map,QList<int> &values);
    void showSkillWgt(const QVariantList &map);
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    QList<int> m_skillIndexSys;
    QList<int> m_skillIndex;

};

#endif // STATICSKILLMAINWIN_H
