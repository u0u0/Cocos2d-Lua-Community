local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_FairyGUI", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
	self:setNodeEventEnabled(true)
	self.fairyRoot = fairygui.GRoot:create(display.getRunningScene())
    self.fairyRoot:retain()

	fairygui.UIPackage:addPackage("fairygui/package01");
    local view = fairygui.UIPackage:createObject("package01", "StartLayer")
	view:setOpaque(false) -- ignore touch
    self.fairyRoot:addChild(view)

	-- btn event, fairy has it's own EventDispatcher, cover the cocos's node
	view:getChild("n9"):addEventListener(fairygui.UIEventType.TouchEnd, function(context)
		print(context:captureTouch())
	end)
end

function TestCase:onExit()
	self.fairyRoot:removeChildren() -- if not remove child, will crash!!
	self.fairyRoot:release()
end

return TestCase
