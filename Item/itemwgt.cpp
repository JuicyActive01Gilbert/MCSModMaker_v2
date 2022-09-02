#include "itemwgt.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "Tools/tool_jsonmanager.h"
#include "ModData.h"
#include "CreateAvatarSeid/createavatarseidwgt.h"

ItemWgt::ItemWgt(QWidget *parent) :
    Tool_Widget(parent)
{
    setupUi(this);
    initialize();
}

ItemWgt::~ItemWgt()
{

}

void ItemWgt::setDatas(const QVariantMap &datas)
{
    QVariantMap map = datas;
    int shuxing = map.value(ShuXingType->objectName()).toInt();
    if(shuxing > 0){
        if(shuxing % 2 == 0){
            shuxing = 9 + shuxing / 10;
        }else{
            shuxing = shuxing / 10 + 1;
        }
    }
    map.insert(ShuXingType->objectName(),shuxing);
    dealForm(map.value(type->objectName()).toInt());
    Tool_Widget::setDatas(map);

    displayIcon();
}

QVariantMap ItemWgt::getDatas()
{
    QVariantMap map = Tool_Widget::getDatas();
    map.remove(affixTips->objectName());
    map.remove(FaBaoTip->objectName());
    map.remove(wudaoTip->objectName());
    map.remove(flagTip->objectName());
    map.remove(shopTypeTip->objectName());
    map.remove(itemSeidTips->objectName());

    int shuxing = ShuXingType->currentIndex();
    if(shuxing > 0){
        if(shuxing >= 9){
            shuxing = (shuxing - 9) * 10 + 2;;
        }else{
            shuxing = (shuxing - 1) * 10 + 1;
        }
    }
    map.insert(ShuXingType->objectName(),shuxing);

    return map;
}

void ItemWgt::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);

    QList<int> val;
    MOD_DATA.iniComboxFromJson(shopTypeTip,
                               QApplication::applicationDirPath() + "/ConfigsJson/item/shopTypeTip.json",
                               val);
    MOD_DATA.iniComboxFromJson(flagTip,
                               QApplication::applicationDirPath() + "/ConfigsJson/item/itemFlagTip.json",
                               val);

    affixTips->initialize();
    connect(ItemIcon,SIGNAL(valueChanged(int)),this,SLOT(displayIcon()));
    connect(m_pBtnCustomIcon,SIGNAL(clicked(bool)),this,SLOT(onCustomIcon()));
    connect(name,SIGNAL(textChanged(QString)),this,SLOT(setWindowTitle(QString)));
    connect(m_pBtnCancel,SIGNAL(clicked(bool)),this,SLOT(onCancel()));
    connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onOK()));
    connect(m_pBtnSeid,SIGNAL(clicked(bool)),this,SLOT(onOpenSeid()));
    connect(m_pBtnDelCustomIcon,SIGNAL(clicked(bool)),this,SLOT(onDeleteCustomIcon()));
    connect(type,SIGNAL(currentIndexChanged(int)),this,SLOT(dealForm(int)));
}

void ItemWgt::dealForm(int index)
{
    QList<int> val;
    MOD_DATA.iniComboxFromJson(itemSeidTips,
                               QApplication::applicationDirPath() + "/ConfigsJson/item/seidTip.json",
                               val);


    if(index < 3){
        MOD_DATA.iniComboxFromJson(itemSeidTips,
                                   QApplication::applicationDirPath() + "/ConfigsJson/item/equipSeidTip.json",
                                   val);
        quality->clear();
        quality->addItem("无");
        quality->addItem("符器");
        quality->addItem("法器");
        quality->addItem("法宝");
        quality->addItem("纯阳法宝");
        quality->addItem("通天灵宝");
    }

    if(index == 3 || index == 4){
        quality->clear();
        quality->addItem("无");
        quality->addItem("人阶");
        quality->addItem("地阶");
        quality->addItem("天阶");
    }else if(index > 3){
        quality->clear();
        quality->addItem("无");
        quality->addItem("一品");
        quality->addItem("二品");
        quality->addItem("三品");
        quality->addItem("四品");
        quality->addItem("五品");
        quality->addItem("六品");
    }

    //    switch (index) {
    //    case 0: case 1: case 2:   //装备
    //    {
    //        MOD_DATA.iniComboxFromJson(itemSeidTips,
    //                                   QApplication::applicationDirPath() + "/ConfigsJson/item/equipSeidTip.json",
    //                                   val);
    //        maxNum->setValue(1);
    //        enableWidget(maxNum,false);

    //        enableWidget(FaBaoType,true);

    //        TuJianType->setCurrentIndex(0);
    //        enableWidget(TuJianType,false);

    //        WuWeiType->setCurrentIndex(0);
    //        enableWidget(WuWeiType,false);

    //        ShuXingType->setCurrentIndex(0);
    //        enableWidget(ShuXingType,false);

    //        enableWidget(typePinJie,true);

    //        StuTime->setValue(0);
    //        enableWidget(StuTime,false);

    //        vagueType->setCurrentIndex(0);
    //        enableWidget(vagueType,false);

    //        DanDu->setValue(0);
    //        enableWidget(DanDu,false);

    //        yaoZhi1->setValue(0);
    //        enableWidget(yaoZhi1,false);

    //        yaoZhi2->setValue(0);
    //        enableWidget(yaoZhi2,false);

    //        yaoZhi3->setValue(0);
    //        enableWidget(yaoZhi3,false);

    //        NPCCanUse->setCurrentIndex(0);
    //        enableWidget(NPCCanUse,false);

    //        wuDao->setText("");
    //        enableWidget(wuDao,false);

    //    }
    //        break;
    //    case 3: case 4:  //技能
    //    {
    //        maxNum->setValue(1);
    //        enableWidget(maxNum,false);

    //        FaBaoType->setText("");
    //        enableWidget(FaBaoType,false);

    //        TuJianType->setCurrentIndex(0);
    //        enableWidget(TuJianType,false);

    //        WuWeiType->setCurrentIndex(0);
    //        enableWidget(WuWeiType,false);

    //        ShuXingType->setCurrentIndex(0);
    //        enableWidget(ShuXingType,false);

    //        enableWidget(typePinJie,true);

    //        enableWidget(StuTime,true);

    //        vagueType->setCurrentIndex(1);
    //        enableWidget(vagueType,false);

    //        DanDu->setValue(0);
    //        enableWidget(DanDu,false);

    //        yaoZhi1->setValue(0);
    //        enableWidget(yaoZhi1,false);

    //        yaoZhi2->setValue(0);
    //        enableWidget(yaoZhi2,false);

    //        yaoZhi3->setValue(0);
    //        enableWidget(yaoZhi3,false);

    //        NPCCanUse->setCurrentIndex(0);
    //        enableWidget(NPCCanUse,false);

    //        enableWidget(wuDao,true);
    //    }
    //        break;
    //    case 5:   //丹药
    //    {
    ////        maxNum->setValue(1);
    //        enableWidget(maxNum,true);

    //        FaBaoType->setText("");
    //        enableWidget(FaBaoType,false);

    //        TuJianType->setCurrentIndex(4);
    //        enableWidget(TuJianType,false);

    //        WuWeiType->setCurrentIndex(0);
    //        enableWidget(WuWeiType,false);

    //        ShuXingType->setCurrentIndex(0);
    //        enableWidget(ShuXingType,false);

    //        typePinJie->setCurrentIndex(0);
    //        enableWidget(typePinJie,false);

    //        StuTime->setValue(0);
    //        enableWidget(StuTime,false);

    //        vagueType->setCurrentIndex(1);
    //        enableWidget(vagueType,false);

    ////        DanDu->setValue(0);
    //        enableWidget(DanDu,true);

    //        yaoZhi1->setValue(0);
    //        enableWidget(yaoZhi1,false);

    //        yaoZhi2->setValue(0);
    //        enableWidget(yaoZhi2,false);

    //        yaoZhi3->setValue(0);
    //        enableWidget(yaoZhi3,false);

    //        NPCCanUse->setCurrentIndex(0);
    //        enableWidget(NPCCanUse,false);

    //        wuDao->setText("");
    //        enableWidget(wuDao,false);
    //    }
    //        break;
    //    case 6:             //药材
    //    default:
    //        break;
    //    }
}

void ItemWgt::onCustomIcon()
{
    if(id->value() <= 0){
        QMessageBox::warning(nullptr,"警告","物品ID必须大于0");
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(nullptr, "选择图标",
                                                    "C:/",
                                                    "Images (*.png)");
    if(fileName.isEmpty()){
        return;
    }
    QString cache = APP_TEMP_PATH + "item icon/" + QString::number(id->value()) + ".png";
    if(!MOD_DATA.copyFile(fileName,cache)){
        QMessageBox::critical(nullptr,"错误","文件复制错误，请手动复制。");
        return;
    }
    ItemIcon->setValue(id->value());
    displayIcon();
}

void ItemWgt::onCancel()
{
    MOD_DATA.clearDirectory(APP_TEMP_PATH + "item icon/");
}

void ItemWgt::onOK()
{
    QVariantMap map = this->getDatas();
    m_pJsonMgr->writeJson(map,QString(MOD_DATA.catchPath + "ItemJsonData/%1.json").arg(id->value()));
    QString path = APP_TEMP_PATH + "item icon/" + QString::number(id->value()) + ".png";
    if(QFile::exists(path)){
        QString path2 = MOD_DATA.catchPath + "Assets/item icon/" + QString::number(id->value()) + ".png";
        if(!MOD_DATA.copyFile(path,path2)){
            QMessageBox::critical(nullptr,"错误","文件复制错误，请手动复制。");
            return;
        }
        MOD_DATA.removeFile(path);
    }
    emit widgetOK();
}

void ItemWgt::onOpenSeid()
{
    QString path1 = QApplication::applicationDirPath() + "/ConfigsJson/item/seidTip.json";
    QString path2 = QApplication::applicationDirPath() + "/ConfigsJson/item/itemSeid.json";
    QString path3 =  "ItemsSeidJsonData";
    if(type->currentIndex() < 3){
        path1 = QApplication::applicationDirPath() + "/ConfigsJson/item/equipSeidTip.json";
        path2 = QApplication::applicationDirPath() + "/ConfigsJson/item/equipmentSeid.json";
        path3 =  "EquipSeidJsonData";
    }
    CreateAvatarSeidWgt *pW = new CreateAvatarSeidWgt(path1,
                                                      path2,
                                                      path3,"id");
    pW->setSeidList(seid->getValueList(),id->value());
    pW->show();

}

void ItemWgt::onDeleteCustomIcon()
{
    int iconNumber = ItemIcon->value();
    if(iconNumber == 0){
        iconNumber = id->value();
    }
    QString cachePath = MOD_DATA.catchPath + "Assets/item icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "item icon/" + QString::number(iconNumber) + ".png";

    MOD_DATA.removeFile(cachePath);
    MOD_DATA.removeFile(tempPath);
    displayIcon();
}


void ItemWgt::displayIcon()
{
    m_pLabIcon->clear();
    int iconNumber = ItemIcon->value();
    if(iconNumber == 0){
        iconNumber = id->value();
    }
    QString sysPath = MOD_PATH_SYS + "Assets/item icon/" + QString::number(iconNumber) + ".png";
    QString cachePath = MOD_DATA.catchPath + "Assets/item icon/" + QString::number(iconNumber) + ".png";
    QString tempPath = APP_TEMP_PATH + "item icon/" + QString::number(iconNumber) + ".png";
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

void ItemWgt::enableWidget(QWidget *pWgt, bool isEnable)
{
    pWgt->setEnabled(isEnable);
}
