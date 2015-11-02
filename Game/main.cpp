#define DEBUG_MODE

#include "enet/enet.h"
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

		GameWindow* window = new GameWindow(height, width);

		if (enet_initialize() == 0)
			printf("ENet initialized successful.\n");
		else
			printf("ENet failed to initialize.\n");

		if (window->InitDirectX())
		{
			printf("Game initialization successful. Starting game loop.\n");
			window->GameLoop();
		}
		else
		{
			printf("Game initialization failed.\n");
			window->Release();
#ifdef DEBUG_MODE
			system("pause");
#endif
		}
		
		delete window;

		enet_deinitialize();

	return 0;
}