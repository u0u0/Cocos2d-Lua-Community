local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_WebSocket", BaseLayer)

-- sync from AsyncTCP.h
local EVENT_CONNECTING = 0
local EVENT_FAILED = 1
local EVENT_CONNECTED = 2
local EVENT_CLOSED = 3
local EVENT_DATA = 4

function TestCase:ctor()
	self.super.ctor(self)

	self:setNodeEventEnabled(true)
	-- tips
	local label = display.newTTFLabel({
		text = "Async TCP",
		size = 25,
		color = cc.c3b(255, 255, 255),
	})
	label:align(display.CENTER, display.cx, display.cy + 200)
	self:addChild(label)

	local btn = ccui.Button:create()
		:pos(display.cx, 200)
		:addTo(self)
	btn:setTitleText("Click me to test")
	btn:setTitleFontSize(30)
	btn:setTitleColor(cc.c3b(255, 255, 0))
	btn:addTouchEventListener(function(sender, eventType)
		if 2 == eventType then
			if self.asyncTCP then return end

			self.asyncTCP = AsyncTCP:create()
			self.asyncTCP:setEventCB(handler(self, self.onTCPEvent))
			self.asyncTCP:open("127.0.0.1", 1234, 5)

			self:performWithDelay(function()
				if self.asyncTCP then
					self.asyncTCP:close()
				end
			end, 3)
		end
	end)
end

function TestCase:onTCPEvent(state, data)
	if state == EVENT_CONNECTING then
		print("** AsyncTCP connecting **")
	elseif state == EVENT_FAILED then
		print("** AsyncTCP failed **")
		self.asyncTCP = nil
	elseif state == EVENT_CONNECTED then
		self.asyncTCP:send("Hello AsyncTCP")
	elseif state == EVENT_DATA then
		print(data)
	elseif state == EVENT_CLOSED then
		print("** AsyncTCP closed **")
		self.asyncTCP = nil
	end
end

function TestCase:onExit()
	if self.asyncTCP then
		self.asyncTCP:close()
	end
end

return TestCase
