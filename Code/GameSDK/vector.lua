--[[
 * Copyright (C) Sense Games, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Herman Semenov <GermanAizek@sensegames.ru>, September 2019
]]--

--- A module creates a 2D vector object.
-- @module vector
local Vector = {}
do
    local meta = {
        _metatable = "Private metatable",
        _DESCRIPTION = "Vectors in 2D"
    }

    meta.__index = meta

    function meta:__add( v )
        return Vector(self.i + v.i, self.j + v.j)
    end

    function meta:__mul( v )
        return self.i * v.i + self.j * v.j
    end

    function meta:__tostring()
        return ("<%g, %g>"):format(self.i, self.j)
    end

    function meta:magnitude()
        return math.sqrt( self * self )
    end

    setmetatable( Vector, {
        __call = function( V, i ,j ) return setmetatable( {i = i, j = j}, meta ) end
    } )
end

Vector.__index = Vector

return Vector