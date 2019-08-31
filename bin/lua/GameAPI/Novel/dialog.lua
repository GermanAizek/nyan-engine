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
-- @number text size
-- @string path to texture
-- @string path to texture
Dialog.width = ScrW() * 0.1 or nil
Dialog.height = ScrH() * 0.74 or nil
Dialog.sizeFont = 38 or nil
Dialog.bodyDialog = "content/textures/ui/dialogue_body.png" or nil
Dialog.headerDialog = "content/textures/ui/dialogue_header.png" or nil

--- setText Sets custom text to body of the dialog.
-- @param text to display
-- @return boolean flag
function Dialog.setText(text)
	draw.DrawText(text, Dialog.sizeFont, Dialog.width, Dialog.height)
end

--- setText Sets custom text to header of the dialog.
-- @param text to display
-- @return boolean flag
function Dialog.setHeader()
	
end

return Dialog