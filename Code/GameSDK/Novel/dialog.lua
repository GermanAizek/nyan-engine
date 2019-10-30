--[[
 * Copyright (C) Sense Games, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Herman Semenov <GermanAizek@sensegames.ru>, September 2019
]]--

local Render = require "render_functions"

--- A module that provides a ready-made template for creating a simple dialogue.
-- @module dialog
local Dialog = {}

--- Members dialog
-- @number dialog box x
-- @number dialog box y
-- @number dialog texture width
-- @number dialog texture height
-- @number text size
-- @string path to dialog body texture
-- @string path to dialog header texture
Dialog.x = ScrW() * 0.13 or nil
Dialog.y = ScrH() * 0.68 or nil
Dialog.sizeWidth = 1.0 or nil
Dialog.sizeHeight = 1.0 or nil
Dialog.nameFont = "content/fonts/arial.ttf" or nil
Dialog.sizeFont = 38 or nil
Dialog.bodyTexture = "content/textures/ui/dialogue_body.png" or nil
Dialog.headerTexture = "content/textures/ui/dialogue_header.png" or nil
Dialog.bodyText = nil
Dialog.headerText = nil

--- setText Set custom text to body of the dialog.
-- @param text to display
-- @return boolean flag
function Dialog.setText(text)
	Dialog.bodyText = text
end

--- setHeader Set custom text to header of the dialog.
-- @param text to display
-- @return boolean flag
function Dialog.setHeader(text)
	Dialog.headerText = text
end

--- show Render sprites body, header and texts.
-- @return boolean flag
function Dialog.show()
	Render.drawSprite(Dialog.bodyTexture, Dialog.x, Dialog.y, Dialog.sizeWidth, Dialog.sizeHeight)
	Render.drawSprite(Dialog.headerTexture, Dialog.x, Dialog.y, Dialog.sizeWidth, Dialog.sizeHeight)
	Render.drawText(text, Dialog.nameFont, Dialog.sizeFont, Dialog.x, Dialog.y)
	Render.drawText(text, Dialog.nameFont, Dialog.sizeFont, Dialog.x, Dialog.y)
end

return Dialog