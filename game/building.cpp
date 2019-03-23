
#include "building.h"

#include "game/player.h"

#include "game/terrain.h"

#include "coreengine/console.h"

#include "game/gamemap.h"

#include "game/unit.h"
#include "game/co.h"

#include "resource_management/buildingspritemanager.h"

Building::Building(const QString& BuildingID)
    : m_BuildingID(BuildingID),
      m_pOwner(nullptr),
      m_pTerrain(nullptr)
{
    Interpreter::setCppOwnerShip(this);
}

void Building::setUnitOwner(Unit* pUnit)
{
    setOwner(pUnit->getOwner());
}

void Building::setOwner(Player* pOwner)
{
    // change ownership
    m_pOwner = pOwner;
    // update sprites :)
    updateBuildingSprites();
}

Player* Building::getOwner()
{
    return m_pOwner;
}

qint32 Building::getOwnerID()
{
    if (m_pOwner != nullptr)
    {
        return m_pOwner->getPlayerID();
    }
    return -1;
}

void Building::loadSprite(QString spriteID, bool addPlayerColor)
{
    BuildingSpriteManager* pBuildingSpriteManager = BuildingSpriteManager::getInstance();
    oxygine::ResAnim* pAnim = pBuildingSpriteManager->getResAnim(spriteID.toStdString());
    if (pAnim != nullptr)
    {
        oxygine::spSprite pSprite = new oxygine::Sprite();
        if (pAnim->getTotalFrames() > 1)
        {
            oxygine::spTween tween = oxygine::createTween(oxygine::TweenAnim(pAnim), pAnim->getTotalFrames() * GameMap::frameTime * 2, -1);
            pSprite->addTween(tween);
        }
        else
        {
            pSprite->setResAnim(pAnim);
        }
        // repaint the building?
        if (addPlayerColor && m_pOwner != nullptr)
        {
            QColor color = m_pOwner->getColor();
            for (qint32 i = 0; i < 5; i++)
            {
                oxygine::Sprite::TweenColor tweenColor(oxygine::Color(color.red(), color.green(), color.blue(), 255));
                oxygine::spTween tween = oxygine::createTween(tweenColor, 1);
                //pSprite->setBlendMode(oxygine::blend_disabled);
                pSprite->addTween(tween);
            }
        }
        pSprite->setScale(GameMap::Imagesize / pAnim->getWidth());
        pSprite->setPosition(-(pSprite->getScaledWidth() - GameMap::Imagesize) / 2, -(pSprite->getScaledHeight() - GameMap::Imagesize));
        this->addChild(pSprite);
        m_pBuildingSprites.append(pSprite);

    }
    else
    {
        Console::print("Unable to load terrain sprite: " + spriteID, Console::eERROR);
    }
}

void Building::updateBuildingSprites()
{
    Mainapp* pApp = Mainapp::getInstance();
    for (qint32 i = 0; i < m_pBuildingSprites.size(); i++)
    {
        this->removeChild(m_pBuildingSprites[i]);
    }
    // call the js loader function to do the rest
    m_pBuildingSprites.clear();
    QString function1 = "loadSprites";
    QJSValueList args1;
    QJSValue obj1 = pApp->getInterpreter()->newQObject(this);
    args1 << obj1;
    pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
}

bool Building::canBuildingBePlaced(QString terrainID)
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "canBuildingBePlaced";
    QJSValueList args1;
    args1 << terrainID;
    QJSValue ret = pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
    if (ret.isBool())
    {
        return ret.toBool();
    }
    else
    {
        return false;
    }
}

quint32 Building::getBaseIncome() const
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "getBaseIncome";
    QJSValueList args1;
    QJSValue ret = pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
    if (ret.isNumber())
    {
        return ret.toUInt();
    }
    else
    {
        return 0;
    }
}

QString Building::getMinimapIcon()
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "getMiniMapIcon";
    QJSValueList args1;
    QJSValue ret = pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
    if (ret.isString())
    {
        return ret.toString();
    }
    else
    {
        return "";
    }
}

qint32 Building::getX() const
{
    return m_pTerrain->getX();
}

qint32 Building::getY() const
{
    return m_pTerrain->getY();
}

QStringList Building::getActionList()
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "getActions";
    QJSValueList args1;
    QJSValue ret = pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
    if (ret.isString())
    {
        QString retString = ret.toString();

        CO* pCO = m_pOwner->getCO(0);
        if (pCO != nullptr)
        {
            QString result = pCO->getAdditionalBuildingActions(this);
            if (retString.isEmpty())
            {
                retString = result;
            }
            else if (!result.isEmpty())
            {
                retString += "," + result;
            }
        }
        pCO = m_pOwner->getCO(1);
        if (pCO != nullptr)
        {
            QString result = pCO->getAdditionalBuildingActions(this);
            if (retString.isEmpty())
            {
                retString = result;
            }
            else if (!result.isEmpty())
            {
                retString += "," + result;
            }
        }
        return retString.split(",");
    }
    else
    {
        return QStringList();
    }
}

void Building::startOfTurn()
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "startOfTurn";
    QJSValueList args1;
    QJSValue obj1 = pApp->getInterpreter()->newQObject(this);
    args1 << obj1;
    pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
}

qint32 Building::getOffensiveBonus()
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "getOffensiveBonus";
    QJSValueList args1;
    QJSValue obj1 = pApp->getInterpreter()->newQObject(this);
    args1 << obj1;
    QJSValue ret = pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
    if (ret.isNumber())
    {
        return ret.toInt();
    }
    else
    {
        return 0;
    }
}

qint32 Building::getDefensiveBonus()
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "getDefensiveBonus";
    QJSValueList args1;
    QJSValue obj1 = pApp->getInterpreter()->newQObject(this);
    args1 << obj1;
    QJSValue ret = pApp->getInterpreter()->doFunction(m_BuildingID, function1, args1);
    if (ret.isNumber())
    {
        return ret.toInt();
    }
    else
    {
        return 0;
    }
}

qint32 Building::getVisionBonus()
{
    Mainapp* pApp = Mainapp::getInstance();
    QString function1 = "getVisionBonus";
    QJSValue ret = pApp->getInterpreter()->doFunction(m_BuildingID, function1);
    if (ret.isNumber())
    {
        return ret.toInt();
    }
    else
    {
        return 0;
    }
}

Terrain* Building::getTerrain()
{
    return m_pTerrain;
}

qint32 Building::getFireCount() const
{
    return fireCount;
}

void Building::setFireCount(const qint32 &value)
{
    fireCount = value;
}

qint32 Building::getHp() const
{
    return m_Hp;
}

void Building::setHp(const qint32 &Hp)
{
    m_Hp = Hp;
}

void Building::serialize(QDataStream& pStream)
{
    pStream << getVersion();
    pStream << m_BuildingID.toStdString().c_str();
    if (m_pOwner == nullptr)
    {
        pStream << static_cast<qint32>(-1);
    }
    else
    {
        pStream << static_cast<qint32>(m_pOwner->getPlayerID());
    }
    pStream << m_Hp;
    pStream << fireCount;
    m_Variables.serialize(pStream);
}

void Building::deserialize(QDataStream& pStream)
{
    qint32 version = 0;
    pStream >> version;
    char* id;
    pStream >> id;
    m_BuildingID = id;
    qint32 playerID = -1;
    pStream >> playerID;
    m_pOwner = GameMap::getInstance()->getPlayer(playerID);
    if (version > 1)
    {
        pStream >> m_Hp;
        pStream >> fireCount;
    }
    if (version > 2)
    {
        m_Variables.deserialize(pStream);
    }
}