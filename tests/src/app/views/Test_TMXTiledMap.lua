local BaseLayer = require("app.scenes.BaseLayer")

local TestCase = class("Test_RichText", BaseLayer)

function TestCase:ctor()
	self.super.ctor(self)

	-- tips
	local map = cc.TMXTiledMap:create("tiled/desert.tmx")
	map:addTo(self)
	-- NOTE: In tiled edit, use defined properites suggest use title case word for the KEY.
	local objs = map:getObjectGroup("Objects"):getObjects()
	for _, obj in ipairs(objs) do
		-- ObjectGroup's object's pos had convert to cocos coordinate
		dump(obj)
	end

	local layer = map:getLayer("Ground")
	local gid = layer:getTileGIDAt(cc.p(6, 12))
	local prop = map:getPropertiesForGID(gid)
	-- ObjectGroup's object's pos had convert to cocos coordinate
	dump(prop)
end

return TestCase
