/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#ifndef __cocos2d_libs__CCMouseEvent__
#define __cocos2d_libs__CCMouseEvent__

#include "base/CCEvent.h"
#include "math/CCGeometry.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/** @class EventMouse
 * @brief The mouse event.
 */
class CC_DLL EventMouse : public Event
{
public:
    /**
    * MouseEventType Different types of MouseEvent.
    * @js NA
    */
    enum class MouseEventType
    {
        MOUSE_NONE,
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_MOVE,
        MOUSE_SCROLL,
    };

    enum class MouseButton
    {
      BUTTON_UNSET   = -1,
      BUTTON_LEFT    =  0,
      BUTTON_RIGHT   =  1,
      BUTTON_MIDDLE  =  2,
      BUTTON_4       =  3,
      BUTTON_5       =  4,
      BUTTON_6       =  5,
      BUTTON_7       =  6,
      BUTTON_8       =  7
    };

    /** Constructor.
     *
     * @param mouseEventCode A given mouse event type.
     * @js ctor
     */
    EventMouse(MouseEventType mouseEventCode);

    /** Set mouse scroll data. ONLY be call by GLFW
     * 
     * @param scrollX The scroll data of x axis.
     * @param scrollY The scroll data of y axis.
     */
    void setScrollData(float scrollX, float scrollY) { _scrollX = scrollX; _scrollY = scrollY; }
    
    /** Get mouse scroll data of x axis.
     * 
     * @return The scroll data of x axis.
     */
    float getScrollX() const { return _scrollX; }
    
    /** Get mouse scroll data of y axis.
     *
     * @return The scroll data of y axis.
     */
    float getScrollY() const { return _scrollY; }

    /** Set the cursor position. ONLY be call by GLFW
     *
     * @param x The x coordinate of cursor position.
     * @param y The y coordinate of cursor position.
     * @js setLocation
     */
    void setCursorPosition(float x, float y);

    /** Set mouse button. ONLY be call by GLFW
     * 
     * @param button a given mouse button.
     * @js setButton
     */
    void setMouseButton(MouseButton button) { _mouseButton = button; }
    
    /** Get mouse button.
     *
     * @return The mouse button.
     * @js getButton
     */
    MouseButton getMouseButton() const { return _mouseButton; }

    /** Returns the current touch location in OpenGL coordinates.
     *
     * @return The current touch location in OpenGL coordinates.
     */
    Vec2 getLocation() const;
    
    /** Returns the current touch location in screen coordinates.
     *
     * @return The current touch location in screen coordinates.
     */
    Vec2 getLocationInView() const;

private:
    MouseEventType _mouseEventType;
    MouseButton _mouseButton;
    float _scrollX;
    float _scrollY;
    Vec2 _point;

    friend class EventListenerMouse;
};

NS_CC_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__CCMouseEvent__) */
