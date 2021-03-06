import("Scripts/Libraries/Class.lua")

-- A FIFO container.

local META = {}

function META:__init()
	self._first = 0
	self._last = -1
	self._list = {}
end

function META:push(pValue)
	local last = self._last + 1
	self._last = last
	self._list[last] = pValue
end

function META:pop()
	if self._first > self._last then error("Failed to \"pop\". Queue is empty.") end
	local value = self._list[self._first]
	self._list[self._first] = nil
	self._first = self._first + 1
	
	return value
end

function META:empty()
	return #self._list == 0 and true or false
end

class.Register("Queue", META)                               