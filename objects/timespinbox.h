#ifndef TIMESPINBOX_H
#define TIMESPINBOX_H

#include <QObject>
#include <QTime>
#include "oxygine-framework.h"

#include "oxygine/KeyEvent.h"

class TimeSpinBox;
typedef oxygine::intrusive_ptr<TimeSpinBox> spTimeSpinBox;

class TimeSpinBox : public QObject, public oxygine::Actor
{
    Q_OBJECT
public:
    enum
    {
        BLINKFREQG = 250
    };

    explicit TimeSpinBox(qint32 width);
    /**
     * @brief getCurrentValue
     * @return the current value of the spin box
     */
    qint32 getCurrentValue();
    virtual void update(const oxygine::UpdateState& us) override;
    /**
     * @brief setCurrentValue changes the value of this spin box
     * @param text
     */
    void setCurrentValue(qint32 value);
    qint32 getSpinSpeed() const;
    void setSpinSpeed(qint32 SpinSpeed);

    virtual void setEnabled(bool value) override;
signals:
    void sigValueChanged(qint32 value);
public slots:
    void KeyInput(oxygine::KeyEvent event);
protected:
    /**
     * @brief checkInput checks if the input is correct and updates it if needed and returns the new value
     * @return current value
     */
    qint32 checkInput();
    /**
     * @brief setValue
     * @param value
     */
    void setValue(qint32 value);
private:
    bool m_focused{false};
    oxygine::spBox9Sprite m_pSpinBox;
    oxygine::spBox9Sprite m_Textbox;
    oxygine::spTextField m_Textfield;
    oxygine::spButton m_pArrowDown;
    oxygine::spButton m_pArrowUp;
    QString m_Text;
    QTime toggle;
    qint32 curmsgpos{0};
    qint32 m_spinDirection{0};
    qint32 m_SpinSpeed{1000 * 60};
};

#endif // SPINBOX_H
