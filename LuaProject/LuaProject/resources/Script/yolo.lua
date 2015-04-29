
keyTable = {}

player = {}

function init()
    keyTable['w'] = false
    keyTable['a'] = false
    keyTable['s'] = false
    keyTable['d'] = false
    
    player['x'] = 400
    player['y'] = 400
    
end

function getPlayerPos()

    return player['x'], player['y']
end

function setKeyState(key, state)
    keyTable[key] = state
end

function update()

    if keyTable['w'] then
        player['y'] = player['y'] - 2
        --print("w down")
    end
   
    if keyTable['a'] then
        player['x'] = player['x'] - 2
        --print("a down")
    end
    
    if keyTable['s'] then
        player['y'] = player['y'] + 2
        --print("s down")
    end
    
    if keyTable['d'] then
    player['x'] = player['x'] + 2
        --print("d down")
    end
   
end