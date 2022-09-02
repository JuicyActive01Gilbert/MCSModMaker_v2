#include "skillwgt.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include "CreateAvatarSeid/createavatarseidwgt.h"

SkillWgt::SkillWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);
    initialize();
}

SkillWgt::~SkillWgt()
{

}

void SkillWgt::setSkillData(const QVariantList &skills)
{
    m_skills = skills;
    onLvActivate(0);
    displayIcon();
}

void SkillWgt::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);
    QList<int> val;
    MOD_DATA.iniComboxFromJson(skillSeidTips,
                               QApplication::applicationDirPath() + "/ConfigsJson/skill/seidTip.json",
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

void SkillWgt::dealResData(QVariantMap &map, bool isAdd)
{
    if(isAdd){
        dealSkill(map,"Skill_Lv");
        dealSkill(map,"Skill_LV");
        dealSkill(map,"typePinJie");
        dealSkill(map,"Skill_Open");

        if(map.value("script").toString() == "SkillAttack"){
            map.insert("script",0);
        }else{
            map.insert("script",1);
        }

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
        dealSkill(map,"Skill_Open",1);

        if(map.value("script").toInt() == 0){
            map.insert("script","SkillAttack");
        }else{
            map.insert("script","SkillSelf");
        }

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

void SkillWgt::displaySkillData(QVariantMap map)
{
    dealResData(map);
    this->setDatas(map);
}

void SkillWgt::dealSkill(QVariantMap &map, QString key, int offset)
{
    map.insert(key,map.value(key).toInt() + offset);
}

void SkillWgt::displayIcon()
{
    m_pLabIcon->clear();
    int iconNumber = icon->value();
    if(iconNumber == 0){
        iconNumber = Skill_ID->value();
    }
    QString sysPath = MOD_PATH_SYS + "Assets/skill icon/" + QString::number(iconNumber) + ".png";
    QString cachePath = MOD_DATA.catchPath + "Assets/skill icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "skill icon/" + QString::number(iconNumber) + ".png";
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

void SkillWgt::onCustomIcon()
{
    if(Skill_ID->value() <= 0){
        QMessageBox::warning(nullptr,"警告","神通组 ID必须大于0");
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(nullptr, "选择图标",
                                                    "C:/",
                                                    "Images (*.png)");
    if(fileName.isEmpty()){
        return;
    }
    QString cache = APP_TEMP_PATH + "skill icon/" + QString::number(Skill_ID->value()) + ".png";
    if(!MOD_DATA.copyFile(fileName,cache)){
        QMessageBox::critical(nullptr,"错误","文件复制错误，请手动复制。");
        return;
    }
    icon->setValue(Skill_ID->value());
    displayIcon();
}

void SkillWgt::onCancel()
{
    MOD_DATA.clearDirectory(APP_TEMP_PATH + "skill icon/");
}

void SkillWgt::onOK()
{
    QVariantMap map = this->getDatas();
    dealResData(map,false);
    map.remove(skillSeidTips->objectName());
    map.remove(affixTips->objectName());
    map.remove(attackTypeTips->objectName());
    map.remove(lingQiTips->objectName());

    QString path = APP_TEMP_PATH + "skill icon/" + QString::number(Skill_ID->value()) + ".png";
    if(QFile::exists(path)){
        QString path2 = MOD_DATA.catchPath + "Assets/skill icon/" + QString::number(Skill_ID->value()) + ".png";
        if(!MOD_DATA.copyFile(path,path2)){
            emit showInfo("文件复制错误，请手动复制。");
            return;
        }
        MOD_DATA.removeFile(path);
    }

    m_pJsonMgr->writeJson(map,QString(MOD_DATA.catchPath + "skillJsonData/%1.json").arg(id->value()));

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
    emit showInfo("保存成功！");
    emit widgetOK();
}

void SkillWgt::onDeleteCustomIcon()
{
    int iconNumber = icon->value();
    if(iconNumber == 0){
        iconNumber = Skill_ID->value();
    }
    QString cachePath = MOD_DATA.catchPath + "Assets/skill icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "skill icon/" + QString::number(iconNumber) + ".png";

    MOD_DATA.removeFile(cachePath);
    MOD_DATA.removeFile(tempPath);
    displayIcon();
}


void SkillWgt::onLvActivate(int index)
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

void SkillWgt::onOpenSeid()
{
    CreateAvatarSeidWgt *pW = new CreateAvatarSeidWgt(QApplication::applicationDirPath() + "/ConfigsJson/skill/seidTip.json",
                                                      QApplication::applicationDirPath() + "/ConfigsJson/skill/skillSeid.json",
                                                      "SkillSeidJsonData","id");
    pW->setSeidList(seid->getValueList(),id->value());
    pW->show();

}

