#ifndef CONSOLE_H
#define CONSOLE_H

#include <QVector>
#include <QObject>

#include "oxygine-framework.h"

#include "QKeyEvent"

class QString;
class QMutex;
class QKeyEvent;
class Interpreter;

class Console : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:

    static const QString functions[];

    enum eLogLevels
    {
        eDEBUG = 0,
        eINFO,
        eWARNING,
        eERROR,
        eFATAL,
        eOFF
    };

    enum
    {
        BLINKFREQG = 250,
        MAXLASTMSG = 20
    };

    static Console* getInstance();
    static void dotask(QString message);
    static void draw();
    void init();
// use slots here since they're part of QMetaObject thus they get published to JSEngine.
public slots:
    static void print(QString message, qint8 LogLevel);
    /**
     * @brief Print
     * @param message
     * @param debugMessage false for Errors or Setup Messages. True for Ingame Actions used for Debugging. But unneeded in release build
     */
    static void print(QString message, eLogLevels LogLevel);
    static void createfunnymessage(qint32 message = -1);
    // Lua Libs Functions
    void setVolume(qint32 volume);
    void setLogLevel(eLogLevels newLogLevel);
    /**
     * @brief createSprites
     * @param input
     * @param colorTable
     * @param maskTable
     */
    void createSprites(QString input, QString colorTable, QString maskTable);
    /**
     * @brief updateMaskImages
     * @param folder
     * @param filter
     */
    void updateMaskImages(QString folder, QString filter, qint32 min);
    /**
     * @brief help shows the helps messages between given indexes or all as default
     * @param start
     * @param end
     */
    void help(qint32 start = 0, qint32 end = -1);
    virtual void update(const oxygine::UpdateState& us) override;
    /**
     * @brief KeyInput event called when a key is pressed
     * @param event
     */
    void KeyInput(oxygine::KeyEvent event);
    /**
     * @brief toggleView
     */
    void toggleView();
private:
    static eLogLevels LogLevel;
    static QString curmsg;
    static QList<QString> lastmsgs;
    static const qint32 lastMsgSize{10};
    static qint32 curlastmsgpos;
    static qint32 curmsgpos;
    static QTime toggle;
    static Console* m_pConsole;
    static bool show;
    static bool toggled;
    static QList<QString> output;
    static qint32 outputSize;
    static QMutex datalocker;
    oxygine::spSprite m_pBackgroundsprite;
    oxygine::spTextField m_text;

    Console();
    virtual  ~Console() = default;

    void createSprites(QString file, QImage& colorTable, QImage maskTable);
};

#endif // CONSOLE_H
