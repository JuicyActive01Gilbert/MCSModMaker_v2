#ifndef MODDATA_H
#define MODDATA_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QComboBox>

#define MOD_DATA ModData::getInstance()
#define MOD_PATH_SYS QApplication::applicationDirPath() + "/OutPut/Data/"
#define APP_PATH QApplication::applicationDirPath() + "/"
#define CFG_PATH QApplication::applicationDirPath() + "/ConfigsJson/"
#define CATCH_PATH APP_PATH + "Catches/"
#define APP_TEMP_PATH QApplication::applicationDirPath() + "/Temps/"

class ModData {
public:

    QVariantList buffs;             //自定义
    QVariantList buffSeids;         //自定义

    QVariantList buffs_sys;         //系统
    QVariantList buffSeids_sys;     //系统

    QVariantMap buffSeidClass;      //buffseid类型
    QVariantMap skillSeidClass;     //神通seid类型
    QVariantList seidFormClass;     //seid分类


    QVariantMap skills;             //神通
    QVariantMap skills_sys;

    QVariantMap staticSkills;       //功法
    QVariantMap staticSkills_sys;

    QVariantMap items;               //物品
    QVariantMap items_sys;


    QString modPath = "";           //MOD路径
    QString catchPath = "";         //缓存路径

    QVariantMap loadJson(const QString &path);
    void writeJson(const QVariant &data,const QString &path);

    bool createFile(QString path);

    void iniComboxFromJson(QComboBox *pCombox, const QString &path, QList<int> &values);
    void iniComboxFromJson(QComboBox *pCombox, QVariantMap &map, QList<int> &values);
    QList<int> mapNumberKey(const QVariantMap &map);
    void sortListFromNumberKey(QVariantList &list, QString key = "id");
    QString currentDateTimeStr();
    QVariantList mergeDatas(QVariantList lst1,QVariantList lst2,const QString &flagKey);

    void loadCurrentBuffDatas();
    void loadCurrentSkillDatas();

    void loadSystemDatas();
    void loadBuffSeids(QString path, QVariantList &list);

    void loadBuffSeidClass();
    void loadSkillSeidClass();

    void loadSeidFormClass();
    void loadBuffs(QString path, QVariantList &list);

    void removeSeids(const QVariantList &seids,const QString &path,const QString &id);

    void clearDirectory(const QString &path);
    void clearCatches();
    QStringList getDirFiles(const QString &dirPath,bool isAbs = false);
    bool createDirectory(const QString &path);
    bool removeFile(const QString &path);

    //(源文件目录路劲，目的文件目录，文件存在是否覆盖)
    bool copyDirectory(const QString& srcPath, const QString& dstPath, bool coverFileIfExist = true);
    //(源文件文件路径，目的文件路径，文件存在是否覆盖)
    bool copyFile(QString srcPath, QString dstPath, bool coverFileIfExist = true);
    QString uuid();

    static ModData& getInstance() {
        static ModData value;
        return value;
    }

private:
    ModData() = default;
    ModData(const ModData& other) = delete;
    ModData& operator = (const ModData&) = delete;

};

#endif // MODDATA_H
