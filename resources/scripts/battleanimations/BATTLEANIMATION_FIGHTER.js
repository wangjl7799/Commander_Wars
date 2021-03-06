var Constructor = function()
{
    this.getMaxUnitCount = function()
    {
        return 5;
    };

    this.loadStandingAnimation = function(sprite, unit, defender, weapon)
    {
		var player = unit.getOwner();
        // get army name
        var armyName = player.getArmy().toLowerCase();
        if (armyName === "bg")
        {
            armyName = "bh"
        }
        if ((armyName !== "yc") &&
            (armyName !== "ge") &&
            (armyName !== "bm") &&
            (armyName !== "bh"))
        {
            armyName = "os";
        }
        sprite.loadSprite("fighter+" + armyName,  false,
                          BATTLEANIMATION_FIGHTER.getMaxUnitCount(), Qt.point(-40, 20));
        sprite.loadSprite("fighter+" + armyName + "+mask",  true,
                          BATTLEANIMATION_FIGHTER.getMaxUnitCount(), Qt.point(-40, 20));
    };

    this.loadFireAnimation = function(sprite, unit, defender, weapon)
    {
        BATTLEANIMATION_FIGHTER.loadStandingAnimation(sprite, unit, defender, weapon);
        var player = unit.getOwner();
        // get army name
        var armyName = player.getArmy().toLowerCase();
        if (armyName === "bg")
        {
            armyName = "bh"
        }
        var offset = Qt.point(-5, 37);
        // gun
        if (armyName === "yc")
        {
            offset = Qt.point(4, 34);
        }
        else if (armyName === "ge")
        {
            offset = Qt.point(3, 36);
        }
        else if (armyName === "bm")
        {
            offset = Qt.point(0, 33);
        }
        else if (armyName === "bh")
        {
            offset = Qt.point(0, 42);
        }
        sprite.loadMovingSprite("rocket", false, sprite.getMaxUnitCount(), offset,
                                Qt.point(127, 0), 400, false,
                                1, 1, -1);
        sprite.loadSound("rocket_launch.wav", 1, "resources/sounds/", 0);
    };

    this.getFireDurationMS = function()
    {
        // the time will be scaled with animation speed inside the engine
        return 500;
    };

    this.loadImpactAnimation = function(sprite, unit, defender, weapon)
    {
        sprite.loadSprite("unit_explosion",  false, sprite.getMaxUnitCount(), Qt.point(0, 20),
                          1, 1.0, 0, 300);
        sprite.loadMovingSprite("rocket", false, sprite.getMaxUnitCount(), Qt.point(127, 20),
                                Qt.point(-127, 0), 400, true,
                                1, 1, 0, 0, true);
        sprite.loadSound("rocket_flying.wav", 1, "resources/sounds/", 0);
        sprite.loadSound("impact_explosion.wav", 1, "resources/sounds/", 200);
    };

    this.getImpactDurationMS = function()
    {
        // should be a second or longer.
        // the time will be scaled with animation speed inside the engine
        return 1500;
    };
};

Constructor.prototype = BATTLEANIMATION;
var BATTLEANIMATION_FIGHTER = new Constructor();
