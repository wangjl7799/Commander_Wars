#ifndef CAMPAIGNEDITOR_H
#define CAMPAIGNEDITOR_H

#include <QObject>

#include <QVector>

#include "oxygine-framework.h"

#include "objects/panel.h"

#include "objects/textbox.h"

#include "qtextstream.h"

class CampaignEditor;
typedef oxygine::intrusive_ptr<CampaignEditor> spCampaignEditor;

class CampaignEditor : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    static const QString campaign;
    static const QString campaignName;
    static const QString campaignDescription;
    static const QString campaignAuthor;
    static const QString campaignMaps;
    static const QString campaignMapsFolder;
    static const QString campaignMapNames;
    static const QString campaignMapEnabled;
    static const QString campaignMapDisabled;
    static const QString campaignMapAdd;
    static const QString campaignMapFinished;
    static const QString campaignFinished;

    struct MapData
    {
        QString map;
        QString mapName;
        QStringList previousMaps;
        qint32 previousCount{0};
        QStringList disableMaps;
        qint32 disableCount{1};
        bool lastMap{false};
    };
    explicit CampaignEditor();
    virtual ~CampaignEditor() = default;
signals:
    /**
     * @brief sigFinished
     */
    void sigFinished();
    /**
     * @brief sigShowAddCampaign
     */
    void sigShowAddCampaign();
    /**
     * @brief sigShowSelectFolder
     */
    void sigShowSelectFolder();
    /**
     * @brief sigupdateCampaignData
     */
    void sigUpdateCampaignData();
    /**
     * @brief sigShowLoadCampaign
     */
    void sigShowLoadCampaign();
    /**
     * @brief sigShowSaveCampaign
     */
    void sigShowSaveCampaign();
public slots:
    /**
     * @brief showSaveCampaign
     */
    void showSaveCampaign();
    /**
     * @brief saveCampaign
     */
    void saveCampaign(QString filename);
    /**
     * @brief showLoadCampaign
     */
    void showLoadCampaign();
    /**
     * @brief loadCampaignMaps
     * @param stream
     */
    void loadCampaignMaps(QTextStream& stream);
    /**
     * @brief updateMapNames
     */
    void updateMapNames();
    /**
     * @brief loadCampaign
     * @param filename
     */
    void loadCampaign(QString filename);
    /**
     * @brief showAddCampaign
     */
    void showAddCampaign();
    /**
     * @brief addCampaign
     */
    void addCampaign(QString filename);
    /**
     * @brief getMapName
     * @param filename
     * @return
     */
    QString getMapName(QString filename);
    /**
     * @brief showSelectFolder
     */
    void showSelectFolder();
    /**
     * @brief selectFolder
     * @param folder
     */
    void selectFolder(QString folder);
    /**
     * @brief clearCampaignData
     */
    void clearCampaignData();
    /**
     * @brief updateCampaignData
     */
    void updateCampaignData();
    /**
     * @brief showEditEnableMaps
     * @param index
     */
    void showEditEnableMaps(qint32 index);
    /**
     * @brief showEditDisableMaps
     * @param index
     */
    void showEditDisableMaps(qint32 index);
private:
    spPanel m_Panel;
    /**
     * @brief m_CampaignFolder
     */
    spTextbox m_CampaignFolder;
    /**
     * @brief mapData
     */
    QVector<MapData> mapDatas;

    spTextbox m_Description;
    spTextbox m_Author;
    spTextbox m_Name;
};

#endif // CAMPAIGNEDITOR_H
