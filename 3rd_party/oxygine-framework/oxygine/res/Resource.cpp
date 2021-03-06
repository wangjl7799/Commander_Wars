#include "Resource.h"
#include "CreateResourceContext.h"
#include <stdio.h>

#include "qfileinfo.h"

namespace oxygine
{
    Resource::Resource(): _loadCounter(0), _useLoadCounter(false), _parent(0)
    {

    }

    Resource::~Resource()
    {

    }

    void Resource::load(LoadResourcesContext* context /* = 0 */)
    {
        if (!context)
            context = LoadResourcesContext::get();

        if (_loadCounter == 0)
            _load(context);

        _loadCounter = _useLoadCounter ? _loadCounter + 1 : 1;
    }

    void Resource::unload()
    {
        if (_loadCounter == 1)
            _unload();

        _loadCounter = _useLoadCounter ? _loadCounter - 1 : 0;
    }

    QString Resource::extractID(const QDomElement& node, QString file, QString def)
    {
        QString id = node.attribute("id");
        if (id.isEmpty())
        {
            if (file.isEmpty())
            {
                return def.toLower();
            }
            return extractID(file);
        }

        return id.toLower();
    }

    QString Resource::extractID(QString file)
    {
        QFileInfo info(file);
        return info.baseName().toLower();
    }


    QString Resource::getAttribute(QString attr) const
    {
        return _node.attribute(attr);
    }
}
