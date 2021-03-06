#ifndef TOPBAR_H
#define TOPBAR_H

#include <QObject>
#include <QVector>
#include "oxygine-framework.h"

class Topbar;
typedef oxygine::intrusive_ptr<Topbar> spTopbar;

class Topbar : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    explicit Topbar(qint32 x, qint32 width);
    ~Topbar() = default;
    /**
     * @brief addItem adds an item to the bar
     * @param text the text shown for this item
     * @param itemID the depending id used for event handling
     * @param group the used group item number
     */
    void addItem(QString text, QString itemID, qint32 group);
    /**
     * @brief addGroup adds a group to the topbar
     * @param text
     */
    void addGroup(QString text);
    /**
     * @brief hide
     */
    void hide();
signals:
    /**
     * @brief sigItemClicked connect to this signal in order to recieve when an item was clicked so you can handle it
     * @param itemID
     */
    void sigItemClicked(QString itemID);
public slots:
private:
    QVector<QVector<oxygine::spBox9Sprite>*> m_Items;
    QVector<oxygine::spButton> m_Buttons;    
    oxygine::spBox9Sprite m_pSpriteBox;
};

#endif // TOPBAR_H
