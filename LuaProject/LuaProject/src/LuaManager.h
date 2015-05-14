#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include "lua.hpp"
#include <string>
#include "Map.h"

class LuaManager
{

public:

	LuaManager();
	~LuaManager();

	void load(std::string fileName);

	void setKeyState(char key, bool state);

	void getPos(float &x, float &y);

	bool toggleEditState();
	void togglePauseState();

	void getCamPos(float &y);

	void sendCollison(int collider, int bonus, bool Y);

	void update();

	void updateX();
	void updateY();

	static Map* map;

private:

	lua_State* l;
	
};

#endif