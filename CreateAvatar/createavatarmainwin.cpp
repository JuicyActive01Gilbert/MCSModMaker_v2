#include "createavatarmainwin.h"

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include <QMessageBox>
#include <QDebug>
#include "createavatarwgt.h"

CreateAvatarMainWin::CreateAvatarMainWin(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

CreateAvatarMainWin::~CreateAvatarMainWin()
{

}

void CreateAvatarMainWin::iniData()
{
    QString path = MOD_DATA.catchPath + "CreateAvatarJsonData.json";
    m_datas = readDatas(path);
    displayCombobox(m_pCBoxDatas,m_datas,m_DataIndex);
}

void CreateAvatarMainWin::iniSysData()
{
    QString path = MOD_PATH_SYS + "CreateAvatarJsonData.json";
    m_datasSys = readDatas(path);
    displayCombobox(m_pCBoxDatasSys,m_datasSys,m_DataIndexSys);
}

void CreateAvatarMainWin::onOpenSysData()
{
    if(m_pCBoxDatasSys->currentIndex() < 0){
        return;
    }
    QVariantMap map = m_datasSys.value(QString::number(m_DataIndexSys[m_pCBoxDatasSys->currentIndex()])).toMap();
    showDataWgt(map);
}

void CreateAvatarMainWin::onOpenData()
{
    if(m_pCBoxDatas->currentIndex() < 0){
        return;
    }
    QVariantMap map = m_datas.value(QString::number(m_DataIndex[m_pCBoxDatas->currentIndex()])).toMap();
    showDataWgt(map);
}

void CreateAvatarMainWin::onDeleteData()
{
    int index = m_pCBoxDatas->currentIndex();
    if(index < 0){
        return;
    }

    if(QMessageBox::question(nullptr,"删除",QString("确定删除天赋[%1]吗？").arg(m_pCBoxDatas->currentText()),QMessageBox::Yes,QMessageBox::No) != QMessageBox::Yes){
        return;
    }
    QString key = QString::number(m_DataIndex[m_pCBoxDatas->currentIndex()]);
    QVariantMap map = m_datas.value(key).toMap();
    QVariantList seids = map.value("seid").toList();
    QString id = map.value("id").toString();
    MOD_DATA.removeSeids(seids,MOD_DATA.catchPath + "CrateAvatarSeidJsonData/",id);

    m_datas.remove(key);
    m_pJsonMgr->writeJson(m_datas,MOD_DATA.catchPath + "CreateAvatarJsonData.json");

    iniData();
    QMessageBox::information(nullptr,"保存成功","保存成功！");
}

void CreateAvatarMainWin::onNewData()
{
    showDataWgt(QVariantMap());
}

void CreateAvatarMainWin::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);

    connect(m_pBtnOpen,SIGNAL(clicked(bool)),this,SLOT(onOpenData()));
    connect(m_pBtnOpenSys,SIGNAL(clicked(bool)),this,SLOT(onOpenSysData()));
    connect(m_pBtnNew,SIGNAL(clicked(bool)),this,SLOT(onNewData()));
    connect(m_pBtnDelete,SIGNAL(clicked(bool)),this,SLOT(onDeleteData()));
}

QVariantMap CreateAvatarMainWin::readDatas(const QString &path)
{
    return m_pJsonMgr->readJsonObj(path);;
}

void CreateAvatarMainWin::displayCombobox(QComboBox *pCombox, QVariantMap &map, QList<int> &values)
{
    pCombox->clear();
    values = MOD_DATA.mapNumberKey(map);
    QStringList lst;
    for (int key : values) {
        QString name = map.value(QString::number(key)).toMap().value("Title").toString();
        lst.append(QString::number(key) + "_" + name);
    }
    pCombox->addItems(lst);
}

void CreateAvatarMainWin::showDataWgt(const QVariantMap &map)
{
    CreateAvatarWgt *w = new CreateAvatarWgt;
    connect(w,SIGNAL(widgetOK()),this,SLOT(iniData()));
    w->setDatas(map);
    w->show();
}

