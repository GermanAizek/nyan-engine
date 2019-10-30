_G.i = 1

backgrounds = {
	"content/textures/back_1.jpg",
	"content/textures/back_2.jpg",
	"content/textures/back_3.jpg",
	"content/textures/back_4.png",
	"content/textures/back_5.png",
	"content/textures/back_6.jpg",
	"content/textures/back_7.jpg",
}

CreateRecorder(5)
CurTime()

--print("_G TABLE = " .. _G.i)

function init()
	--EmitMusic("content/sounds/music_intro.ogg")--, {0, 0, 0})
	--print(EmitSound("content/sounds/battle.wav", {0, 3, 3}))

	Msg("Running init.lua")

	--draw.DrawBackground("content/textures/back_1.jpg")
end

init()