
function tolua.cloneTable(src)
	if type(src)~="table" then
		return nil
	end

	local dest = {}
    for k, v in pairs(src) do
        dest[k] = v
    end

    local mt = getmetatable(src)
    if mt then
	    setmetatable(dest, mt)
    end

    return dest
end

function tolua.fullgc(classes)
    collectgarbage("collect")

    if type(classes) == "string" then
        classes = {classes}
    else
        classes = {}
    end

    local o = tolua.getregval("tolua_gc")
    local t = tolua.cloneTable(o)
    if t then
	    tolua.setregval("tolua_gc", t)
    end

    for i,v in ipairs(classes) do
    	o =  tolua.getubox(v)
    	t = tolua.cloneTable(o)
    	if o then
    		tolua.setubox(v, t)
    	end
    end

    o = nil
    t = nil

    collectgarbage("collect")
end
