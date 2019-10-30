--local init = require("init")

if input.IsMouseDown("MOUSE_LEFT") then
	if _G.i == 7 then
		_G.i = 1
		--exit()
	else
		draw.DrawBackground(backgrounds[_G.i])
		_G.i = _G.i + 1
		render.SetCursor("wait")
	end
	
	render.DrawSprite("content/textures/actor.png", (ScrW()*0.01 + (_G.i * 100)), ScrH()*0.1, 1.3, 1.3)
end

if input.IsMouseDown("MOUSE_RIGHT") then
	render.SetCursor("hand")
	exit()
end

if input.IsKeyDown("KEY_A") then
	render.DrawSprite("content/textures/actor.png", (ScrW()*0.65), ScrH()*0.1, 1.3, 1.3)
end

render.DrawSprite("content/textures/ui/dialogue.png", ScrW()*0.02, ScrH()*0.735, 2.2, 1.4)
--local text = draw.DrawText("Charlotte\nMother fucker uber engine.", "content/fonts/arialbd.ttf", 38, ScrW()*0.1, ScrH()*0.74)
--print(text)

--RunScript("init.lua")
-- print(CurTime())
-- print(SysTime())
