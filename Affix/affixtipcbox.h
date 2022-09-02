#ifndef AFFIXTIPCBOX_H
#define AFFIXTIPCBOX_H

#include <QWidget>
#include <QComboBox>

class Tool_JsonManager;
class AffixTipCBox : public QComboBox
{
    Q_OBJECT
public:
    explicit AffixTipCBox(QWidget *parent = nullptr);
    ~AffixTipCBox();

    void initialize();

private:
    Tool_JsonManager *m_pJsonMgr = nullptr;
};

#endif // AFFIXTIPCBOX_H
