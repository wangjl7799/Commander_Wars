var Constructor = function()
{
    // called for loading the main sprite
    this.canBePerformed = function(action)
    {
        return true;
    };
    this.getActionText = function()
    {
        return qsTr("Game Info");
    };
    this.getIcon = function()
    {
        return "intel";
    };
    this.perform = function(action)
    {
        map.showGameInfo();
    };
    this.isFinalStep = function(action)
    {
        action.setIsLocal(true);
        return true;
    };
}


Constructor.prototype = ACTION;
var ACTION_GAMEINFO = new Constructor();
