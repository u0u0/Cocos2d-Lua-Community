#include "CCArmatureDisplay.h"
#include "CCSlot.h"

DRAGONBONES_NAMESPACE_BEGIN

CCArmatureDisplay* CCArmatureDisplay::create()
{
    CCArmatureDisplay* displayContainer = new (std::nothrow) CCArmatureDisplay();
    if (displayContainer && displayContainer->init())
    {
        displayContainer->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(displayContainer);
    }

    return displayContainer;
}

void CCArmatureDisplay::dbInit(Armature* armature)
{
    _armature = armature;
}

void CCArmatureDisplay::dbClear()
{
    setEventDispatcher(cocos2d::Director::getInstance()->getEventDispatcher());

    _armature = nullptr;
    CC_SAFE_RELEASE_NULL(_dispatcher);
    release();
}

void CCArmatureDisplay::dispose(bool disposeProxy)
{
    if (_armature != nullptr)
    {
        _armature->dispose();
        _armature = nullptr;
    }
}

void CCArmatureDisplay::dbUpdate()
{
    const auto drawed = DragonBones::debugDraw;
    if (drawed)
    {
        // TODO
    }
}

void CCArmatureDisplay::addDBEventListener(const std::string& type, const std::function<void(EventObject*)>& callback)
{
    auto lambda = [callback](cocos2d::EventCustom* event) -> void
    {
        callback(static_cast<EventObject*>(event->getUserData()));
    };
    _dispatcher->addCustomEventListener(type, lambda);
}

void CCArmatureDisplay::dispatchDBEvent(const std::string& type, EventObject* value)
{
    _dispatcher->dispatchCustomEvent(type, value);
}

void CCArmatureDisplay::removeDBEventListener(const std::string& type, const std::function<void(EventObject*)>& callback)
{
    // TODO
    _dispatcher->removeCustomEventListeners(type);
}

cocos2d::Rect CCArmatureDisplay::getBoundingBox() const
{
    auto isFirst = true;
    float minX = 0.0f;
    float minY = 0.0f;
    float maxX = 0.0f;
    float maxY = 0.0f;

    for (const auto slot : _armature->getSlots())
    {
        if (!slot->getVisible() || !slot->getDisplay())
        {
            continue;
        }
        
        const auto display = static_cast<CCSlot*>(slot)->getCCDisplay();
        const auto bounds = display->getBoundingBox();
        if (isFirst)
        {
            isFirst = false;
            minX = bounds.getMinX();
            minY = bounds.getMinY();
            maxX = bounds.getMaxX();
            maxY = bounds.getMaxY();
        }
        else
        {
            minX = std::min(minX, bounds.getMinX());
            minY = std::min(minY, bounds.getMinY());
            maxX = std::max(maxX, bounds.getMaxX());
            maxY = std::max(maxY, bounds.getMaxY());
        }
    }

    cocos2d::Rect rect(minX, minY, maxX - minX, maxY - minY);

    return cocos2d::RectApplyTransform(rect, getNodeToParentTransform());
}

DBCCSprite* DBCCSprite::create()
{
    DBCCSprite* sprite = new (std::nothrow) DBCCSprite();

    if (sprite && sprite->init())
    {
        sprite->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(sprite);
    }

    return sprite;
}

void DBCCSprite::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
#if CC_USE_CULLING    
    // Don't calculate the culling if the transform was not updated
    auto visitingCamera = cocos2d::Camera::getVisitingCamera();
    if (visitingCamera == nullptr)
        _insideBounds = true;
    else
        _insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY) || visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;

    if (_insideBounds)
#endif
    {
        _trianglesCommand.init(_globalZOrder, _texture, _blendFunc, _polyInfo.triangles, transform, flags);
        renderer->addCommand(&_trianglesCommand);

#if CC_SPRITE_DEBUG_DRAW
        _debugDrawNode->clear();
        auto count = _polyInfo.triangles.indexCount / 3;
        auto indices = _polyInfo.triangles.indices;
        auto verts = _polyInfo.triangles.verts;
        for (ssize_t i = 0; i < count; i++)
        {
            //draw 3 lines
            auto from = verts[indices[i * 3]].vertices;
            auto to = verts[indices[i * 3 + 1]].vertices;
            _debugDrawNode->drawLine(cocos2d::Vec2(from.x, from.y), cocos2d::Vec2(to.x, to.y), cocos2d::Color4F::WHITE);

            from = verts[indices[i * 3 + 1]].vertices;
            to = verts[indices[i * 3 + 2]].vertices;
            _debugDrawNode->drawLine(cocos2d::Vec2(from.x, from.y), cocos2d::Vec2(to.x, to.y), cocos2d::Color4F::WHITE);

            from = verts[indices[i * 3 + 2]].vertices;
            to = verts[indices[i * 3]].vertices;
            _debugDrawNode->drawLine(cocos2d::Vec2(from.x, from.y), cocos2d::Vec2(to.x, to.y), cocos2d::Color4F::WHITE);
        }
#endif //CC_SPRITE_DEBUG_DRAW
    }
}

cocos2d::PolygonInfo& DBCCSprite::getPolygonInfoModify()
{
    return _polyInfo;
}

DRAGONBONES_NAMESPACE_END
