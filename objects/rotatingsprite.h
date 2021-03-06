#ifndef ROTATINGSPRITE_H
#define ROTATINGSPRITE_H

#include <QTime>

#include "oxygine-framework.h"

class RotatingSprite;
typedef oxygine::intrusive_ptr<RotatingSprite> spRotatingSprite;

class RotatingSprite : public oxygine::Actor
{
public:
    explicit RotatingSprite();
    virtual ~RotatingSprite() = default;
    void setSprite(oxygine::spActor firstSprite, oxygine::spActor secondSprite);
    qint32 getSpeed() const;
    void setSpeed(const qint32 &value);
    virtual void sizeChanged(const oxygine::Vector2& size) override;
    qint32 getDirection() const;
    void setDirection(const qint32 &value);

protected:
    virtual void doUpdate(const oxygine::UpdateState& us) override;
private:
    oxygine::spClipRectActor m_FirstRect;
    oxygine::spClipRectActor m_SecondRect;
    oxygine::spActor m_FirstSprite;
    oxygine::spActor m_SecondSprite;
    QTime speedTimer;
    qint32 speed{10};
    qint32 direction{1};
};

#endif // ROTATINGSPRITE_H
