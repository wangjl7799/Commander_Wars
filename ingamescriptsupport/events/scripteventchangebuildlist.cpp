#include "scripteventchangebuildlist.h"

#include "ingamescriptsupport/scripteditor.h"
#include "ingamescriptsupport/genericbox.h"

#include "resource_management/fontmanager.h"

#include "coreengine/mainapp.h"

#include "objects/spinbox.h"

#include "resource_management/unitspritemanager.h"

#include "objects/dropdownmenu.h"

#include "objects/checkbox.h"

ScriptEventChangeBuildlist::ScriptEventChangeBuildlist()
    : ScriptEvent (EventType::changeBuildlist)
{

}

QString ScriptEventChangeBuildlist::getUnitID() const
{
    return unitID;
}

void ScriptEventChangeBuildlist::setUnitID(const QString &value)
{
    unitID = value;
}

bool ScriptEventChangeBuildlist::getRemove() const
{
    return remove;
}

void ScriptEventChangeBuildlist::setRemove(bool value)
{
    remove = value;
}


void ScriptEventChangeBuildlist::readEvent(QTextStream& rStream)
{
    QString line = rStream.readLine().simplified();
    QStringList items = line.replace("map.getPlayer(", "")
                            .replace(").changeBuildlist(\"", ",")
                        .replace("\", ", ",")
                            .replace("); // ", ",").split(",");
    if (items.size() >= 3)
    {
        player = items[0].toInt();
        unitID = items[1];
        remove = QVariant(items[2]).toBool();
    }
}

void ScriptEventChangeBuildlist::writeEvent(QTextStream& rStream)
{
    rStream <<  "            map.getPlayer(" << QString::number(player) << ").changeBuildlist(\"" + unitID + "\", " + QVariant(remove).toString() + "); // "
            << QString::number(getVersion()) << " " << EventChangeBuildlist << "\n";
}

qint32 ScriptEventChangeBuildlist::getPlayer() const
{
    return player;
}

void ScriptEventChangeBuildlist::setPlayer(const qint32 &value)
{
    player = value;
}

void ScriptEventChangeBuildlist::showEditEvent(spScriptEditor pScriptEditor)
{
    spGenericBox pBox = new GenericBox();

    oxygine::TextStyle style = FontManager::getMainFont();
    style.color = QColor(255, 255, 255, 255);
    style.vAlign = oxygine::TextStyle::VALIGN_TOP;
    style.hAlign = oxygine::TextStyle::HALIGN_LEFT;
    style.multiline = false;

    qint32 width = 300;

    oxygine::spTextField pText = new oxygine::TextField();
    pText->setStyle(style);
    pText->setHtmlText(tr("Player: "));
    pText->setPosition(30, 30);
    pBox->addItem(pText);
    spSpinBox spinBox = new SpinBox(150, 1, 9999);
    spinBox->setPosition(width, 30);
    spinBox->setCurrentValue(player + 1);
    connect(spinBox.get(), &SpinBox::sigValueChanged,
            [=](qreal value)
    {
        setPlayer(static_cast<qint32>(value) - 1);
    });
    pBox->addItem(spinBox);

    pText = new oxygine::TextField();
    pText->setStyle(style);
    pText->setHtmlText(tr("Unit ID: "));
    pText->setPosition(30, 70);
    pBox->addItem(pText);
    QVector<QString> items;
    UnitSpriteManager* pUnitSpriteManager = UnitSpriteManager::getInstance();
    qint32 currentItem = 0;
    for (qint32 i = 0; i < pUnitSpriteManager->getUnitCount(); i++)
    {
        QString id = pUnitSpriteManager->getUnitID(i);
        items.append(id);
        if (unitID == id)
        {
            currentItem = i;
        }
    }
    spDropDownmenu pMenu = new DropDownmenu(300, items);
    pMenu->setPosition(width, 70);
    pMenu->setCurrentItem(currentItem);
    pBox->addItem(pMenu);
    connect(pMenu.get(), &DropDownmenu::sigItemChanged, [=](qint32)
    {
        unitID = pMenu->getCurrentItemText();
    });

    pText = new oxygine::TextField();
    pText->setStyle(style);
    pText->setHtmlText(tr("Remove: "));
    pText->setPosition(30, 110);
    pBox->addItem(pText);

    spCheckbox checkBox = new Checkbox();
    checkBox->setPosition(width, 110);
    checkBox->setChecked(remove);
    connect(checkBox.get(), &Checkbox::checkChanged,
            [=](bool value)
    {
        setRemove(value);
    });
    pBox->addItem(checkBox);

    pScriptEditor->addChild(pBox);
    connect(pBox.get(), &GenericBox::sigFinished, pScriptEditor.get(), &ScriptEditor::updateEvents, Qt::QueuedConnection);
}
