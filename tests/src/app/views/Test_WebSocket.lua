local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_WebSocket", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	self:setNodeEventEnabled(true)
	-- tips
	local label = display.newTTFLabel({
		text = "Wait connect",
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
			self.socket = cc.WebSocket:create("wss://127.0.0.1:1234")
			if self.socket then
				self.socket:registerScriptHandler(handler(self, self.onOpen), cc.WEBSOCKET_OPEN)
				self.socket:registerScriptHandler(handler(self, self.onMessage), cc.WEBSOCKET_MESSAGE)
				self.socket:registerScriptHandler(handler(self, self.onClose), cc.WEBSOCKET_CLOSE)
				self.socket:registerScriptHandler(handler(self, self.onError), cc.WEBSOCKET_ERROR)
			end
		end
	end)
end

function TestCase:onOpen()
	print("==onOpen")
	self.socket:sendString("Hello server, i'm Quick websocket")
	-- delay to close
	-- self:performWithDelay(function () self.socket:close() end, 1.0)
end

function TestCase:onMessage(message)
	print("==onMessage:" .. message)
end

function TestCase:onClose()
	print("==onClose")
	self.socket = nil
end

function TestCase:onError(error)
	print("==onError:" .. error)
end

function TestCase:onExit()
	if self.socket then
		self.socket:close()
	end
end

return TestCase
