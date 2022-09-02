#include "tool_widget.h"
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>

#include "tool_listedit.h"

#include <QDebug>

Tool_Widget::Tool_Widget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("觅长生可视化制作工具");
}

Tool_Widget::~Tool_Widget()
{

}

void Tool_Widget::setDatas(const QVariantMap &datas)
{
    m_datas = datas;
    QVariantMap map = datas;
    displayData(map);
}

QVariantMap Tool_Widget::getDatas()
{
    getDataFromComboBox();
    getDataFromDoubleSpinBox();
    getDataFromSpinBox();
    getDataFromLineEdit();

    getDataFromListEdit();

    m_datas.remove("");
    return m_datas;
}

void Tool_Widget::iniData()
{

}

void Tool_Widget::displayData(QVariantMap &data)
{
    displayListEdit(data);
    displayComboBox(data);
    displayDoubleSpinBox(data);
    displaySpinBox(data);
    displayLineEdit(data);
}

void Tool_Widget::displayLineEdit(QVariantMap &data)
{
    QList<QLineEdit*> children = this->findChildren<QLineEdit*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        if(data.contains(key)){
            p->setText(data.value(key).toString());
            data.remove(key);
        }
    }
}

void Tool_Widget::displayDoubleSpinBox(QVariantMap &data)
{
    QList<QDoubleSpinBox*> children = this->findChildren<QDoubleSpinBox*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        if(data.contains(key)){
            p->setValue(data.value(key).toDouble());
            data.remove(key);
        }
    }
}

void Tool_Widget::displayComboBox(QVariantMap &data)
{
    QList<QComboBox*> children = this->findChildren<QComboBox*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        if(data.contains(key)){
            p->setCurrentIndex(data.value(key).toInt());
            data.remove(key);
        }
    }
}

void Tool_Widget::displaySpinBox(QVariantMap &data)
{
    QList<QSpinBox*> children = this->findChildren<QSpinBox*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        if(data.contains(key)){
            p->setValue(data.value(key).toInt());
            data.remove(key);
        }
    }
}

void Tool_Widget::displayListEdit(QVariantMap &data)
{
    QList<Tool_ListEdit*> children = this->findChildren<Tool_ListEdit*>();
    foreach (Tool_ListEdit *p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        if(data.contains(key)){
            p->setValue(data.value(key).toList());
            data.remove(key);
        }
    }
}

void Tool_Widget::getDataFromLineEdit()
{
    QList<QLineEdit*> children = this->findChildren<QLineEdit*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        m_datas.insert(key,p->text().trimmed());
    }
}

void Tool_Widget::getDataFromDoubleSpinBox()
{
    QList<QDoubleSpinBox*> children = this->findChildren<QDoubleSpinBox*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        m_datas.insert(key,p->value());
    }
}

void Tool_Widget::getDataFromComboBox()
{
    QList<QComboBox*> children = this->findChildren<QComboBox*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        m_datas.insert(key,p->currentIndex());
    }
}

void Tool_Widget::getDataFromSpinBox()
{
    QList<QSpinBox*> children = this->findChildren<QSpinBox*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        m_datas.insert(key,p->value());
    }
}

void Tool_Widget::getDataFromListEdit()
{
    QList<Tool_ListEdit*> children = this->findChildren<Tool_ListEdit*>();
    foreach (auto p, children) {
        QString key = p->objectName();
        if(key.contains("qt_")){
            continue;
        }
        m_datas.insert(key,p->getValue());
    }
}
