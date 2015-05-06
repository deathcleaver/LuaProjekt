
keyTable = {}

player = {}

function init()
    keyTable['w'] = false
    keyTable['a'] = false
    keyTable['s'] = false
    keyTable['d'] = false
    
    player['x'] = 400
    player['y'] = 400
    
    player['lastX'] = 0
    player['lastY'] = 0
    
end

function getPlayerPos()

    return player['x'], player['y']
end

function setKeyState(key, state)
    keyTable[key] = state
end

function collisionX(collider, bonus)

    if collider == 51 then
        print("collision X")
        player['x'] = player['lastX']
    end
    
    
    
end

function collisionY(collider, bonus)

    if collider == 51 then
        print("collision Y")
        player['y'] = player['lastY']
    end
    
end


function updateX()

    player['lastX'] = player['x']

    if keyTable['a'] then
        player['x'] = player['x'] - 2
        --print("a down")
    end
    
    if keyTable['d'] then
        player['x'] = player['x'] + 2
        --print("d down")
    end
   
    
end


function updateY()

    player['lastY'] = player['y']

    if keyTable['w'] then
        player['y'] = player['y'] - 4
        --print("w down")
    end
    
    if keyTable['s'] then
        player['y'] = player['y'] + 2
        --print("s down")
    end
    
   
    player['y'] = player['y'] + 2;
    
end
