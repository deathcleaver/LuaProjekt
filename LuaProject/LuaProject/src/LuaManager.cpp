#include "LuaManager.h"
#include <iostream>

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

}

void LuaManager::setKeyState(char key, bool state)
{
	lua_getglobal(l, "setKeyState");
	lua_pushstring(l, &key);
	lua_pushboolean(l, state);
	lua_pcall(l, 2, 0, 0);
}

void LuaManager::getPos(float &x, float &y)
{

	lua_getglobal(l, "getPlayerPos");
	lua_pcall(l, 0, 2, 0);
	
	x = lua_tonumber(l, 1);
	y = lua_tonumber(l, 2);

	lua_pop(l, 2);

}

void LuaManager::update()
{
	lua_getglobal(l, "update");
	lua_pcall(l, 0, 0, 0);
}