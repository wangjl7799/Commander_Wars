#ifndef BATTLEANIMATION_H
#define BATTLEANIMATION_H

#include <QObject>

#include "game/gameanimation.h"

#include "game/GameEnums.h"

#include <QTimer>

#include "game/battleanimationsprite.h"

class BattleAnimation : public GameAnimation
{
    Q_OBJECT
public:
    enum class AnimationProgress
    {
        MoveIn,
        WaitAfterIn,
        AttackerFire,
        AttackerImpact,
        DefenderFire,
        DefenderImpact,
        WaitAfterBattle,
        Finished,
    };

    BattleAnimation(Terrain* pAtkTerrain, Unit* pAtkUnit, float atkStartHp, float atkEndHp, qint32 atkWeapon,
                    Terrain* pDefTerrain, Unit* pDefUnit, float defStartHp, float defEndHp, qint32 defWeapon, float defenderDamage);

    virtual void restart() override;
    virtual void stop() override;
    /**
     * @brief onFinished called when the animation is finished
     */
    virtual bool onFinished() override;

public slots:
    /**
     * @brief getPAtkUnit
     * @return
     */
    Unit *getAtkUnit() const;
    /**
     * @brief getPDefUnit
     * @return
     */
    Unit *getDefUnit() const;
private:
    /**
     * @brief getIsRight
     * @param pUnit1
     * @param pUnit2
     * @return
     */
    bool getIsLeft(Unit* pUnit1, Unit* pUnit2);
    /**
     * @brief setSpritePosition
     * @param pSprite
     * @param pAtkUnit
     * @param pDefUnit
     */
    void setSpritePosition(oxygine::spSprite pSprite, Unit* pUnit1, Unit* pUnit2);
    /**
     * @brief setCOMood
     * @param hp1
     * @param hp2
     */
    void setCOMood(oxygine::spSprite pSprite, float hp1, float hp2);
    /**
     * @brief loadTerrainSprite
     * @param pUnit
     * @return
     */
    oxygine::spSprite loadTerrainSprite(Unit* pUnit);
    /**
     * @brief setHealthBarColor
     * @param pColorBar
     * @param hp
     */
    QColor getHealthBarColor(float hp);
    /**
     * @brief loadMoveInAnimation
     * @param pSprite
     */
    void loadMoveInAnimation(spBattleAnimationSprite pSprite, Unit* pUnit1, Unit* pUnit2, qint32 weapon);
    /**
     * @brief loadFireAnimation
     * @param pSprite
     */
    void loadFireAnimation(spBattleAnimationSprite pSprite, Unit* pUnit1, Unit* pUnit2, qint32 weapon);
    /**
     * @brief loadImpactAnimation
     * @param pUnit1
     * @param pUnit2
     * @param pSprite
     * @param pColorRect
     * @param endHp
     * @param pCO0
     * @param pCO1
     * @param enemyHp
     */
    void loadImpactAnimation(Unit* pUnit1, Unit* pUnit2, spBattleAnimationSprite pSprite, spBattleAnimationSprite pAttackerSprite,
                             oxygine::spColorRectSprite pColorRect, float endHp, qint32 weapon, float enemyHp);
    /**
     * @brief nextAnimatinStep
     */
    void nextAnimatinStep();

    QTimer battleTimer;

    oxygine::spSprite m_AtkCO0;
    oxygine::spSprite m_AtkCO1;
    oxygine::spSprite m_DefCO0;
    oxygine::spSprite m_DefCO1;

    oxygine::spColorRectSprite m_HealthBar0;
    oxygine::spColorRectSprite m_HealthBar1;

    spBattleAnimationSprite m_pAttackerAnimation;
    spBattleAnimationSprite m_pDefenderAnimation;

    Terrain* m_pAtkTerrain;
    Unit* m_pAtkUnit;
    float m_atkStartHp;
    float m_atkEndHp;
    qint32 m_AtkWeapon{0};
    Terrain* m_pDefTerrain;
    Unit* m_pDefUnit;
    float m_defStartHp;
    float m_defEndHp;
    qint32 m_DefWeapon{0};
    float m_DefenderDamage{-1};

    AnimationProgress currentState{AnimationProgress::AttackerImpact};

    static const short priorityBack = -1;
    static const short priorityFront = 1;
    static const short priorityCOBack = 2;
    static const short priorityCO = 3;
    static const short priorityCOFront = 4;
};

#endif // BATTLEANIMATION_H
