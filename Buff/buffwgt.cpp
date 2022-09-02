#include "buffwgt.h"

#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include "CreateAvatarSeid/createavatarseidwgt.h"

BuffWgt::BuffWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);

    initialize();
}

BuffWgt::~BuffWgt()
{

}

void BuffWgt::setDatas(const QVariantMap &datas)
{
    QVariantMap map = datas;
    if(map.isEmpty()){
        trigger->setCurrentIndex(0);
        removeTrigger->setCurrentIndex(0);
        bufftype->setCurrentIndex(0);
        BuffType->setCurrentIndex(0);
    }else{
        map.insert("trigger",m_triggers.indexOf(datas.value("trigger").toInt()));
        map.insert("removeTrigger",m_removeTriggers.indexOf(datas.value("removeTrigger").toInt()));
        map.insert("bufftype",m_bufftypes.indexOf(datas.value("bufftype").toInt()));
        map.insert("BuffType",m_BuffTypes.indexOf(datas.value("BuffType").toInt()));
    }

    Tool_Widget::setDatas(map);
    displayIcon();
}

QVariantMap BuffWgt::getDatas()
{
    QVariantMap data = Tool_Widget::getDatas();
    data.insert("trigger",m_triggers[trigger->currentIndex()]);
    data.insert("removeTrigger",m_removeTriggers[removeTrigger->currentIndex()]);
    data.insert("bufftype",m_bufftypes[bufftype->currentIndex()]);
    data.insert("BuffType",m_BuffTypes[BuffType->currentIndex()]);

    data.remove("seidTip");
    data.remove("affixTip");

    return data;
}

void BuffWgt::onCustomIcon()
{
    if(buffid->value() <= 0){
        emit showInfo("buffID必须大于0");
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(nullptr, "选择图标",
                                                    "C:/",
                                                    "Images (*.png)");
    if(fileName.isEmpty()){
        return;
    }
    QString cache = APP_TEMP_PATH + "buff icon/" + QString::number(buffid->value()) + ".png";// MOD_DATA.catchPath + "Assets/buff icon/" + QString::number(buffid->value()) + ".png";
    if(!MOD_DATA.copyFile(fileName,cache)){
        emit showInfo("文件复制错误，请手动复制。");
        return;
    }
    BuffIcon->setValue(buffid->value());
    displayIcon();
}

void BuffWgt::onNameChange(QString text)
{
    this->setWindowTitle(text);
}

void BuffWgt::onCancel()
{
    MOD_DATA.clearDirectory(APP_TEMP_PATH + "buff icon/");
}

void BuffWgt::onOK()
{
    QVariantMap map = this->getDatas();
    m_pJsonMgr->writeJson(map,QString(MOD_DATA.catchPath + "BuffJsonData/%1.json").arg(buffid->value()));
    QString path = APP_TEMP_PATH + "buff icon/" + QString::number(buffid->value()) + ".png";
    if(QFile::exists(path)){
        QString path2 = MOD_DATA.catchPath + "Assets/buff icon/" + QString::number(buffid->value()) + ".png";
        if(!MOD_DATA.copyFile(path,path2)){
            emit showInfo("文件复制错误，请手动复制。");
            return;
        }
        MOD_DATA.removeFile(path);
    }
    emit showInfo("保存buff成功。");
    emit widgetOK();
}

void BuffWgt::onOpenSeid()
{
    CreateAvatarSeidWgt *pW = new CreateAvatarSeidWgt(QApplication::applicationDirPath() + "/ConfigsJson/buff/seidTip.json",
                                                      QApplication::applicationDirPath() + "/ConfigsJson/buff/buffSeid.json",
                                                      "BuffSeidJsonData","buffid");
    pW->setSeidList(seid->getValueList(),buffid->value());
    pW->show();
}

void BuffWgt::onDeleteCustomIcon()
{
    int iconNumber = BuffIcon->value();
    if(iconNumber == 0){
        iconNumber = buffid->value();
    }
    QString cachePath = MOD_DATA.catchPath + "Assets/buff icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "buff icon/" + QString::number(iconNumber) + ".png";

    MOD_DATA.removeFile(cachePath);
    MOD_DATA.removeFile(tempPath);
    displayIcon();
}

void BuffWgt::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);

    MOD_DATA.iniComboxFromJson(trigger,
                               QApplication::applicationDirPath() + "/ConfigsJson/buff/trigger.json",
                               m_triggers);
    MOD_DATA.iniComboxFromJson(removeTrigger,
                               QApplication::applicationDirPath() + "/ConfigsJson/buff/removetrigger.json",
                               m_removeTriggers);
    MOD_DATA.iniComboxFromJson(BuffType,
                               QApplication::applicationDirPath() + "/ConfigsJson/buff/BuffType.json",
                               m_BuffTypes);
    MOD_DATA.iniComboxFromJson(bufftype,
                               QApplication::applicationDirPath() + "/ConfigsJson/buff/bufftype2.json",
                               m_bufftypes);

    affixTip->initialize();
    connect(BuffIcon,SIGNAL(valueChanged(int)),this,SLOT(displayIcon()));
    connect(m_pBtnCustomIcon,SIGNAL(clicked(bool)),this,SLOT(onCustomIcon()));
    connect(name,SIGNAL(textChanged(QString)),this,SLOT(onNameChange(QString)));
    connect(m_pBtnCancel,SIGNAL(clicked(bool)),this,SLOT(onCancel()));
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
    connect(m_pBtnSeid,SIGNAL(clicked(bool)),this,SLOT(onOpenSeid()));
    connect(m_pBtnDelCustomICon,SIGNAL(clicked(bool)),this,SLOT(onDeleteCustomIcon()));

}

void BuffWgt::displayIcon()
{
    m_pLabIcon->clear();
    int iconNumber = BuffIcon->value();
    if(iconNumber == 0){
        iconNumber = buffid->value();
    }
    QString sysPath = MOD_PATH_SYS + "Assets/buff icon/" + QString::number(iconNumber) + ".png";
    QString cachePath = MOD_DATA.catchPath + "Assets/buff icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "buff icon/" + QString::number(iconNumber) + ".png";
    if(QImage(tempPath).isNull()){
        tempPath = cachePath;
        if(QImage(tempPath).isNull()){
            tempPath = sysPath;
        }
    }
    QImage img(tempPath);
    if(img.isNull()){
        return;
    }
    img = img.scaled(64,64);
    m_pLabIcon->setPixmap(QPixmap::fromImage(img));
}

