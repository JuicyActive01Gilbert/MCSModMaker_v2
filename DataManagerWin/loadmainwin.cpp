#include "loadmainwin.h"

#include <QPainter>
#include <QPixmap>

#include "ModData.h"

LoadMainWin::LoadMainWin(QWidget *parent) : Tool_Widget(parent)
{
    setupUi(this);
    initialize();
}

LoadMainWin::~LoadMainWin()
{

}

void LoadMainWin::loadDatas()
{
    QVariantMap datas = MOD_DATA.loadJson(CFG_PATH + "savedatas/save.json");
    m_pDataWgt->setDatas(datas);
}

void LoadMainWin::initialize()
{
    m_pBtnBack->setProperty("ButtonColor","Back");
    connect(m_pBtnBack,SIGNAL(clicked(bool)),this,SIGNAL(backInitialize()));
    connect(m_pDataWgt,SIGNAL(loadMod()),this,SIGNAL(loadMod()));
}

void LoadMainWin::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/resources/background/load.png"));

}
