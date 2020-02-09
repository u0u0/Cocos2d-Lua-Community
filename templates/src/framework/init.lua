print("===========================================================")
print("              LOAD Cocos2d-Lua-Community FRAMEWORK")
print("===========================================================")

if type(DEBUG) ~= "number" then DEBUG = 0 end
if type(DEBUG_FPS) ~= "boolean" then DEBUG_FPS = false end
if type(DEBUG_MEM) ~= "boolean" then DEBUG_MEM = false end

local CURRENT_MODULE_NAME = ...

cc = cc or {}
cc.PACKAGE_NAME = string.sub(CURRENT_MODULE_NAME, 1, -6)

require(cc.PACKAGE_NAME .. ".debug")
require(cc.PACKAGE_NAME .. ".functions")

printInfo("")
printInfo("# DEBUG                        = "..DEBUG)
printInfo("#")

device     = require(cc.PACKAGE_NAME .. ".device")
display    = require(cc.PACKAGE_NAME .. ".display")
audio      = require(cc.PACKAGE_NAME .. ".audio")
network    = require(cc.PACKAGE_NAME .. ".network")
crypto     = require(cc.PACKAGE_NAME .. ".crypto")
json       = require(cc.PACKAGE_NAME .. ".json")
require(cc.PACKAGE_NAME .. ".shortcodes")
require(cc.PACKAGE_NAME .. ".NodeEx")
require(cc.PACKAGE_NAME .. ".WidgetEx")

if device.platform == "android" then
    require(cc.PACKAGE_NAME .. ".platform.android")
elseif device.platform == "ios" then
    require(cc.PACKAGE_NAME .. ".platform.ios")
elseif device.platform == "mac" then
    require(cc.PACKAGE_NAME .. ".platform.mac")
end


local sharedTextureCache = cc.Director:getInstance():getTextureCache()
local sharedDirector = cc.Director:getInstance()

if DEBUG_FPS then
    sharedDirector:setDisplayStats(true)
else
    sharedDirector:setDisplayStats(false)
end

if DEBUG_MEM then
    local sharedTextureCache = cc.Director:getInstance():getTextureCache()
    local function showMemoryUsage()
        printInfo(string.format("LUA VM MEMORY USED: %0.2f KB", collectgarbage("count")))
        printInfo(sharedTextureCache:getCachedTextureInfo())
        printInfo("---------------------------------------------------")
    end
    sharedDirector:getScheduler():scheduleScriptFunc(showMemoryUsage, DEBUG_MEM_INTERVAL or 10.0, false)
end

-- export global variable
local __g = _G
cc.exports = {}
setmetatable(cc.exports, {
    __newindex = function(_, name, value)
        rawset(__g, name, value)
    end,

    __index = function(_, name)
        return rawget(__g, name)
    end
})

-- disable create unexpected global variable
function cc.disable_global()
    setmetatable(__g, {
        __newindex = function(_, name, value)
            error(string.format("USE \" cc.exports.%s = value \" INSTEAD OF SET GLOBAL VARIABLE", name), 0)
        end
    })
end
