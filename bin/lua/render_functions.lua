--[[
 * Copyright (C) Sense Games, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Herman Semenov <GermanAizek@sensegames.ru>, September 2019
]]--

--- A module providing functions for working with engine render.
-- @module engine
local Render = {}

function Render.drawText(text, font, size, x, y)
	createText(text, font, size, x, y)
end

function Render.drawSprite(texture, width, height, sizeX, sizeY)
	createSprite(texture, width, height, sizeX, sizeY)
end

function Render.setCursor(cursorKey)
	changeCursor(cursorKey)
end

function Render.CalcScaleTextureForFullscreen(texture)
	return GetScaleTextureFullscreen(texture)
end

return Render