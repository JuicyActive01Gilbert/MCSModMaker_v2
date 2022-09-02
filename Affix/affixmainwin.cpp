#include "affixmainwin.h"

#include "ModData.h"
#include "Tools/tool_jsonmanager.h"
#include "affixwgt.h"
#include <QMessageBox>

AffixMainWin::AffixMainWin(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

AffixMainWin::~AffixMainWin()
{

}

void AffixMainWin::iniAffix()
{
    m_data = m_pJsonMgr->readJsonObj(MOD_DATA.catchPath + "TuJianChunWenBen.json");
    loadAffixComboBox(m_data,m_pCBoxDatas);
}

void AffixMainWin::iniSysAffix()
{
    m_dataSys = m_pJsonMgr->readJsonObj(MOD_PATH_SYS + "TuJianChunWenBen.json");
    loadAffixComboBox(m_dataSys,m_pCBoxDatasSys);
}

void AffixMainWin::onOpenSys()
{
    if(m_pCBoxDatasSys->currentIndex() < 0){
        return;
    }

    QString idKey = m_pCBoxDatasSys->currentText().split("_").first();
    QVariantMap map = m_dataSys.value(idKey).toMap();
    showDataWgt(map);
}

void AffixMainWin::onOpenMy()
{
    if(m_pCBoxDatas->currentIndex() < 0){
        return;
    }
    QString idKey = m_pCBoxDatas->currentText().split("_").first();
    QVariantMap map = m_dataSys.value(idKey).toMap();
    showDataWgt(map);
}

void AffixMainWin::onDelete()
{
    if(QMessageBox::question(nullptr,"删除",QString("确定删除词缀[%1]吗？")
                             .arg(m_pCBoxDatas->currentText()),QMessageBox::Yes,QMessageBox::No) != QMessageBox::Yes){
        return;
    }
    QString idKey = m_pCBoxDatas->currentText().split("_").first();
    m_data.remove(idKey);
    m_pJsonMgr->writeJson(m_data,MOD_DATA.catchPath + "TuJianChunWenBen.json");
    iniAffix();
}

void AffixMainWin::onNew()
{
    showDataWgt(QVariantMap());
}

void AffixMainWin::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);

    connect(m_pBtnOpenSys,SIGNAL(clicked(bool)),this,SLOT(onOpenSys()));
    connect(m_pBtnOpen,SIGNAL(clicked(bool)),this,SLOT(onOpenMy()));
    connect(m_pBtnNew,SIGNAL(clicked(bool)),this,SLOT(onNew()));
    connect(m_pBtnDelete,SIGNAL(clicked(bool)),this,SLOT(onDelete()));
}

void AffixMainWin::loadAffixComboBox(QVariantMap map, QComboBox *pCbox)
{
    pCbox->clear();
    QList<int> values = MOD_DATA.mapNumberKey(map);
    QStringList lst;
    for (int key : values) {
        QVariantMap daMap = map.value(QString::number(key)).toMap();
        if(daMap.value("name1").toString() != "词缀"){
            continue;
        }
        QString id = daMap.value("id").toString();
        QString name = daMap.value("name2").toString();
        lst.append(QString("%1_%2").arg(id).arg(name));
    }
    pCbox->addItems(lst);
}

void AffixMainWin::showDataWgt(const QVariantMap &map)
{
    AffixWgt *w = new AffixWgt;
    connect(w,SIGNAL(widgetOK()),this,SLOT(iniAffix()));
    w->setDatas(map);
    w->show();
}

