#include <iostream>

#include "CG_GameEngine.h"

#include "XenonLevel.h"

using namespace std;

int main()
{
	MyGameEngine myEngine = MyGameEngine("Xenon", 640, 480);
	

	XenonLevel* level = new XenonLevel(&myEngine);

	myEngine.SetLevel(level);

	myEngine.EngineLoop();
}