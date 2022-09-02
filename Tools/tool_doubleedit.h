#ifndef TOOL_DOUBLEEDIT_H
#define TOOL_DOUBLEEDIT_H

#include <QDoubleSpinBox>

class Tool_DoubleEdit : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit Tool_DoubleEdit(QWidget *parent = nullptr);
    ~Tool_DoubleEdit();

protected:
    void initialize();

};

#endif // TOOL_DOUBLEEDIT_H
