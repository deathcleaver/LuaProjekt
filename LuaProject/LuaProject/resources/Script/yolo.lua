
keyTable = {}

player = {}

function init()
    keyTable['w'] = false
    keyTable['a'] = false
    keyTable['s'] = false
    keyTable['d'] = false
    keyTable[13] = false -- enter key
    
    player['x'] = 400
    player['y'] = 400
    
    player['lastX'] = 0
    player['lastY'] = 0
    
	player['speedY'] = 0;
	player['speedX'] = 0;
	
	player['accX'] = 1;
	player['fricX'] = 0.5;
	player['jump'] = -20;
	player['grounded'] = false;
	
	player['grav'] = 1;
    
    player['camPos'] = 400;
    
    player['editState'] = false
	
end

function toggleEditState()

    player['editState'] = not player['editState']

end

function getPlayerPos()

    return player['x'], player['y']
end

function getCampos()
    return player['camPos']
end

function setKeyState(key, state)
    keyTable[key] = state
end

function collisionX(collider, bonus)

    if collider == 51 then
        print("collision X")
        player['x'] = player['lastX']
		player['speedX'] = 0;
    end
    
    if(player['x'] < 10) then
        player['x'] = player['lastX']
        player['speedX'] = 0;
    end
    
    if(player['x'] > 775) then
        player['x'] = player['lastX']
        player['speedX'] = 0;
    end
    
end

function collisionY(collider, bonus)

    if collider == 51 then
        print("collision Y")
        player['y'] = player['lastY']
		player['speedY'] = 0;
    end
    
end

function update()

    if not player['editState'] then
        updateY()
        collider, bonus = checkCollision(player['x'], player['y'])
        collisionY(collider, bonus)

        updateX()
        collider, bonus = checkCollision(player['x'], player['y'])
        collisionX(collider, bonus)
        player['camPos'] = player['camPos'] + 1
    else
    
        if keyTable['w'] then
            player['camPos'] = player['camPos'] - 3
            --print("w down")
        end
        
        if keyTable['s'] then
            player['camPos'] = player['camPos'] + 3
            --print("s down")
        end
    end
    
end


function updateX()

    player['lastX'] = player['x']

	if player['speedX'] > 0.01 then
		 player['speedX'] = player['speedX'] - player['fricX'];
	end
	
	if player['speedX'] < -0.01 then
		 player['speedX'] = player['speedX'] + player['fricX'];
	end
	
    if keyTable['a'] then
         player['speedX'] = player['speedX'] - player['accX'];
        --print("a down")
    end
    
    if keyTable['d'] then
        player['speedX'] = player['speedX'] + player['accX'];
        --print("d down")
    end
   
   player['x'] = player['x'] + player['speedX'];
    
end


function updateY()

    player['lastY'] = player['y']

	player['speedY'] = player['speedY'] + player['grav'];
	
    if keyTable['w'] then
        player['speedY'] = player['jump']
        --print("w down")
    end
    
    if keyTable['s'] then
        player['y'] = player['y'] + 2
        --print("s down")
    end
    
   
    player['y'] = player['y'] + player['speedY'];
    
end
