#include "buffseidtipcbox.h"
#include <QApplication>
#include "ModData.h"

BuffSeidTipCBox::BuffSeidTipCBox(QWidget *parent) : QComboBox(parent)
{
    initialize();
}

BuffSeidTipCBox::~BuffSeidTipCBox()
{

}

void BuffSeidTipCBox::initialize()
{
    QList<int> seidTips;
    MOD_DATA.iniComboxFromJson(this,
                               QApplication::applicationDirPath() + "/ConfigsJson/buff/seidTip.json",
                               seidTips);
}
