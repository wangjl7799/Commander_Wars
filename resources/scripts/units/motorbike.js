var Constructor = function()
{
    this.init = function(unit)
    {
        unit.setAmmo1(10);
        unit.setMaxAmmo1(10);
        unit.setWeapon1ID("WEAPON_MOTORBIKE_MG");

        unit.setAmmo2(0);
        unit.setMaxAmmo2(0);
        unit.setWeapon2ID("");

        unit.setFuel(70);
        unit.setMaxFuel(70);
        unit.setBaseMovementPoints(5);
        unit.setMinRange(1);
        unit.setMaxRange(1);
        unit.setVision(2);
    };
    this.getBaseCost = function()
    {
        return 2500;
    };
    // called for loading the main sprite
    this.loadSprites = function(unit)
    {
        // load sprites
        unit.loadSprite("motorbike" , false);
        unit.loadSprite("motorbike+mask", true);
    };
    this.getMovementType = function()
    {
        return "MOVE_TIRE_B";
    };
    this.getActions = function()
    {
        // returns a string id list of the actions this unit can perform
        return "ACTION_MISSILE,ACTION_CAPTURE,ACTION_FIRE,ACTION_JOIN,ACTION_LOAD,ACTION_WAIT,ACTION_CO_UNIT_0,ACTION_CO_UNIT_1";
    };
    this.getName = function()
    {
        return qsTr("Motorbike");
    };
    this.canMoveAndFire = function()
    {
        return true;
    };

    this.doWalkingAnimation = function(action)
    {
        var unit = action.getTargetUnit();
        var animation = GameAnimationFactory.createWalkingAnimation(unit, action);
        var unitID = unit.getUnitID().toLowerCase();
        animation.loadSprite(unitID + "+walk+mask", true, 1.5);
        animation.loadSprite(unitID + "+walk", false, 1.5);
        animation.setSound("movetire.wav", -2);
        return animation;
    };

    this.getDescription = function()
    {
        return "<r>" + qsTr("Infantry unit. High mobility. Able to ") + "</r>" +
               "<div c='#00ff00'>" + qsTr("capture ") + "</div>" +
               "<r>" + qsTr(" bases.") + "</r>";
    };
    this.getUnitType = function()
    {
        return GameEnums.UnitType_Ground;
    };
}

Constructor.prototype = UNIT;
var MOTORBIKE = new Constructor();
