#ifndef AI_DECISIONTREE
#define AI_DECISIONTREE

#include <QObject>
#include <QVector>
#include <QString>

#include "decisionnode.h"
#include "decisionquestion.h"

#include "coreengine/fileserializable.h"

class DecisionTree : public QObject, public FileSerializable
{
	Q_OBJECT
public:
    DecisionTree(spDecisionNode pRootNode);
    DecisionTree(QVector<QVector<float>>& trainingData, QVector<QVector<spDecisionQuestion>>& questions);
    DecisionTree(QString treeFile, QString trainingDataFile);

    virtual ~DecisionTree();

    spDecisionNode train(QVector<QVector<float>>& trainingData, QVector<QVector<spDecisionQuestion>>& questions);

    static QVector<qint32> countClassItems(QVector<QVector<float>>& trainingData);

    virtual void serializeObject(QDataStream& pStream)  override;
    virtual void deserializeObject(QDataStream& pStream)  override;
    virtual qint32 getVersion() override
    {
        return 1;
    }
public slots:
    float getDecision(QVector<float>& input);
    void printTree(DecisionNode* pNode = nullptr, QString spacing = "");
protected:
    void seperateData(QVector<QVector<float>>& trainingData, spDecisionQuestion question, QVector<QVector<QVector<float>>>& splitData);
    float giniImpurity(QVector<QVector<float>>& trainingData);
    float infoGain(QVector<QVector<QVector<float>>>& splitTrainingData, float currentUncertainty);
    spDecisionQuestion findBestSplit(QVector<QVector<float>>& trainingData, float& bestGain, QVector<QVector<spDecisionQuestion>>& questions);
private:
        spDecisionNode m_pRootNode;
};

#endif
