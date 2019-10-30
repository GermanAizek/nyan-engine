local Input = require "input_functions"
local Render = require "render_functions"

if Input.isMouseDown("MOUSE_LEFT") then
	_MODULES.scene.showNext()
end
if Input.isKeyDown("KEY_A") then
	_MODULES.scene.showPrev()
end

if _MODULES.scene.startIndexSlide == 1 then
	Render.drawSprite("content/textures/actor.png", ScrW()*0.01, ScrH()*0.1, 1.3, 1.3)

	local dialog = require "GameAPI/Novel.dialog"
	-- dialog.setHeader("Саня")
	-- dialog.setText("Я в порядке.")
	dialog.show()
end
