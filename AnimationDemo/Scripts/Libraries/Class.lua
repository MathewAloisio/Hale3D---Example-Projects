_G.class = _G.class or {}

-- Adapated from: http://lua-users.org/wiki/SimpleLuaClasses
-- Modifications by: Mathew Aloisio

local function weak_copy(pDst, pSrc)
	for key, value in pairs(pSrc) do
		if pDst[key] == nil then
			pDst[key] = pSrc[key]
		end
	end
end

local _class_array = {}
function class.Register(pClassname, pMeta, pBase)
	local c = pMeta -- class.
	if type(pBase) == "table" then
		weak_copy(c, pBase)
		c.__base = pBase
	elseif type(pBase) == "string" then
		if _class_array[pBase] ~= nil then
			weak_copy(c, _class_array[pBase])
			c.__base = _class_array[pBase]
		else 
			print(("Class \"%s\" could not inherit from non-existant base-class: \"%s\"."):format(pClassname, pBase))
		end
	end
	-- The class will be the metatable for all its objects,
	-- and they will look up their methods in it.
	c.__index = c

	-- Expose a constructor which can be called by <classname>(<args>)
	local mt = {}
	mt.__call = function(class_tbl, ...)
		local obj = {}
		setmetatable(obj, c)
		if class_tbl.__init then
			class_tbl.__init(obj, ...)
		else 
			-- Make sure that any stuff from the pBase class is initialized.
			if pBase and pBase.__init then
				pBase.__init(obj, ...)
			end
		end
		return obj
	end
	c.is_type = function(self, pClass)
		local m = getmetatable(self)
		while m do 
			if m == pClass then return true end
			m = m.__base
		end
		return false
	end
	_class_array[pClassname] = setmetatable(c, mt)
end

function class.Get(pClassname)
	return _class_array[pClassname]
end                                                           