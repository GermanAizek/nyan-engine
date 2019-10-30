--[[
 * Copyright (C) Sense Games, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Herman Semenov <GermanAizek@sensegames.ru>, September 2019
]]--

local Render = require "render_functions"
local Vector = require 'vector'

--- A module that provides a ready-made template for creating a simple actor.
-- @module actor
local Actor = {}

--- Members actor
-- @number actor width
-- @number actor height
-- @number actor texture width
-- @number actor texture height
-- @string path to texture
-- @string path to texture
Actor.width = ScrW() or nil
Actor.height = ScrH() * 0.25 or nil
Actor.sizeWidth = 1.0 or nil
Actor.sizeHeight = 1.0 or nil
Actor.bodyTexture = "content/textures/ui/dialogue_body.png" or nil
Actor.headTexture = "content/textures/ui/dialogue_header.png" or nil
Actor.bodyPos = Vector(0, 0)
Actor.headPos = Vector(0, 0)
Actor.emotions = {} or nil
Actor.actions = {} or nil

--- addEmotion
-- @param emotionName
-- @param emotionTexture
-- @return boolean flag
function Actor.addEmotion(emotionName, emotionTexture)
	emotions[emotionName] = emotionTexture
	
	if emotions[emotionName] ~= nil then
		return true
	else
		return false
	end
end

--- setEmotion
-- @param emotionName
-- @return boolean flag
function Actor.setEmotion(emotionName)
	Render.drawSprite(Dialog.headTexture, Dialog.width, Dialog.height, Dialog.sizeWidth, Dialog.sizeHeight)
end

--- show Render sprite body of the dialog.
-- @param text to display
-- @return boolean flag
function Dialog.show()
	Render.drawSprite(Dialog.bodyTexture, Dialog.width, Dialog.height, Dialog.sizeWidth, Dialog.sizeHeight)
	Render.drawSprite(Dialog.headTexture, Dialog.width, Dialog.height, Dialog.sizeWidth, Dialog.sizeHeight)
end

return Dialog