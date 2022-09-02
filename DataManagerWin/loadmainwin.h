#ifndef LOADMAINWIN_H
#define LOADMAINWIN_H

#include "ui_loadmainwin.h"
#include <QWidget>
#include "Tools/tool_widget.h"
#include "loadlistwgt.h"


class LoadMainWin : public Tool_Widget,public Ui_LoadMainWin
{
    Q_OBJECT
public:
    explicit LoadMainWin(QWidget *parent = nullptr);
    ~LoadMainWin();

    void clearDatas();

signals:
    void backInitialize();
    void loadMod();
public slots:
    void loadDatas();
protected:
    void initialize();

    void paintEvent(QPaintEvent *event);


private:

};

#endif // LOADMAINWIN_H
