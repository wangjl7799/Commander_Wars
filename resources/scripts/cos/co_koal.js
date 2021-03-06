var Constructor = function()
{
    this.getCOStyles = function()
    {
        // string array containing the endings of the alternate co style
        // e.g. co_adder has ["+alt"]
        return ["+alt"];
    };

    this.init = function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(2);
    };

    this.loadCOMusic = function(co)
    {
        // put the co music in here.
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Power:
                audio.addMusic("resources/music/cos/bh_power.mp3", 1091 , 49930);
                break;
            case GameEnums.PowerMode_Superpower:
                audio.addMusic("resources/music/cos/bh_superpower.mp3", 3161 , 37731);
                break;
            case GameEnums.PowerMode_Tagpower:
                audio.addMusic("resources/music/cos/bh_tagpower.mp3", 779 , 51141);
                break;
            default:
                audio.addMusic("resources/music/cos/koal.mp3", 14166, 103617);
                break;
        }
    };

    this.activatePower = function(co)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(GameEnums.PowerMode_Power);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getOwner().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);

            var animation = GameAnimationFactory.createAnimation(unit.getX(), unit.getY());
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
        units.remove();

        audio.clearPlayList();
        CO_KOAL.loadCOMusic(co);
        audio.playRandom();
    };

    this.activateSuperpower = function(co, powerMode)
    {
        var dialogAnimation = co.createPowerSentence();
        var powerNameAnimation = co.createPowerScreen(powerMode);
        dialogAnimation.queueAnimation(powerNameAnimation);

        var units = co.getOwner().getUnits();
        var animations = [];
        var counter = 0;
        units.randomize();
        for (var i = 0; i < units.size(); i++)
        {
            var unit = units.at(i);

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
        units.remove();

        audio.clearPlayList();
        CO_KOAL.loadCOMusic(co);
        audio.playRandom();
    };

    this.getCOUnitRange = function(co)
    {
        return 3;
    };
    this.getCOArmy = function()
    {
        return "BG";
    };
    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        if (typeof map !== 'undefined')
        {
            if (map.onMap(atkPosX, atkPosY))
            {
                var terrainID = map.getTerrain(atkPosX, atkPosY).getID();
                switch (co.getPowerMode())
                {
                case GameEnums.PowerMode_Tagpower:
                case GameEnums.PowerMode_Superpower:
                    if (terrainID === "STREET")
                    {
                        return 40;
                    }
                    return 10;
                case GameEnums.PowerMode_Power:
                    if (terrainID === "STREET")
                    {
                        return 30;
                    }
                    return 10;
                default:
                    if (co.inCORange(Qt.point(atkPosX, atkPosY), attacker))
                    {
                        if (terrainID === "STREET")
                        {
                            return 30;
                        }
                        return 10;
                    }
                    break;
                }
            }
        }
        return 0;
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

    this.getMovementpointModifier = function(co, unit, posX, posY)
    {
        if (co.getPowerMode() === GameEnums.PowerMode_Superpower ||
            co.getPowerMode() === GameEnums.PowerMode_Tagpower)
        {
            return 2;
        }
		else if (co.getPowerMode() === GameEnums.PowerMode_Power)
        {
            return 1;
        }
        return 0;
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A commander of the Black Hole army who is always planning his next destructive act.Endless March");
    };
    this.getHits = function()
    {
        return qsTr("Proverbs");
    };
    this.getMiss = function()
    {
        return qsTr("Fondue");
    };
    this.getCODescription = function()
    {
        return qsTr("A master of road-based battles. Firepower of all units increased on roads.");
    };
    this.getLongCODescription = function()
    {
        return qsTr("\nGlobal Effect:\nNo Effects.") +
               qsTr("\nCO Zone Effect:\nUnits gain 30% increased firepower on street.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("Movement range for all units is increased by one space. Units have more firepower on roads.");
    };
    this.getPowerName = function()
    {
        return qsTr("Forced March");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("Movement range for all units is increased by two spaces. Greatly increases firepower of units on roads.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Trail of Woe");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("I will crush your units, one by one!"),
                qsTr("I am a warrior and a scholar. My victory is all but certain."),
                qsTr("Heh heh heh. I'll not surrender! Bend your knees and beg for mercy!"),
                qsTr("Heh heh heh... None shall escape."),
                qsTr("My speed knows no equal!"),
                qsTr("Heh heh heh... Fate has smiled on me this day!")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("I have no equal on the field of war!"),
                qsTr("Wallow in your shame, swine! Wallow, I say"),
                qsTr("Victory is no accident.")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("He! He! He!...??? What?"),
                qsTr("One time you win and another time you loose.")];
    };
    this.getName = function()
    {
        return qsTr("Koal");
    };
}

Constructor.prototype = CO;
var CO_KOAL = new Constructor();
