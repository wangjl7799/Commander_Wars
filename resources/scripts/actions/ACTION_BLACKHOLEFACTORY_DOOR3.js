var Constructor = function()
{
    // called for loading the main sprite
    this.canBePerformed = function(action)
    {
        var building = action.getTargetBuilding();
        var x = building.getX();
        var y = building.getY() + 1;
		var firecount = building.getFireCount();
        if ((firecount === 4 || firecount === 5 || firecount === 6 || firecount === 7) &&
            map.onMap(x, y) && map.getTerrain(x, y).getUnit() === null &&
            ACTION_BLACKHOLEFACTORY_DOOR3.canBuildUnit(action))
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
        return qsTr("Build Door 3");
    };
    this.getIcon = function()
    {
        return "build";
    };
    this.isFinalStep = function(action)
    {
		if (action.getInputStep() === 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    };
	
	this.getStepInputType = function(action)
    {
        // supported types are MENU and FIELD
        if (action.getInputStep() === 0)
        {
            return "MENU";
        }
        return "";
    };

    this.canBuildUnit = function(action)
    {
        var building = action.getTargetBuilding();
        var x = building.getX();
        var y = building.getY() + 1;
        var units = map.getAllUnitIDs();
        for (var i = 0; i < units.length; i++)
        {
            // check all units if they can move over this terrain
            if (Global[Global[units[i]].getMovementType()].getMovementpoints(map.getTerrain(x, y), null) > 0)
            {
                return true;
            }
        }
        return false;
    };

    this.getStepData = function(action, data)
    {
        var building = action.getTargetBuilding();
        var x = building.getX();
        var y = building.getY() + 1;
        var units = map.getAllUnitIDs();
        for (var i = 0; i < units.length; i++)
        {
            // check all units if they can move over this terrain
            if (Global[Global[units[i]].getMovementType()].getMovementpoints(map.getTerrain(x, y), null) > 0)
            {
                var name = Global[units[i]].getName();
                data.addData(name, units[i], units[i], 0, true);
            }
        }
    }
	
    this.perform = function(action)
    {
		action.startReading();
        var unitID = action.readDataString();
        // we need to move the unit to the target position
        var building = action.getTargetBuilding();
		var player = building.getOwner();
        var x = building.getX();
        var y = building.getY() + 1;
        building.setFireCount(building.getFireCount() - 4);
		// spawn the unit
		var unit = map.spawnUnit(x, y, unitID, player);
        map.getGameRecorder().buildUnit(player.getPlayerID());
        player.buildedUnit(unit);
    };
}

Constructor.prototype = ACTION;
var ACTION_BLACKHOLEFACTORY_DOOR3 = new Constructor();
