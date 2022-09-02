#include "initializewin.h"
#include <QPainter>
#include <QImage>

InitializeWin::InitializeWin(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    initialize();
}

InitializeWin::~InitializeWin()
{

}

void InitializeWin::initialize()
{
    m_pLabTitle->setProperty("LabelType","Title");
    m_pLabTitle2->setProperty("LabelType","Title");
//    label_5->setProperty("LabelType","Title");
    m_pBtnStart->setProperty("ButtonColor","MainBtn");
    m_pBtnQuit->setProperty("ButtonColor","MainBtn");

    this->setWindowTitle(tr("《觅长生》Mod制作v2.0.0"));

    connect(m_pBtnStart,SIGNAL(clicked(bool)),this,SIGNAL(startMake()));
    connect(m_pBtnQuit,SIGNAL(clicked(bool)),this,SIGNAL(quitMake()));

}

void InitializeWin::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/resources/background/bg.png"));

}

