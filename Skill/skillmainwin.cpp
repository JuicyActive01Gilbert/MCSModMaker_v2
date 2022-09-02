#include "skillmainwin.h"

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include "skillwgt.h"
#include <QMessageBox>
#include <QDebug>

SkillMainWin::SkillMainWin(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

SkillMainWin::~SkillMainWin()
{

}

void SkillMainWin::iniSkill()
{
    QStringList paths = MOD_DATA.getDirFiles(MOD_DATA.catchPath + "skillJsonData/",true);
    MOD_DATA.skills = readSkills(paths);
    displayCombobox(m_pCBoxDatas,MOD_DATA.skills,m_skillIndex);
}

void SkillMainWin::iniSysSkill()
{
    QStringList paths = MOD_DATA.getDirFiles(MOD_PATH_SYS + "skillJsonData/",true);
    MOD_DATA.skills_sys = readSkills(paths);
    displayCombobox(m_pCBoxDatasSys,MOD_DATA.skills_sys,m_skillIndexSys);
}

void SkillMainWin::onOpenSysSkill()
{
    if(m_pCBoxDatasSys->currentIndex() < 0){
        return;
    }
    QVariantList lst = MOD_DATA.skills_sys.value(QString::number(m_skillIndexSys[m_pCBoxDatasSys->currentIndex()])).toList();
    showSkillWgt(lst);
}

void SkillMainWin::onOpenSkill()
{
    if(m_pCBoxDatas->currentIndex() < 0){
        return;
    }
    QVariantList lst = MOD_DATA.skills.value(QString::number(m_skillIndex[m_pCBoxDatas->currentIndex()])).toList();
    showSkillWgt(lst);
}

void SkillMainWin::onDeleteSkill()
{
    int index = m_pCBoxDatas->currentIndex();
    if(index < 0){
        return;
    }

    if(QMessageBox::question(nullptr,"删除",QString("确定删除神通[%1]吗？").arg(m_pCBoxDatas->currentText()),QMessageBox::Yes,QMessageBox::No) != QMessageBox::Yes){
        return;
    }
    QVariantList skills = MOD_DATA.skills.value(QString::number(m_skillIndex[m_pCBoxDatas->currentIndex()])).toList();

    for (QVariant var  : skills) {
        QVariantMap map = var.toMap();

        QString path = QString(MOD_DATA.catchPath + "skillJsonData/%1.json").arg(map.value("id").toInt());
        MOD_DATA.removeFile(path);

        QString skillID = map.value("id").toString();
        QString skillGid = map.value("Skill_ID").toString();
        QVariantList seids = map.value("seid").toList();
        //删除Seid中的内容
        for (QVariant var : seids) {
            int seid = var.toInt();
            path = QString(MOD_DATA.catchPath + "SkillSeidJsonData/%1.json").arg(seid);
            QVariantMap map2 = m_pJsonMgr->readJsonObj(path);
            if(map2.contains(skillID)){
                map2.remove(skillID);
                m_pJsonMgr->writeJson(map2,path);
            }
        }
        //删除缓存图片
        MOD_DATA.removeFile(MOD_DATA.catchPath + "Assets/skill icon/" + skillGid + ".png");
    }

    iniSkill();
}

void SkillMainWin::onNewSkill()
{
    showSkillWgt(QVariantList());
}

void SkillMainWin::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);

    connect(m_pBtnOpen,SIGNAL(clicked(bool)),this,SLOT(onOpenSkill()));
    connect(m_pBtnOpenSys,SIGNAL(clicked(bool)),this,SLOT(onOpenSysSkill()));
    connect(m_pBtnNew,SIGNAL(clicked(bool)),this,SLOT(onNewSkill()));
    connect(m_pBtnDelete,SIGNAL(clicked(bool)),this,SLOT(onDeleteSkill()));
}

QVariantMap SkillMainWin::readSkills(const QStringList &paths)
{
    QVariantMap skills;
    skills.clear();
    for (QString path : paths) {
        QVariantMap map = m_pJsonMgr->readJsonObj(path);
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

void SkillMainWin::displayCombobox(QComboBox *pCombox, QVariantMap &map, QList<int> &values)
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

void SkillMainWin::showSkillWgt(const QVariantList &map)
{
    SkillWgt *w = new SkillWgt;
    connect(w,SIGNAL(widgetOK()),this,SLOT(iniSkill()));
    w->setSkillData(map);
    w->show();
}
