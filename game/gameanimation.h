#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H

#include <QObject>
#include <QVector>
#include <QColor>
#include <QBuffer>
#include <QDataStream>

#include "oxygine-framework.h"

class GameAnimation;
typedef oxygine::intrusive_ptr<GameAnimation> spGameAnimation;

class GameAnimation : public QObject, public oxygine::Sprite
{
    Q_OBJECT
public:
    explicit GameAnimation(quint32 frameTime);
    virtual ~GameAnimation() = default;

    virtual void restart();
    virtual void stop();
signals:
    void sigFinished();
public slots:
    /**
     * @brief setRotation sets the rotation of this animation
     * @param angle angle in degree 0° to 360°
     */
    void setRotation(float angle);
    /**
     * @brief queueAnimation
     * @param pGameAnimation
     */
    void queueAnimation(GameAnimation* pGameAnimation);
    /**
     * @brief addSprite
     * @param spriteID
     */
    void addSprite(QString spriteID, float offsetX, float offsetY, qint32 sleepAfterFinish = 0, float scale = 1.0f, qint32 delay = 0);
    /**
     * @brief addSprite
     * @param spriteID
     */
    void addSprite2(QString spriteID, float offsetX, float offsetY, qint32 sleepAfterFinish = 0, float scaleX = 1.0f, float scaleY = 1.0f, qint32 delay = 0);
    /**
      * @brief addSprite3
      * @param spriteID
      * @param offsetX
      * @param offsetY
      * @param sleepAfterFinish
      * @param scaleX
      * @param scaleY
      * @param delay
      */
    void addSprite3(QString spriteID, float offsetX, float offsetY, QColor color, qint32 sleepAfterFinish = 0, float scaleX = 1.0f, float scaleY = 1.0f, qint32 delay = 0);
    /**
     * @brief addText
     * @param text
     */
    void addText(QString text, float offsetX, float offsetY, float scale, QColor color = Qt::GlobalColor::black);
    /**
     * @brief onFinished called when the animation is finished
     */
    virtual bool onFinished();
    /**
     * @brief setEndOfAnimationCall calls a java script function when the animation is finished. Note: no parameters can be used to call the function
     * @param postActionObject java script object that will be used
     * @param postActionFunction java script function of the object that will be called
     */
    void setEndOfAnimationCall(QString postActionObject, QString postActionFunction);
    /**
     * @brief setSound sets the sound to be played during this animation
     * @param soundFile sound file
     * @param loops amount of loops to play this sound -1 till the animation is over;
     */
    void setSound(QString soundFile, qint32 loops, QString folder = "resources/sounds/");
    /**
     * @brief addTweenScale adds a tween to change the scale of this animation
     * @param endScale final scaling of the animation
     * @param duration duration of scaling up
     */
    void addTweenScale(float endScale, qint32 duration);
    /**
     * @brief addTweenPosition adds a tween to change the position of this animation
     * @param point final position of the animation
     * @param duration duration of scaling up
     */
    void addTweenPosition(QPoint point, qint32 duration);
    /**
     * @brief addTweenColor
     * @param startColor
     * @param endColor
     * @param duration
     * @param twoSided
     */
    void addTweenColor(qint32 spriteIdx, QColor startColor, QColor endColor, qint32 duration, bool twoSided, qint32 delay = 0);
    /**
     * @brief addTweenWait
     * @param duration
     */
    void addTweenWait(qint32 duration);
    /************ post animation stuff **************************/
    /**
     * @brief seekBuffer seeks the variable buffer to 0
     */
    void seekBuffer()
    {
        buffer.seek(0);
    }
    /**
     * @brief writeDataString adds a string to the action data
     * @param data
     */
    void writeDataString(QString data)
    {
        actionData << data;
    }
    /**
     * @brief readDataString
     * @return reads a string from the action data
     */
    QString readDataString()
    {
        QString data;
        if (buffer.size() > 0)
        {
            actionData >> data;
        }
        return data;
    }
    /**
     * @brief writeDataInt32 adds a int32 to the action data
     * @param data
     */
    void writeDataInt32(qint32 data)
    {
        actionData << data;
    }
    /**
     * @brief readDataInt32
     * @return reads a int32 from the action data
     */
    qint32 readDataInt32()
    {
        qint32 data = 0;
        if (buffer.size() > 0)
        {
            actionData >> data;
        }
        return data;
    }
    /**
     * @brief writeDataFloat adds a float to the action data
     * @param data
     */
    void writeDataFloat(float data)
    {
        actionData << data;
    }
    /**
     * @brief readDataFloat
     * @return reads a float from the action data
     */
    float readDataFloat()
    {
        float data = 0.0f;
        if (buffer.size() > 0)
        {
            actionData >> data;
        }
        return data;
    }
    /**
     * @brief writeDataFloat adds a float to the action data
     * @param data
     */
    void writeDataBool(bool data)
    {
        actionData << data;
    }
    /**
     * @brief readDataBool
     * @return reads a float from the action data
     */
    bool readDataBool()
    {
        bool data = false;
        if (buffer.size() > 0)
        {
            actionData >> data;
        }
        return data;
    }
protected:
    virtual void update(const oxygine::UpdateState& us) override;
    quint32 m_frameTime{1};
    bool m_stopped{false};
private:

    QVector<GameAnimation*> m_QueuedAnimations;
    QString jsPostActionObject{""};
    QString jsPostActionFunction{""};

    QString m_soundFile;
    QString m_soundFolder;
    qint32 m_loops;
    bool m_SoundStarted{false};

    /**
     * @brief animation data needed to perform this action
     */
    QBuffer buffer;
    QDataStream actionData{&buffer};

};

#endif // GAMEANIMATION_H
