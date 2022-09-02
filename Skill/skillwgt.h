#ifndef SKILLWGT_H
#define SKILLWGT_H

#include "ui_skillwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"

class Tool_JsonManager;
class SkillWgt : public Tool_Widget,public Ui_SkillWgt
{
    Q_OBJECT

public:
    explicit SkillWgt(QWidget *parent = nullptr);
    ~SkillWgt();

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

#endif // SKILLWGT_H
