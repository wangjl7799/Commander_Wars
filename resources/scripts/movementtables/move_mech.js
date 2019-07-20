var Constructor = function()
{
    this.getName = function()
    {
        return qsTr("Mech");
    };
    this.getMovementpoints = function(terrain)
    {
        switch (terrain.getID())
        {
            case "PLAINS":
            case "PLAINS_DESTROYED":
            case "PLAINS_PLASMA":
            case "BEACH":
            case "BRIDGE":
            case "DESTROYEDWELD":
            case "FOREST":
            case "RUIN":
            case "STREET":
            case "WASTELAND":
            case "AIRPORT":
            case "FACTORY":
            case "HARBOUR":
            case "HQ":
            case "MINE":
            case "PIPESTATION":
            case "RADAR":
            case "TOWER":
            case "TOWN":
            case "SILO":
            case "SILO_ROCKET":
            case "LABOR":
            case "TEMPORARY_AIRPORT":
            case "TEMPORARY_HARBOUR":
			case "MOUNTAIN":
            case "RIVER":                
            case "DESERT":
            case "DESERT_DESTROYEDWELD":
            case "DESERT_PATH":
            case "DESERT_TRY_RIVER":
            case "SNOW":
            case "SNOW_DESTROYEDWELD":
            case "WASTELAND":
            case "DESERT_FOREST":
            case "DESERT_WASTELAND":
            case "SNOW_FOREST":
            case "SNOW_WASTELAND":
                return 1;
        }
        return -1;
    };
};
Constructor.prototype = MOVEMENTTABLE;
var MOVE_MECH = new Constructor();
