var Constructor = function()
{
    this.getMaxUnitCount = function()
    {
        return 5;
    };

    this.loadStandingAnimation = function(sprite, unit, defender, weapon)
    {
        armyName = "os";
        sprite.loadSprite("sniper+" + armyName,  false,
                          BATTLEANIMATION_SNIPER.getMaxUnitCount(), Qt.point(-35, 5));
        sprite.loadSprite("sniper+" + armyName + "+mask",  true,
                          BATTLEANIMATION_SNIPER.getMaxUnitCount(), Qt.point(-35, 5));
    };

    this.getPositionOffset = function(sprite, unit, terrain, unitIdx)
    {
        if (terrain !== null)
        {
            if (terrain.getID() === "MOUNTAIN")
            {
                if (unitIdx >= 4)
                {
                    return Qt.point(-20 * (6 - unitIdx), 0);
                }
            }
        }
        return Qt.point(0, 0);
    };

    this.loadFireAnimation = function(sprite, unit, defender, weapon)
    {
        BATTLEANIMATION_SNIPER.loadStandingAnimation(sprite, unit, defender, weapon);
        // mg
        var player = unit.getOwner();
        // get army name
        var armyName = player.getArmy().toLowerCase();
        if (armyName === "bg")
        {
            armyName = "bh"
        }
        var offset = Qt.point(31, 31);
        sprite.loadSprite("mg_shot",  false, sprite.getMaxUnitCount(), offset,
                          1, 1, 0, 0);
        sprite.loadSound("mg_impact.wav", 1, "resources/sounds/", 0);
    };

    this.getFireDurationMS = function()
    {
        // the time will be scaled with animation speed inside the engine
        return 500;
    };

    this.loadImpactAnimation = function(sprite, unit, defender, weapon)
    {
        sprite.loadSprite("mg_hit",  false, sprite.getMaxUnitCount(), Qt.point(0, 22),
                          1, 1.0, 0, 0);
    };
};

Constructor.prototype = BATTLEANIMATION;
var BATTLEANIMATION_SNIPER = new Constructor();
