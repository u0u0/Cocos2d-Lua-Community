local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_FairyGUI", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
	self.fairyRoot = fairygui.GRoot:create(display.getRunningScene())
    self.fairyRoot:retain()

	fairygui.UIPackage:addPackage("fairygui/package01");
    local view = fairygui.UIPackage:createObject("package01", "StartLayer")
	view:setOpaque(false) -- ignore touch
    self.fairyRoot:addChild(view)

	-- btn event, fairy has it's own EventDispatcher, cover the cocos's node
	local btn = view:getChild("n9")
	btn:addEventListener(fairygui.UIEventType.TouchEnd, function(context)
		local input = context:getInput()
		local touchPos = input:getTouch():getLocation()
		if btn:displayObject():hitTest(touchPos) then
			print("touch ended")
			self.fairyRoot:release()
		else
			print("touch canceled")
		end
	end)

	-- displayObject is FUIInput, FUIInput is derive from Editbox
	local inputText = view:getChild("inputText"):displayObject()
	inputText:registerScriptEditBoxHandler(function(event, target)
        if event == "began" then
            -- 开始输入
            print("开始输入")
        elseif event == "changed" then
            -- 输入框内容发生变化
            print("输入框内容发生变化")
            local text = inputText:getText()
            print(text)
        elseif event == "ended" then
            -- 输入结束
            print("输入结束")
        elseif event == "return" then
            -- 从输入框返回
            print("从输入框返回")
        end
	end)
end

return TestCase
