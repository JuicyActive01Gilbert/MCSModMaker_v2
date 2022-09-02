#include "tool_formwidget.h"

Tool_FormWidget::Tool_FormWidget(QWidget *parent) : Tool_Widget(parent)
{
    initialize();
}

Tool_FormWidget::~Tool_FormWidget()
{

}

void Tool_FormWidget::iniForms(const QVariantList &forms)
{
    clearForms();
    m_forms = forms;
    for (int i = forms.count() - 1; i >= 0;--i) {
        QVariant var = forms[i];
        QVariantMap f = var.toMap();
        QHBoxLayout *pLayout = new QHBoxLayout;
        QLabel *pLabel = new QLabel;
        pLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        pLabel->setText(f.value(FORM_LABEL).toString());
        pLabel->setFixedWidth(100);
        pLayout->addWidget(pLabel);
        pLabel->setFixedHeight(30);
//        pLabel->setMaximumWidth(75);
        m_labels.append(pLabel);

        int type = f.value(FORM_TYPE).toInt();
        switch (type) {
        case 0:    //lineEdit
        {
            QLineEdit *pEdt = new QLineEdit;
            pEdt->setObjectName(f.value(FORM_NAME).toString());
            pEdt->setFixedHeight(30);
            pLayout->addWidget(pEdt);
            m_edits.append(pEdt);
        }
            break;
        case 1:     //doubleEdit
        {
            Tool_DoubleEdit *pEdt = new Tool_DoubleEdit;
            pEdt->setObjectName(f.value(FORM_NAME).toString());
            pEdt->setFixedHeight(30);
            pLayout->addWidget(pEdt);
            m_doubleEdits.append(pEdt);
        }
            break;
        case 2:     //numberEidt
        {
            Tool_NumberEdit *pEdt = new Tool_NumberEdit;
            pEdt->setObjectName(f.value(FORM_NAME).toString());
            pEdt->setFixedHeight(30);
            pLayout->addWidget(pEdt);
            m_numberEdits.append(pEdt);
        }
            break;
        case 3:     //listEidt
        {
            Tool_ListEdit *pEdt = new Tool_ListEdit;
            pEdt->setObjectName(f.value(FORM_NAME).toString());
            pEdt->setFixedHeight(30);
            pLayout->addWidget(pEdt);
            m_listEdits.append(pEdt);
        }
            break;
        default:
            break;
        }
        m_pLayout->insertLayout(0,pLayout);
    }

}

void Tool_FormWidget::clearForms()
{
    for (auto p : m_labels) {
        m_pLayout->removeWidget(p);
        delete p;
        p = nullptr;
    }

    for (auto p : m_edits) {
        m_pLayout->removeWidget(p);
        delete p;
        p = nullptr;
    }

    for (auto p : m_doubleEdits) {
        m_pLayout->removeWidget(p);
        delete p;
        p = nullptr;
    }

    for (auto p : m_numberEdits) {
        m_pLayout->removeWidget(p);
        delete p;
        p = nullptr;
    }

    for (auto p : m_listEdits) {
        m_pLayout->removeWidget(p);
        delete p;
        p = nullptr;
    }

    m_labels.clear();
    m_edits.clear();
    m_doubleEdits.clear();
    m_numberEdits.clear();
    m_listEdits.clear();

}

void Tool_FormWidget::initialize()
{
    m_pLayout = new QVBoxLayout;
    m_pLayout->addStretch();
    this->setLayout(m_pLayout);
}
