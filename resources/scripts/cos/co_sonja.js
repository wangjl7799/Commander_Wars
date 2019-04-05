var Constructor = function()
{
    this.init = function(co)
    {
        co.setPowerStars(3);
        co.setSuperpowerStars(2);
    };

    this.activatePower = function(co)
    {
        var animation2 = GameAnimationFactory.createAnimation(0, 0);
        animation2.addSprite2("white_pixel", 0, 0, 3200, map.getMapWidth(), map.getMapHeight());
        animation2.addTweenColor(0, "#00FFFFFF", "#FFFFFFFF", 3000, true);

        audio.clearPlayList();
        audio.addMusic("resources/music/cos/power.mp3");
        audio.playRandom();
    };

    this.activateSuperpower = function(co)
    {
        var animation2 = GameAnimationFactory.createAnimation(0, 0);
        animation2.addSprite2("white_pixel", 0, 0, 3200, map.getMapWidth(), map.getMapHeight());
        animation2.addTweenColor(0, "#00FFFFFF", "#FFFFFFFF", 3000, true);

        audio.clearPlayList();
        audio.addMusic("resources/music/cos/superpower.mp3");
        audio.playRandom();
    };
    this.startOfTurn = function(co)
    {
        audio.addMusic("resources/music/cos/sonja.mp3")
    };

    this.getCOUnitRange = function(co)
    {
        return 2;
    };
    this.getCOArmy = function()
    {
        return "YC";
    };
	
    this.getBonusMisfortune = function(co, unit, posX, posY)
    {
        return 5;
    };

    this.getVisionrangeModifier = function(co, unit, posX, posY)
    {
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
            case GameEnums.PowerMode_Power:
                return 2;
            default:
                return 1;
        }
    };
    this.getEnemyTerrainDefenseModifier = function(co, unit, posX, posY)
    {
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                return -3;
            case GameEnums.PowerMode_Power:
                return -2;
            default:
                return -1;
        }
    };

    this.getPerfectVision = function(co)
    {
        // return true if forest and reafs etc are disabled in fog of war see sonja
        switch (co.getPowerMode())
        {
            case GameEnums.PowerMode_Superpower:
                return true;
            case GameEnums.PowerMode_Power:
                return true;
            default:
                return false;
        }
    };

    this.getHpHidden = function(co, unit, posX, posY)
    {
        // are the hp hidden of this unit?
        return true;
    };
}

Constructor.prototype = CO;
var CO_SONJA = new Constructor();
