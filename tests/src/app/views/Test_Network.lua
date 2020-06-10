local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_Network", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

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
			local function onRequestCallback(event)
				local request = event.request
				if event.name == "completed" then
					print(request:getResponseHeadersString())
					local code = request:getResponseStatusCode()
					if code ~= 200 then
						print(code) -- get error
						return
					end

					-- get success
					print("response length" .. request:getResponseDataLength())
					local response = request:getResponseString()
					print(response)
				elseif event.name == "progress" then
					print("progress" .. event.dltotal)
				else
					print(event.name) -- get error
					print(request:getErrorCode(), request:getErrorMessage())
					return
				end
			end

			local request = network.createHTTPRequest(onRequestCallback, "https://baidu.com", "GET")
			request:start()
		end
	end)
end

return TestCase
