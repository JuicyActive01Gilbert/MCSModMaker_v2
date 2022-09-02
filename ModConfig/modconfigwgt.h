#ifndef MODCONFIGWGT_H
#define MODCONFIGWGT_H

#include "ui_modconfigwgt.h"
#include <QWidget>

#include "Tools/tool_widget.h"
#include "ModData.h"

class Tool_JsonManager;
class ModConfigWgt : public Tool_Widget,public Ui_ModConfigWgt
{
    Q_OBJECT

public:
    explicit ModConfigWgt(QWidget *parent = nullptr);
    ~ModConfigWgt();

public slots:
    void iniData() override;

protected slots:
    void onOK();

private:
    QString m_cfgPath;
    Tool_JsonManager *m_pJsonMgr = nullptr;

};

#endif // MODCONFIGWGT_H
