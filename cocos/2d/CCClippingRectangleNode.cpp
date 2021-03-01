/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2020-2021 cocos2d-lua.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "2d/CCClippingRectangleNode.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "math/Vec2.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

ClippingRectangleNode* ClippingRectangleNode::create(const Rect& clippingRegion)
{
    ClippingRectangleNode* node = new (std::nothrow) ClippingRectangleNode();
    if (node && node->init()) {
        // ClippingRectangleNode mostly use for UI, enable below two attributes.
        node->setCascadeColorEnabled(true);
        node->setCascadeOpacityEnabled(true);
        node->setClippingRegion(clippingRegion);
        node->autorelease();
    } else {
        CC_SAFE_DELETE(node);
    }
    return node;
}

ClippingRectangleNode* ClippingRectangleNode::create()
{
    ClippingRectangleNode* node = new (std::nothrow) ClippingRectangleNode();
    if (node && node->init()) {
        // ClippingRectangleNode mostly use for UI, enable below two attributes.
        node->setCascadeColorEnabled(true);
        node->setCascadeOpacityEnabled(true);
        node->autorelease();
    } else {
        CC_SAFE_DELETE(node);
    }
    return node;
}

void ClippingRectangleNode::setClippingRegion(const Rect &clippingRegion)
{
    _clippingRegion = clippingRegion;
}

void ClippingRectangleNode::onBeforeVisitScissor()
{
    if (_clippingEnabled) {
		// get this ClipRegion
		const Point pos1 = convertToWorldSpace(Point(_clippingRegion.origin.x, _clippingRegion.origin.y));
		const Point pos2 = convertToWorldSpace(Point(_clippingRegion.origin.x + _clippingRegion.size.width, _clippingRegion.origin.y + _clippingRegion.size.height));
		float px = pos1.x;
		float py = pos1.y;
		float width = pos2.x - pos1.x;
		float height = pos2.y - pos1.y;
		if (width < 0) {
			width = 0; //ClippingRectangle should not be rotated
		}
		if (height < 0) {
			height = 0; //ClippingRectangle should not be rotated
		}

        // record old ClipRegion
        GLView* glView = Director::getInstance()->getOpenGLView();
        if (glView->isScissorEnabled()) {
			_preClipRegion = glView->getScissorRect();
			// check collision
			float centerXdelta = (width + _preClipRegion.size.width) / 2;
			float centerYdelta = (height + _preClipRegion.size.height) / 2;
			if (std::abs((px + width / 2) - (_preClipRegion.origin.x + _preClipRegion.size.width / 2)) <= centerXdelta
				&& std::abs((py + height / 2) - (_preClipRegion.origin.y + _preClipRegion.size.height / 2)) <= centerYdelta)
			{
				// get Intersecting rectangle
				px = std::max(px, _preClipRegion.origin.x);
				py = std::max(py, _preClipRegion.origin.y);
				width = std::min(pos1.x + width - px, _preClipRegion.origin.x + _preClipRegion.size.width - px);
				height = std::min(pos1.y + height - py, _preClipRegion.origin.y + _preClipRegion.size.height- py);
			} else {
				//ZERO rect will auto disable Scissor clip, cheat with below code.
				px = -1;
				py = -1;
				width = 1;
				height = 1;
			}
        } else {
            _preClipRegion = Rect::ZERO;
            auto renderer = Director::getInstance()->getRenderer();
            renderer->setScissorTest(true);
        }
        
        glView->setScissorInPoints(px, py, width, height);
    }
}

void ClippingRectangleNode::onAfterVisitScissor()
{
    if (_clippingEnabled) {
        // rollback to old ClipRegion
        if (!_preClipRegion.equals(Rect::ZERO)) {
            auto glview = Director::getInstance()->getOpenGLView();
            glview->setScissorInPoints(_preClipRegion.origin.x,
                      _preClipRegion.origin.y,
                      _preClipRegion.size.width,
                      _preClipRegion.size.height);
        } else {
            // revert scissor test
            auto renderer = Director::getInstance()->getRenderer();
            renderer->setScissorTest(false);
        }
    }
}

void ClippingRectangleNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (!_visible) {
        return;
    }
    
    if (isVisitableByVisitingCamera()) {
        _beforeVisitCmdScissor.init(_globalZOrder);
        _beforeVisitCmdScissor.func = CC_CALLBACK_0(ClippingRectangleNode::onBeforeVisitScissor, this);
        renderer->addCommand(&_beforeVisitCmdScissor);
        
        Node::visit(renderer, parentTransform, parentFlags);
        
        _afterVisitCmdScissor.init(_globalZOrder);
        _afterVisitCmdScissor.func = CC_CALLBACK_0(ClippingRectangleNode::onAfterVisitScissor, this);
        renderer->addCommand(&_afterVisitCmdScissor);
    }
}

NS_CC_END
