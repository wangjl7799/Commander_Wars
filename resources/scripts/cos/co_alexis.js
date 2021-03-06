var Constructor = function()
{
    this.init = function(co)
    {
        co.setPowerStars(4);
        co.setSuperpowerStars(4);
    };

    this.activatePower = function(co)
    {

        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(GameEnums.PowerMode_Power);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var animations = [];
        var counter = 0;
        var buildings = co.getOwner().getBuildings();
        buildings.randomize();
        var fields = globals.getCircle(0, 2);
        for (var i2 = 0; i2 < buildings.size(); i2++)
        {
            var building = buildings.at(i2);
            var x = building.getX();
            var y = building.getY();
            var animation = null;
            for (var i = 0; i < fields.size(); i++)
            {
                var point = fields.at(i);
                if (map.onMap(x + point.x, y + point.y))
                {
                    var unit = map.getTerrain(x + point.x, y + point.y).getUnit();
                    if ((unit !== null) &&
                            (unit.getOwner() === co.getOwner()))
                    {
                        animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                        animation.writeDataInt32(unit.getX());
                        animation.writeDataInt32(unit.getY());
                        animation.writeDataInt32(3);
                        animation.setEndOfAnimationCall("ANIMATION", "postAnimationHeal");

                        if (animations.length < 5)
                        {
                            animation.addSprite("power0", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                            powerNameAnimation.queueAnimation(animation);
                            animations.push(animation);
                        }
                        else
                        {
                            animation.addSprite("power0", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
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
            }
        }
        fields.remove();
        buildings.remove();

        audio.clearPlayList();
        CO_ALEXIS.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co, powerMode)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(powerMode);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var animations = [];
        var counter = 0;
        var buildings = co.getOwner().getBuildings();
        buildings.randomize();
        var fields = globals.getCircle(0, 2);
        for (var i2 = 0; i2 < buildings.size(); i2++)
        {
            var building = buildings.at(i2);
            var x = building.getX();
            var y = building.getY();
            var animation = null;
            for (var i = 0; i < fields.size(); i++)
            {
                var point = fields.at(i);
                if (map.onMap(x + point.x, y + point.y))
                {
                    var unit = map.getTerrain(x + point.x, y + point.y).getUnit();
                    if ((unit !== null) &&
                        (unit.getOwner() === co.getOwner()))
                    {
                        animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                        animation.writeDataInt32(unit.getX());
                        animation.writeDataInt32(unit.getY());
                        animation.writeDataInt32(3);
                        animation.setEndOfAnimationCall("ANIMATION", "postAnimationHeal");
                        if (animations.length < 5)
                        {
                            animation.addSprite("power4", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                            powerNameAnimation.queueAnimation(animation);
                            animations.push(animation);
                        }
                        else
                        {
                            animation.addSprite("power4", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
                            animations[counter].queueAnimation(animation);
                            animations[counter] = animation;
                            counter++;
                            if (counter >= animations.length)
                            {
                                counter = 0;
                            }
                        }
                    }
                    else if ((unit !== null) &&
                             (co.getOwner().isEnemyUnit(unit)))
                    {
                        animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                        animation.writeDataInt32(unit.getX());
                        animation.writeDataInt32(unit.getY());
                        animation.writeDataInt32(3);
                        animation.setEndOfAnimationCall("ANIMATION", "postAnimationDamage");
                        if (animations.length < 5)
                        {
                            animation.addSprite("power4", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                            powerNameAnimation.queueAnimation(animation);
                            animations.push(animation);
                        }
                        else
                        {
                            animation.addSprite("power4", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
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
            }
        }
        fields.remove();
        buildings.remove();

        audio.clearPlayList();
        CO_ALEXIS.loadCOMusic(co);
        audio.playRandom();
    };

    this.loadCOMusic = function(co)
    {
        // put the co music in here.
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/power.mp3", 992, 45321);
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/superpower.mp3", 1505, 49515);
                break;
            case GameEnums.PowerMode_Tagpower:
                audio.addMusic("resources/music/cos/tagpower.mp3", 14611, 65538);
                break;
            default:
                audio.addMusic("resources/music/cos/alexis.mp3", 51, 56938);
                break;
        }
    };

    this.getCOUnitRange = function(co)
    {
        return 2;
    };
    this.getCOArmy = function()
    {
        return "PF";
    };

    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var nearBuildings = false;
        var fields = globals.getCircle(0, 2);
        if (typeof map !== 'undefined')
        {
            for (var i = 0; i < fields.size(); i++)
            {
                var x = fields.at(i).x + atkPosX;
                var y = fields.at(i).y + atkPosY;
                if (map.onMap(x, y))
                {
                    var building = map.getTerrain(x, y).getBuilding();
                    if (building !== null && building.getOwner() === co.getOwner())
                    {
                        nearBuildings = true;
                        break;
                    }
                }
            }
        }
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                if (nearBuildings)
                {
                    return 50;
                }
                return 10;
            case GameEnums.PowerMode_Power:
                if (nearBuildings)
                {
                    return 30;
                }
                return 10;
            default:
                if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
                {
                    return 10;
                }
        }
    };

    this.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        if (co.inCORange(Qt.point(defPosX, defPosY), defender) ||
            co.getPowerMode() > GameEnums.PowerMode_Off)
        {
            return 10;
        }
        return 0;
    };

    this.startOfTurn = function(co)
    {
        var buildings = co.getOwner().getBuildings();
        var fields = globals.getCircle(1, 1);
        for (var i2 = 0; i2 < buildings.size(); i2++)
        {
            var building = buildings.at(i2);
            var x = building.getX();
            var y = building.getY();
            var animation = null;
            for (var i = 0; i < fields.size(); i++)
            {
                var point = fields.at(i);
                if (map.onMap(x + point.x, y + point.y))
                {
                    var unit = map.getTerrain(x + point.x, y + point.y).getUnit();
                    if ((unit !== null) &&
                            (unit.getOwner() === co.getOwner()))
                    {
                        UNIT.repairUnit(unit, 1);
                        animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                        animation.addSprite("power0", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5);
                    }
                }
            }
        }
        fields.remove();
        buildings.remove();
    };

    this.getRepairBonus = function(co, unit, posX, posY)
    {
        return -1;
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A crystal-obsessed person. Blindly follows orders.");
    };
    this.getHits = function()
    {
        return qsTr("Crystals");
    };
    this.getMiss = function()
    {
        return qsTr("Experiments");
    };
    this.getCODescription = function()
    {
        return qsTr("Units adjacent to own properties restore one HP of health at the beginning of each turn.");
    };
    this.getLongCODescription = function()
    {
        return qsTr("\nGlobal Effect:\nUnits adjacent to own properties restore one HP of health at the beginning of each turn.") +
               qsTr("\nCO Zone Effect:\nUnits gain additional 10% firepower.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Units nearby an allied property receive offensive bonuses, and restore three HP");
    };
    this.getPowerName = function()
    {
        return qsTr("Crystal Brace");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("Units nearby an allied property receive firepower bonuses. Enemies nearby their own properties suffer three HP of damage.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Crystal Edge");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("You'll regret angering me!"),
                qsTr("It's time you learned the real power of the crystals!"),
                qsTr("You were probably enjoying this battle, until now!"),
                qsTr("Witness the power the Black Crystal gave to me!"),
                qsTr("I hope you're ready for what's coming next!"),
                qsTr("See, now my army really shines, like diamonds!")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("I'm unbreakable, just like a diamond!"),
                qsTr("Haha, you were shattered!"),
                qsTr("I'll leave you to clean this up, 'kay?")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("My diamonds didn't help me."),
                qsTr("My diamonds broke?")];
    };
    this.getName = function()
    {
        return qsTr("Alexis");
    };
};

Constructor.prototype = CO;
var CO_ALEXIS = new Constructor();
