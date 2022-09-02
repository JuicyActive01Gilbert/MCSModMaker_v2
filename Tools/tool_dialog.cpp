#include "tool_dialog.h"

#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QRect>



Tool_Dialog::Tool_Dialog(Tool_Widget *centerWidget, QWidget *parent):QDialog(parent)
{
    setCenterWgt(centerWidget);
}

Tool_Dialog::Tool_Dialog(QWidget *parent):QDialog(parent)
{

}

Tool_Dialog::~Tool_Dialog()
{

}

void Tool_Dialog::setCenterWgt(Tool_Widget *centerWidget)
{
    m_pCenter = centerWidget;
    if(nullptr == m_pCenter->parent()){
        m_pCenter->setParent(this);
    }
    initialize();
}

void Tool_Dialog::onWidgetClose()
{
//    closeDialog(QDialog::Rejected);
    this->reject();
}

void Tool_Dialog::onWidgetOK()
{
//    closeDialog(QDialog::Accepted);
    this->accept();
}


void Tool_Dialog::initialize()
{
//    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
//    this->setAttribute(Qt::WA_TranslucentBackground, true);

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(10);
    pLayout->addWidget(m_pCenter);
    this->setLayout(pLayout);

    if(m_pCenter){
        connect(m_pCenter,SIGNAL(widgetOK()),this,SLOT(onWidgetOK()));
        connect(m_pCenter,SIGNAL(widgetCancel()),this,SLOT(onWidgetClose()));
    }

//    iniShadow();
}

