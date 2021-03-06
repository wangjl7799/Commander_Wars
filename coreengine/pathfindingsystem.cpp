#include "pathfindingsystem.h"

#include "QTime"

#include "coreengine/interpreter.h"

#include "coreengine/mainapp.h"

const qint32 PathFindingSystem::infinite = std::numeric_limits<qint32>::max();

PathFindingSystem::PathFindingSystem(qint32 startX, qint32 startY,
                                     qint32 width, qint32 heigth)
    : m_StartPoint(startX, startY),
      m_width(width),
      m_heigth(heigth),
      costs(new qint32[static_cast<quint32>(width * heigth)]),
      movecosts(new qint32[static_cast<quint32>(width * heigth)])
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    Interpreter::setCppOwnerShip(this);
    qint32 count = m_width * m_heigth;
    for (int i = 0; i < count; ++i)
    {
        costs[i] = infinite;
        movecosts[i] = infinite;
    }
}

PathFindingSystem::~PathFindingSystem()
{
    delete[] costs;
    delete[] movecosts;
}

void PathFindingSystem::setStartPoint(qint32 startX, qint32 startY)
{
    m_StartPoint = QPoint(startX, startY);
}

void PathFindingSystem::setFinishNode(qint32 x, qint32 y)
{
    m_FinishNode = x + y  * m_width;
    m_FinishNodeX = x;
    m_FinishNodeY = y;
}

void PathFindingSystem::explore()
{
    qint32 neighboursIndex = getIndex(m_StartPoint.x(), m_StartPoint.y());
    Node* pCurrent = new Node(m_StartPoint.x(), m_StartPoint.y(), neighboursIndex, 0, 0);
    m_OpenList.append(pCurrent);
    qint32 remainingCosts;
    qint32 neighboursX = -1;
    qint32 neighboursY = -1;
    qint32 fieldCost = -1;
    qint32 neighboursCosts = -1;
    qint32 mid = -1;
    qint32 low = -1;
    qint32 high = -1;
    // explore till we reached the end
    while (!m_OpenList.empty())
    {
        // get current node and pop it
        pCurrent = m_OpenList.last();
        m_OpenList.removeLast();
        if (costs[pCurrent->index] != infinite)
        {
            // already searched item
            delete pCurrent;
            continue;
        }
        // still the best node?
        qint32 currentCost = pCurrent->currentCosts;
        costs[pCurrent->index] = currentCost;
        if (finished(pCurrent->x, pCurrent->y, pCurrent->totalCost))
        {
            setFinishNode(pCurrent->x, pCurrent->y);
            break;
        }
        // right

        for (qint32 i = 0; i < 4; i++)
        {
            // calculate neighbour node data
            if (i == 0)
            {
                if (pCurrent->x + 1 < m_width)
                {
                    neighboursIndex = pCurrent->index + 1;
                    fieldCost = costs[neighboursIndex];
                    if (fieldCost != infinite)
                    {
                        // skip searched fields
                        continue;
                    }
                    neighboursX = pCurrent->x + 1;
                    neighboursY = pCurrent->y;
                }
                else
                {
                    continue;
                }
            }
            else if (i == 1)
            {
                // left
                if (pCurrent->x > 0)
                {
                    neighboursIndex = pCurrent->index - 1;
                    fieldCost = costs[neighboursIndex];
                    if (fieldCost != infinite)
                    {
                        // skip searched fields
                        continue;
                    }
                    neighboursX = pCurrent->x - 1;
                    neighboursY = pCurrent->y;
                }
                else
                {
                    continue;
                }
            }
            else if (i == 2)
            {
                // bottom
                if (pCurrent->y + 1 < m_heigth)
                {
                    neighboursIndex = pCurrent->index + m_width;
                    fieldCost = costs[neighboursIndex];
                    if (fieldCost != infinite)
                    {
                        // skip searched fields
                        continue;
                    }
                    neighboursX = pCurrent->x;
                    neighboursY = pCurrent->y + 1;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                // top
                if (pCurrent->y > 0)
                {
                    neighboursIndex = pCurrent->index - m_width;
                    fieldCost = costs[neighboursIndex];
                    if (fieldCost != infinite)
                    {
                        // skip searched fields
                        continue;
                    }
                    neighboursX = pCurrent->x;
                    neighboursY = pCurrent->y - 1;
                }
                else
                {
                    continue;
                }
            }
            // get field costs from index
            neighboursCosts = getCosts(neighboursIndex, neighboursX, neighboursY);
            if (neighboursCosts >= 0) // passable?
            {
                // costs to reach this field
                qint32 newCosts = neighboursCosts + currentCost;
                remainingCosts = getRemainingCost(neighboursX, neighboursY, newCosts);
                // usable path to target?
                if (remainingCosts >= 0)
                {
                    qint32 totalCost = newCosts + remainingCosts;
                    // node we want to insert
                    Node* workNode = new Node(neighboursX, neighboursY, neighboursIndex, totalCost, newCosts);
                    // iterate over the list and find the best position to insert the item
                    // also check if an open node with the same field is in the open list
                    if (m_OpenList.empty())
                    {
                        m_OpenList.append(workNode);
                    }
                    // best node?
                    else if (workNode->compare(m_OpenList.last()))
                    {
                        m_OpenList.append(workNode);
                    }
                    else
                    {
                        // binary tree search insertion
                        high =  m_OpenList.size() - 1;
                        while (high > 0)
                        {
                            // divide by two by shifting
                            mid = high >> 1;
                            if (workNode->compare(m_OpenList[mid]))
                            {
                                low = mid + 1;
                                high = high - mid - 1;
                            }
                            else
                            {
                                high = mid;

                            }
                        }
                        m_OpenList.insert(mid, workNode);
                    }
                }
            }
        }
        delete pCurrent;
    }
}

QVector<QPoint> PathFindingSystem::getFields(qint32 startX, qint32 startY, qint32 min, qint32 max)
{
    QVector<QPoint> points;
    for (qint32 x = -max; x <= max; x++)
    {
        for (qint32 y = -max; y <= max; y++)
        {
            if ((qAbs(x) + qAbs(y) >= min) && (qAbs(x) + qAbs(y) <= max))
            {
                points.append(QPoint(startX + x, startY + y));
            }
        }
    }
    return points;
}

QVector<QPoint> PathFindingSystem::getAllNodePoints()
{
    QVector<QPoint> points;
    for (qint32 x = 0; x < m_width; x++)
    {
        for (qint32 y = 0; y < m_heigth; y++)
        {
            if (costs[getIndex(x, y)] >= 0 && costs[getIndex(x, y)] < infinite)
            {
                points.append(QPoint(x, y));
            }
        }
    }
    return points;
}

QmlVectorPoint* PathFindingSystem::getAllQmlVectorPoints()
{
    QmlVectorPoint* ret = new QmlVectorPoint();
    for (qint32 x = 0; x < m_width; x++)
    {
        for (qint32 y = 0; y < m_heigth; y++)
        {
            if (costs[getIndex(x, y)] >= 0 && costs[getIndex(x, y)] < infinite)
            {
                ret->append(QPoint(x, y));
            }
        }
    }
    return ret;
}

QVector<QPoint> PathFindingSystem::getTargetPath()
{
    if (m_FinishNode >= 0)
    {
        return getPath(m_FinishNodeX, m_FinishNodeY);
    }
    return QVector<QPoint>();
}

QVector<QPoint> PathFindingSystem::getPath(qint32 x, qint32 y)
{
    QVector<QPoint> points;
    qint32 startCost = getTargetCosts(x, y);
    if (startCost >= 0)
    {

        qint32 nextCosts = startCost;
        qint32 curX = x;
        qint32 curY = y;
        points.append(QPoint(curX, curY));
        while (curX != m_StartPoint.x() ||
               curY != m_StartPoint.y())
        {
            qint32 fieldX = curX;
            qint32 fieldY = curY;
            for (qint32 i = 0; i < 4; i++)
            {
                qint32 testX, testY;
                switch (i)
                {
                    case 0:
                    {
                        testX = fieldX + 1;
                        testY = fieldY;
                        break;
                    }
                    case 1:
                    {
                        testX = fieldX - 1;
                        testY = fieldY;
                        break;
                    }
                    case 2:
                    {
                        testX = fieldX;
                        testY = fieldY + 1;
                        break;
                    }
                    default:
                    {
                        testX = fieldX;
                        testY = fieldY - 1;
                        break;
                    }
                }
                qint32 newCosts = getTargetCosts(testX, testY);
                if (newCosts >= 0 && newCosts <= nextCosts)
                {
                    curX = testX;
                    curY = testY;
                    nextCosts = newCosts;
                }
            }
            points.append(QPoint(curX, curY));
        }
    }
    return points;
}

qint32 PathFindingSystem::getTargetCosts(qint32 x, qint32 y)
{
    if (x >= 0 && x < m_width &&
        y >= 0 && y < m_heigth)
    {
        qint32 cost = costs[getIndex(x, y)];
        if (cost < infinite)
        {
            return cost;
        }
    }
    return -1;
}

bool PathFindingSystem::isReachable(qint32 x, qint32 y)
{
    return getTargetCosts(x, y) >= 0;
}
