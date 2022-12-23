local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_EditBox", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
    self:addTextUIInput()
    self:addPDUIInput()
end

-- 文本输入框
function TestCase:addTextUIInput()
	local editbox = ccui.EditBox:create(cc.size(134, 43), "editbox.png", 0)
	editbox:setInputMode(cc.EDITBOX_INPUT_MODE_SINGLELINE)
	editbox:setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_CENTER)
	editbox:setPlaceholderFontSize(22)
	editbox:setFontSize(22)
    editbox:setPosition(display.width / 2, display.height / 2)
	self:addChild(editbox)
    -- editbox:setText("默认文本")
    editbox:setPlaceHolder("输入文本") -- 提示输入文本
	editbox:registerScriptEditBoxHandler(function(event, target)
        if event == "began" then
            -- 开始输入
            print("开始输入")
        elseif event == "changed" then
            -- 输入框内容发生变化
            print("输入框内容发生变化")
            local text = editbox:getText()
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

-- 密码输入框
function TestCase:addPDUIInput()
	local editbox = ccui.EditBox:create(cc.size(134, 43), "editbox.png", 0)
	editbox:setInputMode(cc.EDITBOX_INPUT_MODE_SINGLELINE)
	editbox:setPlaceholderFontSize(22)
	editbox:setFontSize(22)
	editbox:setPosition(display.width / 2, display.height / 2 - 100)
	self:addChild(editbox)
	editbox:setPlaceHolder("输入密码")
    editbox:setInputFlag(cc.EDITBOX_INPUT_FLAG_PASSWORD)
	editbox:registerScriptEditBoxHandler(function(event, target)
		if event == "began" then
			-- 开始输入
			print("开始输入")
		elseif event == "changed" then
			-- 输入框内容发生变化
			print("输入框内容发生变化")
			local text = editbox:getText()
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
