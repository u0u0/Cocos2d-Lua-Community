local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_RichText", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
	local rt = ccui.RichText:create():addTo(self):center()
	-- add custom
	local btn = ccui.Button:create()
	btn:setTitleText("Button")
	btn:setTitleFontSize(30)
	btn:setTitleColor(cc.c3b(255, 255, 0))
	btn:addTouchEventListener(function(sender, eventType)
		if 2 == eventType then
			print("Button clicked")
		end
	end)
	local element = ccui.RichElementCustomNode:create(0, display.COLOR_WHITE, 255, btn)
	rt:pushBackElement(element)
	-- add label
	local element = ccui.RichElementText:create(0, display.COLOR_WHITE, 255, "Hello Text", "Airal", 24)
	rt:pushBackElement(element)
	-- add newline
	local element = ccui.RichElementNewLine:create(0, display.COLOR_WHITE, 255)
	rt:pushBackElement(element)
	-- add image
	local element = ccui.RichElementImage:create(0, display.COLOR_BLUE, 255, "button.png")
	-- element:setHeight(100)
	rt:pushBackElement(element)
end

return TestCase
