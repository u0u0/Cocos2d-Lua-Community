local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_Spine", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
	local spineSP = sp.SkeletonAnimation:createWithJsonFile(
		"spine/spineboy-pro.json", "spine/spineboy.atlas"
	)
	spineSP:setScale(0.5)
	spineSP:pos(display.cx, 100):addTo(self)
	spineSP:setAnimation(0, "run", true)
	-- aim mode
	spineSP:setAnimation(1, "aim", false)

	self:performWithDelay(function()
		spineSP:setAnimation(2, "shoot", false)
		spineSP:registerSpineEventHandler(function(event)
			if event.animation == "shoot" and event.trackIndex == 2 then
				spineSP:clearTrack(2)
				spineSP:setEmptyAnimation(1, 0.1) -- remove aim, back to run only
			end
		end, sp.EventType.ANIMATION_COMPLETE)
	end, 4)

	local y = 0
	spineSP:setPostUpdateWorldTransformsListener(function()
		if y > 247 then
			return
		end
		y = y + 1
		spineSP:updateBone("crosshair", {x = 400, y = y})
	end)
end

return TestCase
