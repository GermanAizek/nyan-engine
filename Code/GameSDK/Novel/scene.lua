--[[
 * Copyright (C) Sense Games, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Herman Semenov <GermanAizek@sensegames.ru>, September 2019
]]--

local Input = require "input_functions"
local Render = require "render_functions"

local Scene = {}

Scene.width = 0 or nil
Scene.height = 0 or nil
Scene.sizeWidth = 1.0 or nil
Scene.sizeHeight = 1.0 or nil
Scene.startIndexSlide = 1 or nil
Scene.slides = {} or nil
Scene.countSlides = 0 or nil

function Scene.scaleFullscreen(texture)
	local scaleX, scaleY = Render.CalcScaleTextureForFullscreen(texture)
	Scene.sizeWidth = scaleX
	Scene.sizeHeight = scaleY
end

function Scene.addSlideByName(sceneName, sceneTexture)
	Scene.slides[sceneName] = sceneTexture
	Scene.countSlides = Scene.countSlides + 1
	
	if Scene.slides[sceneName] ~= nil then
		return true
	else
		return false
	end
end

function Scene.addSlideById(id, sceneTexture)
	Scene.slides[id] = sceneTexture
	Scene.countSlides = Scene.countSlides + 1
	
	if Scene.slides[id] ~= nil then
		return true
	else
		return false
	end
end

function Scene.showNext()
	if Scene.startIndexSlide < Scene.countSlides then
		Scene.startIndexSlide = Scene.startIndexSlide + 1
		local texture = Scene.slides[Scene.startIndexSlide]
		Scene.scaleFullscreen(texture)
		Render.drawSprite(texture, Scene.width, Scene.height, Scene.sizeWidth, Scene.sizeHeight)
		return true
	else
		return false
	end
end

function Scene.showPrev()
	if Scene.startIndexSlide > 1 then
		Scene.startIndexSlide = Scene.startIndexSlide - 1
		local texture = Scene.slides[Scene.startIndexSlide]
		Scene.scaleFullscreen(texture)
		Render.drawSprite(texture, Scene.width, Scene.height, Scene.sizeWidth, Scene.sizeHeight)
		return true
	else
		return false
	end
end

function Scene.show()
	local texture = Scene.slides[Scene.startIndexSlide]
	Scene.scaleFullscreen(texture)
	Render.drawSprite(texture, Scene.width, Scene.height, Scene.sizeWidth, Scene.sizeHeight)
end

function Scene.showByName(sceneName)
	local texture = Scene.slides[Scene.startIndexSlide]
	Scene.scaleFullscreen(texture)
	Render.drawSprite(texture, Scene.width, Scene.height, Scene.sizeWidth, Scene.sizeHeight)
end

return Scene