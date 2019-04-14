var Constructor = function()
{
    this.init = function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(4);
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
                audio.addMusic("resources/music/cos/olaf.mp3")
                break;
        }
    };

    this.activatePower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(false);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var animation2 = GameAnimationFactory.createAnimation(0, 0);
        animation2.addSprite2("white_pixel", 0, 0, 3200, map.getMapWidth(), map.getMapHeight());
        animation2.addTweenColor(0, "#00FFFFFF", "#FFFFFFFF", 3000, true);
        powerNameAnimation.queueAnimation(animation2);
        map.getGameRules().changeWeather("WEATHER_SNOW", map.getPlayerCount() * 2);
        audio.clearPlayList();
        CO_OLAF.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(false);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var animation2 = GameAnimationFactory.createAnimation(0, 0);
        animation2.addSprite2("white_pixel", 0, 0, 3200, map.getMapWidth(), map.getMapHeight());
        animation2.addTweenColor(0, "#00FFFFFF", "#FFFFFFFF", 3000, true);
        map.getGameRules().changeWeather("WEATHER_SNOW", map.getPlayerCount() * 2);
        powerNameAnimation.queueAnimation(animation2);
        CO_OLAF.olafDamage(co, 2, animation2);
        audio.clearPlayList();
        CO_OLAF.loadCOMusic(co);
        audio.playRandom();
    };

    this.olafDamage = function(co, value, animation2)
    {
        var player = co.getPlayer();
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
                        animation2.queueAnimation(animation);
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
                    var hp = unit.getHpRounded();
                    if (hp <= value)
                    {
                        // set hp to very very low
                        unit.setHp(0.001);
                    }
                    else
                    {
                        unit.setHp(hp - value);
                    }
                }
                units.remove();
            }
        }
    };

    this.startOfTurn = function(co)
    {
        audio.addMusic("resources/music/cos/olaf.mp3")
    };

    this.getCOUnitRange = function(co)
    {
        return 2;
    };
    this.getCOArmy = function()
    {
        return "BM";
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (map.getGameRules().getCurrentWeather().getWeatherId() === "WEATHER_SNOW")
                {
                    // apply snow buff :)
                    return 40;
                }
                else
                {
                    return 20;
                }
            case GameEnums.PowerMode_Power:
                if (map.getGameRules().getCurrentWeather().getWeatherId() === "WEATHER_SNOW")
                {
                    // apply snow buff :)
                    return 40;
                }
                else
                {
                    return 20;
                }
            default:
                if (co.inCORange(Qt.point(atkPosX, atkPosY)))
                {
                    if (map.getGameRules().getCurrentWeather().getWeatherId() === "WEATHER_SNOW")
                    {
                        // apply snow buff :)
                        return 20;
                    }
                    return 10;
                }
                break;
        }
        if (map.getGameRules().getCurrentWeather().getWeatherId() === "WEATHER_SNOW")
        {
            // apply snow buff :)
            return 10;
        }
        return 0;
    };
    this.getMovementpointModifier = function(co, unit, posX, posY)
    {
        if (map.getGameRules().getCurrentWeather().getWeatherId() === "WEATHER_SNOW")
        {
            // apply snow buff :)
            return -1;
        }
        else
        {
            return 0;
        }
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("He may be a pompous braggart, but his tactical prowess has earned him the respect of his peers and the admiration of his people. Old Man Winter");
    };
    this.getHits = function()
    {
        return qsTr("Warm boots");
    };
    this.getMiss = function()
    {
        return qsTr("Rain clouds");
    };
    this.getCODescription = function()
    {
        return qsTr("Winter poses no problem for Olaf or his troops. Snow causes his firepower to rise, and his troops can move through it without any penalties.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Causes snow to fall for two days, causing his firepower to rise.");
    };
    this.getPowerName = function()
    {
        return qsTr("Blizzard");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("A mighty blizzard causes two HP of damage to all enemy troops. The snow will also cause his firepower to rise for two days.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Winter Fury");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("Oho ho ho.  Do you think your pitiful troops can stand the cold?"),
                qsTr("Neither man nor machine can withstand the fury of nature!"),
                qsTr("You're going to regret challenging me!"),
                qsTr("Let the winds of war bring snow!"),
                qsTr("I'll bury you!"),
                qsTr("Your weapons are powerless before the might of nature!")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("Olaf's troops know no match!"),
                qsTr("I won! ...That is...we won!"),
                qsTr("In the end, Olaf stands victorious!")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("Unbelievable! We've been forced to withdraw? What's going on?"),
                qsTr("Next time, I will give them a display of true might! Mark my words!")];
    };
    this.getName = function()
    {
        return qsTr("Olaf");
    };
}

Constructor.prototype = CO;
var CO_OLAF = new Constructor();
