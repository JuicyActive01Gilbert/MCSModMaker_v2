#include "tool_jsonmanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

Tool_JsonManager::Tool_JsonManager(QObject *parent) : QObject(parent)
{

}

Tool_JsonManager::~Tool_JsonManager()
{

}

QVariantList Tool_JsonManager::readJson(const QString &path, bool &isMap)
{
    QVariantList datas;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        emit errorString(file.errorString());
        return datas;
    }
    QByteArray data = file.readAll();
    file.close();
    return parserJson(data,isMap);
}

QVariantList Tool_JsonManager::readJson(const QString &path)
{
    bool isMap = false;
    return readJson(path,isMap);
}

QVariantMap Tool_JsonManager::readJsonObj(const QString &path)
{
    bool isMap = false;
    QVariantList lst = readJson(path,isMap);
    if(lst.isEmpty()){
        return QVariantMap();
    }
    return lst.first().toMap();
}

bool Tool_JsonManager::writeJson(const QVariant &data,
                                 const QString &path)
{
    QJsonDocument document = QJsonDocument::fromVariant(data);
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)){
        emit errorString(file.errorString());
        qDebug() << __FUNCTION__ << file.errorString() << path;
        return false;
    }
    file.write(document.toJson());
    file.close();
    return true;
}

QVariantList Tool_JsonManager::parserJson(const QByteArray &data,bool &isMap)
{
    QVariantList datas;
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(data,&error);
    if(error.error != QJsonParseError::NoError){
        emit errorString(error.errorString());
        return QVariantList();
    }
    isMap = document.isObject();
    if(document.isArray()){
        datas = parserArray(document.array());
    }else if(document.isObject()){
        datas.append(parserObject(document.object()));
    }

    return datas;
}

QVariantList Tool_JsonManager::parserArray(const QJsonArray &array)
{
    QVariantList datas;
    for (QJsonValue val : array) {
        datas.append(parserVale(val));
    }
    return datas;
}

QVariantMap Tool_JsonManager::parserObject(const QJsonObject &obj)
{
    QVariantMap map;
    QStringList keys = obj.keys();
    for (QString key : keys) {
        map.insert(key,parserVale(obj.value(key)));
    }
    return map;
}

QVariant Tool_JsonManager::parserVale(const QJsonValue &val)
{
    switch (val.type()) {
    case QJsonValue::Array:
        return QVariant(parserArray(val.toArray()));
    case QJsonValue::Double:
        return val.toDouble();
    case QJsonValue::Object:
        return parserObject(val.toObject());
    case QJsonValue::String:
        return val.toString();
    case QJsonValue::Bool:
        return val.toBool();
    default:
        break;
    }

    return QVariant();
}

