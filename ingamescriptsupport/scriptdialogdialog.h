#ifndef SCRIPTDIALOGDIALOG_H
#define SCRIPTDIALOGDIALOG_H

#include <QObject>

#include "qvector.h"

#include "oxygine-framework.h"

#include "ingamescriptsupport/events/scripteventdialog.h"

#include "objects/panel.h"

#include "objects/dropdownmenu.h"
#include "objects/dropdownmenucolor.h"
#include "objects/textbox.h"

class ScriptDialogDialog;
typedef oxygine::intrusive_ptr<ScriptDialogDialog> spScriptDialogDialog;

class ScriptDialogDialog : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit ScriptDialogDialog(spScriptEventDialog scriptEventDialog);
    virtual ~ScriptDialogDialog() = default;
signals:
    /**
     * @brief sigFinished
     */
    void sigFinished();
    /**
     * @brief sigRemoveLast
     */
    void sigRemoveLast();
    /**
     * @brief sigAddItem
     */
    void sigAddItem();
    /**
     * @brief sigShowChangeBackground
     */
    void sigShowChangeBackground();
public slots:
    /**
     * @brief addItem
     */
    void addItem();
    /**
     * @brief removeLast
     */
    void removeLast();
    /**
     * @brief updateDialog
     */
    void updateDialog();
    /**
     * @brief showChangeBackground
     */
    void showChangeBackground();
    /**
     * @brief setCurrentDialogBackground
     * @param file
     */
    void setCurrentDialogBackground(QString file);
private:
    oxygine::spBox9Sprite m_pSpriteBox;
    spScriptEventDialog m_Event;
    qint32 dialogIndex{-1};
    spPanel m_Panel;
};

#endif // SCRIPTDIALOGDIALOG_H
