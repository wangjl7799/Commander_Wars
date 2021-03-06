#ifndef VICTORYMENUE_H
#define VICTORYMENUE_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QColor>

#include "oxygine-framework.h"

#include "objects/panel.h"
#include "objects/checkbox.h"

class VictoryMenue : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    enum class GraphModes
    {
        Funds,
        Income,
        Buildings,
        Units,
        PlayerStrength,
        Max,
        VictoryRanking
    };

    explicit VictoryMenue(bool multiplayer);
    virtual ~VictoryMenue() = default;

    /**
     * @brief createLine creates a nice sweet polygon line for drawing our graphs
     * @param end
     * @param width
     * @param color
     * @return
     */
    oxygine::spActor createLine(QPointF end, qint32 width, QColor color);
signals:
    void sigExitMenue();
    void sigShowGraph(VictoryMenue::GraphModes mode);
    void sigFinishCurrentGraph();
public slots:
    void exitMenue();
    /**
     * @brief showGraph
     * @param mode
     */
    void showGraph(VictoryMenue::GraphModes mode);
    /**
     * @brief updateGraph
     */
    void updateGraph();
    /**
     * @brief finishGraph
     */
    void finishGraph();
protected:
    /**
     * @brief drawGraphStep
     */
    void drawGraphStep(qint32 progress);
private:
    GraphModes m_CurrentGraphMode{GraphModes::Funds};
    /**
     * @brief m_PlayerGraphs first dimensions holds the graph modes, second dimension the graphs for each player
     */
    QVector<QVector<oxygine::spActor>> m_PlayerGraphs{static_cast<qint32>(GraphModes::Max)};
    /**
     * @brief m_GraphProgress how far we got with drawing each graph
     */
    QVector<qint32> m_GraphProgress = QVector<qint32>(static_cast<qint32>(GraphModes::Max), 0);
    /**
     * @brief m_GraphMaxValues maximum values for each graph :)
     */
    QVector<qint32> m_GraphMaxValues = QVector<qint32>(static_cast<qint32>(GraphModes::Max), 0);

    QVector<oxygine::spColorRectSprite> m_GraphsProgessLine = QVector<oxygine::spColorRectSprite>(static_cast<qint32>(GraphModes::Max), nullptr);
    /**
     * @brief m_VisiblePlayers holds the graphs of which players are drawn (by default all)
     */
    QVector<bool> m_VisiblePlayers;
    /**
     * @brief m_ProgressTimer tick timer for updating the graph
     */
    QTimer m_ProgressTimer;

    float lineLength{0};

    oxygine::spBox9Sprite m_pGraphBackground;

    oxygine::spTextField m_Textfield;

    spPanel m_PlayerSelectPanel;

    QVector<oxygine::spTextField> m_YGraphItems;

    QVector<QVector3D> m_VictoryScores;
    QVector<QVector<oxygine::spTextField>> m_VictoryTexts;
    spPanel m_VictoryPanel;
    qint32 progress = 0;

    bool m_Multiplayer{false};

};

#endif // VICTORYMENUE_H

