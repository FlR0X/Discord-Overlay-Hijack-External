#include "includes.hpp"
#include "overlay.hpp"
#include "menu.hpp"

//This just takes over the new Discord overlay, which is a fullscreen and topmost app.By doing this, we avoid any
//overlay flags since we aren't resizing our own window or setting it to topmost since Discord does that already.
//Plus, since it's signed and trusted by all the major anti-cheats, it stays flag-free.
//Heavily based on https://github.com/leoiwnl/MedalDX9ImGuiOverlay

int main()
{
	// Took Wallpaper engine as an example because i cba to open up Rust or FN rn it works for any application where the NEW discord overlay is injected
	HWND game = FindWindowA("WPEUI", "Wallpaper UI"); // ClassName (the first thing) and the WindowTitle (second thing) can both be found using WinLister

	while (!game)
	{
		std::cout << "Waiting for game..." << std::endl;
		game = FindWindowA("WPEUI", "Wallpaper UI");  // ClassName (the first thing) and the WindowTitle (second thing) can both be found using WinLister
	}

	std::cout << "Game found!" << std::endl;
	Sleep(3000);

	HWND DiscordOverlay = FindWindowA("Chrome_WidgetWin_1", "Discord Overlay");  // Check for Overlay - DO NOT CHANGE THIS
	while (!DiscordOverlay)
	{
		std::cout << "Waiting for Discord Overlay..." << std::endl;
		DiscordOverlay = FindWindowA("Chrome_WidgetWin_1", "Discord Overlay"); // Check for Overlay - DO NOT CHANGE THIS
	}

	std::cout << "Discord Overlay found!" << std::endl;
	Sleep(3000);
	
	if (!Overlay::Begin())
	{
		std::cerr << "Failed to start overlay." << std::endl;
		Sleep(3000);
		return 1;
	}

	std::cout << "Overlay started." << std::endl;
	Sleep(3000);

	while (Overlay::StartRender())
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			Menu::open = !Menu::open;

		if (Menu::open)
		{
			SetForegroundWindow(Overlay::hwnd);
			Menu::Draw();
		}

		Overlay::EndRender();

		if (GetAsyncKeyState(VK_DELETE))
			break;
	}

	Overlay::StartRender();
	Overlay::EndRender();
		
	Overlay::Destroy();
	std::cout << "Overlay destroyed." << std::endl;

	Sleep(2000);

	return 0;
}