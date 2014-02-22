local SkillDatabase = {}
package.loaded["SkillDatabase"] = SkillDatabase

function loadSkill( skill )
	skill.range = createRange(skill.rangeTable)
	SkillDatabase[skill.id] = skill
end

function createRange(rangeTable)
	if rangeTable == nil then return end
	local center
	local range = { { x = 0, y = 0 } }
	for i,row in ipairs(rangeTable) do
		for j,v in ipairs(row) do
			if v == 2 then
				center = {x = j, y = i}
			end
		end
	end
	for i,row in ipairs(rangeTable) do
		for j,v in ipairs(row) do
			if v == 1 then
				range[#range + 1] = 
				{x = j - center.x, y = i - center.y}
			end
		end
	end
	return range
end

loadSkill{
	id = 1,
	name = "ŭ������",
	maxtimes = 15,
	minDistance = 1,
	maxDistance = 1,
	-- no need for range
	damage = 40,
	property = "P",
	description = "��ŭ��֮��������ȭͷ�ͻ��Է�",
	-- animation = "overhead attack"
}

loadSkill{
	id = 2,
	name  = "��������",
	maxtimes = 10,
	minDistance = 0,
	maxDistance = 0,
	rangeTable = {
			{0, 1, 0},
			{1, 2, 1},
			{0, 1, 0}
		},
	damage = 50,
	property = "P",
	description = "������Χ�ĵ���",
	-- animation = "swipe and spin sword"
}

loadSkill{
	id = 3,
	name = "��������",
	maxtimes = "MAX",
	minDistance = 1,
	maxDistance = 1,
	damage = 10,
	property = "N",
	description = "������ͨ�Ĺ�������",
	-- animation = "punch and swipe sword"
}

return SkillDatabase