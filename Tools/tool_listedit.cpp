#include "tool_listedit.h"

Tool_ListEdit::Tool_ListEdit(QWidget *parent) : QLineEdit(parent)
{

}

Tool_ListEdit::~Tool_ListEdit()
{

}

void Tool_ListEdit::setValue(const QVariantList &list)
{
    QString text;
    for (QVariant v : list) {
        text += v.toString() + ",";
    }
    if(text.isEmpty()){
       return;
    }
    text.chop(1);
    this->setText(text);
}

QVariantList Tool_ListEdit::getValue()
{
    QVariantList list;
    QStringList tList = getValueList();
    for (auto s : tList) {
        list.append(s.toInt());
    }
    return list;
}

QStringList Tool_ListEdit::getValueList()
{
    QString text = this->text().trimmed();
    if(text.isEmpty()){
        return QStringList();
    }
    text = text.replace("，",",");
    QStringList tList = text.split(",");
    return tList;
}
