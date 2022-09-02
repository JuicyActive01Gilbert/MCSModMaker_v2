#ifndef INITIALIZEWIN_H
#define INITIALIZEWIN_H

#include "ui_initializewin.h"
#include <QWidget>

class InitializeWin : public QWidget,public Ui_InitializeWin
{
    Q_OBJECT

public:
    InitializeWin(QWidget *parent = nullptr);
    ~InitializeWin();

signals:
    void startMake();
    void quitMake();

protected:
    void initialize();

    void paintEvent(QPaintEvent *event);

private:

};
#endif // INITIALIZEWIN_H
