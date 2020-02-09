--[[
 Short function of cc.Node & cc.Sprite, all shortcodes return self.
]]

local c = cc
local Node = c.Node

--[[
  Same with addChild, and return self.
  @function add
  @param node child
  @param number zorder
  @param number tag
  @return self
]]--
function Node:add(child, zorder, tag)
    self:addChild(child, zorder or child:getLocalZOrder(), tag or child:getTag())
    return self
end

--[[
  Add self as a child to target.
  @function addTo
  @param node target, parent node
  @param number zorder
  @param number tag
  @return self
]]--
function Node:addTo(target, zorder, tag)
    target:addChild(self, zorder or self:getLocalZOrder(), tag or self:getTag())
    return self
end

--[[
  Show self.
  @function show
  @return self
]]--
function Node:show()
    self:setVisible(true)
    return self
end

--[[
  Hide self.
  @function hide
  @return self
]]--
function Node:hide()
    self:setVisible(false)
    return self
end

--[[
  Set self's position.
  @function pos
  @param number x
  @param number y
  @return self
]]--
function Node:pos(x, y)
    self:setPosition(x, y)
    return self
end

--[[
  Set self's position to screen center.
  NOTE: parent must screen root or size equal to screen size.
  @function center
  @return self
]]--
function Node:center()
    self:setPosition(display.cx, display.cy)
    return self
end

--[[
  Scale self.
  @function scale
  @param number scale
  @return self
]]--
function Node:scale(scale)
    self:setScale(scale)
    return self
end

--[[
  Rotate self.
  @function rotation
  @param number r
  @return self
]]--
function Node:rotation(r)
    self:setRotation(r)
    return self
end

--[[
  Set self's content size.
  @function size
  @param number width or table cc.size
  @param number height
  @return self
]]--
function Node:size(width, height)
    if type(width) == "table" then
        self:setContentSize(width)
    else
        self:setContentSize(cc.size(width, height))
    end
    return self
end

--[[
  Set opacity of self.
  @function opacity
  @param integer opacity, 0 ~ 255
  @return self
]]--
function Node:opacity(opacity)
    self:setOpacity(opacity)
    return self
end

--[[
  Set local zorder of self.
  @function zorder
  @param integer z
  @return self
]]--
function Node:zorder(z)
    self:setLocalZOrder(z)
    return self
end

--[[
  Set node's all action.
  @function stop
  @return self
]]--
function Node:stop()
    self:stopAllActions()
    return self
end

--[[
  Node run a fadeIn action by time.
  @function fadeIn
  @param number time
  @return self
]]--
function Node:fadeIn(time)
    self:runAction(cc.FadeIn:create(time))
    return self
end

--[[
  Node run a fadeOut action by time.
  @function fadeOut
  @param number time
  @return self
]]--
function Node:fadeOut(time)
    self:runAction(cc.FadeOut:create(time))
    return self
end

--[[
  Node run a fadeTo action by time and opacity.
  @function fadeTo
  @param number time
  @param integer opacity
  @return self
]]--
function Node:fadeTo(time, opacity)
    self:runAction(cc.FadeTo:create(time, opacity))
    return self
end

--[[
  Node run a moveTo action by time.
  @function moveTo
  @param number time
  @param integer x
  @param integer y
  @return self
]]--
function Node:moveTo(time, x, y)
    self:runAction(cc.MoveTo:create(time, cc.p(x or self:getPositionX(), y or self:getPositionY())))
    return self
end

--[[
  Node run a moveBy action by time.
  @function moveBy
  @param number time
  @param integer x
  @param integer y
  @return self
]]--
function Node:moveBy(time, x, y)
    self:runAction(cc.MoveBy:create(time, cc.p(x or 0, y or 0)))
    return self
end

--[[
  Node run a rotateTo action by time.
  @function rotateTo
  @param number time
  @param number rotation
  @return self
]]--
function Node:rotateTo(time, rotation)
    self:runAction(cc.RotateTo:create(time, rotation))
    return self
end

--[[
  Node run a rotateBy action by time.
  @function rotateBy
  @param number time
  @param number rotation
  @return self
]]--
function Node:rotateBy(time, rotation)
    self:runAction(cc.RotateBy:create(time, rotation))
    return self
end

--[[
  Node run a scaleTo action by time.
  @function scaleTo
  @param number time
  @param number scale
  @return self
]]--
function Node:scaleTo(time, scale)
    self:runAction(cc.ScaleTo:create(time, scale))
    return self
end

--[[
  Node run a scaleBy action by time.
  @function scaleBy
  @param number time
  @param number scale
  @return self
]]--
function Node:scaleBy(time, scale)
    self:runAction(cc.ScaleBy:create(time, scale))
    return self
end

--[[
  Node run a skewTo action by time.
  @function skewTo
  @param number time
  @param number sx
  @param number sy
  @return self
]]--
function Node:skewTo(time, sx, sy)
    self:runAction(cc.SkewTo:create(time, sx or self:getSkewX(), sy or self:getSkewY()))
    return self
end

--[[
  Node run a skewBy action by time.
  @function skewBy
  @param number time
  @param number sx
  @param number sy
  @return self
]]--
function Node:skewBy(time, sx, sy)
    self:runAction(cc.SkewBy:create(time, sx or 0, sy or 0))
    return self
end

--[[
  Node run a tintTo action by time.
  @function tintTo
  @param number time
  @param integer r
  @param integer g
  @param integer b
  @return self
]]--
function Node:tintTo(time, r, g, b)
    self:runAction(cc.TintTo:create(time, r or 0, g or 0, b or 0))
    return self
end

--[[
  Node run a tintBy action by time.
  @function tintBy
  @param number time
  @param integer r
  @param integer g
  @param integer b
  @return self
]]--
function Node:tintBy(time, r, g, b)
    self:runAction(cc.TintBy:create(time, r or 0, g or 0, b or 0))
    return self
end

local Sprite = c.Sprite

--[[
  Set sprite's display frame.
  @function displayFrame
  @param SpriteFrame frame
  @return self
]]--
function Sprite:displayFrame(frame)
	self:setSpriteFrame(frame)
	return self
end

--[[
  Set sprite's flipX flag.
  @function flipX
  @param boolean b
  @return self
]]--
function Sprite:flipX(b)
	self:setFlippedX(b)
	return self
end

--[[
  Set sprite's flipY flag.
  @function flipY
  @param boolean b
  @return self
]]--
function Sprite:flipY(b)
	self:setFlippedY(b)
	return self
end
