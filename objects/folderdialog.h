#ifndef FOLDERDIALOG_H
#define FOLDERDIALOG_H

#include <QObject>
#include "oxygine-framework.h"
#include "objects/textbox.h"
#include "objects/panel.h"
#include "objects/dropdownmenu.h"


class FolderDialog;
typedef oxygine::intrusive_ptr<FolderDialog> spFolderDialog;

/**
 * @brief The FolderDialog class folder dialog for accessing folders.
 * Upon success or cancel the dialog will delete itself from the scene.
 * You have to hold a smart pointer to this object if you need further info from it.
 */
class FolderDialog : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    /**
     * @brief FolderDialog
     * @param startFolder initial folder of the file dialog
     */
    explicit FolderDialog(QString startFolder);
    virtual ~FolderDialog();

signals:
    void sigFolderSelected(QString file);
    void sigCancel();
    void sigShowFolder(QString folder);
public slots:
    void showFolder(QString folder);
private:
    spTextbox m_CurrentFolder;
    spPanel m_MainPanel;
    oxygine::spButton m_OkButton;
    oxygine::spButton m_CancelButton;
    /**
     * @brief m_Items items directories or folders
     */
    QVector<oxygine::spBox9Sprite> m_Items;
};

#endif // FOLDERDIALOG_H
