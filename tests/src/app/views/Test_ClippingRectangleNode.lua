local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_ClippingRectangleNode", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
	local rect = cc.rect(20, 20, 400, 400)
	local shape3 = display.newRect(rect, {
		borderColor = cc.c4f(0,1,0,1),
		borderWidth = 2
	}):addTo(self)

	local clipA = display.newClippingRectangleNode(rect):addTo(self)
	local spB = display.newSprite("clip/11.png"):addTo(clipA):pos(150, 150)

	local spD = display.newSprite("clip/22.png"):addTo(clipA):pos(300, 380)
	local clipC = display.newClippingRectangleNode(cc.rect(200, 200, 300, 300)):addTo(spB)

	local btn = ccui.Button:create():pos(display.right - 100, 100):addTo(self)
	btn:setTitleText("snap")
	btn:setTitleFontSize(30)
	btn:setTitleColor(cc.c3b(255, 255, 0))
	btn:addTouchEventListener(function(sender, eventType)
		if 2 == eventType then
			local render_texture = cc.RenderTexture:create(display.width, display.height)
			render_texture:begin()
			self:visit()
			render_texture:endToLua()

			local photo_texture = render_texture:getSprite():getTexture()
			local sprite_photo = cc.Sprite:createWithTexture(photo_texture)
			sprite_photo:flipY(true)
			sprite_photo:scale(0.5)

			sprite_photo:addTo(self):center()
		end
	end)
end

return TestCase
