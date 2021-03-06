#ifndef AI_DECISIONNODE
#define AI_DECISIONNODE

#include "QObject"

#include "oxygine-framework.h"

#include "decisionquestion.h"

#include "coreengine/fileserializable.h"

class DecisionNode;
typedef oxygine::intrusive_ptr<DecisionNode> spDecisionNode;

class DecisionNode : public QObject, public FileSerializable, public oxygine::ref_counter
{
    Q_OBJECT
public:
        DecisionNode() = default;
        DecisionNode(spDecisionQuestion pQuestion, QVector<spDecisionNode> pNodes);
        virtual ~DecisionNode();

        virtual void serializeObject(QDataStream& pStream)  override;
        virtual void deserializeObject(QDataStream& pStream)  override;
        virtual qint32 getVersion() override
        {
            return 1;
        }

        inline qint32 getNodeSize()
        {
            return m_pNodes.size();
        }
        inline DecisionNode* getNode(qint32 index)
        {
            return m_pNodes[index].get();
        }
        inline DecisionQuestion* getQuestion()
        {
            return m_pQuestion.get();
        }
public slots:
        virtual float getDecision(QVector<float>& input);
private:
        spDecisionQuestion m_pQuestion;
        QVector<spDecisionNode> m_pNodes;
};

#endif
