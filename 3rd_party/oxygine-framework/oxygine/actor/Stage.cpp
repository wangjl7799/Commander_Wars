#include "Stage.h"
#include "../Clock.h"
#include "../RenderState.h"
#include "../STDRenderDelegate.h"
#include "../core/oxygine.h"
#include "../math/Rect.h"
#include <sstream>

#include "../core/gamewindow.h"

namespace oxygine
{
    spStage Stage::instance;

    Stage::Stage() : _statUpdate(0), _clipOuter(false), _viewport(0, 0, 0, 0) //, _active(true)
    {
        spClock clock = new Clock();
        setClock(clock);
        setName("Stage");
        _stage = this;
    }

    Stage::~Stage()
    {

    }

    void Stage::onDeactivate(Event*)
    {
        //_active = false;
        core::reset();
    }

    Rect    Stage::calcCenteredViewport(const Point& displaySize, const Point& gameSize)
    {
        float width = (float)displaySize.x;
        float height = (float)displaySize.y;

        float scaleFactorX = width / gameSize.x;
        float scaleFactorY = height / gameSize.y;

        float scaleFactor = scaleFactorX < scaleFactorY ? scaleFactorX : scaleFactorY;
        Vector2 size = gameSize * scaleFactor;

        Vector2 free = displaySize.cast<Vector2>() - size;

        return Rect((free / 2).cast<Point>(), size.cast<Point>());
    }

    void Stage::init(const Point& displaySize, const Point& gameSize)
    {
        //_realDisplaySize = displaySize;
        setSize(gameSize);

        _viewport = calcCenteredViewport(displaySize, gameSize);

        float scaleFactor = _viewport.size.x / (float)gameSize.x;

        setScale(scaleFactor);
        setPosition(_viewport.pos);
    }

    bool Stage::isOn(const Vector2& localPosition, float localScale)
    {
        return true;
    }


    RectF Stage::getDestRect() const
    {
//        Q_ASSERT(0);
        Vector2 s = getSize() + getPosition();
        return RectF(-getPosition(), s);
    }

    /*
    bool Stage::handleEvent(const EventState &es)
    {
        bool handled = Actor::handleEvent(es);
        return handled;
    }
    */

    void Stage::render(const QColor* clearColor, const Rect& viewport, const Matrix& view, const Matrix& proj)
    {

        IVideoDriver* driver = IVideoDriver::instance;
        driver->setViewport(viewport);

        if (clearColor)
            driver->clear(*clearColor);

        Matrix vp = view * proj;
        STDRenderer::instance->setViewProj(vp);

        RenderState rs;

        QSize ds = oxygine::GameWindow::getWindow()->size();


        RectF clip(0.0f, 0.0f, (float)ds.width(), (float)ds.height());
        rs.clip = &clip;

        if (_clipOuter)
        {
            driver->setScissorRect(&_viewport);
            clip = _viewport.cast<RectF>();
        }

        Actor::render(rs);
        STDRenderer::getCurrent()->flush();

        Material::null->apply();
    }

    void Stage::render(const QColor& clearColor, const Rect& viewport)
    {
        //initialize projection and view matrix
        Matrix proj;
        Matrix::orthoLH(proj, (float)viewport.getWidth(), (float)viewport.getHeight(), 0.2f, 10000);
        Matrix view = makeViewMatrix(viewport.getWidth(), viewport.getHeight());
        render(&clearColor, viewport, view, proj);
    }

    void Stage::cleanup()
    {
    }

    void Stage::update()
    {
        timeMS t = Clock::getTimeMS();
        UpdateState us;
        Actor::update(us);

        _statUpdate = Clock::getTimeMS() - t;
    }
}
