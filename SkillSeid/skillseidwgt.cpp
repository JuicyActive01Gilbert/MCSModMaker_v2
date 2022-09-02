#include "skillseidwgt.h"

#include "ModData.h"
#include "Tools/tool_jsonmanager.h"
#include <QMessageBox>

SkillSeidWgt::SkillSeidWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);
    initialize();
}

SkillSeidWgt::~SkillSeidWgt()
{

}

void SkillSeidWgt::setSeidList(QStringList text, int skillID)
{
    m_skillID = skillID;
    m_pCBoxSeid->clear();
    m_pCBoxSeid->addItems(text);
    if(!text.isEmpty()){
        onSeidChange(0);
    }

}

void SkillSeidWgt::onSeidChange(int index)
{
    Q_UNUSED(index)
    m_pFormWgt->clearForms();
    m_pFormWgt->setDatas(QVariantMap());
    QString t = m_pCBoxSeid->currentText();
    int i = MOD_DATA.skillSeidClass.value(t).toInt() - 1;
    if(i >= 0 && i < MOD_DATA.seidFormClass.count()){
        QVariantMap map = MOD_DATA.seidFormClass[i].toMap();
        m_pFormWgt->iniForms(map.value("forms").toList());
        displayData();
    }

    m_pLabSeidTip->setText(m_seidTips.value(t).toString());
}

void SkillSeidWgt::onOK()
{
    QVariantMap map = m_pFormWgt->getDatas();
    if(map.isEmpty()){
        return;
    }
    QString seid = m_pCBoxSeid->currentText();
    QString path = QString(MOD_DATA.catchPath + "SkillSeidJsonData/%1.json").arg(seid);
    QVariantMap oldMap = m_pJsonMgr->readJsonObj(path);
    map.insert("skillid",m_skillID);
    oldMap.insert(QString::number(m_skillID),map);
    m_pJsonMgr->writeJson(oldMap,path);
    QMessageBox::information(nullptr,"保存成功","保存成功！");
}

void SkillSeidWgt::initialize()
{
    this->setWindowTitle("神通特性");
    m_pJsonMgr = new Tool_JsonManager(this);
    m_seidTips = m_pJsonMgr->readJson(QApplication::applicationDirPath() + "/ConfigsJson/skill/seidTip.json").first().toMap();

    connect(m_pCBoxSeid,SIGNAL(activated(int)),this,SLOT(onSeidChange(int)));
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
}

void SkillSeidWgt::displayData()
{
    if(m_pCBoxSeid->currentIndex() < 0){
        return;
    }
    QVariantMap map = m_pJsonMgr->readJsonObj(QString(MOD_DATA.catchPath + "SkillSeidJsonData/%1.json").arg(m_pCBoxSeid->currentText()));
    if(map.isEmpty()){
        map = m_pJsonMgr->readJsonObj(QString(MOD_PATH_SYS + "SkillSeidJsonData/%1.json").arg(m_pCBoxSeid->currentText()));
    }

    if(map.isEmpty() || !map.contains(QString::number(m_skillID))){
        return;
    }
    m_pFormWgt->setDatas(map.value(QString::number(m_skillID)).toMap());
}

