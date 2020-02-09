--[[
  Global scheduler. This is Not auto loaded module, use following code to load.
  example:
  local scheduler = require(cc.PACKAGE_NAME .. ".scheduler")
]]--

local scheduler = {}

local sharedScheduler = cc.Director:getInstance():getScheduler()

--[[
  Global frame event scheduler, need manually call scheduler.unscheduleGlobal() to stop scheduler.
  @function scheduleUpdateGlobal
  @param function listener
  @return handler
]]--
function scheduler.scheduleUpdateGlobal(listener)
    return sharedScheduler:scheduleScriptFunc(listener, 0, false)
end

--[[
  Global scheduler with interval, need manually call scheduler.unscheduleGlobal() to stop scheduler.
  @function scheduleGlobal
  @param function listener
  @param integer interval
  @return handler
]]--
function scheduler.scheduleGlobal(listener, interval)
    return sharedScheduler:scheduleScriptFunc(listener, interval, false)
end

--[[
  Stop a global scheduler.
  @function unscheduleGlobal
  @param function handler
]]--
function scheduler.unscheduleGlobal(handle)
    sharedScheduler:unscheduleScriptEntry(handle)
end

--[[
  Start a delay call by Global scheduler, NO need do stop manually,
  but can cancel before timeout by scheduler.unscheduleGlobal().
  @function scheduleGlobal
  @param function listener
  @param integer interval
  @return handler
]]--
function scheduler.performWithDelayGlobal(listener, time)
    local handle
    handle = sharedScheduler:scheduleScriptFunc(function()
        scheduler.unscheduleGlobal(handle)
        listener()
    end, time, false)
    return handle
end

return scheduler
