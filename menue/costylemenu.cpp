#include "qfile.h"

#include "costylemenu.h"

#include "coreengine/mainapp.h"
#include "coreengine/console.h"

#include "menue/mainwindow.h"

#include "resource_management/backgroundmanager.h"
#include "resource_management/fontmanager.h"
#include "resource_management/objectmanager.h"
#include "resource_management/cospritemanager.h"

#include "objects/coselection.h"

#include "objects/dialogcostyle.h"

COStyleMenu::COStyleMenu()
    : QObject()
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());

    Console::print("Entering Main Menue", Console::eDEBUG);
    BackgroundManager* pBackgroundManager = BackgroundManager::getInstance();
    // load background
    oxygine::spSprite sprite = new oxygine::Sprite();
    addChild(sprite);
    oxygine::ResAnim* pBackground = pBackgroundManager->getResAnim("Background+1");
    sprite->setResAnim(pBackground);
    sprite->setPosition(0, 0);
    // background should be last to draw
    sprite->setPriority(static_cast<short>(Mainapp::ZOrder::Background));
    sprite->setScaleX(pApp->getSettings()->getWidth() / pBackground->getWidth());
    sprite->setScaleY(pApp->getSettings()->getHeight() / pBackground->getHeight());

    pApp->getAudioThread()->clearPlayList();
    pApp->getAudioThread()->loadFolder("resources/music/hauptmenue");
    pApp->getAudioThread()->playRandom();

    oxygine::spButton pButtonExit = ObjectManager::createButton(tr("Exit"));
    pButtonExit->attachTo(this);
    pButtonExit->setPosition(20, pApp->getSettings()->getHeight() - pButtonExit->getHeight() - 10);
    pButtonExit->addEventListener(oxygine::TouchEvent::CLICK, [=](oxygine::Event * )->void
    {
        emit sigExitMenue();
    });
    connect(this, &COStyleMenu::sigExitMenue, this, &COStyleMenu::exitMenue, Qt::QueuedConnection);

    oxygine::spButton pButtonEdit = ObjectManager::createButton(tr("Edit CO"));
    pButtonEdit->attachTo(this);
    pButtonEdit->setPosition(pApp->getSettings()->getWidth() - pButtonExit->getWidth() - 20, pApp->getSettings()->getHeight() - pButtonExit->getHeight() - 10);
    pButtonEdit->addEventListener(oxygine::TouchEvent::CLICK, [=](oxygine::Event * )->void
    {
        emit sigEditCOStyle();
    });
    connect(this, &COStyleMenu::sigEditCOStyle, this, &COStyleMenu::editCOStyle, Qt::QueuedConnection);

    spCOSelection pCOSelection = new COSelection();
    pCOSelection->colorChanged(QColor(248, 88, 0));
    pCOSelection->setScale((Settings::getWidth() - 70) / (pCOSelection->getWidth() + 208));
    addChild(pCOSelection);



    m_pCurrentCO = new oxygine::Sprite();
    m_pCurrentCO->setPosition(40 + pCOSelection->getScaledWidth(), 30);
    m_pCurrentCO->setScale(pCOSelection->getScale());
    addChild(m_pCurrentCO);
    connect(pCOSelection.get(), &COSelection::coSelected, this, &COStyleMenu::selectedCOIDChanged, Qt::QueuedConnection);
}

void COStyleMenu::exitMenue()
{
    Mainapp* pApp = Mainapp::getInstance();
    pApp->suspendThread();
    Console::print("Leaving CO Style Menue", Console::eDEBUG);
    oxygine::getStage()->addChild(new Mainwindow());
    addRef();
    oxygine::Actor::detach();
    deleteLater();
    pApp->continueThread();
}

void COStyleMenu::reloadMenue()
{
    Mainapp* pApp = Mainapp::getInstance();
    pApp->suspendThread();
    Console::print("Leaving CO Style Menue", Console::eDEBUG);
    oxygine::getStage()->addChild(new COStyleMenu());
    addRef();
    oxygine::Actor::detach();
    deleteLater();
    pApp->continueThread();
}

void COStyleMenu::selectedCOIDChanged(QString coid)
{
    Mainapp* pApp = Mainapp::getInstance();
    pApp->suspendThread();
    COSpriteManager* pCOSpriteManager = COSpriteManager::getInstance();
    oxygine::ResAnim* pAnim = nullptr;
    if (!coid.isEmpty())
    {
        pAnim = pCOSpriteManager->getResAnim((coid + "+nrm"));
    }
    m_pCurrentCO->setResAnim(pAnim);
    m_currentCOID = coid;
    pApp->continueThread();
}

void COStyleMenu::editCOStyle()
{
    Mainapp* pApp = Mainapp::getInstance();
    pApp->suspendThread();
    COSpriteManager* pCOSpriteManager = COSpriteManager::getInstance();
    oxygine::ResAnim* pAnim = nullptr;
    if (!m_currentCOID.isEmpty())
    {
        spDialogCOStyle pDialogCOStyle = new DialogCOStyle(m_currentCOID);
        addChild(pDialogCOStyle);
        connect(pDialogCOStyle.get(), &DialogCOStyle::sigFinished, this, &COStyleMenu::reloadMenue, Qt::QueuedConnection);
    }
    pApp->continueThread();
}
