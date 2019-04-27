var Constructor = function()
{
    this.init = function(co)
    {
        co.setPowerStars(2);
        co.setSuperpowerStars(4);
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
        units.remove();

        audio.clearPlayList();
        CO_ADDER.loadCOMusic(co);
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
        CO_ADDER.loadCOMusic(co);
        audio.playRandom();
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
                audio.addMusic("resources/music/cos/sanjuro.mp3")
                break;
        }
    };

    this.getCOUnitRange = function(co)
    {
        return 2;
    };
    this.getCOArmy = function()
    {
        return "GS";
    };

    this.getDeffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY)
    {
        if (attacker !== null)
        {
            var variables = co.getVariables();
            var buildedVar = variables.createVariable("SANJURO_BUILDED_" + defender.getUnitID());
            var builded = buildedVar.readDataBool();
            switch (co.getPowerMode())
            {
            case GameEnums.PowerMode_Superpower:
                if (builded === true)
                {
                    return 30;
                }
                else
                {
                    return 0;
                }
            case GameEnums.PowerMode_Power:
                return 0;
            default:
                break;
            }
        }
        return 0;
    };

    this.getOffensiveBonus = function(co, attacker, atkPosX, atkPosY,
                                 defender, defPosX, defPosY, isDefender)
    {
        var variables = co.getVariables();
        var dmgModVar = variables.createVariable("SANJURO_DMG_MOD");
        var builded = false
        if (attacker !== null)
        {
            var buildedVar = variables.createVariable("SANJURO_BUILDED_" + attacker.getUnitID());
            builded = buildedVar.readDataBool();
        }
        var modifier = dmgModVar.readDataFloat();
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (builded === true)
                {
                    return modifier + 50;
                }
                else
                {
                    return modifier;
                }
            case GameEnums.PowerMode_Power:
                return modifier;
            default:
                if (modifier > 0)
                {
                    if (co.inCORange(Qt.point(atkPosX, atkPosY)))
                    {
                        return modifier;
                    }
                    else
                    {
                        return modifier / 2;
                    }
                }
                else
                {
                    return modifier;
                }
        }
    };

    this.buildedUnit = function(co, unit)
    {
        // called when someone builded a unit -> ACTION_BUILD_UNITS was performed
        var variables = co.getVariables();
        var buildedVar = variables.createVariable("SANJURO_BUILDED_" + unit.getUnitID());
        buildedVar.writeDataBool(true);
    };

    this.startOfTurn = function(co)
    {
        var player = co.getPlayer();
        var fonds = player.getFonds();
        var income = player.calcIncome();
        var costModifier = 0.0;
        var damageModifier = 0.0;
        var exceed = 0;
        var maxCounter = 20;
        var counter = 0;
        if (income < fonds)
        {
            // we have more fonds than income
            exceed = fonds - income;
            // this means our troops get stronger and more expensive
            while (exceed >= 0 && counter < maxCounter)
            {
                damageModifier += 2;
                costModifier += 0.01;
                exceed -= income * 0.1;
                counter++;
            }
        }
        else
        {
            // we have less fonds than income
            exceed = income - fonds;
            // this means our troops get weaker and less expensive
            while (exceed >= 0 && counter < maxCounter)
            {
                damageModifier -= 1;
                costModifier -= 0.01;
                exceed -= income * 0.05;
                counter++;
            }
        }
        var variables = co.getVariables();
        // clean up possible variables from scop
        variables.clear();
        // create new cost and damage variables
        var dmgModVar = variables.createVariable("SANJURO_DMG_MOD");
        dmgModVar.writeDataFloat(damageModifier);
        var costModVar = variables.createVariable("SANJURO_COST_MOD");
        costModVar.writeDataFloat(costModifier);
    };

    this.getCostModifier = function(co, id, baseCost)
    {
        var variables = co.getVariables();
        var costModVar = variables.createVariable("SANJURO_COST_MOD");
        var buildedVar = variables.createVariable("SANJURO_BUILDED_" + id);
        var builded = buildedVar.readDataBool();
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                if (builded === true)
                {
                    // reduce cost of following units of the same type
                    return -(baseCost * costModVar.readDataFloat() + baseCost) * 0.5;
                }
                break;
            case GameEnums.PowerMode_Power:
                break;
            default:
                break;
        }
        return baseCost * costModVar.readDataFloat();
    };

    this.getMovementpointModifier = function(co, unit, posX, posY)
    {
        var variables = co.getVariables();
        var buildedVar = variables.createVariable("SANJURO_BUILDED_" + unit.getUnitID());
        var builded = buildedVar.readDataBool();
        if (builded === true)
        {
            // movement boost for builded units
            return -999;
        }
        return 0;
    };

    this.postBattleActions = function(co, attacker, atkDamage, defender, gotAttacked)
    {
        if (gotAttacked === true)
        {
            switch (co.getPowerMode())
            {
                case GameEnums.PowerMode_Superpower:

                    break;
                case GameEnums.PowerMode_Power:
                    // get refunds
                    co.getPlayer().addFonds(atkDamage / 10.0 * defender.getUnitCosts() * 0.5);
                    break;
                default:
                    break;
            }
        }
    };

    // CO - Intel
    this.getBio = function()
    {
        return qsTr("A respected mercenary from Golden Sun. Once he accepts a job, he sees it through to the end no matter how difficult or dangerous it becomes.");
    };
    this.getHits = function()
    {
        return qsTr("Honest work");
    };
    this.getMiss = function()
    {
        return qsTr("Shady business");
    };
    this.getCODescription = function()
    {
        return qsTr("A keen mind for his finances, he spends more for better equipment when there's a surplus and focuses on getting the best deal when he's pressed for money.");
    };
    this.getPowerDescription = function()
    {
        return qsTr("When his units take combat damage, he recieves a portion of the value of the damage in funds.");
    };
    this.getPowerName = function()
    {
        return qsTr("Heart of Gold");
    };
    this.getSuperPowerDescription = function()
    {
        return qsTr("When a unit is built, units of the same type recieve a firepower and defense boost, unhindered by terrain, and production costs reduced by half.");
    };
    this.getSuperPowerName = function()
    {
        return qsTr("Buying Power");
    };
    this.getPowerSentences = function()
    {
        return [qsTr("My services are expensive, and worth every penny."),
                qsTr("Consider this a free sample!"),
                qsTr("You're finished! Surrender now!"),
                qsTr("War is my livelihood. Can you handle my level of experience?"),
                qsTr("I was born for battle. I have no limits!"),
                qsTr("If you think this is strictly business, think again. The battlefield calls to me!")];
    };
    this.getVictorySentences = function()
    {
        return [qsTr("I have a reputation to keep, you know."),
                qsTr("Another job well done...where's the next fight?"),
                qsTr("Did you expect anything less from a hardened mercenary?")];
    };
    this.getDefeatSentences = function()
    {
        return [qsTr("For this i get to less money"),
                qsTr("Now, i know how the Romans felt like.")];
    };
    this.getName = function()
    {
        return qsTr("Sanjuro");
    };
}

Constructor.prototype = CO;
var CO_SANJURO = new Constructor();