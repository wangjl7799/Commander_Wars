#include "scriptevent.h"

#include "scripteventdialog.h"
#include "scripteventspawnunit.h"
#include "scripteventdefeatplayer.h"
#include "scripteventchangebuildlist.h"
#include "scripteventaddfunds.h"
#include "scripteventchangecobar.h"
#include "scripteventchangeweather.h"

const QString ScriptEvent::EventDialog  = "Dialog";
const QString ScriptEvent::EventSpawnUnit = "Spawn Unit";
const QString ScriptEvent::EventDefeatPlayer = "Defeat Player";
const QString ScriptEvent::EventChangeBuildlist = "Change Buildlist";
const QString ScriptEvent::EventAddFunds = "Add Funds";
const QString ScriptEvent::EventChangeWeather = "Change Weather";
const QString ScriptEvent::EventChangeCOBar = "Change CO Bar";

ScriptEvent::ScriptEvent(EventType type)
    : QObject(),
      m_Type(type)
{
}

spScriptEvent ScriptEvent::createReadEvent(QTextStream& rStream)
{
    qint64 pos = rStream.pos();
    QString line = rStream.readLine().simplified();
    rStream.seek(pos);
    ScriptEvent* ret = nullptr;
    if (line.endsWith(EventDialog))
    {
         ret = new ScriptEventDialog();
    }
    else if (line.endsWith(EventSpawnUnit))
    {
         ret = new ScriptEventSpawnUnit();
    }
    else if (line.endsWith(EventDefeatPlayer))
    {
         ret = new ScriptEventDefeatPlayer();
    }
    else if (line.endsWith(EventAddFunds))
    {
         ret = new ScriptEventAddFunds();
    }
    else if (line.endsWith(EventChangeBuildlist))
    {
         ret = new ScriptEventChangeBuildlist();
    }
    else if (line.endsWith(EventChangeWeather))
    {
         ret = new ScriptEventChangeWeather();
    }
    else if (line.endsWith(EventChangeCOBar))
    {
         ret = new ScriptEventChangeCOBar();
    }
    if (ret != nullptr)
    {
        ret->readEvent(rStream);
    }
    else
    {
        // skip line
        rStream.readLine();
    }
    return ret;
}

spScriptEvent ScriptEvent::createEvent(EventType type)
{
    switch (type)
    {
        case EventType::dialog:
        {
            return new ScriptEventDialog();
        }
        case EventType::spawnUnit:
        {
            return new ScriptEventSpawnUnit();
        }
        case EventType::defeatPlayer:
        {
            return new ScriptEventDefeatPlayer();
        }
        case EventType::addFunds:
        {
            return new ScriptEventAddFunds();
        }
        case EventType::changeCOBar:
        {
            return new ScriptEventChangeCOBar();
        }
        case EventType::changeWeather:
        {
            return new ScriptEventChangeWeather();
        }
        case EventType::changeBuildlist:
        {
            return new ScriptEventChangeBuildlist();
        }
    }
    return nullptr;
}
