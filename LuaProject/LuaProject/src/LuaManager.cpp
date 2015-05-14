#include "LuaManager.h"
#include <iostream>

Map* LuaManager::map = NULL;

int collisionCheck(lua_State* l)
{

	Player p;

	float x, y;

	x = lua_tonumber(l, 1);
	y = lua_tonumber(l, 2);

	p.setPos(x, y);

	type collision = NONE;
	type boons = NONE;

	LuaManager::map->mapCollide(&p, &collision, &boons);

	lua_pushinteger(l, collision);
	lua_pushinteger(l, boons);
	
	return 2;
}


int resetMap(lua_State* l)
{
	LuaManager::map->mapReset();
	return 0;
}

LuaManager::LuaManager()
{
	l = luaL_newstate();
	luaL_openlibs(l);
}

LuaManager::~LuaManager()
{
	lua_close(l);
}

void LuaManager::load(std::string file)
{
	int error = luaL_loadfile(l, file.c_str()) || lua_pcall(l, 0, 0, 0);

	if (error)
	{
		std::cerr << "Unable to run : " << lua_tostring(l, -1);
		lua_pop(l, 1);
	}
	else
	{
		std::cout << "loaded script" << std::endl;
	}

	lua_getglobal(l, "init");
	lua_pcall(l, 0, 0, 0);


	lua_register(l, "checkCollision", collisionCheck);
	lua_register(l, "resetMap", resetMap);

}

void LuaManager::setKeyState(char key, bool state)
{
	lua_getglobal(l, "setKeyState");
	lua_pushstring(l, &key);
	lua_pushboolean(l, state);
	lua_pcall(l, 2, 0, 0);
}

bool LuaManager::toggleEditState()
{
	lua_getglobal(l, "toggleEditState");
	lua_pcall(l, 0, 1, 0);
	
	bool ret = lua_toboolean(l, 1);

	lua_pop(l, 1);

	return ret;
}

void LuaManager::togglePauseState()
{
	lua_getglobal(l, "togglePauseState");
	lua_pcall(l, 0, 0, 0);
}

void LuaManager::getPos(float &x, float &y)
{

	lua_getglobal(l, "getPlayerPos");
	lua_pcall(l, 0, 2, 0);
	
	x = lua_tonumber(l, 1);
	y = lua_tonumber(l, 2);

	lua_pop(l, 2);

}

void LuaManager::getCamPos(float &y)
{
	lua_getglobal(l, "getCampos");
	lua_pcall(l, 0, 1, 0);

	y = lua_tonumber(l, 1);

	lua_pop(l, 1);
}

void LuaManager::sendCollison(int collider, int bonus, bool Y)
{
	if (!Y)
		lua_getglobal(l, "collisionX");
	else
		lua_getglobal(l, "collisionY");
	
	lua_pushinteger(l, collider);
	lua_pushinteger(l, bonus);
	lua_pcall(l, 2, 0, 0);
}

void LuaManager::update()
{
	lua_getglobal(l, "update");
	lua_pcall(l, 0, 0, 0);
}

void LuaManager::updateX()
{
	lua_getglobal(l, "updateX");
	lua_pcall(l, 0, 0, 0);
}

void LuaManager::updateY()
{
	lua_getglobal(l, "updateY");
	lua_pcall(l, 0, 0, 0);
}