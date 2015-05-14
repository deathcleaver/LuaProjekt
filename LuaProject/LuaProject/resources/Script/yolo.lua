
keyTable = {}

player = {}

function init()
    keyTable['w'] = false
    keyTable['a'] = false
    keyTable['s'] = false
    keyTable['d'] = false
    keyTable[13] = false -- enter key
    
    player['x'] = 380
    player['y'] = 370
    
    player['lastX'] = 0
    player['lastY'] = 0
    
	player['speedY'] = 0;
	player['speedX'] = 0;
	
	player['accX'] = 1;
	player['fricX'] = 0.5;
	player['jump'] = -20;
	player['grounded'] = false;
	
	player['grav'] = 1;
    
    player['camPos'] = 0;
    
    player['timeBonusTimer'] = 0
    player['speedBonusTimer'] = 0
    
    player['camSpeed'] = 2
    
    player['editState'] = false
    player['pauseState'] = true
	
end

function toggleEditState()

    player['editState'] = not player['editState']
    
    if not player['editState'] then
        init()
    end
    
    return player['editState']
    
end

function togglePauseState()

    player['pauseState'] = not player['pauseState']
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

function activateTime()
    player['timeBonusTimer'] = 250
end

function activateSpeed()
    player['speedBonusTimer'] = 250
end

function collisionX(collider, bonus)

    if collider == 51 then
        print("collision X")
        player['x'] = player['lastX']
		player['speedX'] = 0;
    end
    
    if(bonus == 49) then
        activateSpeed()
    end
    
    if(bonus == 50) then
        activateTime()
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
		
		if player['lastY'] < player['y'] then
			player['grounded'] = true;
		end
        player['y'] = player['lastY']
		player['speedY'] = 0;
		
    end
    
    if(bonus == 49) then
        activateSpeed()
    end
    
    if(bonus == 50) then
        activateTime()
    end
    
    if collider == 52 then
        init()
        resetMap()
    end
    
    if player['y'] < player['camPos'] - 100 then
        init()
        resetMap()
    end
    
end

function update()

    if not player['editState'] and not player['pauseState'] then
        updateY()
        collider, bonus = checkCollision(player['x'], player['y'])
        collisionY(collider, bonus)

        updateX()
        collider, bonus = checkCollision(player['x'], player['y'])
        collisionX(collider, bonus)
        
        if player['y'] > player['camPos'] + 400 then
            player['camSpeed'] = 3
        else
            player['camSpeed'] = 2
        end
        
        if player['timeBonusTimer'] > 0 then
            player['camSpeed'] = 1
            player['timeBonusTimer'] = player['timeBonusTimer'] - 1
        end
        
        if player['speedBonusTimer'] > 0 then
            player['accX'] = 2
            player['speedBonusTimer'] = player['speedBonusTimer'] - 1
        else
            player['accX'] = 1
        end
        
        player['camPos'] = player['camPos'] + player['camSpeed']
    
    elseif player['editState'] then
    
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

	player['speedY'] = player['speedY'] + player['grav']
	
    if keyTable['w'] then
		if player['grounded'] then
			player['speedY'] = player['jump']
			player['grounded'] = false;
		end
    end
    
    if keyTable['s'] then
        player['y'] = player['y'] + 2
        --print("s down")
    end
    
   
    player['y'] = player['y'] + player['speedY']
    
end
