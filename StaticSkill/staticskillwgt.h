#ifndef STATICSKILLWGT_H
#define STATICSKILLWGT_H

#include "ui_staticskillwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"

class StaticSkillWgt : public Tool_Widget,public Ui_StaticSkillWgt
{
    Q_OBJECT

public:
    explicit StaticSkillWgt(QWidget *parent = nullptr);
    ~StaticSkillWgt();

    void setSkillData(const QVariantList &skills);

protected:
    void initialize();

    void dealResData(QVariantMap &map, bool isAdd = true);
    void displaySkillData(QVariantMap map);
    void dealSkill(QVariantMap &map, QString key, int offset = -1);
protected slots:
    void displayIcon();
    void onCustomIcon();
    void onCancel();
    void onOK();
    void onLvActivate(int index);

    void onOpenSeid();
    void onDeleteCustomIcon();
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    QVariantList m_skills;
};

#endif // STATICSKILLWGT_H
