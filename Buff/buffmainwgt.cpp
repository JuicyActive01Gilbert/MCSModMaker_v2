#include "buffmainwgt.h"

#include <QMessageBox>

#include "ModData.h"
#include "Buff/buffwgt.h"
#include "Tools/tool_jsonmanager.h"

BuffMainWgt::BuffMainWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    initialize();
}

BuffMainWgt::~BuffMainWgt()
{

}

void BuffMainWgt::iniSysBuffs()
{
    m_pCBoxBuffSys->clear();
    m_pCBoxBuffSys->addItems(getStringList(MOD_DATA.buffs_sys));
}

void BuffMainWgt::iniBuffs()
{
    MOD_DATA.loadCurrentBuffDatas();
    m_pCBoxBuff->clear();
    m_pCBoxBuff->addItems(getStringList(MOD_DATA.buffs));
}

void BuffMainWgt::onOpenBuff_Sys()
{
    if(MOD_DATA.buffs_sys.isEmpty()){
        return;
    }
    showBuffWgt(MOD_DATA.buffs_sys[m_pCBoxBuffSys->currentIndex()].toMap());
}

void BuffMainWgt::onOpenBuff()
{
    if(!MOD_DATA.buffs.isEmpty()){
        showBuffWgt(MOD_DATA.buffs[m_pCBoxBuff->currentIndex()].toMap());
    }
}

void BuffMainWgt::onNewBuff()
{
    showBuffWgt(QVariantMap());
}

void BuffMainWgt::onDeleteBuff()
{
    int index = m_pCBoxBuff->currentIndex();
    if(index < 0){
        return;
    }

    if(QMessageBox::question(nullptr,"删除",QString("确定删除Buff[%1]吗？").arg(m_pCBoxBuff->currentText()),QMessageBox::Yes,QMessageBox::No) != QMessageBox::Yes){
        return;
    }
    QVariantMap map = MOD_DATA.buffs[m_pCBoxBuff->currentIndex()].toMap();
    QString path = QString(MOD_DATA.catchPath + "BuffJsonData/%1.json").arg(map.value("buffid").toInt());
    MOD_DATA.removeFile(path);

    QString buffID = map.value("buffid").toString();
    QVariantList seids = map.value("seid").toList();

    //删除Seid中的内容
    for (QVariant var : seids) {
        int seid = var.toInt();
        path = QString(MOD_DATA.catchPath + "BuffSeidJsonData/%1.json").arg(seid);
        QVariantMap map2 = m_pJsonMgr->readJsonObj(path);
        if(map2.contains(buffID)){
            map2.remove(buffID);
            m_pJsonMgr->writeJson(map2,path);
        }
    }

    //删除缓存图片
    MOD_DATA.removeFile(MOD_DATA.catchPath + "Assets/buff icon/" + buffID + ".png");

    iniBuffs();
}

void BuffMainWgt::initialize()
{
    this->setWindowTitle("Buff管理页面");
    m_pJsonMgr = new Tool_JsonManager(this);

    connect(m_pBtnNew,SIGNAL(clicked(bool)),this,SLOT(onNewBuff()));
    connect(m_pBtnOpen,SIGNAL(clicked(bool)),this,SLOT(onOpenBuff()));
    connect(m_pBtnOpenSys,SIGNAL(clicked(bool)),this,SLOT(onOpenBuff_Sys()));
    connect(m_pBtnDelete,SIGNAL(clicked(bool)),this,SLOT(onDeleteBuff()));

}

QStringList BuffMainWgt::getStringList(const QVariantList &list)
{
    QStringList strList;
    for (QVariant v : list) {
        QVariantMap map = v.toMap();
        QString text = QString("%1_%2").arg(map.value("buffid").toString()).arg(map.value("name").toString());
        strList.append(text);
    }

    return strList;
}

void BuffMainWgt::showBuffWgt(const QVariantMap &map)
{
    BuffWgt *w = new BuffWgt;
    connect(w,SIGNAL(buffOK()),this,SLOT(iniBuffs()));
    w->setDatas(map);
    w->show();
}
