#ifndef CREATEAVATARWGT_H
#define CREATEAVATARWGT_H

#include "ui_createavatarwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"


class CreateAvatarWgt : public Tool_Widget,public Ui_CreateAvatarWgt
{
    Q_OBJECT

public:
    explicit CreateAvatarWgt(QWidget *parent = nullptr);
    ~CreateAvatarWgt();

     void setDatas(const QVariantMap &datas) override;
     QVariantMap getDatas() override;

protected slots:
     void onOK();
     void onSeidManager();
protected:
     void initialize();

private:

};

#endif // CREATEAVATARWGT_H
