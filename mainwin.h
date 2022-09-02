#ifndef MAINWIN_H
#define MAINWIN_H

#include "ui_mainwin.h"
#include <QWidget>

#include "initializewin.h"
#include "DataManagerWin/loadmainwin.h"
#include "MakerWin/makermainwin.h"

class MainWin : public QWidget,public  Ui_MainWin
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();

protected slots:
    void onStartMake();
    void onLoadBack();
    void onLoadMod();
protected:
    void initialize();

private:
    InitializeWin *m_pIniWin    = nullptr;
    LoadMainWin *m_pLoadWin     = nullptr;
    MakerMainWin *m_pMakerWin   = nullptr;


};

#endif // MAINWIN_H
