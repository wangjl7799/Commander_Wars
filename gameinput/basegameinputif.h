#ifndef BASEGAMEINPUTIF_H
#define BASEGAMEINPUTIF_H

#include <QObject>
#include <QVector>

#include "oxygine-framework.h"

#include "coreengine/fileserializable.h"

class Player;

class BaseGameInputIF;
typedef oxygine::intrusive_ptr<BaseGameInputIF> spBaseGameInputIF;

class BaseGameInputIF : public QObject, public FileSerializable, public oxygine::ref_counter
{
    Q_OBJECT
public:
    enum class AiTypes
    {
        ProxyAi = -1,
        Human = 0,
        VeryEasy,
        Normal,
        NormalOffensive,
        NormalDefensive,
        Max,
        Open = 200
    };

    explicit BaseGameInputIF(AiTypes aiType);

    void setPlayer(Player* pPlayer);

    virtual void init() = 0;

    static void serializeInterface(QDataStream& pStream, BaseGameInputIF* input);

    static BaseGameInputIF* deserializeInterface(QDataStream& pStream, qint32 version);
    AiTypes getAiType() const;
    static BaseGameInputIF* createAi(BaseGameInputIF::AiTypes type);
signals:

public slots:
    /**
     * @brief getEnableNeutralTerrainAttack
     * @return
     */
    bool getEnableNeutralTerrainAttack() const;
    /**
     * @brief setEnableNeutralTerrainAttack
     * @param value
     */
    void setEnableNeutralTerrainAttack(bool value);
    /**
     * @brief setUnitBuildValue only applies to Normal AI and better
     * @param unitID unit to alter the building score
     * @param value score modification value. value <= 0 means won't be produced. value means 1.0 normal chance. value 2.0 means doubled score mostlikely AI will only build this unit
     */
    void setUnitBuildValue(QString unitID, float value);
    /**
     * @brief getUnitBuildValue only applies to Normal AI and better
     * @param unitID unit to alter the building score
     * @return value score modification value. value <= 0 means won't be produced. value means 1.0 normal chance. value 2.0 means doubled score mostlikely AI will only build this unit
     */
    float getUnitBuildValue(QString unitID);
    /**
     * @brief setMoveCostMapValue
     * @param x
     * @param y
     */
    void setMoveCostMapValue(qint32 x, qint32 y, qint32 value);
    /**
     * @brief getMoveCostMapValue
     * @param x
     * @param y
     * @return
     */
    qint32 getMoveCostMapValue(qint32 x, qint32 y);
protected:
    Player* m_pPlayer{nullptr};
    AiTypes m_AiType{AiTypes::Human};
    bool enableNeutralTerrainAttack{true};
    QVector<std::tuple<QString, float>> m_BuildingChanceModifier;
    /**
     * @brief m_MoveCostMap move cost modifier map for the ai
     */
    QVector<QVector<std::tuple<qint32, bool>>> m_MoveCostMap;
};

#endif // BASEGAMEINPUTIF_H
