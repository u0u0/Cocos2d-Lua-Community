
function tolua.cloneTable(src)
	if type(src) ~= "table" then
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

function tolua.fullgc()
	collectgarbage("collect")
end
