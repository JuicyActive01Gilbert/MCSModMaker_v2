#ifndef SKILLMAINWIN_H
#define SKILLMAINWIN_H
#include "ui_skillmainwin.h"
#include <QWidget>

class Tool_JsonManager;
class SkillMainWin : public QWidget,public Ui_SkillMainWin
{
    Q_OBJECT

public:
    explicit SkillMainWin(QWidget *parent = nullptr);
    ~SkillMainWin();

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
    QVariantMap readSkills(const QStringList &paths);
    void displayCombobox(QComboBox *pCombox,QVariantMap &map,QList<int> &values);
    void showSkillWgt(const QVariantList &map);
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    QList<int> m_skillIndexSys;
    QList<int> m_skillIndex;
};

#endif // SKILLMAINWIN_H
