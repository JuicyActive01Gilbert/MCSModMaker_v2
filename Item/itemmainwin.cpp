#include "itemmainwin.h"

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include "itemwgt.h"
#include <QMessageBox>
#include <QDebug>

ItemMainWin::ItemMainWin(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

ItemMainWin::~ItemMainWin()
{

}

void ItemMainWin::iniData()
{
    QStringList paths = MOD_DATA.getDirFiles(MOD_DATA.catchPath + "ItemJsonData/",true);
    MOD_DATA.items = readItems(paths);
    displayCombobox(m_pCBoxDatas,MOD_DATA.items,m_itemIndex);
}

void ItemMainWin::iniSysData()
{
    QStringList paths = MOD_DATA.getDirFiles(MOD_PATH_SYS + "ItemJsonData/",true);
    MOD_DATA.items_sys = readItems(paths);
    displayCombobox(m_pCBoxDatasSys,MOD_DATA.items_sys,m_itemIndexSys);
}

void ItemMainWin::onOpenSysSkill()
{
    if(m_pCBoxDatasSys->currentIndex() < 0){
        return;
    }
    QVariantMap map = MOD_DATA.items_sys.value(QString::number(m_itemIndexSys[m_pCBoxDatasSys->currentIndex()])).toMap();
    showDataWgt(map);
}

void ItemMainWin::onOpenSkill()
{
    if(m_pCBoxDatas->currentIndex() < 0){
        return;
    }
    QVariantMap map = MOD_DATA.items.value(QString::number(m_itemIndex[m_pCBoxDatas->currentIndex()])).toMap();
    showDataWgt(map);
}

void ItemMainWin::onDeleteSkill()
{
    int index = m_pCBoxDatas->currentIndex();
    if(index < 0){
        return;
    }

    if(QMessageBox::question(nullptr,"删除",QString("确定删除物品[%1]吗？").arg(m_pCBoxDatas->currentText()),QMessageBox::Yes,QMessageBox::No) != QMessageBox::Yes){
        return;
    }

    QVariantMap map =  MOD_DATA.items.value(QString::number(m_itemIndex[m_pCBoxDatas->currentIndex()])).toMap();
    QString path = QString(MOD_DATA.catchPath + "ItemJsonData/%1.json").arg(map.value("id").toInt());
    MOD_DATA.removeFile(path);

    QString id = map.value("id").toString();
    QVariantList seids = map.value("seid").toList();
    MOD_DATA.removeSeids(seids,MOD_DATA.catchPath + "itemseidJsonData/",id);
    MOD_DATA.removeSeids(seids,MOD_DATA.catchPath + "EquipSeidJsonData/",id);
    //删除缓存图片
    MOD_DATA.removeFile(MOD_DATA.catchPath + "Assets/item icon/" + id + ".png");

    iniData();
}

void ItemMainWin::onNewSkill()
{
    showDataWgt(QVariantMap());
}

void ItemMainWin::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);

    connect(m_pBtnOpen,SIGNAL(clicked(bool)),this,SLOT(onOpenSkill()));
    connect(m_pBtnOpenSys,SIGNAL(clicked(bool)),this,SLOT(onOpenSysSkill()));
    connect(m_pBtnNew,SIGNAL(clicked(bool)),this,SLOT(onNewSkill()));
    connect(m_pBtnDelete,SIGNAL(clicked(bool)),this,SLOT(onDeleteSkill()));
}

QVariantMap ItemMainWin::readItems(const QStringList &paths)
{
    QVariantMap items;
    items.clear();
    for (QString path : paths) {
        QVariantMap map = m_pJsonMgr->readJsonObj(path);
        QString id = map.value("id").toString();
        items.insert(id,map);
    }
    return items;
}

void ItemMainWin::displayCombobox(QComboBox *pCombox, QVariantMap &map, QList<int> &values)
{
    pCombox->clear();
    values = MOD_DATA.mapNumberKey(map);
    QStringList lst;
    for (int key : values) {
        QString name = map.value(QString::number(key)).toMap().value("name").toString();
        lst.append(QString::number(key) + "_" + name);
    }
    pCombox->addItems(lst);
}

void ItemMainWin::showDataWgt(const QVariantMap &map)
{
    ItemWgt *w = new ItemWgt;
    connect(w,SIGNAL(widgetOK()),this,SLOT(iniData()));
    w->setDatas(map);
    w->show();
}
