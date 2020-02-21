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
    self.fairyRoot:addChild(view)

	-- btn event, fairy has it's own EventDispatcher, cover the cocos's node
	view:getChild("n9"):addEventListener(12, function(context)
		print(context)
		self:getParent():openScrollView()
		self:removeSelf()
	end)
end

function TestCase:onExit()
	self.fairyRoot:removeChildren() -- if not remove child, will crash!!
	self.fairyRoot:release()
end

return TestCase
