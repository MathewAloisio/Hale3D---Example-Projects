_G.concommand = _G.concommand or {}
_G.concommand.commands = {}

function concommand.Register(pName, pCallback)
	concommand.commands[pName] = pCallback
end

function concommand.Execute(pName, ...)
	local args = {...}
	Console.ExecuteCommand(pName .. ' ' .. table.concat(args, ' '))
end
           