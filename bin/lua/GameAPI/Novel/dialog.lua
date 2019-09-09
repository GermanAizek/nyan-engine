--[[
 * Copyright (C) Sense Games, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Herman Semenov <GermanAizek@sensegames.ru>, September 2019
]]--

--- A module that provides a ready-made template for creating a simple dialogue.
-- @module dialog
local Dialog = {}

--- Members dialog
-- @number dialog box width
-- @number dialog box height
-- @number dialog texture width
-- @number dialog texture height
-- @number text size
-- @string path to dialog body texture
-- @string path to dialog header texture
Dialog.width = ScrW() or nil
Dialog.height = ScrH() * 0.25 or nil
Dialog.sizeWidth = 1.0 or nil
Dialog.sizeHeight = 1.0 or nil
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
	render.DrawSprite(Dialog.bodyTexture, Dialog.width, Dialog.height, Dialog.sizeWidth, Dialog.sizeHeight)
	render.DrawSprite(Dialog.headerTexture, Dialog.width, Dialog.height, Dialog.sizeWidth, Dialog.sizeHeight)
	draw.DrawText(text, Dialog.sizeFont, Dialog.width, Dialog.height)
	draw.DrawText(text, Dialog.sizeFont, Dialog.width, Dialog.height)
end

return Dialog