#ifndef MAKERMAINWIN_H
#define MAKERMAINWIN_H

#include "ui_makermainwin.h"
#include <QWidget>
#include <QButtonGroup>
#include <QVBoxLayout>

#include "ModConfig/modconfigwgt.h"
#include "Buff/buffwgt.h"
#include "Skill/skillwgt.h"
#include "StaticSkill/staticskillwgt.h"
#include "Item/itemwgt.h"
#include "CreateAvatar/createavatarwgt.h"
#include "Affix/affixwgt.h"


class Tool_JsonManager;
class MakerMainWin : public QWidget,public Ui_MakerMainWin
{
    Q_OBJECT

public:
    explicit MakerMainWin(QWidget *parent = nullptr);
    ~MakerMainWin();

signals:
    void backDataWin();

public slots:
    void clearInfo();

    void onSave();
    void onDataOk();
    void onTBtnChecked(int id);
    void onShowLabInfo(QString info);
    void onSearch(QString text);

    void iniFunBtns(const QVariantList &lst, QString name, QString id);

protected slots:
    void onTabItemSelect(QTableWidgetItem *pItem);
protected:
    void initialize();
    void iniButtons();
    void iniFunWgts();

    void loadBuffs();
    void loadSkills();
    void loadStaticSkill();
    void laodItems();
    void loadCA();
    void loadAffix();

    QVariantList readFiles(const QString &dirPath, bool isSys, QString id);
    QVariantMap getDataFromID(QString val,QString key);
    QVariantList mergeSkills(QVariantList lst,QVariantList lst2);
    QVariantList readStaticSkill(const QString &path);

private:
    ModConfigWgt *m_pCfgWgt             = nullptr;
    BuffWgt *m_pBuffWgt                 = nullptr;
    SkillWgt *m_pSkillWgt               = nullptr;
    StaticSkillWgt *m_pS_SkilWgt        = nullptr;
    ItemWgt *m_pItemWgt                 = nullptr;
    CreateAvatarWgt *m_pCAWgt           = nullptr;
    AffixWgt *m_pAffixWgt               = nullptr;

    QButtonGroup *m_pBtnGroup           = nullptr;

    QVariantList m_datas;

    QString m_id                       = "";

    Tool_JsonManager *m_pJsonMgr        = nullptr;
};

#endif // MAKERMAINWIN_H
