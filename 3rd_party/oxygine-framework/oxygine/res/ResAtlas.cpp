#include "ResAtlas.h"
#include "ResAtlasGeneric.h"
#include "Resources.h"
#include "../Image.h"
#include "../core/VideoDriver.h"

#include "qvariant.h"

namespace oxygine
{
    static load_texture_hook _hook = nullptr;
    void set_load_texture_hook(load_texture_hook hook)
    {
        _hook = hook;
    }

    void load_texture_internal(QString file, spNativeTexture nt, bool linearFilter, bool clamp2edge, LoadResourcesContext* load_context)
    {
        ImageData im;
        spImage mt = new Image;

        qDebug("loading atlas: %s", file.toStdString().c_str());
        QImage img (file);
        qDebug("atlas file loaded: %s", file.toStdString().c_str());
        mt->init(img, true);
        im = mt->lock();
        qDebug("atlas size: %d %d", im.w, im.h);

        CreateTextureTask opt;
        opt.src = mt;
        opt.dest = nt;
        opt.linearFilter = linearFilter;
        opt.clamp2edge = clamp2edge;
        load_context->createTexture(opt);
    }

    void load_texture(QString file, spNativeTexture nt, bool linearFilter, bool clamp2edge, LoadResourcesContext* load_context)
    {
        if (_hook)
        {
            _hook(file, nt, linearFilter, clamp2edge, load_context);
            return;
        }

        load_texture_internal(file, nt, linearFilter, clamp2edge, load_context);
    }


    void ResAtlas::init_resAnim(ResAnim* rs, QString file, QDomElement node)
    {
        rs->setName(Resource::extractID(node, file, ""));
        setNode(rs, node);
    }

    void ResAtlas::addAtlas(ImageData::TextureFormat tf, QString base, QString alpha, int w, int h)
    {
        atlas atl;
        atl.base = IVideoDriver::instance->createTexture();
        atl.base_path = base;
        atl.base->setName(base);
        atl.base->init(nullptr, w, h, tf);

        if (!alpha.isEmpty())
        {
            atl.alpha = IVideoDriver::instance->createTexture();
            atl.alpha_path = alpha;
            atl.alpha->setName(alpha);
            atl.alpha->init(nullptr, w, h, tf);
        }

        _atlasses.push_back(atl);
    }

    Resource* ResAtlas::create(CreateResourceContext& context)
    {
        context.walker.checkSetAttributes();
        ResAtlas* ra = nullptr;
        ResAtlasGeneric* rs = new ResAtlasGeneric();
        rs->loadAtlas(context);
        ra = rs;

        ra->setName(Resource::extractID(context.walker.getNode(), "", QString("!atlas:") + context.xml_name));
        context.resources->add(ra);
        setNode(ra, context.walker.getNode());

        return ra;
    }

    ResAtlas::ResAtlas(): _linearFilter(true), _clamp2edge(true)
    {

    }

    ResAtlas::~ResAtlas()
    {
        for (atlasses::iterator i = _atlasses.begin(); i != _atlasses.end(); ++i)
        {
            atlas& atl = *i;
            if (atl.base)
                atl.base->release();
            if (atl.alpha)
                atl.alpha->release();
        }
    }


    void ResAtlas::loadBase(QDomElement node)
    {
        QVariant value = QVariant(node.attribute("linearFilter"));
        if (value.type() == QVariant::Type::Bool)
        {
            _linearFilter = value.toBool();
        }
        else
        {
            _linearFilter = true;
        }
        value = QVariant(node.attribute("clamp2edge"));
        if (value.type() == QVariant::Type::Bool)
        {
            _clamp2edge = value.toBool();
        }
        else
        {
            _clamp2edge = true;
        }
    }

    void ResAtlas::_restore(Restorable* r, void*)
    {
        NativeTexture* texture = (NativeTexture*)r->_getRestorableObject();

        for (atlasses::iterator i = _atlasses.begin(); i != _atlasses.end(); ++i)
        {
            atlas& atl = *i;
            if (atl.base.get() == texture)
            {
                load_texture(atl.base_path, atl.base, _linearFilter, _clamp2edge, &RestoreResourcesContext::instance);
                atl.base->reg(CLOSURE(this, &ResAtlas::_restore), nullptr);
                break;
            }

            if (atl.alpha.get() == texture)
            {
                load_texture(atl.alpha_path, atl.alpha, _linearFilter, _clamp2edge, &RestoreResourcesContext::instance);
                atl.alpha->reg(CLOSURE(this, &ResAtlas::_restore), nullptr);
                break;
            }
        }
    }

    void ResAtlas::_load(LoadResourcesContext* load_context)
    {
        for (atlasses::iterator i = _atlasses.begin(); i != _atlasses.end(); ++i)
        {
            atlas& atl = *i;
            if (!load_context->isNeedProceed(atl.base))
                continue;

            load_texture(atl.base_path, atl.base, _linearFilter, _clamp2edge, load_context);
            atl.base->reg(CLOSURE(this, &ResAtlas::_restore), nullptr);

            if (atl.alpha)
            {
                load_texture(atl.alpha_path, atl.alpha, _linearFilter, _clamp2edge, load_context);
                atl.alpha->reg(CLOSURE(this, &ResAtlas::_restore), nullptr);
            }
        }
    }

    void ResAtlas::_unload()
    {
        for (atlasses::iterator i = _atlasses.begin(); i != _atlasses.end(); ++i)
        {
            atlas& atl = *i;
            if (atl.base)
                atl.base->release();

            if (atl.alpha)
                atl.alpha->release();
        }
    }

    ResAnim* ResAtlas::createEmpty(const XmlWalker& walker, CreateResourceContext& context)
    {
        ResAnim* ra = new ResAnim(this);
        ra->init(nullptr, 0, 0, walker.getScaleFactor());
        init_resAnim(ra, "", walker.getNode());
        ra->setParent(this);
        context.resources->add(ra);

        return ra;
    }
}
