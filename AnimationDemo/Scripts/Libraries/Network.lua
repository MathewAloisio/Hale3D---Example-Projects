_G.network = _G.network or {}
_G.network.handlers = {}

function network.RegisterHandler(pName, pCallback)
	network.handlers[pName] = pCallback
end

--Network variables--
_G.netvars = _G.netvars or {}
function netvars.Register(pName)
	Message:Register(("_nv_%s"):format(pName))
end

local net_vars = {} -- TODO: me!
function netvars.SetString(pName, pValue)
	if type(pValue) ~= "string" then 
		return print(("\"netvars.SetString()\" string expected, got %s."):format(type(pValue))) 
	end
	local message = Message:new(("_nv_%s"):format(pName))
	message:WriteString(pValue)
end                    