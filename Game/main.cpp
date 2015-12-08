#include "stdafx.h"
#include "enet/enet.h"
#include "GameWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	//Default resolution
	int height = 600;
	int width = 800;

	std::wstring cmd(pCmdLine);
	std::vector<std::wstring> args;

	int last = 0;

	for (int i = 0; i < cmd.size(); i++)
	{
		if (cmd[i] == L' ')
		{
			args.push_back(std::wstring(cmd.begin() + last, cmd.begin() + i));
			last = i;
		}
		if (i == cmd.size() - 1)
		{
			args.push_back(std::wstring(cmd.begin() + last, cmd.end()));
		}
	}

	if (args.size() > 0)
	{
		if (args[0] == L"-debug")
		{
			FILE* fd;
			AllocConsole();
			freopen_s(&fd, "CONOUT$", "w", stdout);
		}

		if (args.size() == 3)
		{
			width = std::wcstol(args[1].c_str(), nullptr, 10);
			height = std::wcstol(args[2].c_str(), nullptr, 10);
		}
	}
	
	GameWindow* window = new GameWindow(height, width);
	
	wchar_t path[255];
	GetModuleFileNameW(hInstance, path, 255);
	
	std::wstring exepath(path);

	ContentLoader::gameFolder = exepath.substr(0, exepath.find_last_of('\\'));
	ContentLoader::bitmapFolder = ContentLoader::gameFolder + L"\\Resources\\img\\";

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
		system("pause");
	}
		
	delete window;

	enet_deinitialize();

	return 0;
}