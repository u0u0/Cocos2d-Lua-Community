local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_3D", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	self:setBackGroundColorOpacity(0) -- make UI layer not cover 3d moule
	-- tips
	local rootNode = display.newNode()
	rootNode:addTo(self)
	-- create 3D camera
	local camera = cc.Camera:createPerspective(60, display.width / display.height, 10, 1000)
	camera:setPosition3D(cc.vec3(0, 0, 50))
	camera:lookAt(cc.vec3(0.0, 0.0, 0.0))
	camera:setCameraFlag(cc.CameraFlag.USER1)
	rootNode:addChild(camera)
	-- 3D sprite
	local sprite = cc.Sprite3D:create("3D/orc.c3b")
	sprite:setScale(2.0)
	sprite:setPosition3D(cc.vec3(0, -15, 0))
	sprite:setRotation3D(cc.vec3(0, 180, 0))
	rootNode:addChild(sprite)
	-- 3D animation
	local animation = cc.Animation3D:create("3D/orc.c3b")
	local animate = cc.Animate3D:create(animation)
	animate:setSpeed(1.5)
	animate:setQuality(cc.Animate3DQuality.QUALITY_HIGH)
	local repeatAction = cc.RepeatForever:create(animate)
	sprite:runAction(repeatAction)

	rootNode:setCameraMask(cc.CameraFlag.USER1) -- set render mask after all child add
end

function TestCase:onExit()
end

return TestCase
