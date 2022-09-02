#include "affixwgt.h"

#include "ModData.h"
#include "Tools/tool_jsonmanager.h"

AffixWgt::AffixWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);
    initialize();
}

AffixWgt::~AffixWgt()
{

}

void AffixWgt::setDatas(const QVariantMap &datas)
{
    QVariantMap map = datas;
    if(map.isEmpty()){
        type->setCurrentIndex(0);
    }else{
        map.insert("type",m_affixType.indexOf(datas.value("type").toInt()));
    }

    Tool_Widget::setDatas(map);
}

QVariantMap AffixWgt::getDatas()
{
    QVariantMap data = Tool_Widget::getDatas();
    data.insert("type",m_affixType[type->currentIndex()]);

    return data;
}

void AffixWgt::onOK()
{
    QString affixID = QString::number(id->value());
    QString path = MOD_DATA.catchPath + "TuJianChunWenBen.json";
    QVariantMap map = m_pJsonMgr->readJsonObj(path);
    map.insert(affixID,getDatas());

    m_pJsonMgr->writeJson(map,path);

    emit widgetOK();
}

void AffixWgt::initialize()
{
    this->setWindowTitle("词缀");
    m_pJsonMgr = new Tool_JsonManager(this);
    MOD_DATA.iniComboxFromJson(type,
                               QApplication::applicationDirPath() + "/ConfigsJson/affix/affixType.json",
                               m_affixType);

    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
}
