#include "staticskillmainwin.h"

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include "staticskillwgt.h"
#include <QMessageBox>
#include <QDebug>

StaticSkillMainWin::StaticSkillMainWin(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

StaticSkillMainWin::~StaticSkillMainWin()
{

}

void StaticSkillMainWin::iniSkill()
{
    MOD_DATA.staticSkills = readSkills(MOD_DATA.catchPath + "StaticSkillJsonData.json");
    displayCombobox(m_pCBoxDatas,MOD_DATA.staticSkills,m_skillIndex);
}

void StaticSkillMainWin::iniSysSkill()
{
    MOD_DATA.staticSkills_sys = readSkills(MOD_PATH_SYS + "StaticSkillJsonData.json");
    displayCombobox(m_pCBoxDatasSys,MOD_DATA.staticSkills_sys,m_skillIndexSys);
}

void StaticSkillMainWin::onOpenSysSkill()
{
    if(m_pCBoxDatasSys->currentIndex() < 0){
        return;
    }
    QVariantList lst = MOD_DATA.staticSkills_sys.value(QString::number(m_skillIndexSys[m_pCBoxDatasSys->currentIndex()])).toList();
    showSkillWgt(lst);
}

void StaticSkillMainWin::onOpenSkill()
{
    if(m_pCBoxDatas->currentIndex() < 0){
        return;
    }
    QVariantList lst = MOD_DATA.staticSkills.value(QString::number(m_skillIndex[m_pCBoxDatas->currentIndex()])).toList();
    showSkillWgt(lst);
}

void StaticSkillMainWin::onDeleteSkill()
{
    int index = m_pCBoxDatas->currentIndex();
    if(index < 0){
        return;
    }

    if(QMessageBox::question(nullptr,"删除",QString("确定删除功法[%1]吗？").arg(m_pCBoxDatas->currentText()),QMessageBox::Yes,QMessageBox::No) != QMessageBox::Yes){
        return;
    }
    QVariantList skills = MOD_DATA.staticSkills.value(QString::number(m_skillIndex[m_pCBoxDatas->currentIndex()])).toList();

    QString modPath = MOD_DATA.catchPath + "StaticSkillJsonData.json";
    QVariantMap map2 = m_pJsonMgr->readJsonObj(modPath);
    for (QVariant var  : skills) {
        QVariantMap map = var.toMap();
        QString skillID = map.value("id").toString();
        QString skillGid = map.value("Skill_ID").toString();
        QVariantList seids = map.value("seid").toList();
        map2.remove(skillID);

        MOD_DATA.removeSeids(seids,MOD_DATA.catchPath + "StaticSkillSeidJsonData/",skillID);
        //删除缓存图片
        MOD_DATA.removeFile(MOD_DATA.catchPath + "Assets/staticskill icon/" + skillGid + ".png");
    }
    m_pJsonMgr->writeJson(map2,modPath);

    iniSkill();
}

void StaticSkillMainWin::onNewSkill()
{
    showSkillWgt(QVariantList());
}

void StaticSkillMainWin::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);

    connect(m_pBtnOpen,SIGNAL(clicked(bool)),this,SLOT(onOpenSkill()));
    connect(m_pBtnOpenSys,SIGNAL(clicked(bool)),this,SLOT(onOpenSysSkill()));
    connect(m_pBtnNew,SIGNAL(clicked(bool)),this,SLOT(onNewSkill()));
    connect(m_pBtnDelete,SIGNAL(clicked(bool)),this,SLOT(onDeleteSkill()));
}

QVariantMap StaticSkillMainWin::readSkills(const QString &path)
{
    QVariantMap skills;
    skills.clear();
    QVariantMap mapAll = m_pJsonMgr->readJsonObj(path);
    QStringList keys = mapAll.keys();
    for (QString key : keys) {
        QVariantMap map = mapAll.value(key).toMap();
        QString skillID = map.value("Skill_ID").toString();
        QVariantList sks;
        if(skills.contains(skillID)){
            sks = skills.value(skillID).toList();
        }
        sks.append(map);
        skills.insert(skillID,sks);
    }

    return skills;
}

void StaticSkillMainWin::displayCombobox(QComboBox *pCombox, QVariantMap &map, QList<int> &values)
{
    pCombox->clear();
    values = MOD_DATA.mapNumberKey(map);
    QStringList lst;
    for (int key : values) {
        QString name = map.value(QString::number(key)).toList().first().toMap().value("name").toString();
        lst.append(QString::number(key) + "_" + name.replace( QRegExp("[1-5]"),""));
    }
    pCombox->addItems(lst);
}

void StaticSkillMainWin::showSkillWgt(const QVariantList &map)
{
    StaticSkillWgt *w = new StaticSkillWgt;
    connect(w,SIGNAL(widgetOK()),this,SLOT(iniSkill()));
    w->setSkillData(map);
    w->show();
}
