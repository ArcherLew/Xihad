-- for i=0, 9 do
-- 	io.write("{")
-- 	for j=0, 9 do
-- 		local tile = {
-- 			x = j,
-- 			y = i,
-- 			terrain = "ƽԭ"
-- 		}
-- 		if i % 2 == 0 then
-- 			tile.terrain = "ɽ��"
-- 		end
-- 		-- if j % 3 == 0 then
-- 		-- 	tile.terrain = "����"
-- 		-- end
-- 		io.write("\"" .. tile.terrain .. "\",")
-- 		-- self:createTile( tile )
-- 	end
-- 	io.write("}\n")
-- end	
local a = {4, 5, 1}
table.sort( a )
for i,v in ipairs(a) do
	print(i,v)
end