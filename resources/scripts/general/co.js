var CO =
{
    init : function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(3);
    },

    onCOUnitLost : function(co)
    {
        // called when a co unit got destroyed
        co.setPowerFilled(co.getPowerFilled() / 2.0);
    },

    loadCOMusic : function(co)
    {
        // put the co music in here.
    },

    getMovementpointModifier : function(co, unit, posX, posY)
    {
        return 0;
    },

    buildedUnit : function(co, unit)
    {
        // called when someone builded a unit -> ACTION_BUILD_UNITS was performed
    },

    getFirerangeModifier : function(co, unit, posX, posY)
    {
        return 0;
    },

    getCaptureBonus : function(co, unit, posX, posY)
    {
        return 0;
    },

    getAttackHpBonus : function(co, unit, posX, posY)
    {
        return 0;
    },

    getVisionrangeModifier: function(co, unit, posX, posY)
    {
        return 0;
    },

    getTerrainDefenseModifier : function(co, unit, posX, posY)
    {
        return 0;
    },

    getFirstStrike : function(co, unit, posX, posY, defender)
    {
        return false;
    },

    getEnemyTerrainDefenseModifier : function(co, unit, posX, posY)
    {
        return 0;
    },

    getDamageReduction : function(co, damage, attacker, atkPosX, atkPosY, attackerBaseHp,
                                  defender, defPosX, defPosY, isDefender, luckMode)
    {
        return 0;
    },

    getTrueDamage : function(co, damage, attacker, atkPosX, atkPosY, attackerBaseHp,
                             defender, defPosX, defPosY, isDefender)
    {
        return 0;
    },

    getPerfectVision : function(co)
    {
        // return true if forest and reafs etc are disabled in fog of war see sonja
        return false;
    },

    getHpHidden : function(co, unit, posX, posY)
    {
        // are the hp hidden of this unit?
        return false;
    },

    getRepairBonus : function(co, unit, posX, posY)
    {
        return 0;
    },

    getBonusLuck : function(co, unit, posX, posY)
    {
        return 0;
    },

    getBonusMisfortune : function(co, unit, posX, posY)
    {
        return 0;
    },

    getActionModifierList : function(co, unit)
    {
        // return empty list as default
        return [];
    },

    activatePower : function(co)
    {
    },

    activateSuperpower : function(co)
    {
    },

    getFuelCostModifier : function(co, unit, posX, posY, costs)
    {
        // modifies the fuel cost at the start of a turn
        return 0;
    },

    getOffensiveBonus : function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        return 0;
    },

    getOffensiveReduction : function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        return 0;
    },

    getDeffensiveBonus : function(co, attacker, atkPosX, atkPosY,
                                  defender, defPosX, defPosY, isDefender)
    {
        return 0;
    },

    getDeffensiveReduction : function(co, attacker, atkPosX, atkPosY,
                                  defender, defPosX, defPosY, isDefender)
    {
        return 0;
    },

    canBeRepaired : function(co, unit, posX, posY)
    {
        // called from all co's for a unit -> so you can apply boni from own co and mali from enemy co's here
        return true;
    },

    getCostModifier : function(co, id, baseCost)
    {
        return 0;
    },

    getMovementcostModifier : function(co, unit, posX, posY)
    {
        // called from all co's for a unit -> so you can apply boni from own co and mali from enemy co's here
        return 0;
    },

    getMovementFuelCostModifier : function(co, unit, fuelCost)
    {
        // modifies the fuel cost when moving
        // called from all co's for a unit -> so you can apply boni from own co and mali from enemy co's here
        // fuelCost are the costs needed for the current movement
        return 0;
    },

    getCanMoveAndFire : function(co, unit, posX, posY)
    {
        return false;
    },

    getCostModifier : function(co, id, baseCost)
    {
        return 0;
    },

    getCOArmy : function()
    {
        return "OS";
    },

    gainPowerstar : function(co, fundsDamage, x, y)
    {
        co.setPowerFilled(co.getPowerFilled() + fundsDamage / 11000)
    },

    getCOUnitRange : function(co)
    {
        return 0;
    },

    getCOUnits : function(co, building)
    {
        return [];
    },

    getAdditionalBuildingActions : function(co, building)
    {
        // called from all co's for a building -> so you can boni from own co and mali from enemy co's here
        // - before an action id will disable the action -> see Mary
        return "";
    },

    getBonusIncome : function(co, building, income)
    {
        return 0;
    },

    getIncomeReduction : function(co, building, income)
    {
        return 0;
    },

    postBattleActions : function(co, attacker, atkDamage, defender, gotAttacked)
    {
        // called after damage was dealt to the defender unit.
        // the damage given is the damage was dealt to the unit.
        // gotAttacked means we own the unit which got damage dealt.
    },

    startOfTurn : function(co)
    {
        // called at the start of the turn use it to do cool co stuff like caulder's healing :)
    },

    // CO - Intel
    getBio : function()
    {
        return "";
    },
    getLongBio : function()
    {
        return "";
    },
    getHits : function()
    {
        return "";
    },
    getMiss : function()
    {
        return "";
    },
    getCODescription : function()
    {
        return "";
    },
    getLongCODescription : function()
    {
        return "";
    },
    getPowerDescription : function()
    {
        return "";
    },
    getPowerName : function()
    {
        return "";
    },
    getSuperPowerDescription : function()
    {
        return "";
    },
    getSuperPowerName : function()
    {
        return "";
    },
    getPowerSentences : function()
    {
        return [];
    },
    getVictorySentences : function()
    {
        return [];
    },
    getDefeatSentences : function()
    {
        return [];
    },
    getName : function()
    {
        return "";
    },

    getCOStyles : function()
    {
        // string array containing the endings of the alternate co style
        // e.g. co_adder has ["+alt"]
        return [];
    },

    // ai hints for using co powers
    /**
      * co              : getting checked
      * powerSurplus    : surplus on the co power e.g 1 if one more star is filled over the normal co power
      * unitCount       : amount of units owned by the player
      * repairUnits     : amount of units that need to be repaired
      * indirectUnits   : amount of indirect units
      * directUnits     : amount of direct units
      * enemyUnits      : amount of enemy units
      * turnMode        : see GameEnums.h AiTurnMode describes the current turn mode on the ai
      * return          : see GameEnums PowerMode return unknown for default fallback -> not recommended
      */
    getAiUsePower(co, powerSurplus, unitCount, repairUnits, indirectUnits, directUnits, enemyUnits, turnMode)
    {
        return CO.getAiUsePowerAtStart(co, powerSurplus, turnMode);
    },

    getAiUsePowerAlways : function(co, powerSurplus)
    {
        if (powerSurplus <= 0.5)
        {
            if (co.canUseSuperpower())
            {
                return GameEnums.PowerMode_Superpower;
            }
            else if (co.canUsePower())
            {
                return GameEnums.PowerMode_Power;
            }
        }
        return GameEnums.PowerMode_Off;
    },

    getAiUsePowerAtStart : function(co, powerSurplus, turnMode)
    {
        if (powerSurplus <= 0.5 &&
            turnMode === GameEnums.AiTurnMode_StartOfDay)
        {
            if (co.canUseSuperpower())
            {
                return GameEnums.PowerMode_Superpower;
            }
            else if (co.canUsePower())
            {
                return GameEnums.PowerMode_Power;
            }
        }
        return GameEnums.PowerMode_Off;
    },

    getAiUsePowerAtEnd : function(co, powerSurplus, turnMode)
    {
        if (powerSurplus <= 0.5 &&
            turnMode === GameEnums.AiTurnMode_EndOfDay)
        {
            if (co.canUseSuperpower())
            {
                return GameEnums.PowerMode_Superpower;
            }
            else if (co.canUsePower())
            {
                return GameEnums.PowerMode_Power;
            }
        }
        return GameEnums.PowerMode_Off;
    },

    getAiUsePowerAtUnitCount : function(co, powerSurplus, turnMode, unitCount)
    {
        if (powerSurplus <= 0.5 &&
            turnMode === GameEnums.AiTurnMode_StartOfDay &&
            unitCount >= 5)
        {
            if (co.canUseSuperpower())
            {
                return GameEnums.PowerMode_Superpower;
            }
            else if (co.canUsePower())
            {
                return GameEnums.PowerMode_Power;
            }
        }
        return GameEnums.PowerMode_Off;
    },
}

