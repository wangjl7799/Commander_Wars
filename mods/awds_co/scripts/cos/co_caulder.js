CO_CAULDER.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                         defender, defPosX, defPosY, isDefender)
{
    if (co.getIsCO0() === true)
    {
        switch (co.getPowerMode())
        {
        case GameEnums.PowerMode_Tagpower:
        case GameEnums.PowerMode_Superpower:
            return 50;
        case GameEnums.PowerMode_Power:
            return 30;
        default:
            return 20;
        }
    }
};

CO_CAULDER.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                        defender, defPosX, defPosY, isDefender)
{
    if (co.getIsCO0() === true)
    {
        switch (co.getPowerMode())
        {
        case GameEnums.PowerMode_Tagpower:
        case GameEnums.PowerMode_Superpower:
            return 50;
        case GameEnums.PowerMode_Power:
            return 30;
        default:
            return 20;
        }
    }
};

CO_CAULDER.startOfTurn = function(co)
{
    if (co.getIsCO0() === true)
    {
        var units = co.getOwner().getUnits();
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            UNIT.repairUnit(unit, 1);
            animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
            animation.addSprite("power0", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
        }
        units.remove();
    }
};

