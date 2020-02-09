--[[
  extension of cc.Node
]]--

local c = cc
local Node = c.Node

-- Lua Node event Type
c.NODE_EVENT                 = 1
c.NODE_ENTER_FRAME_EVENT     = 2
c.NODE_TOUCH_EVENT           = 3
c.KEYPAD_EVENT               = 4
c.ACCELEROMETER_EVENT        = 5

-- touch mode
c.TOUCH_MODE_ALL_AT_ONCE              = cc.TOUCHES_ALL_AT_ONCE
c.TOUCH_MODE_ONE_BY_ONE               = cc.TOUCHES_ONE_BY_ONE

--[[
  Set Node's AnchorPoint and Position.
  @function align
  @param integer anchorPoint, anchor point TYPE defined in display.
  @param integer x
  @param integer y
  @return self
]]--
function Node:align(anchorPoint, x, y)
    self:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then self:setPosition(x, y) end
    return self
end

--[[
  Start a schedule belong to the node.
  @function schedule
  @param function callback
  @param number interval
  @return cc.Action
]]--
function Node:schedule(callback, interval)
    local seq = c.Sequence:create(
        c.DelayTime:create(interval),
        c.CallFunc:create(callback)
    )
    local action = c.RepeatForever:create(seq)
    self:runAction(action)
    return action
end

--[[
  Start a delay callback belong to the node.
  @function performWithDelay
  @param function callback
  @param number delay
  @return cc.Action
]]--
function Node:performWithDelay(callback, delay)
    local action = c.Sequence:create(
        c.DelayTime:create(delay),
        c.CallFunc:create(callback)
    )
    self:runAction(action)
    return action
end

--[[
  Test whether a point is in the node rect.
  @function hitTest
  @param table point
  @return boolean
]]--
function Node:hitTest(point)
    local nsp = self:convertToNodeSpace(point)
    local rect = self:getContentSize()
    rect.x = 0
    rect.y = 0
    if c.rectContainsPoint(rect, nsp) then
        return true
    end
    return false
end

--[[
  Remove self from parent and cleanup.
  @function removeSelf
  @return self
]]--
function Node:removeSelf()
    self:removeFromParent(true)
end

-- override me for setNodeEventEnabled(true)
function Node:onEnter()
end

-- override me for setNodeEventEnabled(true)
function Node:onExit()
end

-- override me for setNodeEventEnabled(true)
function Node:onEnterTransitionFinish()
end

-- override me for setNodeEventEnabled(true)
function Node:onExitTransitionStart()
end

-- override me for setNodeEventEnabled(true)
function Node:onCleanup()
end

--[[
  Enable Accelerometer, call after addNodeEventListener(cc.ACCELEROMETER_EVENT).
  @function setAccelerometerEnabled
  @param boolean enabled
  @return self
]]--
function Node:setAccelerometerEnabled(enabled)
	cc.Device:setAccelerometerEnabled(enabled)
	if not enabled then
		return self
	end

	local listener = cc.EventListenerAcceleration:create(function(event, x, y, z, timestamp)
		-- call listener
		self._LuaListeners[c.ACCELEROMETER_EVENT]{
			x = x,
			y = y,
			z = z,
			timestamp = timestamp
		}
	end)
	self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
	return self
end

--[[
  Enable Node event, auto cal node's member functions.
  @function setNodeEventEnabled
  @param boolean enabled
  @return self
]]--
function Node:setNodeEventEnabled(enabled)
	if enabled then
		local listener = function(event)
			local name = event.name
			if name == "enter" then
				self:onEnter()
			elseif name == "exit" then
				self:onExit()
			elseif name == "enterTransitionFinish" then
				self:onEnterTransitionFinish()
			elseif name == "exitTransitionStart" then
				self:onExitTransitionStart()
			elseif name == "cleanup" then
				self:onCleanup()
			end
		end
		self:addNodeEventListener(c.NODE_EVENT, listener)
	else
		self:removeNodeEventListener(c.NODE_EVENT)
	end
	return self
end

local function KeypadEventCodeConvert(code)
    local key
    if code == 6 then
        key = "back"
    elseif code == 16 then
        key = "menu"
    else
        key = tostring(code)
    end
    return key
end

--[[
  Enable keyboard event, call after addNodeEventListener(cc.KEYPAD_EVENT)
  @function setKeypadEnabled
  @param boolean enabled
  @return self
]]--
function Node:setKeypadEnabled(enable)
    if enable == self:isKeypadEnabled() then
        return self
    end

	local eventDispatcher = self:getEventDispatcher()
    if enable then
        local onKeyPressed = function(keycode, event)
			-- call listener
			self._LuaListeners[c.KEYPAD_EVENT]{
				code = keycode,
				key = KeypadEventCodeConvert(keycode),
				type = "Pressed"
			}
        end

        local onKeyReleased = function(keycode, event)
			-- call listener
			self._LuaListeners[c.KEYPAD_EVENT]{
				code = keycode,
				key = KeypadEventCodeConvert(keycode),
				type = "Released"
			}
        end

        local listener = c.EventListenerKeyboard:create()
        listener:registerScriptHandler(onKeyPressed, c.Handler.EVENT_KEYBOARD_PRESSED)
        listener:registerScriptHandler(onKeyReleased, c.Handler.EVENT_KEYBOARD_RELEASED)
        eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
        self.__key_event_handle__ = listener
	else
        eventDispatcher:removeEventListener(self.__key_event_handle__)
        self.__key_event_handle__ = nil
	end

    return self
end

--[[
  Is keyboard event enabled.
  @function setKeypadEnabled
  @return boolean
]]--
function Node:isKeypadEnabled()
    if self.__key_event_handle__ then
		return true
	end
	return false
end

--[[
  Start node's frame event.
  @function scheduleUpdate
  @return self
]]--
function Node:scheduleUpdate()
    local listener = function (dt)
		-- call listener
		self._LuaListeners[c.NODE_ENTER_FRAME_EVENT](dt)
    end

    self:scheduleUpdateWithPriorityLua(listener, 0)
    return self
end

--[[
  Set node's touch mode.
  @function setTouchMode
]]--
function Node:setTouchMode(mode)
	if mode ~= c.TOUCH_MODE_ALL_AT_ONCE and mode ~= c.TOUCHES_ONE_BY_ONE then
		print("== wrong mode", mode)
		return
	end
	self._luaTouchMode = mode
end

--[[
  Enable touch event, call after addNodeEventListener(cc.NODE_TOUCH_EVENT)
  @function setTouchEnabled
  @param boolean enabled
]]--
function Node:setTouchEnabled(enable)
	-- remove old
	local eventDispatcher = self:getEventDispatcher()
	if self._luaTouchListener then
		eventDispatcher:removeEventListener(self._luaTouchListener)
		self._luaTouchListener = nil
	end

	if not enable then
		return
	end

	assert(self._LuaListeners, "Error: addNodeEventListener(cc.NODE_TOUCH_EVENT, func) first!")
	assert(self._LuaListeners[c.NODE_TOUCH_EVENT], "Error: addNodeEventListener(cc.NODE_TOUCH_EVENT, func) first!")

	local isSingle = true
	if self._luaTouchMode and self._luaTouchMode == c.TOUCH_MODE_ALL_AT_ONCE then
		isSingle = false
	end

	-- add new
	if isSingle then
		self._luaTouchListener = c.EventListenerTouchOneByOne:create()
		self._luaTouchListener:setSwallowTouches(true)
		local dealFunc = function(touch, name)
			local tp = touch:getLocation()
			local sp = touch:getStartLocation()
			local pp = touch:getPreviousLocation()

			if name == "began" then
				if not self:isVisible(true) or not self:hitTest(tp) then
					return false
				end
			elseif name == "ended" then
				if not self:hitTest(tp) then -- out of touch area
					name = "cancelled"
				end
			end

			-- call listener
			return self._LuaListeners[c.NODE_TOUCH_EVENT]{
				name = name,
				x = tp.x,
				y = tp.y,
				startX = sp.x,
				startY = sp.y,
				prevX = pp.x,
				prevY = pp.y,
			}
		end
		self._luaTouchListener:registerScriptHandler(function(touch, event)
			return dealFunc(touch, "began")
		end, c.Handler.EVENT_TOUCH_BEGAN)
		self._luaTouchListener:registerScriptHandler(function(touch, event)
			dealFunc(touch, "moved")
		end, c.Handler.EVENT_TOUCH_MOVED)
		self._luaTouchListener:registerScriptHandler(function(touch, event)
			dealFunc(touch, "ended")
		end, c.Handler.EVENT_TOUCH_ENDED)
		self._luaTouchListener:registerScriptHandler(function(touch, event)
			dealFunc(touch, "cancelled")
		end, c.Handler.EVENT_TOUCH_CANCELLED)
	else
		self._luaTouchListener = c.EventListenerTouchAllAtOnce:create()
		local dealFunc = function(touchs, name)
			local points = {}
			for _, touch in pairs(touchs) do
				local tp = touch:getLocation()
				local sp = touch:getStartLocation()
				local pp = touch:getPreviousLocation()
				points[touch:getId()] = {
					x = tp.x,
					y = tp.y,
					startX = sp.x,
					startY = sp.y,
					prevX = pp.x,
					prevY = pp.y,
				}
			end

			-- call listener
			self._LuaListeners[c.NODE_TOUCH_EVENT]{
				name = name,
				points = points,
			}
		end
		self._luaTouchListener:registerScriptHandler(function(touchs, event)
			dealFunc(touchs, "began")
		end, c.Handler.EVENT_TOUCHES_BEGAN)
		self._luaTouchListener:registerScriptHandler(function(touchs, event)
			dealFunc(touchs, "moved")
		end, c.Handler.EVENT_TOUCHES_MOVED)
		self._luaTouchListener:registerScriptHandler(function(touchs, event)
			dealFunc(touchs, "ended")
		end, c.Handler.EVENT_TOUCHES_ENDED)
		self._luaTouchListener:registerScriptHandler(function(touchs, event)
			dealFunc(touchs, "cancelled")
		end, c.Handler.EVENT_TOUCHES_CANCELLED)
	end
	eventDispatcher:addEventListenerWithSceneGraphPriority(self._luaTouchListener, self)
end

--[[
  Change the node's touch swallow flag
  @function setTouchSwallowEnabled
  @param boolean enabled
]]--
function Node:setTouchSwallowEnabled(enable)
	if self._luaTouchListener then
		self._luaTouchListener:setSwallowTouches(enable)
	end
end

--[[
  Register node evet by type.
  @function addNodeEventListener
  @param integer evt, value can be:
    cc.NODE_EVENT
    cc.NODE_ENTER_FRAME_EVENT
    cc.NODE_TOUCH_EVENT
    cc.KEYPAD_EVENT
    cc.ACCELEROMETER_EVENT
  @param function hdl
]]--
function Node:addNodeEventListener(evt, hdl)
	self._LuaListeners = self._LuaListeners or {}
	if evt == c.NODE_EVENT then
		self:registerScriptHandler(function(evt)
			-- call listener
			self._LuaListeners[c.NODE_EVENT]{name = evt}
		end)
	end

	self._LuaListeners[evt] = hdl
end

--[[
  Unregister node evet by type.
  @function addNodeEventListener
  @param integer evt, value can be:
    cc.NODE_EVENT
    cc.NODE_ENTER_FRAME_EVENT
    cc.NODE_TOUCH_EVENT
    cc.KEYPAD_EVENT
    cc.ACCELEROMETER_EVENT
]]--
function Node:removeNodeEventListener(evt)
    if not self._LuaListeners then return end

	if evt == c.KEYPAD_EVENT then
		self:setKeypadEnabled(false)
	elseif evt == c.NODE_EVENT then
		self:unregisterScriptHandler()
	elseif evt == c.NODE_ENTER_FRAME_EVENT then
		self:unscheduleUpdate()
	elseif evt == c.NODE_TOUCH_EVENT then
		self:setTouchEnabled(false)
	elseif evt == c.ACCELEROMETER_EVENT then
		cc.Device:setAccelerometerEnabled(false)
	end

	self._LuaListeners[evt] = nil
end

--[[
  Unregister all node's event.
  @function removeAllNodeEventListeners
]]--
function Node:removeAllNodeEventListeners()
    self:removeNodeEventListener(c.NODE_EVENT)
    self:removeNodeEventListener(c.NODE_ENTER_FRAME_EVENT)
    self:removeNodeEventListener(c.NODE_TOUCH_EVENT)
    self:removeNodeEventListener(c.KEYPAD_EVENT)
    self:removeNodeEventListener(c.ACCELEROMETER_EVENT)
end
