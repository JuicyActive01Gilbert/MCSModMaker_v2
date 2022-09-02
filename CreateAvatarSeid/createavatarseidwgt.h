#ifndef CREATEAVATARSEIDWGT_H
#define CREATEAVATARSEIDWGT_H

#include "ui_createavatarseidwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"

class Tool_JsonManager;
class CreateAvatarSeidWgt : public Tool_Widget,public Ui_CreateAvatarSeidWgt
{
    Q_OBJECT
public:
    explicit CreateAvatarSeidWgt(const QString &tipsPath,
                                 const QString &tipsClassPath,
                                 const QString &saveDir,
                                 const QString &idKey,QWidget *parent = nullptr);
    ~CreateAvatarSeidWgt();

    void setSeidList(QStringList text,int dataID);

protected slots:
    void onSeidChange(int index);
    void onOK();
protected:
    void initialize();
    void displayData();
private:
    QString m_tipsPath;
    QString m_seidClassPath;
    QString m_saveDir;
    QString m_idKey;
    int m_dataID = 0;
    QVariantMap m_seidTips;
    QVariantMap m_seidClass;
    QList<int> m_seidIndex;
    Tool_JsonManager *m_pJsonMgr = nullptr;
};

#endif // CREATEAVATARSEIDWGT_H
