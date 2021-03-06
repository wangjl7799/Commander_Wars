#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QObject>
#include <QTime>
#include "oxygine-framework.h"

#include "oxygine/KeyEvent.h"

class Textbox;
typedef oxygine::intrusive_ptr<Textbox> spTextbox;

class Textbox : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    enum
    {
        BLINKFREQG = 250
    };
    explicit Textbox(qint32 width);
    /**
     * @brief getCurrentText
     * @return the current text of the textbox
     */
    inline QString getCurrentText()
    {
        return m_Text;
    }
    virtual void update(const oxygine::UpdateState& us) override;
    /**
     * @brief setCurrentText changes the text of this textbox
     * @param text
     */
    void setCurrentText(QString text);
signals:
    void sigTextChanged(QString text);
    void sigEnterPressed(QString text);
public slots:
    void KeyInput(oxygine::KeyEvent event);
private:
    bool m_focused{false};
    oxygine::spBox9Sprite m_Textbox;
    oxygine::spTextField m_Textfield;
    QString m_Text;
    QTime toggle;
    qint32 curmsgpos{0};
};

#endif // TEXTBOX_H
