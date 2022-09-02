#include "loaddatawgt.h"

#include <QPainter>

LoadDataWgt::LoadDataWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

LoadDataWgt::~LoadDataWgt()
{

}

void LoadDataWgt::setData(const QVariantMap &data)
{
    m_pLabName->setVisible(!data.isEmpty());
    m_pLabNameText->setVisible(!data.isEmpty());
    m_pLabTime->setVisible(!data.isEmpty());
    m_pLabTimeText->setVisible(!data.isEmpty());
    m_pLabPath->setVisible(!data.isEmpty());
    m_pLabPathText->setVisible(!data.isEmpty());
    m_pBtnDelete->setVisible(!data.isEmpty());

    m_data = data;
    if(!m_data.isEmpty()){
        m_pLabNameText->setText(data.value("name").toString());
        m_pLabTimeText->setText(data.value("time").toString());
        m_pLabPathText->setText(data.value("path").toString());
        m_flag = data.value("flag").toString();
    }
}

QString LoadDataWgt::getFlag()
{
    return m_data.value("flag").toString();
}

void LoadDataWgt::onDelete()
{
    emit deleteData(m_flag);
}

void LoadDataWgt::initialize()
{
//    this->setMouseTracking(true);
    m_pBtnDelete->setProperty("ButtonColor","Del");
    m_pLabName->setProperty("LabelType","LoadData");
    m_pLabTime->setProperty("LabelType","LoadData");
    m_pLabPath->setProperty("LabelType","LoadData");

    m_pLabNameText->setProperty("LabelType","LoadDataText");
    m_pLabTimeText->setProperty("LabelType","LoadDataText");
    m_pLabPathText->setProperty("LabelType","LoadDataText");

    connect(m_pBtnDelete,SIGNAL(clicked(bool)),this,SLOT(onDelete()));
}

void LoadDataWgt::mousePressEvent(QMouseEvent *event)
{
    emit pressData(m_flag);
    QWidget::mousePressEvent(event);
}

void LoadDataWgt::enterEvent(QEvent *event)
{
    m_isHover = true;
    this->update();
    QWidget::enterEvent(event);
}

void LoadDataWgt::leaveEvent(QEvent *event)
{
    m_isHover = false;
    this->update();
    QWidget::leaveEvent(event);
}


void LoadDataWgt::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::transparent);

    QString path = ":/resources/LoadData/load_normal.png";
    if(m_isHover){
        path =  ":/resources/LoadData/load_hover.png";
    }
    painter.drawPixmap(this->rect(),QPixmap(path));

    if(m_data.isEmpty()){
        painter.setPen(QPen(QColor(182,188,144)));
        painter.setFont(QFont("CloudShuiZhu-GB Normal",40));
        painter.drawText(this->rect(),tr("空"),QTextOption(Qt::AlignCenter));
    }

}
