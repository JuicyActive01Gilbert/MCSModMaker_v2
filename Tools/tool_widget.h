#ifndef TOOL_WIDGET_H
#define TOOL_WIDGET_H

#include <QWidget>
#include <QVariantMap>

class Tool_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Tool_Widget(QWidget *parent = nullptr);
    ~Tool_Widget();

    virtual void setDatas(const QVariantMap &datas);
    virtual QVariantMap getDatas();

public slots:
    virtual void iniData();

signals:
    void widgetOK();
    void widgetCancel();
    void showInfo(QString info);

protected:
    void displayData(QVariantMap &data);

    void displayLineEdit(QVariantMap &data);
    void displayDoubleSpinBox(QVariantMap &data);
    void displayComboBox(QVariantMap &data);
    void displaySpinBox(QVariantMap &data);
    void displayListEdit(QVariantMap &data);

    void getDataFromLineEdit();
    void getDataFromDoubleSpinBox();
    void getDataFromComboBox();
    void getDataFromSpinBox();
    void getDataFromListEdit();


private:
    QVariantMap m_datas;
};

#endif // TOOL_WIDGET_H
