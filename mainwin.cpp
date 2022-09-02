#include "mainwin.h"


MainWin::MainWin(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initialize();
}

MainWin::~MainWin()
{
    MOD_DATA.clearCatches();
}

void MainWin::onStartMake()
{
    m_pLoadWin->loadDatas();
    m_pStackWgt->setCurrentWidget(m_pLoadWin);
}

void MainWin::onLoadBack()
{
    m_pStackWgt->setCurrentWidget(m_pIniWin);
}

void MainWin::onLoadMod()
{

    m_pStackWgt->setCurrentWidget(m_pMakerWin);
        m_pMakerWin->onTBtnChecked(0);
    //    m_pMakerWin->iniDatas();
}

void MainWin::initialize()
{
    this->setWindowTitle("觅长生Mod可视化制作工具");
    m_pIniWin = new InitializeWin;
    m_pLoadWin = new LoadMainWin;
    m_pMakerWin = new MakerMainWin;

    MOD_DATA.loadSeidFormClass();

    m_pStackWgt->addWidget(m_pLoadWin);
    m_pStackWgt->addWidget(m_pIniWin);
    m_pStackWgt->addWidget(m_pMakerWin);

    m_pStackWgt->setCurrentWidget(m_pIniWin);

    connect(m_pIniWin,SIGNAL(startMake()),this,SLOT(onStartMake()));
    connect(m_pIniWin,SIGNAL(quitMake()),this,SLOT(close()));

    connect(m_pLoadWin,SIGNAL(backInitialize()),this,SLOT(onLoadBack()));
    connect(m_pLoadWin,SIGNAL(loadMod()),this,SLOT(onLoadMod()));

    connect(m_pMakerWin,SIGNAL(backDataWin()),this,SLOT(onStartMake()));
}
