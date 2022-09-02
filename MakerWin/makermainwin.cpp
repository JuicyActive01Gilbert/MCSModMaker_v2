#include "makermainwin.h"
#include "Tools/tool_jsonmanager.h"
#include <QTableWidgetItem>
#include <QScrollBar>

MakerMainWin::MakerMainWin(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

MakerMainWin::~MakerMainWin()
{

}

void MakerMainWin::clearInfo()
{
    m_pLabInfo->clear();
}

void MakerMainWin::onSave()
{
    MOD_DATA.clearDirectory(MOD_DATA.modPath);
    if(!MOD_DATA.copyDirectory(MOD_DATA.catchPath,MOD_DATA.modPath)){
        onShowLabInfo("保存失败，请自行复制，地址：" + MOD_DATA.catchPath);
        return;
    }
    onShowLabInfo("保存成功！");
}

void MakerMainWin::onDataOk()
{

//    Tool_Widget *pW = static_cast<Tool_Widget*>(m_pStackWgt->currentWidget());
//    int id = m_pStackWgt->currentIndex();
//    switch (id) {
//    case 1:
//    {
//        m_id = pW->getDatas().value("buffid").toString();
//    }
//        break;
//    case 2:

//    default:
//        break;
//    }
    onTBtnChecked(m_pBtnGroup->checkedId());
}

void MakerMainWin::onTBtnChecked(int id)
{
    m_pStackWgt->setCurrentIndex(id);
    m_pTableFun->setVisible(id != 0);
    Tool_Widget *pW = static_cast<Tool_Widget*>(m_pStackWgt->currentWidget());
    switch (id) {
    case 0:
    {
        pW->iniData();
    }
        break;
    case 1:
    {
        loadBuffs();
    }
        break;
    case 2:
    {
        loadSkills();
    }
        break;
    case 3:
    {
        loadStaticSkill();
    }
        break;
    case 4:
    {
        laodItems();
    }
        break;
    case 5:
    {
        loadCA();
    }
        break;
    case 6:
    {
        loadAffix();
    }
        break;
    default:
        break;
    }

}

void MakerMainWin::onShowLabInfo(QString info)
{
    m_pLabInfo->setText(info);
}

void MakerMainWin::onSearch(QString text)
{
    Q_UNUSED(text)
    onTBtnChecked(m_pBtnGroup->checkedId());
}

void MakerMainWin::iniFunBtns(const QVariantList &lst,
                              QString name,QString id)
{
    m_pTableFun->setRowCount(0);

    QVariantList showList;
    QString text = m_pLEdtSearch->text().trimmed();

    if(!text.isEmpty()){
        for (int i = 0; i < lst.count();i++) {
            QVariantMap map = lst[i].toMap();
            QString n = map.value(name).toString();
            if(!n.contains(text)){
                continue;
            }
            showList.append(map);
        }
    }else{
        showList = lst;
    }
    m_pTableFun->setRowCount(showList.count());
    m_pTableFun->setColumnCount(1);

    int r = -1;
    for (int i = showList.count() - 1; i >= 0;--i) {
        QVariantMap map = showList[i].toMap();
        QString n = map.value(name).toString();
        QTableWidgetItem *pItem = new QTableWidgetItem(n);
        QString t = map.value(id).toString();
        pItem->setWhatsThis(t);
        pItem->setTextAlignment(Qt::AlignCenter);
        m_pTableFun->setItem(i,0,pItem);

        if(!m_id.isEmpty() && t == m_id){
            m_pTableFun->selectRow(i);
            r = i;
        }
    }

    if(r >= 0){
        m_pTableFun->verticalScrollBar()->setValue(r);
    }

}

void MakerMainWin::onTabItemSelect(QTableWidgetItem *pItem)
{
    QString id = pItem->whatsThis();

    int wgtId = m_pStackWgt->currentIndex();
    switch (wgtId) {
    case 1:
    {
        m_pBuffWgt->setDatas(getDataFromID(id,"buffid"));
    }
        break;
    case 2:
    {
        m_pSkillWgt->setSkillData(getDataFromID(id,"id").value("skills").toList());
    }

        break;
    case 3:
    {
        m_pS_SkilWgt->setSkillData(getDataFromID(id,"id").value("skills").toList());
    }
        break;
    case 4:
    {
        m_pItemWgt->setDatas(getDataFromID(id,"id"));
    }
        break;
    case 5:
    {
        m_pCAWgt->setDatas(getDataFromID(id,"id"));
    }

        break;
    case 6:
    {
        m_pAffixWgt->setDatas(getDataFromID(id,"id"));
    }

        break;
    default:
        break;
    }

}

void MakerMainWin::initialize()
{
    m_pJsonMgr = new Tool_JsonManager(this);
    iniButtons();
    iniFunWgts();

    connect(m_pTableFun,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(onTabItemSelect(QTableWidgetItem*)));
    connect(m_pBtnSaveMod,SIGNAL(clicked(bool)),this,SLOT(onSave()));
    connect(m_pLEdtSearch,SIGNAL(textChanged(QString)),this,SLOT(onSearch(QString)));
    connect(m_pBtnBack,SIGNAL(clicked(bool)),this,SIGNAL(backDataWin()));
}

void MakerMainWin::iniButtons()
{
    m_pBtnGroup = new QButtonGroup(this);
    m_pBtnGroup->addButton(m_pTBtnCfg,0);
    m_pBtnGroup->addButton(m_pTBtnBuff,1);
    m_pBtnGroup->addButton(m_pTBtnSkill,2);
    m_pBtnGroup->addButton(m_pTBtnStaticSkill,3);
    m_pBtnGroup->addButton(m_pTBtnItem,4);
    m_pBtnGroup->addButton(m_pTBtnTianFu,5);
    m_pBtnGroup->addButton(m_pTBtnCiZhui,6);
    m_pTBtnCfg->setChecked(true);

    connect(m_pBtnGroup,SIGNAL(buttonClicked(int)),this,SLOT(onTBtnChecked(int)));
}

void MakerMainWin::iniFunWgts()
{
    m_pCfgWgt               = new ModConfigWgt;
    m_pBuffWgt              = new BuffWgt;
    m_pSkillWgt             = new SkillWgt;
    m_pS_SkilWgt            = new StaticSkillWgt;
    m_pItemWgt              = new ItemWgt;
    m_pCAWgt                = new CreateAvatarWgt;
    m_pAffixWgt             = new AffixWgt;

    m_pStackWgt->addWidget(m_pCfgWgt);
    m_pStackWgt->addWidget(m_pBuffWgt);
    m_pStackWgt->addWidget(m_pSkillWgt);
    m_pStackWgt->addWidget(m_pS_SkilWgt);
    m_pStackWgt->addWidget(m_pItemWgt);
    m_pStackWgt->addWidget(m_pCAWgt);
    m_pStackWgt->addWidget(m_pAffixWgt);

    connect(m_pCfgWgt,SIGNAL(showInfo(QString)),this,SLOT(onShowLabInfo(QString)));
    connect(m_pBuffWgt,SIGNAL(showInfo(QString)),this,SLOT(onShowLabInfo(QString)));
    connect(m_pSkillWgt,SIGNAL(showInfo(QString)),this,SLOT(onShowLabInfo(QString)));
    connect(m_pS_SkilWgt,SIGNAL(showInfo(QString)),this,SLOT(onShowLabInfo(QString)));
    connect(m_pItemWgt,SIGNAL(showInfo(QString)),this,SLOT(onShowLabInfo(QString)));
    connect(m_pCAWgt,SIGNAL(showInfo(QString)),this,SLOT(onShowLabInfo(QString)));
    connect(m_pAffixWgt,SIGNAL(showInfo(QString)),this,SLOT(onShowLabInfo(QString)));

    connect(m_pBuffWgt,SIGNAL(widgetOK()),this,SLOT(onDataOk()));
    connect(m_pSkillWgt,SIGNAL(widgetOK()),this,SLOT(onDataOk()));
    connect(m_pS_SkilWgt,SIGNAL(widgetOK()),this,SLOT(onDataOk()));
    connect(m_pItemWgt,SIGNAL(widgetOK()),this,SLOT(onDataOk()));
    connect(m_pCAWgt,SIGNAL(widgetOK()),this,SLOT(onDataOk()));
    connect(m_pAffixWgt,SIGNAL(widgetOK()),this,SLOT(onDataOk()));
}

void MakerMainWin::loadBuffs()
{
    m_datas.clear();
    QVariantList lst = readFiles(MOD_PATH_SYS + "BuffJsonData/",true,"buffid");
    QVariantList lst2 = readFiles(MOD_DATA.catchPath + "BuffJsonData/",false,"buffid");
    m_datas = MOD_DATA.mergeDatas(lst,lst2,"buffid");
    iniFunBtns(m_datas,"name","buffid");
}

void MakerMainWin::loadSkills()
{
    m_datas.clear();
    QVariantList lst = readFiles(MOD_PATH_SYS + "skillJsonData/",true,"id");
    QVariantList lst2 = readFiles(MOD_DATA.catchPath + "skillJsonData/",false,"id");
    m_datas = mergeSkills(lst,lst2);
    iniFunBtns(m_datas,"name","id");
}

void MakerMainWin::loadStaticSkill()
{
    m_datas.clear();
    QVariantList lst = readStaticSkill(MOD_PATH_SYS + "StaticSkillJsonData.json");
    QVariantList lst2 = readStaticSkill(MOD_DATA.catchPath + "StaticSkillJsonData.json");
    m_datas = mergeSkills(lst,lst2);
    iniFunBtns(m_datas,"name","id");
}

void MakerMainWin::laodItems()
{
    m_datas.clear();
    QVariantList lst = readFiles(MOD_PATH_SYS + "ItemJsonData/",true,"id");
    QVariantList lst2 = readFiles(MOD_DATA.catchPath + "ItemJsonData/",false,"id");
    m_datas = MOD_DATA.mergeDatas(lst,lst2,"id");
    iniFunBtns(m_datas,"name","id");
}

void MakerMainWin::loadCA()
{
    m_datas.clear();
    QVariantList lst = readStaticSkill(MOD_PATH_SYS + "CreateAvatarJsonData.json");
    QVariantList lst2 = readStaticSkill(MOD_DATA.catchPath + "CreateAvatarJsonData.json");
    m_datas = MOD_DATA.mergeDatas(lst,lst2,"id");
    iniFunBtns(m_datas,"Title","id");
}

void MakerMainWin::loadAffix()
{
    m_datas.clear();
    QVariantList lst = readStaticSkill(MOD_PATH_SYS + "TuJianChunWenBen.json");
    QVariantList lst2 = readStaticSkill(MOD_DATA.catchPath + "TuJianChunWenBen.json");
    m_datas = MOD_DATA.mergeDatas(lst,lst2,"id");
    iniFunBtns(m_datas,"name2","id");
}

QVariantList MakerMainWin::readFiles(const QString &dirPath, bool isSys,QString id)
{
    Q_UNUSED(isSys)
    QStringList fileLst = MOD_DATA.getDirFiles(dirPath);
    QVariantList lst;

    foreach (QString json, fileLst) {
        if(json.isEmpty()){
            continue;
        }
        QVariantMap map = m_pJsonMgr->readJsonObj(dirPath + json);
        //        map.insert("Mod_Is_Sys",isSys);
        lst.append(map);

    }
    MOD_DATA.sortListFromNumberKey(lst,id);
    return lst;
}



QVariantMap MakerMainWin::getDataFromID(QString val, QString key)
{
    for (QVariant var : m_datas) {
        QVariantMap map = var.toMap();
        if(val == map.value(key).toString()){
            return map;
        }
    }
    return QVariantMap();
}

QVariantList MakerMainWin::mergeSkills(QVariantList lst, QVariantList lst2)
{
    QVariantList resList;
    lst = MOD_DATA.mergeDatas(lst,lst2,"id");

    for (QVariant var : lst) {
        QVariantMap map = var.toMap();
        QString name = map.value("name").toString();
        name.replace( QRegExp("[1-5]"),"");
        QString id = map.value("Skill_ID").toString();

        bool isHave = false;
        for (int i = 0; i < resList.count(); ++i) {
            QVariantMap map2 = resList[i].toMap();
            QString sID = map2.value("id").toString();
            QVariantList lstS = map2.value("skills").toList();
            if(lstS.count() == 5){
                continue;
            }
            if(sID == id){
                lstS.append(map);
                map2.insert("skills",lstS);
                resList[i] = map2;
                isHave = true;
                break;
            }
        }

        if(!isHave){
            QVariantMap map2;
            map2.insert("id",id);
            map2.insert("name",name);
            map2.insert("skills",QVariantList() << map);
            resList.append(map2);
        }
    }


    return resList;
}

QVariantList MakerMainWin::readStaticSkill(const QString &path)
{
    QVariantList skills;

    QVariantMap mapAll = m_pJsonMgr->readJsonObj(path);
    QStringList keys = mapAll.keys();
    for (QString key : keys) {
        QVariantMap map = mapAll.value(key).toMap();
        skills.append(map);
    }

    return skills;
}
