_G.table = _G.table or {}

function table.deep_copy(obj, seen) -- http://stackoverflow.com/questions/640642/how-do-you-copy-a-lua-table-by-value
  if type(obj) ~= 'table' then return obj end
  if seen and seen[obj] then return seen[obj] end
  local s = seen or {}
  local res = setmetatable({}, getmetatable(obj))
  s[obj] = res
  for k, v in pairs(obj) do res[copy(k, s)] = copy(v, s) end
  return res
end

function table.merge(pOne, pTwo, pReplace)
	if pReplace == nil then pReplace = true end
	for key, value in pairs(pTwo) do
		if not pReplace or pOne[key] == nil then
			pOne[key] = pTwo[key]
		end
	end
end

-- http://stackoverflow.com/questions/9168058/how-to-dump-a-table-to-console
function table.print(node)
    local function tab(amt)
        local str = ""
        for i = 1, amt do
            str = str .. "\t"
        end
        return str
    end

    local cache, stack, output = {}, {}, {}
    local depth = 1
    local output_str = "{\n"

    while true do
        local size = 0
        for _, v in pairs(node) do
            size = size + 1
        end

        local cur_index = 1
        for k, v in pairs(node) do
            if cache[node] == nil or cur_index >= cache[node] then

                if string.find(output_str, "}", output_str:len()) then
                    output_str = output_str .. ",\n"
                elseif not string.find(output_str, "\n", output_str:len()) then
                    output_str = output_str .. "\n"
                end

                table.insert(output, output_str)
                output_str = ""

                local key
                if type(k) == "number" or type(k) == "boolean" then
                    key = "["..tostring(k).."]"
                else
                    key = "['"..tostring(k).."']"
                end

                if type(v) == "number" or type(v) == "boolean" then
                    output_str = output_str .. tab(depth) .. key .. " = "..tostring(v)
                elseif type(v) == "table" then
                    output_str = output_str .. tab(depth) .. key .. " = {\n"
                    table.insert(stack,node)
                    table.insert(stack,v)
                    cache[node] = cur_index+1
                    break
                else
                    output_str = output_str .. tab(depth) .. key .. " = '"..tostring(v).."'"
                end

                if cur_index == size then
                    output_str = output_str .. "\n" .. tab(depth-1) .. "}"
                else
                    output_str = output_str .. ","
                end
            else
                if cur_index == size then
                    output_str = output_str .. "\n" .. tab(depth-1) .. "}"
                end
            end

            cur_index = cur_index + 1
        end

        if size == 0 then
            output_str = output_str .. "\n" .. tab(depth-1) .. "}"
        end

        if #stack > 0 then
            node = stack[#stack]
            stack[#stack] = nil
            depth = cache[node] == nil and depth + 1 or depth - 1
        else
            break
        end
    end

    table.insert(output, output_str)
    output_str = table.concat(output)

    print(output_str)
end

function table.count(pTable)
	local count = 0
	for _,_ in pairs(pTable) do
		count = count + 1
	end
	
	return count
end

function sorted_pairs(pTable, pOrder)
	local keys = {}
	for k in pairs(pTable) do table.insert(keys, k) end
	
	if pOrder then
		table.sort(keys, function(pA, pB) return pOrder(pTable, pA, pB) end)
	else
		table.sort(keys)
	end
	
	local i = 0
	return function() -- Iterator function.
		i = i + 1
		if keys[i] then
			return keys[i], pTable[keys[i]]
		end
	end
end                                                                                                                                    