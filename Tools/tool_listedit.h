#ifndef TOOL_LISTEDIT_H
#define TOOL_LISTEDIT_H

#include <QLineEdit>
#include <QVariantList>

class Tool_ListEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit Tool_ListEdit(QWidget *parent = nullptr);
    ~Tool_ListEdit();

    void setValue(const QVariantList &list);
    QVariantList getValue();
    QStringList getValueList();

signals:

};

#endif // TOOL_LISTEDIT_H
