#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QObject>
#include <QVector>
#include "oxygine-framework.h"

class CO;
class PlayerInfo;
typedef oxygine::intrusive_ptr<PlayerInfo> spPlayerInfo;

class PlayerInfo : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit PlayerInfo();

signals:

public slots:
    void updateData();

protected:
    void drawPowerMeter(CO* pCO, qint32 yPos);
private:
    QVector<oxygine::spSprite> playerBackground;
};

#endif // PLAYERINFO_H
