#ifndef TOOL_JSONMANAGER_H
#define TOOL_JSONMANAGER_H

#include <QObject>
#include <QVariantMap>
#include <QVariantList>

class Tool_JsonManager : public QObject
{
    Q_OBJECT
public:
    explicit Tool_JsonManager(QObject *parent = nullptr);
    ~Tool_JsonManager();

    QVariantList readJson(const QString &path,bool &isMap);
    QVariantList readJson(const QString &path);
    QVariantMap readJsonObj(const QString &path);
    bool writeJson(const QVariant &data,
                   const QString &path);

signals:
    void errorString(QString errorText);

protected:
    QVariantList parserJson(const QByteArray &data,bool &isMap);
    QVariantList parserArray(const QJsonArray &array);
    QVariantMap parserObject(const QJsonObject &obj);
    QVariant parserVale(const QJsonValue &val);


};

#endif // TOOL_JSONMANAGER_H
