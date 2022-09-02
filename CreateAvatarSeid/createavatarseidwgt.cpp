#include "createavatarseidwgt.h"

#include "ModData.h"
#include "Tools/tool_jsonmanager.h"
#include <QMessageBox>

CreateAvatarSeidWgt::CreateAvatarSeidWgt(const QString &tipsPath,
                                         const QString &tipsClassPath,
                                         const QString &saveDir,
                                         const QString &idKey, QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);
    m_tipsPath = tipsPath;//QApplication::applicationDirPath() + "/ConfigsJson/skill/seidTip.json"
    m_saveDir = saveDir;
    m_idKey = idKey;
    m_seidClassPath = tipsClassPath;

    initialize();

}

CreateAvatarSeidWgt::~CreateAvatarSeidWgt()
{

}

void CreateAvatarSeidWgt::setSeidList(QStringList text, int dataID)
{
    m_dataID = dataID;
    m_pCBoxSeid->clear();
    m_pCBoxSeid->addItems(text);
    if(!text.isEmpty()){
        onSeidChange(0);
    }

}

void CreateAvatarSeidWgt::onSeidChange(int index)
{
    Q_UNUSED(index)
    m_pFormWgt->clearForms();
    m_pFormWgt->setDatas(QVariantMap());
    QString t = m_pCBoxSeid->currentText();
    int i = m_seidClass.value(t).toInt() - 1;
    if(i >= 0 && i < MOD_DATA.seidFormClass.count()){
        QVariantMap map = MOD_DATA.seidFormClass[i].toMap();
        m_pFormWgt->iniForms(map.value("forms").toList());
        displayData();
    }

    m_pLabSeidTip->setText(m_seidTips.value(t).toString());
}

void CreateAvatarSeidWgt::onOK()
{
    QVariantMap map = m_pFormWgt->getDatas();
    if(map.isEmpty()){
        return;
    }
    QString seid = m_pCBoxSeid->currentText();
    QString path = QString(MOD_DATA.catchPath + m_saveDir + "/%1.json").arg(seid);
    QVariantMap oldMap = m_pJsonMgr->readJsonObj(path);
    map.insert(m_idKey,m_dataID);
    oldMap.insert(QString::number(m_dataID),map);
    m_pJsonMgr->writeJson(oldMap,path);
    QMessageBox::information(nullptr,"保存成功","保存成功！");
//    this->close();
}

void CreateAvatarSeidWgt::initialize()
{
    this->setWindowTitle("特性");
    m_pJsonMgr = new Tool_JsonManager(this);
    m_seidTips = m_pJsonMgr->readJson(m_tipsPath).first().toMap();
    m_seidIndex = MOD_DATA.mapNumberKey(m_seidTips);
    m_seidClass = m_pJsonMgr->readJsonObj(m_seidClassPath);

    connect(m_pCBoxSeid,SIGNAL(activated(int)),this,SLOT(onSeidChange(int)));
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
}

void CreateAvatarSeidWgt::displayData()
{
    if(m_pCBoxSeid->currentIndex() < 0){
        return;
    }
    QVariantMap map = m_pJsonMgr->readJsonObj(QString(MOD_DATA.catchPath + m_saveDir + "/%1.json").arg(m_pCBoxSeid->currentText()));
    if(map.isEmpty()){
        map = m_pJsonMgr->readJsonObj(QString(MOD_PATH_SYS + m_saveDir + "/%1.json").arg(m_pCBoxSeid->currentText()));
    }

    if(map.isEmpty() || !map.contains(QString::number(m_dataID))){
        return;
    }
    m_pFormWgt->setDatas(map.value(QString::number(m_dataID)).toMap());
}
