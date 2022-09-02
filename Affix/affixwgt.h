#ifndef AFFIXWGT_H
#define AFFIXWGT_H

#include "ui_affixwgt.h"
#include <QWidget>
#include "Tools/tool_widget.h"

class Tool_JsonManager;
class AffixWgt : public Tool_Widget,public Ui_AffixWgt
{
    Q_OBJECT

public:
    explicit AffixWgt(QWidget *parent = nullptr);
    ~AffixWgt();

    void setDatas(const QVariantMap &datas) override;
    QVariantMap getDatas() override;

protected slots:
    void onOK();

protected:
    void initialize();
private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
    QList<int> m_affixType;

};

#endif // AFFIXWGT_H
