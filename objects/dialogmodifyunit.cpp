#include "dialogmodifyunit.h"

#include "game/unit.h"

#include "game/player.h"

#include "game/co.h"

#include "coreengine/mainapp.h"

#include "resource_management/objectmanager.h"

#include "resource_management/fontmanager.h"

#include "resource_management/unitspritemanager.h"

#include "game/gamemap.h"

#include "objects/slider.h"
#include "objects/dropdownmenu.h"

DialogModifyUnit::DialogModifyUnit(Unit* pUnit)
    : QObject(),
      m_pUnit(pUnit)
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    ObjectManager* pObjectManager = ObjectManager::getInstance();
    oxygine::spBox9Sprite pSpriteBox = new oxygine::Box9Sprite();
    oxygine::ResAnim* pAnim = pObjectManager->getResAnim("codialog");
    pSpriteBox->setResAnim(pAnim);
    pSpriteBox->setSize(pApp->getSettings()->getWidth(), pApp->getSettings()->getHeight());
    pSpriteBox->setVerticalMode(oxygine::Box9Sprite::TILING_FULL);
    pSpriteBox->setHorizontalMode(oxygine::Box9Sprite::TILING_FULL);
    this->addChild(pSpriteBox);
    pSpriteBox->setPosition(0, 0);
    pSpriteBox->setPriority(static_cast<short>(Mainapp::ZOrder::Objects));
    this->setPriority(static_cast<short>(Mainapp::ZOrder::Dialogs));

    // ok button
    m_OkButton = pObjectManager->createButton(tr("Ok"), 150);
    m_OkButton->setPosition(pApp->getSettings()->getWidth() / 2 - m_OkButton->getWidth() / 2, pApp->getSettings()->getHeight() - 30 - m_OkButton->getHeight());
    pSpriteBox->addChild(m_OkButton);
    m_OkButton->addEventListener(oxygine::TouchEvent::CLICK, [ = ](oxygine::Event*)
    {
        this->getParent()->removeChild(this);
        emit sigFinished();
    });


    m_pPanel = new Panel(true, QSize(pApp->getSettings()->getWidth() - 60, pApp->getSettings()->getHeight() - 110),
                                     QSize(pApp->getSettings()->getWidth() - 60, pApp->getSettings()->getHeight() - 110));
    m_pPanel->setPosition(30, 30);
    pSpriteBox->addChild(m_pPanel);

    connect(this, &DialogModifyUnit::sigUpdateData, this, &DialogModifyUnit::updateData, Qt::QueuedConnection);
    connect(this, &DialogModifyUnit::sigLoadUnit, this, &DialogModifyUnit::loadUnit, Qt::QueuedConnection);
    updateData();
}

void DialogModifyUnit::updateData()
{
    Mainapp* pApp = Mainapp::getInstance();
    pApp->suspendThread();
    m_pPanel->clearContent();

    oxygine::TextStyle style = FontManager::getMainFont();
    style.color = QColor(255, 255, 255, 255);
    style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = false;
    oxygine::spTextField pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText((tr("Unit: ") + m_pUnit->getName()));
    pLabel->setScale(2.0f);
    pLabel->setPosition(m_pPanel->getWidth() / 2 - pLabel->getTextRect().getWidth(), 10);
    m_pPanel->addItem(pLabel);

    qint32 sliderOffset = 400;
    qint32 y = 30 + pLabel->getTextRect().getHeight() * 2;
    pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText(tr("HP: "));
    pLabel->setPosition(10, y);
    m_pPanel->addItem(pLabel);
    spSlider pSlider = new Slider(pApp->getSettings()->getWidth() - 40 - sliderOffset, 1, 10, tr("HP"));
    pSlider->setPosition(sliderOffset - 160, y);
    pSlider->setCurrentValue(m_pUnit->getHpRounded());
    connect(pSlider.get(), &Slider::sliderValueChanged, [=](qint32 value)
    {
        m_pUnit->setHp(value);
    });
    m_pPanel->addItem(pSlider);
    y += 40;
    if (m_pUnit->getMaxFuel() > 0)
    {
        pLabel = new oxygine::TextField();
        pLabel->setStyle(style);
        pLabel->setHtmlText(tr("Fuel: "));
        pLabel->setPosition(10, y);
        m_pPanel->addItem(pLabel);
        spSlider pSlider = new Slider(pApp->getSettings()->getWidth() - 40 - sliderOffset, 0, m_pUnit->getMaxFuel(), tr("Fuel"));
        pSlider->setPosition(sliderOffset - 160, y);
        pSlider->setCurrentValue(m_pUnit->getFuel());
        connect(pSlider.get(), &Slider::sliderValueChanged, [=](qint32 value)
        {
            m_pUnit->setFuel(value);
            if (value == m_pUnit->getMaxFuel())
            {
                m_pUnit->setModdingFlags(static_cast<Unit::ModdingFlags>(m_pUnit->getModdingFlags() & ~Unit::ModdingFlags::FlagFuel));
            }
            else
            {
                m_pUnit->setModdingFlags(static_cast<Unit::ModdingFlags>(m_pUnit->getModdingFlags() | Unit::ModdingFlags::FlagFuel));
            }
        });
        m_pPanel->addItem(pSlider);
        y += 40;
    }
    if (m_pUnit->getMaxAmmo1() > 0)
    {
        pLabel = new oxygine::TextField();
        pLabel->setStyle(style);
        pLabel->setHtmlText(tr("Ammo 1: "));
        pLabel->setPosition(10, y);
        m_pPanel->addItem(pLabel);
        spSlider pSlider = new Slider(pApp->getSettings()->getWidth() - 40 - sliderOffset, 0, m_pUnit->getMaxAmmo1(), tr("Ammo"));
        pSlider->setPosition(sliderOffset - 160, y);
        pSlider->setCurrentValue(m_pUnit->getAmmo1());
        connect(pSlider.get(), &Slider::sliderValueChanged, [=](qint32 value)
        {
            m_pUnit->setAmmo1(value);
            if (value == m_pUnit->getMaxAmmo1())
            {
                m_pUnit->setModdingFlags(static_cast<Unit::ModdingFlags>(m_pUnit->getModdingFlags() & ~Unit::ModdingFlags::FlagAmmo1));
            }
            else
            {
                m_pUnit->setModdingFlags(static_cast<Unit::ModdingFlags>(m_pUnit->getModdingFlags() | Unit::ModdingFlags::FlagAmmo1));
            }
        });
        m_pPanel->addItem(pSlider);
        y += 40;
    }
    if (m_pUnit->getMaxAmmo2() > 0)
    {
        pLabel = new oxygine::TextField();
        pLabel->setStyle(style);
        pLabel->setHtmlText(tr("Ammo 2: "));
        pLabel->setPosition(10, y);
        m_pPanel->addItem(pLabel);
        spSlider pSlider = new Slider(pApp->getSettings()->getWidth() - 40 - sliderOffset, 0, m_pUnit->getMaxAmmo2(), tr("Ammo"));
        pSlider->setPosition(sliderOffset - 160, y);
        pSlider->setCurrentValue(m_pUnit->getAmmo2());
        connect(pSlider.get(), &Slider::sliderValueChanged, [=](qint32 value)
        {
            m_pUnit->setAmmo2(value);
            if (value == m_pUnit->getMaxAmmo2())
            {
                m_pUnit->setModdingFlags(static_cast<Unit::ModdingFlags>(m_pUnit->getModdingFlags() & ~Unit::ModdingFlags::FlagAmmo2));
            }
            else
            {
                m_pUnit->setModdingFlags(static_cast<Unit::ModdingFlags>(m_pUnit->getModdingFlags() | Unit::ModdingFlags::FlagAmmo2));
            }
        });
        m_pPanel->addItem(pSlider);
        y += 40;
    }

    pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText(tr("Player: "));
    pLabel->setPosition(10, y);
    m_pPanel->addItem(pLabel);
    QVector<QString> items;
    GameMap* pMap = GameMap::getInstance();
    for (qint32 i = 0; i < pMap->getPlayerCount(); i++)
    {
        items.append(tr("Player ") + QString::number(i + 1));
    }
    spDropDownmenu pDropdownmenu = new DropDownmenu(300, items);
    pDropdownmenu->setPosition(sliderOffset - 160, y);
    pDropdownmenu->setCurrentItem(m_pUnit->getOwner()->getPlayerID());
    connect(pDropdownmenu.get(), &DropDownmenu::sigItemChanged, [=](qint32 value)
    {
        m_pUnit->setOwner(pMap->getPlayer(value));

    });
    m_pPanel->addItem(pDropdownmenu);
    y += 40;

    pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText(tr("AI-Mode: "));
    pLabel->setPosition(10, y);
    m_pPanel->addItem(pLabel);
    items = {tr("Normal"), tr("Offensive"), tr("Defensive"), tr("Hold")};
    pDropdownmenu = new DropDownmenu(300, items);
    pDropdownmenu->setPosition(sliderOffset - 160, y);
    pDropdownmenu->setCurrentItem(static_cast<qint32>(m_pUnit->getAiMode()));
    connect(pDropdownmenu.get(), &DropDownmenu::sigItemChanged, [=](qint32 value)
    {
        m_pUnit->setAiMode(static_cast<GameEnums::GameAi>(value));
    });
    m_pPanel->addItem(pDropdownmenu);
    y += 40;

    pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText(tr("Unit Rank: "));
    pLabel->setPosition(10, y);
    m_pPanel->addItem(pLabel);
    items = {tr("Soldier"), tr("Lieutenant"), tr("General"), tr("Veteran"), tr("CO 1"), tr("CO 2")};
    pDropdownmenu = new DropDownmenu(300, items);
    pDropdownmenu->setPosition(sliderOffset - 160, y);
    pDropdownmenu->setCurrentItem(static_cast<qint32>(m_pUnit->getUnitRank()));
    connect(pDropdownmenu.get(), &DropDownmenu::sigItemChanged, [=](qint32 value)
    {
        m_pUnit->setUnitRank(static_cast<GameEnums::UnitRanks>(value));
    });
    m_pPanel->addItem(pDropdownmenu);
    y += 40;

    for (qint32 i = 0; i < m_pUnit->getLoadedUnitCount(); i++)
    {
        addLoadUnit(i, sliderOffset, y);
    }
    if (m_pUnit->getLoadedUnitCount() < m_pUnit->getLoadingPlace())
    {
        addLoadUnit(m_pUnit->getLoadedUnitCount(), sliderOffset, y);
    }
    m_pPanel->setContentHeigth(y);
    pApp->continueThread();
}

void DialogModifyUnit::addLoadUnit(qint32 index, qint32 sliderOffset, qint32& y)
{
    UnitSpriteManager* pUnitSpriteManager = UnitSpriteManager::getInstance();
    oxygine::TextStyle style = FontManager::getMainFont();
    style.color = QColor(255, 255, 255, 255);
    style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = false;
    oxygine::spTextField  pLabel = new oxygine::TextField();
    pLabel->setStyle(style);
    pLabel->setHtmlText((tr("Loaded Unit ") + QString::number(index + 1) + ": "));
    pLabel->setPosition(10, y);
    m_pPanel->addItem(pLabel);
    QVector<QString> items = {"-"};
    QStringList units = m_pUnit->getTransportUnits();
    for (qint32 i = 0; i < units.size(); i++)
    {
        if (pUnitSpriteManager->existsUnit(units[i]))
        {
            items.append(units[i]);
        }
    }
    spDropDownmenu pDropdownmenu = new DropDownmenu(300, items);
    pDropdownmenu->setPosition(sliderOffset - 160, y);
    Unit* pLoadedUnit = m_pUnit->getLoadedUnit(index);
    if (pLoadedUnit != nullptr)
    {
        pDropdownmenu->setCurrentItem(pLoadedUnit->getUnitID());
    }
    else
    {
        pDropdownmenu->setCurrentItem("-");
    }
    connect(pDropdownmenu.get(), &DropDownmenu::sigItemChanged, [=](qint32)
    {
        emit sigLoadUnit(pDropdownmenu->getCurrentItemText(), index);
    });
    m_pPanel->addItem(pDropdownmenu);
    y += 40;
}

void DialogModifyUnit::loadUnit(QString unitID, qint32 index)
{
    Mainapp* pApp = Mainapp::getInstance();
    pApp->suspendThread();
    if (unitID == "-")
    {
        m_pUnit->unloadUnit(index, QPoint(-1, -1));
    }
    else
    {
        Unit* pUnit = new Unit(unitID, m_pUnit->getOwner(), false);
        m_pUnit->loadUnit(pUnit);
    }
    emit sigUpdateData();
    pApp->continueThread();
}
