local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_DragonBones", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
	if not app._isDBLoaded then
		-- DragonBones runtime will cache json and atlas, only need load once
		dragonBones.CCFactory:loadDragonBonesData("dragonbones/mecha_1004d_ske.json")
		dragonBones.CCFactory:loadTextureAtlasData("dragonbones/mecha_1004d_tex.json")
		app._isDBLoaded = true
	end
	local db = dragonBones.CCFactory:buildArmatureDisplay("mecha_1004d")
	self.db = db
	local ani = db:getAnimation()
	ani:play("walk")
	db:addDBEventListener("loopComplete", function(event)
		local attackState = ani:getState("attack_01")
		if not attackState then
			attackState = ani:fadeIn("attack_01", 0.1, 1, 1)
			attackState.resetToPose = false
			attackState.autoFadeOutTime = 0.1
			attackState.timeScale = 0.5
			attackState:addBoneMask("chest")
			attackState:addBoneMask("effect_l")
			attackState:addBoneMask("effect_r")
		end
	end)
	db:addTo(self)
	db:pos(display.cx, display.cy - 100)
end

return TestCase
