#include "includes.hpp"

namespace Menu
{
	bool open = true;

	void Draw()
	{
		ImGui::SetWindowSize(ImVec2{ 700, 400 });
		ImGui::Begin("Firox Discord Overlay");
		ImGui::Text("Render using Discord Overlay!");
		// do menu stuff here
		ImGui::End();
	}
}