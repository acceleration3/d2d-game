#define DEBUG_MODE

#include "GameWindow.h"

int main(int argc, char* argv[])
{
	#ifndef DEBUG_MODE
		FreeConsole();
	#endif

		int height = 600;
		int width = 800;

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
			system("pause");
		}

	return 0;
}