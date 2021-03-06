#include "dialogmessagebox.h"

#include "coreengine/mainapp.h"

#include "resource_management/objectmanager.h"

#include "resource_management/fontmanager.h"

DialogMessageBox::DialogMessageBox(QString text, bool withCancel)
    : QObject(),
      m_Message(text)
{
    Mainapp* pApp = Mainapp::getInstance();
    this->moveToThread(pApp->getWorkerthread());
    ObjectManager* pObjectManager = ObjectManager::getInstance();
    oxygine::spBox9Sprite pSpriteBox = new oxygine::Box9Sprite();
    oxygine::ResAnim* pAnim = pObjectManager->getResAnim("codialog");
    pSpriteBox->setResAnim(pAnim);
    pSpriteBox->setSize(pApp->getSettings()->getWidth(), pApp->getSettings()->getHeight());
    pSpriteBox->setVerticalMode(oxygine::Box9Sprite::TILING_FULL);
    pSpriteBox->setHorizontalMode(oxygine::Box9Sprite::TILING_FULL);
    this->addChild(pSpriteBox);
    pSpriteBox->setPosition(0, 0);
    pSpriteBox->setPriority(static_cast<short>(Mainapp::ZOrder::Objects));
    this->setPriority(static_cast<short>(Mainapp::ZOrder::Dialogs));

    oxygine::TextStyle style = FontManager::getMainFont();
    style.color = QColor(255, 255, 255, 255);
    style.vAlign = oxygine::TextStyle::VALIGN_DEFAULT;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = true;

    m_Text = new oxygine::TextField();
    m_Text->setSize(pApp->getSettings()->getWidth() / 3, pApp->getSettings()->getHeight());
    m_Text->setHtmlText(text);
    m_Text->setStyle(style);
    m_Text->setPosition(pApp->getSettings()->getWidth() / 2 - m_Text->getTextRect().getWidth() / 2, pApp->getSettings()->getHeight() / 2 - m_Text->getTextRect().getHeight());
    pSpriteBox->addChild(m_Text);

    m_OkButton = pObjectManager->createButton(tr("Ok"), 150);
    m_OkButton->setPosition(pApp->getSettings()->getWidth() / 2 - m_OkButton->getWidth() / 2,
                            m_Text->getY() + m_Text->getTextRect().getHeight() + 20);
    pSpriteBox->addChild(m_OkButton);
    m_OkButton->addEventListener(oxygine::TouchEvent::CLICK, [ = ](oxygine::Event*)
    {
        emit sigOk();
    });

    if (withCancel)
    {
        m_CancelButton = pObjectManager->createButton(tr("Cancel"), 150);
        m_CancelButton->setPosition(pApp->getSettings()->getWidth() / 2 + 10,
                                m_Text->getY() + m_Text->getTextRect().getHeight() + 20);
        pSpriteBox->addChild(m_CancelButton);
        m_CancelButton->addEventListener(oxygine::TouchEvent::CLICK, [ = ](oxygine::Event*)
        {
            emit sigCancel();
        });
        m_OkButton->setPosition(pApp->getSettings()->getWidth() / 2 - m_OkButton->getWidth() - 10,
                                m_Text->getY() + m_Text->getTextRect().getHeight() + 20);
    }

    connect(this, &DialogMessageBox::sigOk, this, &DialogMessageBox::remove, Qt::QueuedConnection);
    connect(this, &DialogMessageBox::sigCancel, this, &DialogMessageBox::remove, Qt::QueuedConnection);
}

void DialogMessageBox::remove()
{
    detach();
}

