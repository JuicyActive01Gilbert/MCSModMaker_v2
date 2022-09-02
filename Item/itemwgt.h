#ifndef ITEMWGT_H
#define ITEMWGT_H

#include "ui_itemwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"

class Tool_JsonManager;
class ItemWgt : public Tool_Widget,public Ui_ItemWgt
{
    Q_OBJECT

public:
    explicit ItemWgt(QWidget *parent = nullptr);
    ~ItemWgt();

    void setDatas(const QVariantMap &datas) override;
    QVariantMap getDatas() override;

protected:
    void initialize();

    void enableWidget(QWidget *pWgt,bool isEnable);
protected slots:
    void dealForm(int index);
    void displayIcon();
    void onDeleteCustomIcon();
    void onCustomIcon();

    void onCancel();
    void onOK();
    void onOpenSeid();
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
};

#endif // ITEMWGT_H
