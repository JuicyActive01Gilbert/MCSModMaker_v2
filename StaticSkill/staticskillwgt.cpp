#include "staticskillwgt.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include "CreateAvatarSeid/createavatarseidwgt.h"

StaticSkillWgt::StaticSkillWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);
    initialize();
}

StaticSkillWgt::~StaticSkillWgt()
{

}


void StaticSkillWgt::setSkillData(const QVariantList &skills)
{
    m_skills = skills;
    onLvActivate(0);
    displayIcon();
}

void StaticSkillWgt::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);
    QList<int> val;
    MOD_DATA.iniComboxFromJson(skillSeidTips,
                               QApplication::applicationDirPath() + "/ConfigsJson/staticskill/seidTip.json",
                               val);


    affixTips->initialize();
    connect(icon,SIGNAL(valueChanged(int)),this,SLOT(displayIcon()));
    connect(m_pBtnCustomIcon,SIGNAL(clicked(bool)),this,SLOT(onCustomIcon()));
    connect(name,SIGNAL(textChanged(QString)),this,SLOT(setWindowTitle(QString)));
    connect(m_pBtnCancel,SIGNAL(clicked(bool)),this,SLOT(onCancel()));
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
    connect(m_pBtnSeid,SIGNAL(clicked(bool)),this,SLOT(onOpenSeid()));
    connect(m_pBtnDelCustomIcon,SIGNAL(clicked(bool)),this,SLOT(onDeleteCustomIcon()));
    connect(Skill_Lv,SIGNAL(activated(int)),this,SLOT(onLvActivate(int)));

}

void StaticSkillWgt::dealResData(QVariantMap &map, bool isAdd)
{
    if(isAdd){
        dealSkill(map,"Skill_Lv");
        dealSkill(map,"Skill_LV");
        dealSkill(map,"typePinJie");

        int qingjiao = map.value(qingjiaotype->objectName()).toInt();
        switch (qingjiao) {
        case 1:case 2:case 3:
            map.insert(qingjiaotype->objectName(),qingjiao - 1);
            break;
        case 5:case 6:case 7:
            map.insert(qingjiaotype->objectName(),qingjiao - 2);
            break;
        default:
            break;
        }
    }else{
        dealSkill(map,"Skill_Lv",1);
        dealSkill(map,"Skill_LV",1);
        dealSkill(map,"typePinJie",1);

        int qingjiao = map.value(qingjiaotype->objectName()).toInt();
        switch (qingjiao) {
        case 0:case 1:case 2:
            map.insert(qingjiaotype->objectName(),qingjiao + 1);
            break;
        case 3:case 4:case 5:
            map.insert(qingjiaotype->objectName(),qingjiao + 2);
            break;
        default:
            break;
        }
    }
}

void StaticSkillWgt::displaySkillData(QVariantMap map)
{
    dealResData(map);
    this->setDatas(map);
}

void StaticSkillWgt::dealSkill(QVariantMap &map, QString key, int offset)
{
    map.insert(key,map.value(key).toInt() + offset);
}

void StaticSkillWgt::displayIcon()
{
    m_pLabIcon->clear();
    int iconNumber = icon->value();
    if(iconNumber == 0){
        iconNumber = Skill_ID->value();
    }
    QString sysPath = MOD_PATH_SYS + "Assets/staticskill icon/" + QString::number(iconNumber) + ".png";
    QString cachePath = MOD_DATA.catchPath + "Assets/staticskill icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "staticskill icon/" + QString::number(iconNumber) + ".png";
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

void StaticSkillWgt::onCustomIcon()
{
    if(Skill_ID->value() <= 0){
        QMessageBox::warning(nullptr,"警告","功法组 ID必须大于0");
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(nullptr, "选择图标",
                                                    "C:/",
                                                    "Images (*.png)");
    if(fileName.isEmpty()){
        return;
    }
    QString cache = APP_TEMP_PATH + "staticskill icon/" + QString::number(Skill_ID->value()) + ".png";
    if(!MOD_DATA.copyFile(fileName,cache)){
        QMessageBox::critical(nullptr,"错误","文件复制错误，请手动复制。");
        return;
    }
    icon->setValue(Skill_ID->value());
    displayIcon();
}

void StaticSkillWgt::onCancel()
{
    MOD_DATA.clearDirectory(APP_TEMP_PATH + "staticskill icon/");
    this->close();
}

void StaticSkillWgt::onOK()
{
    QVariantMap map = this->getDatas();
    dealResData(map,false);
    map.remove(skillSeidTips->objectName());
    map.remove(affixTips->objectName());

    QString path = APP_TEMP_PATH + "staticskill icon/" + QString::number(Skill_ID->value()) + ".png";
    if(QFile::exists(path)){
        QString path2 = MOD_DATA.catchPath + "Assets/staticskill icon/" + QString::number(Skill_ID->value()) + ".png";
        if(!MOD_DATA.copyFile(path,path2)){
            QMessageBox::critical(nullptr,"错误","文件复制错误，请手动复制。");
            return;
        }
        MOD_DATA.removeFile(path);
    }

    QString modPath = MOD_DATA.catchPath + "StaticSkillJsonData.json";
    QVariantMap map2 = m_pJsonMgr->readJsonObj(modPath);
    map2.insert(QString::number(id->value()),map);
    m_pJsonMgr->writeJson(map2,modPath);

    if(m_skills.isEmpty()){
        m_skills.append(map);
    }else{
        for (int i = 0; i < m_skills.count();++i) {
            QVariantMap sk = m_skills[i].toMap();
            if(sk.value(Skill_Lv->objectName()).toInt() == Skill_Lv->currentIndex() + 1){
                m_skills[i] = map;
                break;
            }
        }
    }

    if(m_skills.count() != 5 &&
            QMessageBox::question(nullptr,"应用","是否将当前数据到其它未输入等级？(需要单独进入页面修改ID并保存)",
                                  QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes){
        QVariantMap testMap = map;
        for (int i = 1; i < 6; ++i) {
            bool isContains = false;
            for (int i = 0; i < m_skills.count();++i) {
                QVariantMap sk = m_skills[i].toMap();
                if(sk.value(Skill_Lv->objectName()).toInt() == i){
                    isContains = true;
                    break;
                }
            }
            if(!isContains){
                testMap.insert(Skill_Lv->objectName(),i);
                m_skills.append(testMap);
            }
            if(m_skills.count() == 5){
                break;
            }
        }
    }

    QStringList seids = seid->getValueList();
    if(seids.contains("9")){
        QVariantMap yuJian;
        yuJian.insert("skillid",id->value());
        yuJian.insert("Spine","MapPlayerYuJian");
        yuJian.insert("OnMoveEnter","");
        yuJian.insert("OnMoveExit","");
        yuJian.insert("OnLoopMoveEnter","");
        yuJian.insert("OnLoopMoveExit","");
        QString path = MOD_DATA.catchPath + "StaticSkillSeidJsonData/9.json";
        QVariantMap yuJianMap =  m_pJsonMgr->readJsonObj(path);
        yuJianMap.insert(QString::number(id->value()),yuJian);
        m_pJsonMgr->writeJson(yuJianMap,path);
    }

    QMessageBox::information(nullptr,"保存成功","保存成功！");
    emit widgetOK();
}

void StaticSkillWgt::onDeleteCustomIcon()
{
    int iconNumber = icon->value();
    if(iconNumber == 0){
        iconNumber = Skill_ID->value();
    }
    QString cachePath = MOD_DATA.catchPath + "Assets/staticskill icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "staticskill icon/" + QString::number(iconNumber) + ".png";

    MOD_DATA.removeFile(cachePath);
    MOD_DATA.removeFile(tempPath);
    displayIcon();
}


void StaticSkillWgt::onLvActivate(int index)
{
    if(m_skills.isEmpty()){
        return;
    }
    index += 1;  //level + 1;
    foreach (QVariant var, m_skills) {
        QVariantMap map = var.toMap();
        if(map.value("Skill_Lv").toInt() == index){
            displaySkillData(map);
            return;
        }
    }
}

void StaticSkillWgt::onOpenSeid()
{
    CreateAvatarSeidWgt *pW = new CreateAvatarSeidWgt(QApplication::applicationDirPath() + "/ConfigsJson/staticskill/seidTip.json",
                                                      QApplication::applicationDirPath() + "/ConfigsJson/staticskill/staticskillSeid.json",
                                                      "StaticSkillSeidJsonData","skillid");
    pW->setSeidList(seid->getValueList(),id->value());
    pW->show();

}
