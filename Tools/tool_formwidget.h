#ifndef TOOL_FORMWIDGET_H
#define TOOL_FORMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "tool_widget.h"
#include "tool_listedit.h"
#include "tool_doubleedit.h"
#include "tool_numberedit.h"


#define FORM_NAME "name"
#define FORM_TYPE "type"
#define FORM_LABEL "label"

class Tool_FormWidget : public Tool_Widget
{
    Q_OBJECT
public:
    explicit Tool_FormWidget(QWidget *parent = nullptr);
    ~Tool_FormWidget();

    void iniForms(const QVariantList &forms);
    void clearForms();

protected:
    void initialize();

private:
    QVariantList m_forms;
    QList<QLabel*> m_labels;
    QList<QLineEdit*> m_edits;
    QList<Tool_DoubleEdit*> m_doubleEdits;
    QList<Tool_NumberEdit*> m_numberEdits;
    QList<Tool_ListEdit*> m_listEdits;


    QVBoxLayout *m_pLayout = nullptr;
};

#endif // TOOL_FORMWIDGET_H
