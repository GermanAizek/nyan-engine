--[[
 * Copyright (C) Sense Games, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Herman Semenov <GermanAizek@sensegames.ru>, September 2019
]]--

--- A module providing functions for working with engine render.
-- @module engine
local Input = {}

function Input.isMouseDown(mouseKey)
	if mouseButtonPressed(mouseKey) then
		return true
	else
		return false
	end
end

function Input.isKeyDown(key)
	if keyboardButtonPressed(key) then
		return true
	else
		return false
	end
end

function Input.isButtonDown(buttonKey)
	if gamepadButtonPressed(buttonKey) then
		return true
	else
		return false
	end
end

return Input