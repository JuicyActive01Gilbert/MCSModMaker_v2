#ifndef BUFFWGT_H
#define BUFFWGT_H

#include "ui_buffwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"

class Tool_JsonManager;
class BuffWgt : public Tool_Widget,public Ui_BuffWgt
{
    Q_OBJECT

public:
    explicit BuffWgt(QWidget *parent = nullptr);
    ~BuffWgt();

    void setDatas(const QVariantMap &datas) override;
    QVariantMap getDatas() override;

signals:
    void buffOK();
protected slots:
    void onCustomIcon();
    void onNameChange(QString text);
    void onCancel();
    void onOK();
    void onOpenSeid();
    void onDeleteCustomIcon();

    void displayIcon();
protected:
    void initialize();

private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    bool m_isEdit = false;
    int m_nIndex = -1;

    QList<int> m_triggers;
    QList<int> m_removeTriggers;
    QList<int> m_BuffTypes;
    QList<int> m_bufftypes;
//    QList<int> m_seidTips;
};

#endif // BUFFWGT_H
