var Constructor = function()
{
    // called for loading the main sprite
    this.canBePerformed = function(action)
    {
        var co = map.getCurrentPlayer().getCO(0);
        if ((co !== null) && co.canUseSuperpower())
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    this.getActionText = function()
    {
        return qsTr("Superpower of ")  + map.getCurrentPlayer().getCO(0).getCOName();
    };
    this.getIcon = function()
    {
        return "superpower";
    };
    this.perform = function(action)
    {
        map.getCurrentPlayer().getCO(0).activateSuperpower(GameEnums.PowerMode_Superpower);
        map.getGameRecorder().addSpecialEvent(map.getCurrentPlayer().getPlayerID(),
                                              GameEnums.GameRecord_SpecialEvents_SuperPower);
    };
    this.isFinalStep = function(action)
    {
        return true;
    };
}


Constructor.prototype = ACTION;
var ACTION_ACTIVATE_SUPERPOWER_CO_0 = new Constructor();
