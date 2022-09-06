#include "modconfigwgt.h"
#include <QFile>
#include "Tools/tool_jsonmanager.h"
#include <QDebug>

ModConfigWgt::ModConfigWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);

    m_pBtnCancel->setProperty("ButtonColor","red");

    m_pJsonMgr = new Tool_JsonManager(this);
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
}

ModConfigWgt::~ModConfigWgt()
{

}

void ModConfigWgt::iniData()
{
    m_cfgPath = MOD_DATA.catchPath + "modConfig.json";
    if(!QFile::exists(m_cfgPath)){
        MOD_DATA.createFile(m_cfgPath);
    }
    QVariantMap map = m_pJsonMgr->readJsonObj(m_cfgPath);
    this->setDatas(map);
}

void ModConfigWgt::onOK()
{
    m_pJsonMgr->writeJson(this->getDatas(),m_cfgPath);
    emit widgetOK();
    emit showInfo(tr("保存配置成功！"));
}
