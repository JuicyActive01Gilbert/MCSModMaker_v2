#include "buffseidwgt.h"

#include "ModData.h"
#include "Tools/tool_jsonmanager.h"
#include <QMessageBox>

BuffSeidWgt::BuffSeidWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

BuffSeidWgt::~BuffSeidWgt()
{

}

void BuffSeidWgt::setSeidList(QStringList text, int buffid)
{
    m_buffID = buffid;
    m_pCBoxSeid->clear();
    m_pCBoxSeid->addItems(text);
    if(!text.isEmpty()){
        onSeidChange(0);
    }

}

void BuffSeidWgt::onSeidChange(int index)
{
    Q_UNUSED(index)
    m_pFormWgt->clearForms();
    m_pFormWgt->setDatas(QVariantMap());
    QString t = m_pCBoxSeid->currentText();
    int i = MOD_DATA.buffSeidClass.value(t).toInt() - 1;
    if(i >= 0 && i < MOD_DATA.seidFormClass.count()){
        QVariantMap map = MOD_DATA.seidFormClass[i].toMap();
        m_pFormWgt->iniForms(map.value("forms").toList());
        displayData();
    }

    m_pLabSeidTip->setText(m_seidTips.value(t).toString());
}

void BuffSeidWgt::onOK()
{
    QVariantMap map = m_pFormWgt->getDatas();
    if(map.isEmpty()){
        return;
    }
    QString seid = m_pCBoxSeid->currentText();
    QString path = QString(MOD_DATA.catchPath + "BuffSeidJsonData/%1.json").arg(seid);
    QVariantMap oldMap = m_pJsonMgr->readJsonObj(path);
    map.insert("id",m_buffID);
    oldMap.insert(QString::number(m_buffID),map);
    m_pJsonMgr->writeJson(oldMap,path);
    MOD_DATA.loadCurrentBuffDatas();
    QMessageBox::information(nullptr,"保存成功","保存成功！");
}

void BuffSeidWgt::initialize()
{
    this->setWindowTitle("Buff特性");
    m_pJsonMgr = new Tool_JsonManager(this);
    m_seidTips = m_pJsonMgr->readJson(QApplication::applicationDirPath() + "/ConfigsJson/buff/seidTip.json").first().toMap();

    connect(m_pCBoxSeid,SIGNAL(activated(int)),this,SLOT(onSeidChange(int)));
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
}

void BuffSeidWgt::displayData()
{
    if(m_pCBoxSeid->currentIndex() < 0){
        return;
    }
    QVariantMap map = m_pJsonMgr->readJsonObj(QString(MOD_DATA.catchPath + "BuffSeidJsonData/%1.json").arg(m_pCBoxSeid->currentText()));
    if(map.isEmpty()){
        map = m_pJsonMgr->readJsonObj(QString(MOD_PATH_SYS + "BuffSeidJsonData/%1.json").arg(m_pCBoxSeid->currentText()));
    }

    if(map.isEmpty() || !map.contains(QString::number(m_buffID))){
        return;
    }
    m_pFormWgt->setDatas(map.value(QString::number(m_buffID)).toMap());
}

