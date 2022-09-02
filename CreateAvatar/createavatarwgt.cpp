#include "createavatarwgt.h"

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"

#include "CreateAvatarSeid/createavatarseidwgt.h"

CreateAvatarWgt::CreateAvatarWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);
    initialize();
}

CreateAvatarWgt::~CreateAvatarWgt()
{

}

void CreateAvatarWgt::setDatas(const QVariantMap &datas)
{
    QVariantMap map = datas;
    int f = datas.value("fenLeiGuanLian").toInt();
    f = f > 4 ? f - 2 : f - 1;

    map.insert("fenLeiGuanLian",f);
    Tool_Widget::setDatas(map);
}

QVariantMap CreateAvatarWgt::getDatas()
{
    QVariantMap datas = Tool_Widget::getDatas();
    datas.remove("seidTips");
    datas.remove("fenZuTips");

    int f = fenLeiGuanLian->currentIndex();
    f = f > 3 ? f + 2 : f + 1;
    datas.insert("fenLeiGuanLian",f);
    datas.insert("fenLei",fenLeiGuanLian->currentText().trimmed());

    return datas;
}

void CreateAvatarWgt::onOK()
{
    QVariantMap map = getDatas();
    Tool_JsonManager *pJsonMgr = new Tool_JsonManager(this);
    QString path = MOD_DATA.catchPath + "/CreateAvatarJsonData.json";
    QVariantMap map2 = pJsonMgr->readJsonObj(path);
    map2.insert(QString::number(id->value()),map);
    pJsonMgr->writeJson(map2,path);

    emit widgetOK();
}

void CreateAvatarWgt::onSeidManager()
{
    CreateAvatarSeidWgt *pW = new CreateAvatarSeidWgt(QApplication::applicationDirPath() + "/ConfigsJson/createAvatar/seidTip.json",
                                                      QApplication::applicationDirPath() + "/ConfigsJson/createAvatar/createAvatarSeid.json",
                                                      "CrateAvatarSeidJsonData","id");
    pW->setSeidList(seid->getValueList(),id->value());
    pW->show();
}

void CreateAvatarWgt::initialize()
{
    this->setWindowTitle("天赋");
    QList<int> val;
    MOD_DATA.iniComboxFromJson(seidTips,
                               QApplication::applicationDirPath() + "/ConfigsJson/createAvatar/seidTip.json",
                               val);
    MOD_DATA.iniComboxFromJson(fenZuTips,
                               QApplication::applicationDirPath() + "/ConfigsJson/createAvatar/FenZuTip.json",
                               val);

    connect(m_pBtnCancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
    connect(m_pBtnSeid,SIGNAL(clicked(bool)),this,SLOT(onSeidManager()));

}
