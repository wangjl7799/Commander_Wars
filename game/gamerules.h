#ifndef GAMERULES_H
#define GAMERULES_H

#include <QObject>

#include "coreengine/fileserializable.h"

#include "game/victoryrule.h"

#include "game/weather.h"

#include "game/GameEnums.h"

#include "coreengine/timer.h"

#include "oxygine-framework.h"

class Player;
class Unit;

class GameRules;
typedef oxygine::intrusive_ptr<GameRules> spGameRules;

/**
 * @brief The GameRules class
 * this class holds the general rules on how the game is played.
 * There is a small amount of rules that's hard coded in this object.
 * But most rules are taken from javascript scripts
 */
class GameRules : public QObject, public FileSerializable, public oxygine::ref_counter
{
    Q_OBJECT
public:
    explicit GameRules();
    virtual ~GameRules() = default;
    /**
     * @brief serialize stores the object
     * @param pStream
     */
    virtual void serializeObject(QDataStream& pStream) override;
    /**
     * @brief deserialize restores the object
     * @param pStream
     */
    virtual void deserializeObject(QDataStream& pStream) override;
    /**
     * @brief getVersion version of the file
     * @return
     */
    inline virtual qint32 getVersion() override
    {
        return 6;
    }
    void addVictoryRule(spVictoryRule rule);
    /**
     * @brief createWeatherSprites
     */
    void createWeatherSprites();

    Timer* getRoundTimer()
    {
        return &m_RoundTimer;
    }


signals:
    void signalVictory(qint32 team);
public slots:
    /**
     * @brief getWeatherPrediction
     * @return
     */
    bool getWeatherPrediction() const;
    /**
     * @brief setWeatherPrediction
     * @param WeatherPrediction
     */
    void setWeatherPrediction(bool WeatherPrediction);
    /**
     * @brief getCOBannlist
     * @return
     */
    QStringList getCOBannlist() const;
    /**
     * @brief setCOBannlist
     * @param COBannlist
     */
    void setCOBannlist(const QStringList &COBannlist);
    /**
     * @brief getAiAttackTerrain
     * @return
     */
    bool getAiAttackTerrain() const;
    /**
     * @brief setAiAttackTerrain
     * @param AiAttackTerrain
     */
    void setAiAttackTerrain(bool AiAttackTerrain);
    /**
     * @brief setStartWeather
     * @param index
     * @param duration
     */
    void setStartWeather(qint32 index);
    /**
     * @brief getStartWeather
     * @return
     */
    qint32 getStartWeather() const;
    /**
     * @brief checkVictory checks for defeats of a player and for the win of a team;
     */
    void checkVictory();
    void addVictoryRule(QString rule);
    void removeVictoryRule(QString rule);
    VictoryRule* getVictoryRule(QString rule);
    /**
     * @brief addWeather
     * @param weatherId
     * @param weatherChance
     */
    void addWeather(QString weatherId, qint32 weatherChance);
    /**
     * @brief changeWeatherChance
     * @param weatherId
     * @param weatherChance
     */
    void changeWeatherChance(QString weatherId, qint32 weatherChance);
    /**
     * @brief changeWeatherChance
     * @param index
     * @param weatherChance
     */
    void changeWeatherChance(qint32 index, qint32 weatherChance);
    /**
     * @brief getCurrentWeather
     * @return
     */
    inline Weather* getCurrentWeather()
    {
        if (m_CurrentWeather >= 0)
        {
            return m_Weathers[m_CurrentWeather].get();
        }
        return nullptr;
    }
    /**
     * @brief getWeatherAtDay
     * @param futureDay
     * @param player
     * @return
     */
    Weather* getWeatherAtDay(qint32 futureDay, qint32 player);

    inline qint32 getCurrentWeatherId()
    {
        return m_CurrentWeather;
    }
    /**
     * @brief getWeather
     * @param index
     * @return
     */
    Weather* getWeather(qint32 index);
    /**
     * @brief getCurrentWeather
     * @return
     */
    Weather* getWeather(QString weatherId);
    /**
     * @brief getWeatherChance
     * @param index
     * @return
     */
    qint32 getWeatherChance(QString weatherId);
    /**
     * @brief getWeatherCount
     * @return
     */
    inline qint32 getWeatherCount()
    {
        return m_Weathers.size();
    }
    /**
     * @brief startOfTurn
     */
    void startOfTurn(bool newDay);
    /**
     * @brief changeWeather
     * @param weatherId
     * @param duration
     */
    void changeWeather(QString weatherId, qint32 duration, qint32 startDay = 0);
    /**
     * @brief changeWeather changes the weather for n-days
     * @param weatherId
     * @param duration
     */
    void changeWeather(qint32 weatherId, qint32 duration, qint32 startDay = 0, bool apply = true);
    /**
     * @brief setCurrentWeather sets the current weather
     * @param weatherId
     */
    void setCurrentWeather(qint32 weatherId);

    bool getRankingSystem() const;
    void setRankingSystem(bool RankingSystem);

    bool getNoPower() const;
    void setNoPower(bool NoPower);

    qint32 getUnitLimit() const;
    void setUnitLimit(const qint32 &UnitLimit);

    bool getRandomWeather() const;
    void setRandomWeather(bool randomWeather);

    GameEnums::Fog getFogMode() const;
    void setFogMode(const GameEnums::Fog &FogMode);
    /**
     * @brief createFogVision
     */
    void createFogVision();
    /**
     * @brief showHideStealthUnit
     * @param pPlayer
     * @param pUnit
     */
    void showHideStealthUnit(Player* pPlayer, Unit* pUnit);
    /**
     * @brief getVictoryRuleSize
     * @return
     */
    inline qint32 getVictoryRuleSize()
    {
        return m_VictoryRules.size();
    }
    inline VictoryRule* getVictoryRule(qint32 index)
    {
        return m_VictoryRules[index].get();
    }
    /**
     * @brief setRoundTimeMs
     * @param timeMs
     */
    void setRoundTimeMs(qint32 timeMs)
    {
        roundTime = timeMs;
    }
    /**
     * @brief getRoundTimeMs
     * @return
     */
    qint32 getRoundTimeMs()
    {
        return roundTime;
    }
    /**
     * @brief pauseRoundTime
     */
    void pauseRoundTime()
    {
        m_RoundTimer.pause();
    }
    /**
     * @brief resumeRoundTime
     */
    void resumeRoundTime();
    /**
     * @brief startRoundTime
     */
    void initRoundTime();


private:
    // victory conditions
    QVector<spVictoryRule> m_VictoryRules;
    // weather chances
    QVector<spWeather> m_Weathers;
    QVector<qint32> m_WeatherChances;
    QVector<QVector<qint32>> m_WeatherDays;
    qint32 m_CurrentWeather{-1};
    qint32 m_StartWeather{-1};
    qint32 m_DayWeather{-1};
    bool m_randomWeather{true};

    bool m_RankingSystem{true};
    bool m_NoPower{false};
    GameEnums::Fog m_FogMode{GameEnums::Fog_Off};
    qint32 m_UnitLimit{0};

    QVector<QVector<oxygine::spSprite>> m_FogSprites;
    QVector<oxygine::spSprite> m_WeatherSprites;

    qint32 roundTime{0};
    Timer m_RoundTimer;

    bool m_AiAttackTerrain{true};
    QStringList m_COBannlist;
    bool m_COBannlistEdited{false};
    bool m_WeatherPrediction{true};

};

#endif // GAMERULES_H
