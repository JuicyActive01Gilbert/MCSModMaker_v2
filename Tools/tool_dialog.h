#ifndef TOOL_DIALOG_H
#define TOOL_DIALOG_H

#include <QDialog>
#include <QResizeEvent>
#include "tool_widget.h"

class Tool_Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Tool_Dialog(Tool_Widget *centerWidget, QWidget *parent = nullptr);
    explicit Tool_Dialog(QWidget *parent = nullptr);
    ~Tool_Dialog();

    void setCenterWgt(Tool_Widget *centerWidget);

protected slots:
    void onWidgetClose();
    void onWidgetOK();
protected:
    void initialize();

private:
    Tool_Widget *m_pCenter = nullptr;
    QDialog::DialogCode m_code;

};

#endif // TOOL_DIALOG_H
