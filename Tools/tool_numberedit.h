#ifndef TOOL_NUMBEREDIT_H
#define TOOL_NUMBEREDIT_H

#include <QSpinBox>

class Tool_NumberEdit : public QSpinBox
{
    Q_OBJECT
public:
    explicit Tool_NumberEdit(QWidget *parent = nullptr);
    ~Tool_NumberEdit();


protected:
    void initialize();
};

#endif // TOOL_NUMBEREDIT_H
