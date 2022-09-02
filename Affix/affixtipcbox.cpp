#include "affixtipcbox.h"

#include <QApplication>

#include "ModData.h"
#include "Tools/tool_jsonmanager.h"

AffixTipCBox::AffixTipCBox(QWidget *parent) : QComboBox(parent)
{
    m_pJsonMgr = new Tool_JsonManager(this);
}

AffixTipCBox::~AffixTipCBox()
{

}

void AffixTipCBox::initialize()
{
    this->clear();
    QVariantMap map = m_pJsonMgr->readJsonObj(MOD_PATH_SYS + "TuJianChunWenBen.json");
    QVariantMap myMap = m_pJsonMgr->readJsonObj(MOD_DATA.catchPath + "TuJianChunWenBen.json");
    QStringList keys = myMap.keys();
    foreach (QString key, keys) {
        map.insert(key,myMap.value(key).toString());
    }

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
    this->addItems(lst);
}
