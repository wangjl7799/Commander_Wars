var Constructor = function()
{
    this.init = function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(5);
    };

    this.loadCOMusic = function(co)
    {
        // put the co music in here.
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/power.mp3");
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/superpower.mp3");
                break;
            default:
                audio.addMusic("resources/music/cos/smitan.mp3")
                break;
        }
    };

    this.activatePower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(false);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getPlayer().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (unit.getMinRange() > 1)
            {
                var variables = unit.getVariables();
                var variable = variables.createVariable("SMITAN_ATTACK_COUNT");
                variable.writeDataInt32(1);
                var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                if (animations.length < 5)
                {
                    animation.addSprite("power9", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                    powerNameAnimation.queueAnimation(animation);
                    animations.push(animation);
                }
                else
                {
                    animation.addSprite("power9", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
                    animations[counter].queueAnimation(animation);
                    animations[counter] = animation;
                    counter++;
                    if (counter >= animations.length)
                    {
                        counter = 0;
                    }
                }
            }
        }
        units.remove();

        audio.clearPlayList();
        CO_SMITAN.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(true);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getPlayer().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);
            if (unit.getMinRange() > 1)
            {
                var variables = unit.getVariables();
                var variable = variables.createVariable("SMITAN_ATTACK_COUNT");
                variable.writeDataInt32(2);
                var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                if (animations.length < 5)
                {
                    animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 1.5, globals.randInt(0, 400));
                    powerNameAnimation.queueAnimation(animation);
                    animations.push(animation);
                }
                else
                {
                    animation.addSprite("power12", -map.getImageSize() * 2, -map.getImageSize() * 2, 0, 1.5);
                    animations[counter].queueAnimation(animation);
                    animations[counter] = animation;
                    counter++;
                    if (counter >= animations.length)
                    {
                        counter = 0;
                    }
                }
            }
        }
        units.remove();

        audio.clearPlayList();
        CO_SMITAN.loadCOMusic(co);
        audio.playRandom();
    };

    this.postBattleActions = function(co, attacker, atkDamage, defender, gotAttacked)
    {
        if (gotAttacked === false)
        {
            switch (co.getPowerMode())
            {
                case GameEnums.PowerMode_Superpower:
                case GameEnums.PowerMode_Power:
                    if (attacker.getMinRange() > 1)
                    {
                        var variables = attacker.getVariables();
                        var variable = variables.createVariable("SMITAN_ATTACK_COUNT");
                        var counter = variable.readDataInt32();
                        counter--;
                        variable.writeDataInt32(counter);
                        // enable unit for another move
                        attacker.setHasMoved(false);
                    }
                    break;
                default:
                    break;
            }
        }
    };

    this.getActionModifierList = function(co, unit)
    {
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
            case GameEnums.PowerMode_Power:
                if (unit.getMinRange() > 1)
                {
                    var variables = unit.getVariables();
                    var variable = variables.createVariable("SMITAN_ATTACK_COUNT");
                    var counter = variable.readDataInt32();
                    if (counter <= 0)
                    {
                        // disable firing with this unit
                        return ["-ACTION_FIRE"];
                    }
                }
                break;
            default:
                break;
        }
        return [];
    };

    this.getCOUnitRange = function(co)
    {
        return 2;
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var inRangeCount = 0;
        if (attacker.getMaxRange() === 1)
        {
            var units = co.getPlayer().getUnits();
            for (var i = 0; i < units.size(); i++)
            {
                var unit = units.at(i);
                var x = unit.getX();
                var y = unit.getY();
                var distance = Math.abs(x - defPosX) + Math.abs(y - defPosY);
                if (unit.getMinRange() <= distance && distance <= unit.getMaxRange())
                {
                    inRangeCount += 1;
                }
            }
        }

        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (attacker.getMaxRange() === 1)
                {
                    return inRangeCount * 20;
                }
                else
                {
                    return 0;
                }
            case GameEnums.PowerMode_Power:
                if (attacker.getMaxRange() === 1)
                {
                    return inRangeCount * 10;
                }
                else
                {
                    return 0;
                }
            default:
                if (attacker.getMaxRange() === 1)
                {
                    if (co.inCORange(Qt.point(atkPosX, atkPosY)))
                    {
                        return inRangeCount * 10;
                    }
                    return inRangeCount * 5;
                }
                break;
        }        
        return 0;
    };
    this.getFirerangeModifier = function(co, unit, posX, posY)
    {
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (unit.getMinRange() > 1)
                {
                    return 2;
                }
                break;
            case GameEnums.PowerMode_Power:
                if (unit.getMinRange() > 1)
                {
                    return 1;
                }
                break;
            default:
                break;
        }
        return 0;
    };
    this.getCOArmy = function()
    {
        return "GE";
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A violent old commander of the Green Earth army who hates limitations.");
    };
    this.getHits = function()
    {
        return qsTr("Dominance, yelling");
    };
    this.getMiss = function()
    {
        return qsTr("(Victory by) Surrender");
    };
    this.getCODescription = function()
    {
        return qsTr("Direct units gain additional firepower against enemy units which may come under fire from indirect units.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Increases the range of indirect units by one space. Indirect units can move after firing.");
    };
    this.getPowerName = function()
    {
        return qsTr("Scramble Tactics");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("Increases the range of indirect units by two spaces. Indirect units can fire twice and move after firing.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Flare Drive");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("Whites of their eyes? Pahaha!"),
                qsTr("It's over! Get used to it!!"),
                qsTr("Fire, you idiots!!"),
                qsTr("What're you waiting for?! SHOOT them!!"),
                qsTr("'Calm before the storm'? ... Nonsense."),
                qsTr("No more games! All units, full power!!")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("Wasn't even any dust to settle."),
                qsTr("Grah hah hah. Ooh, that was FUN.")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("Grah! Ha! Ha. Ooh! What i lost"),
                qsTr("This and that! And what...i've lost?")];
    };
    this.getName = function()
    {
        return qsTr("Smitan");
    };
}

Constructor.prototype = CO;
var CO_SMITAN = new Constructor();