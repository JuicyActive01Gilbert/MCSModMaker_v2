#include "ModData.h"
#include <QDebug>

#include <QDir>
#include <QDirIterator>
#include <QUuid>
#include <QApplication>
#include <QDateTime>

#include "Tools/tool_jsonmanager.h"

QVariantMap ModData::loadJson(const QString &path)
{
    Tool_JsonManager *pJson = new Tool_JsonManager;
    pJson->deleteLater();
    QVariantMap map = pJson->readJsonObj(path);
    pJson = nullptr;
    return map;
}

void ModData::writeJson(const QVariant &data,const QString &path)
{
    Tool_JsonManager *pJson = new Tool_JsonManager;
    pJson->deleteLater();
    pJson->writeJson(data,path);
    pJson = nullptr;
}

void ModData::iniComboxFromJson(QComboBox *pCombox, const QString &path, QList<int> &values)
{
    Tool_JsonManager *pJson = new Tool_JsonManager;
    pJson->deleteLater();
    bool isMap = false;
    QVariantMap map = pJson->readJson(path,isMap).first().toMap();
    iniComboxFromJson(pCombox,map,values);
    //    values = mapNumberKey(map);
    //    QStringList lst;
    //    for (int key : values) {
    //        lst.append(map.value(QString::number(key)).toString());
    //    }
    //    pCombox->addItems(lst);
    pJson = nullptr;
}

void ModData::iniComboxFromJson(QComboBox *pCombox, QVariantMap &map, QList<int> &values)
{
    pCombox->clear();
    values = mapNumberKey(map);
    QStringList lst;
    for (int key : values) {
        lst.append(map.value(QString::number(key)).toString());
    }
    pCombox->addItems(lst);
}

QList<int> ModData::mapNumberKey(const QVariantMap &map)
{
    bool isOK = true;
    QList<int> numberKeys;
    QStringList keys = map.keys();
    for (QString key : keys) {
        numberKeys.append(key.toInt(&isOK));
        if(!isOK){
            return numberKeys;
        }
    }
    qSort(numberKeys.begin(), numberKeys.end());
    return numberKeys;
}

void ModData::sortListFromNumberKey(QVariantList &list,QString key)
{
    QVariantList resList;
    QMap<int,int> temps;
    QList<int> numberKeys;
    for (int i = 0; i < list.count(); ++i) {
        QVariantMap map = list.at(i).toMap();
        int v = map.value(key).toInt();
        temps.insert(v,i);
        numberKeys.append(v);
    }
    qSort(numberKeys.begin(), numberKeys.end());
    for (int key : numberKeys) {
        resList.append(list[temps.value(key)]);
    }
    list = resList;
}

QString ModData::currentDateTimeStr()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

QVariantList ModData::mergeDatas(QVariantList lst1, QVariantList lst2, const QString &flagKey)
{
    for (int i = 0; i < lst1.count(); ++i) {
        QVariantMap map1 = lst1[i].toMap();
        if(lst2.isEmpty()){
            break;
        }
        for (int j = 0; j < lst2.count(); ++j) {
            QVariantMap map2 = lst2[j].toMap();
            if(map1.value(flagKey) == map2.value(flagKey)){
                lst1[i] = lst2[j];
                lst2.removeAt(j);
                break;
            }
        }
    }
    lst1 += lst2;
    return lst1;
}

void ModData::loadCurrentBuffDatas()
{
    MOD_DATA.loadBuffs(MOD_DATA.catchPath + "BuffJsonData/",MOD_DATA.buffs);
    MOD_DATA.loadBuffSeids(MOD_DATA.catchPath + "BuffJsonData/",MOD_DATA.buffSeids);
}

void ModData::loadSystemDatas()
{
    loadBuffs(MOD_PATH_SYS + "BuffJsonData/",MOD_DATA.buffs_sys);
    loadBuffSeids(MOD_PATH_SYS + "BuffSeidJsonData/",MOD_DATA.buffSeids_sys);

    loadSeidFormClass();
    loadBuffSeidClass();
    loadSkillSeidClass();
}

void ModData::loadBuffSeids(QString path,QVariantList &list)
{
    Tool_JsonManager *pJsonMgr = new Tool_JsonManager;
    pJsonMgr->deleteLater();
    list.clear();
    QStringList buffJons = MOD_DATA.getDirFiles(path);
    foreach (QString json, buffJons) {
        if(json.isEmpty()){
            continue;
        }
        QVariantList datas = pJsonMgr->readJson(path + json);
        QVariantMap map;
        if(!datas.isEmpty()){
            map = datas.first().toMap();
        }
        map.insert("id",json.replace(".json",""));
        list.append(map);
    }
    MOD_DATA.sortListFromNumberKey(list,"id");
    pJsonMgr = nullptr;
}

void ModData::loadBuffSeidClass()
{
    Tool_JsonManager *pJsonMgr = new Tool_JsonManager;
    pJsonMgr->deleteLater();
    MOD_DATA.buffSeidClass = pJsonMgr->readJson(QApplication::applicationDirPath() + "/ConfigsJson/buff/buffSeid.json").first().toMap();
    pJsonMgr = nullptr;
}

void ModData::loadSkillSeidClass()
{
    Tool_JsonManager *pJsonMgr = new Tool_JsonManager;
    pJsonMgr->deleteLater();
    MOD_DATA.skillSeidClass = pJsonMgr->readJsonObj(QApplication::applicationDirPath() + "/ConfigsJson/skill/skillSeid.json");
    pJsonMgr = nullptr;
}

void ModData::loadSeidFormClass()
{
    Tool_JsonManager *pJsonMgr = new Tool_JsonManager;
    pJsonMgr->deleteLater();
    MOD_DATA.seidFormClass = pJsonMgr->readJson(QApplication::applicationDirPath() + "/ConfigsJson/seid/formType.json");
    MOD_DATA.sortListFromNumberKey(MOD_DATA.seidFormClass,"index");
    pJsonMgr = nullptr;
}

void ModData::loadBuffs(QString path, QVariantList &list)
{
    Tool_JsonManager *pJsonMgr = new Tool_JsonManager;
    pJsonMgr->deleteLater();
    list.clear();
    QStringList buffJons = MOD_DATA.getDirFiles(path);
    foreach (QString json, buffJons) {
        if(json.isEmpty()){
            continue;
        }
        list.append(pJsonMgr->readJson(path + json).first().toMap());
    }
    MOD_DATA.sortListFromNumberKey(list,"buffid");
    pJsonMgr = nullptr;
}

void ModData::removeSeids(const QVariantList &seids, const QString &path, const QString &id)
{
    Tool_JsonManager *pJsonMgr = new Tool_JsonManager;
    pJsonMgr->deleteLater();
    QString path2 = path;
    for (QVariant var : seids) {
        QString seid = var.toString();
        path2 = path + seid + ".json";
        QVariantMap map2 = pJsonMgr->readJsonObj(path2);
        if(map2.contains(id)){
            map2.remove(id);
            pJsonMgr->writeJson(map2,path2);
        }
    }

    pJsonMgr = nullptr;
}

void ModData::clearDirectory(const QString &path)
{
    if(path.isEmpty()){
        return;
    }
    QDir dir(path);
    dir.removeRecursively();
    dir.mkdir(path);
}

void ModData::clearCatches()
{
    if(MOD_DATA.catchPath.isEmpty()){
        return;
    }
    QDir dir(MOD_DATA.catchPath);
    dir.removeRecursively();
}

QStringList ModData::getDirFiles(const QString &dirPath, bool isAbs)
{
    QStringList lst;
    QDir dir(dirPath);
    if (!dir.exists()) {
        return lst;
    }
    dir.setFilter(QDir::Files);

    QFileInfoList files = dir.entryInfoList();
    for (int i = 0; i < files.size(); ++i) {
        QFileInfo fileInfo = files.at(i);
        if(!isAbs){
            lst.append(fileInfo.fileName());
        }else{
            lst.append(dirPath + fileInfo.fileName());
        }
    }
    return lst;
}

bool ModData::createDirectory(const QString &path)
{
    QDir dir(path);
    if(dir.exists()){
        return true;
    }
    return dir.mkdir(path);
}

bool ModData::removeFile(const QString &path)
{
    if(!QFile::exists(path)){
        return true;
    }

    return QFile::remove(path);
}

bool ModData::copyDirectory(const QString &srcPath, const QString &dstPath, bool coverFileIfExist)
{
    QDir srcDir(srcPath);
    QDir dstDir(dstPath);
    if (!dstDir.exists()) { //目的文件目录不存在则创建文件目录
        if (!dstDir.mkdir(dstDir.absolutePath()))
            return false;
    }
    QFileInfoList fileInfoList = srcDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList) {
        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if (fileInfo.isDir()) {    // 当为目录时，递归的进行copy
            if (!copyDirectory(fileInfo.filePath(),dstDir.filePath(fileInfo.fileName()),coverFileIfExist))
                return false;
        }
        else {            //当允许覆盖操作时，将旧文件进行删除操作
            if (coverFileIfExist && dstDir.exists(fileInfo.fileName())) {
                dstDir.remove(fileInfo.fileName());
            }
            /// 进行文件copy
            if (!QFile::copy(fileInfo.filePath(), dstDir.filePath(fileInfo.fileName()))) {
                return false;
            }
        }
    }
    return true;
}

bool ModData::copyFile(QString srcPath, QString dstPath, bool coverFileIfExist)
{
    srcPath.replace("\\", "/");
    dstPath.replace("\\", "/");
    if (srcPath == dstPath) {
        return true;
    }

    if (!QFile::exists(srcPath)) {  //源文件不存在
        return false;
    }

    if (QFile::exists(dstPath)) {
        if (coverFileIfExist) {
            QFile::remove(dstPath);
        }
    }

    if (!QFile::copy(srcPath, dstPath)){
        return false;
    }
    return true;
}

QString ModData::uuid()
{
    return QUuid::createUuid().toString().replace("{","").replace("}","");
}

