#define DEBUG_MODE

#include "GameWindow.h"

int main(int argc, char* argv[])
{
		//Default resolution
		int height = 600;
		int width = 800;

#ifndef DEBUG_MODE
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

		if (argc >= 3)
		{
			width = atoi(argv[1]);
			height = atoi(argv[2]);
			printf("Using resolution: %ix%i.\n", width, height);
		}
		else
			printf("Using default resolution: %ix%i.\n", width, height);

		GameWindow window(height, width);

		if (window.InitDirectX())
		{
			printf("DirectDraw initialization successfull. Starting game loop.\n", width, height);
			window.GameLoop();
		}
		else
		{
			printf("DirectDraw initialization failed.\n", width, height);
		}

	return 0;
}