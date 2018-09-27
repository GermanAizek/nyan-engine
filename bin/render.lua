--SetBackground("content//textures//1.gif")
SetBackground("content//textures//null.jpg")
for i = 0, 50 do
	CreatePerson("content//textures//1.gif", 0 + i^1.5, 0 + i*12)
	CreatePerson("content//textures//1.gif", 1200 - i^1.5, 0 + i*12)
end
--Write(path)
--SetColorSpace(0.9,0.5,0.7,1.0)
--Write(1,2,3,4)
--СreatePerson("content/textures/1.gif")
--CreateBox("content/textures/1.jpg",100,100,1,1)
--CreateBox("content/textures/1.jpg",10,10,100,100)
