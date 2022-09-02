#ifndef SKILLSEIDWGT_H
#define SKILLSEIDWGT_H

#include "ui_skillseidwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"

class Tool_JsonManager;
class SkillSeidWgt : public Tool_Widget,public Ui_SkillSeidWgt
{
    Q_OBJECT

public:
    explicit SkillSeidWgt(QWidget *parent = nullptr);
    ~SkillSeidWgt();

    void setSeidList(QStringList text,int skillID);

protected slots:
    void onSeidChange(int index);
    void onOK();
protected:
    void initialize();
    void displayData();
private:
    int m_skillID = 0;
    QVariantMap m_seidTips;
    Tool_JsonManager *m_pJsonMgr = nullptr;

};

#endif // SKILLSEIDWGT_H
