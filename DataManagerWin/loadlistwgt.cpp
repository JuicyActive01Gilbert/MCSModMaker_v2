#include "loadlistwgt.h"

#include <QDebug>
#include <QPainter>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>

#include "loaddatawgt.h"
#include "ModData.h"

#include "ModConfig/modconfigwgt.h"
#include "../Tools/tool_dialog.h"

LoadListWgt::LoadListWgt(QWidget *parent) : QWidget(parent)
{
    initialize();
}

LoadListWgt::~LoadListWgt()
{
    clearDatas();
}

void LoadListWgt::setDatas(QVariantMap map)
{
    clearDatas();
    m_indices = MOD_DATA.mapNumberKey(map);
    m_datas = map;
    updateUIs();
}

void LoadListWgt::addData(const QVariantMap &data)
{
    m_datas.insert(data.value("flag").toString(),data);
    setDatas(m_datas);
}

void LoadListWgt::removeData(QString flag)
{
    m_datas.remove(flag);
    setDatas(m_datas);
    saveData();
}

int LoadListWgt::maxIndex()
{
    if(m_indices.isEmpty()){
        return -1;
    }
    return m_indices.last();
}

void LoadListWgt::clearDatas()
{
    for (LoadDataWgt *p : m_vecLoadDataWgts) {
        disconnect(p,SIGNAL(pressData(QString)),this,SLOT(onDataClick(QString)));
        m_pLayout->removeWidget(p);
        p->deleteLater();
        p = nullptr;
    }
    m_vecLoadDataWgts.clear();
}

void LoadListWgt::onDataClick(QString flag)
{
    QVariantMap dataMap;
    QVariantMap cfg;
    QString path;
    if(flag.isEmpty()){
        path = QFileDialog::getExistingDirectory(nullptr,"选择MOD所在文件夹",
                                                         "C:/",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
        if(path.isEmpty()){
            return;
        }
        path += "/";
        cfg = MOD_DATA.loadJson(path + "modConfig.json");
        if(cfg.isEmpty()){
            ModConfigWgt *pW = new ModConfigWgt;
            Tool_Dialog dlg(pW);
            if(dlg.exec() == QDialog::Accepted ){
                cfg = pW->getDatas();
            }else{
                return;
            }
        }
        flag = QString::number(maxIndex() + 1);
        dataMap.insert("flag",flag);
        dataMap.insert("time",MOD_DATA.currentDateTimeStr());
        dataMap.insert("name",cfg.value("Name").toString());
        dataMap.insert("path",path);
        this->addData(dataMap);
        saveData();
    }else{
        path = m_datas.value(flag).toMap().value("path").toString();
    }

    MOD_DATA.clearCatches();
    MOD_DATA.modPath = path;
    MOD_DATA.catchPath = CATCH_PATH + MOD_DATA.uuid() + "/";
    if(!MOD_DATA.copyDirectory(MOD_DATA.modPath,MOD_DATA.catchPath)){
        QMessageBox::warning(nullptr,"错误","加载MOD失败。");
        return;
    }
    emit loadMod();
}

void LoadListWgt::initialize()
{
    this->setProperty("WidgetColor","Transparent");
    m_pLayout = new QVBoxLayout;
    this->setLayout(m_pLayout);

    updateUIs();
}

void LoadListWgt::updateUIs()
{
    int maxNum = m_datas.count() >= 8 ? m_datas.count() + 1 : 8;

    for(int i:m_indices){
        addEmpty(m_datas.value(QString::number(i)).toMap());
    }

    for (int i = m_datas.count(); i < maxNum; ++i) {
        addEmpty(QVariantMap());
    }
}

void LoadListWgt::addEmpty(QVariantMap map)
{
    LoadDataWgt *pWgt = new LoadDataWgt;
    pWgt->setData(map);
    m_pLayout->addWidget(pWgt);
    m_vecLoadDataWgts.append(pWgt);
    connect(pWgt,SIGNAL(pressData(QString)),this,SLOT(onDataClick(QString)));
    connect(pWgt,SIGNAL(deleteData(QString)),this,SLOT(removeData(QString)));
}

void LoadListWgt::saveData()
{
    MOD_DATA.writeJson(m_datas,CFG_PATH + "savedatas/save.json");
}

