include("Scripts/Libraries/Table.lua")

_G.hook = _G.hook or {}
_G.hook.hooks = {}

function hook.Add(pHook, pIdentifier, pCallback, pPriority)
	-- Throw error if pIdentifier was forgot.
	if type(pIdentifier) == "function" then
		error("\"pIdentifier\" argument #2 was a function in call to \"hook.Add\". (Possibly forgot to specify an identifier?)")
		return
	end
	
	if not hook.hooks[pHook] then hook.hooks[pHook] = {} end
	hook.hooks[pHook][pIdentifier] = {
		callback = pCallback,
		priority = pPriority or 0
	}
	table.sort(hook.hooks[pHook], function(a, b) return a.priority > b.priority end)
end

function hook.Remove(pHook, pIdentifier)
	hook.hooks[pHook][pIdentifier] = nil
	if table.count(hook.hooks[pHook]) == 0 then
		hook.hooks[pHook] = nil
	else
		table.sort(hook.hooks[pHook], function(a, b) return a.priority > b.priority end)
	end
end
                            