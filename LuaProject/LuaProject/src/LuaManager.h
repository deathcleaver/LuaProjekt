#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include "lua.hpp"
#include <string>

class LuaManager
{

public:

	LuaManager();
	~LuaManager();

	void load(std::string fileName);

	void setKeyState(char key, bool state);

	void getPos(float &x, float &y);

	void sendCollison(int collider, int bonus, bool Y);

	void updateX();
	void updateY();

private:

	lua_State* l;

};

#endif