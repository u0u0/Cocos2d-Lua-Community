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
	btn:addEventListener(fairygui.UIEventType.Click, function(context)
		-- 不能在fgui事件里面做删除自己等操作,内部会崩.
		self:performWithDelay(function()
			self.fairyRoot:release()
			-- XXX:场景切换的时候需要释放fairygui的静态数据，避免不必要的异常
			fairygui.HtmlObject:clearStaticPools()
			fairygui.DragDropManager:destroyInstance()
		end, 0)
	end)

	local btnOpenWin = view:getChild("btnOpenWin")
	btnOpenWin:addEventListener(fairygui.UIEventType.TouchEnd, function(context)
		local input = context:getInput()
		local touchPos = input:getTouch():getLocation()
		if btnOpenWin:displayObject():hitTest(touchPos) then
			local window = fairygui.Window:create()
			window:addEventListener(fairygui.UIEventType.OnInit, function(context)
				print("Window OnInit")
			end)
			window:addEventListener(fairygui.UIEventType.OnShown, function(context)
				print("Window OnShown")
			end)
			window:addEventListener(fairygui.UIEventType.OnHide, function(context)
				print("Window OnHide")
			end)
			window:setContentPane(fairygui.UIPackage:createObject("package01", "window"))
			window:show()
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

	-- button was created by <object src='ui://2enwy5c4lhol5' name='11' icon=''/>
	local richtext = view:getChild("richtext")
	local htmlObj = richtext:getControl("11")
	dump(htmlObj:getElementAttrs())
	local btnInRT = htmlObj:getUI()
	btnInRT:addEventListener(fairygui.UIEventType.TouchEnd, function(context)
		print("btnInRT clicked")
	end)
end

return TestCase
