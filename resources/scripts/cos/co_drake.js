var Constructor = function()
{
    this.getCOStyles = function()
    {
        // string array containing the endings of the alternate co style
        // e.g. co_adder has ["+alt"]
        return ["+alt"];
    };

    this.getAiUsePower = function(co, powerSurplus, unitCount, repairUnits, indirectUnits, directUnits, enemyUnits, turnMode)
    {
        return CO.getAiUsePowerAlways(co, powerSurplus);
    };

    this.init = function(co)
    {
        co.setPowerStars(4);
        co.setSuperpowerStars(3);
    };

    this.activatePower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(GameEnums.PowerMode_Power);
        dialogAnimation.queueAnimation(powerNameAnimation);

        CO_DRAKE.drakeDamage(co, 1, powerNameAnimation);
        audio.clearPlayList();
        CO_DRAKE.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co, powerMode)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(powerMode);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var animation = GameAnimationFactory.createAnimation(0, 0);
        animation.addSprite2("white_pixel", 0, 0, 3200, map.getMapWidth(), map.getMapHeight());
        animation.addTweenColor(0, "#00FFFFFF", "#FFFFFFFF", 3000, true);
        powerNameAnimation.queueAnimation(animation);

        map.getGameRules().changeWeather("WEATHER_RAIN", map.getPlayerCount() * 2);
        CO_DRAKE.drakeDamage(co, 2, animation);
        audio.clearPlayList();
        CO_DRAKE.loadCOMusic(co);
        audio.playRandom();
    };

    this.drakeDamage = function(co, value, animation2)
    {
        var player = co.getOwner();
        var counter = 0;
        var playerCounter = map.getPlayerCount();
        var animation = null;
        var animations = [];
        for (var i2 = 0; i2 < playerCounter; i2++)
        {
            var enemyPlayer = map.getPlayer(i2);
            if ((enemyPlayer !== player) &&
                (player.checkAlliance(enemyPlayer) === GameEnums.Alliance_Enemy))
            {

                var units = enemyPlayer.getUnits();
                units.randomize();
                for (i = 0; i < units.size(); i++)
                {
                    var unit = units.at(i);

                    animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
                    if (animations.length < 5)
                    {
                        animation.addSprite("power4", -map.getImageSize() * 1.27, -map.getImageSize() * 1.27, 0, 1.5, globals.randInt(0, 400));
                        if (animation2 !== null)
                        {
                            animation2.queueAnimation(animation);
                        }
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
                    animation.writeDataInt32(unit.getX());
                    animation.writeDataInt32(unit.getY());
                    animation.writeDataInt32(value);
                    animation.setEndOfAnimationCall("CO_DRAKE", "postAnimationDamage");

                }
                units.remove();
            }
        }
    };

    this.postAnimationDamage = function(postAnimation)
    {
        postAnimation.seekBuffer();
        var x = postAnimation.readDataInt32();
        var y = postAnimation.readDataInt32();
        var damage = postAnimation.readDataInt32();
        if (map.onMap(x, y))
        {
            var unit = map.getTerrain(x, y).getUnit();
            if (unit !== null)
            {
                var hp = unit.getHpRounded();
                if (hp <= damage)
                {
                    // set hp to very very low
                    unit.setHp(0.001);
                }
                else
                {
                    unit.setHp(hp - damage);
                }
                // reduce fuel
                unit.setFuel(unit.getFuel() / 2);
            }

        }
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
                audio.addMusic("resources/music/cos/drake.mp3", 28, 60371)
                break;
        }
    };

    this.getCOUnitRange = function(co)
    {
        return 3;
    };
    this.getCOArmy = function()
    {
        return "GE";
    };
    this.getAirUnitIDS = function()
    {
        return ["BOMBER", "BLACK_BOMB", "FIGHTER", "DUSTER", "K_HELI", "T_HELI", "STEALTHBOMBER", "TRANSPORTPLANE", "WATERPLANE"];
    };
    this.getSeaUnitIDS = function()
    {
        return ["AIRCRAFTCARRIER", "CRUISER", "BATTLESHIP", "CANNONBOAT", "BLACK_BOAT", "LANDER", "DESTROYER", "SUBMARINE"];
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var airUnits = CO_DRAKE.getAirUnitIDS();
        var seaUnits = CO_DRAKE.getSeaUnitIDS();
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Tagpower:
            case GameEnums.PowerMode_Superpower:
                if (seaUnits.indexOf(attacker.getUnitID()) >= 0)
                {
                    return 20;
                }
                break;
            case GameEnums.PowerMode_Power:
                if (seaUnits.indexOf(attacker.getUnitID()) >= 0)
                {
                    return 20;
                }
                break;
            default:
                if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
                {
                    if (seaUnits.indexOf(attacker.getUnitID()) >= 0)
                    {
                        return 30;
                    }
                    else if (airUnits.indexOf(attacker.getUnitID()) >= 0)
                    {
                        return -5;
                    }
                    return 10;
                }
                break;
        }
        if (seaUnits.indexOf(attacker.getUnitID()) >= 0)
        {
            return 10;
        }
        if (airUnits.indexOf(attacker.getUnitID()) >= 0)
        {
            return -15;
        }
        return 0;
    };
    this.getMovementpointModifier = function(co, unit, posX, posY)
    {
        var seaUnits = CO_DRAKE.getSeaUnitIDS();
        if (seaUnits.indexOf(unit.getUnitID()) >= 0)
        {
            return 1;
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

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A bighearted former pirate who hates fighting. Also a great surfer.");
    };
    this.getHits = function()
    {
        return qsTr("The sea");
    };
    this.getMiss = function()
    {
        return qsTr("High places");
    };
    this.getCODescription = function()
    {
        return qsTr("Naval units have superior firepower, but air units have reduced firepower.");
    };
    this.getLongCODescription = function()
    {
        return qsTr("\nGlobal Effect:\nNaval units have 1 more movement point. Air units are 15% weaker and Sea units 10% stronger") +
               qsTr("\nCO Zone Effect:\nNaval units have 30% increased firepower.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Causes a tidal wave that does one HP of damage to all enemy units.");
    };
    this.getPowerName = function()
    {
        return qsTr("Tsunami");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("Causes a giant tidal wave that does two HP of damage to all enemy units and weather changes to rain.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Typhoon");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("Panic is for landlubbers!"),
                qsTr("Prepare to be washed away!"),
                qsTr("Time to show you how we do things at sea!"),
                qsTr("Wave good-bye to your troops!"),
                qsTr("Can't you just feel the riptide washing you out to open sea?"),
                qsTr("Drake is taking the helm!")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("I'm just glad I survived that..."),
                qsTr("That was some rough sailing!|Blow me down... we finally won.")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("A job well done! You've beaten me."),
                qsTr("Curses! I've been defeated. Time to hoist sail and flee!")];
    };
    this.getName = function()
    {
        return qsTr("Drake");
    };
}

Constructor.prototype = CO;
var CO_DRAKE = new Constructor();
