#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "UIButton.h"

class UIWindow
{
private:
	sf::RenderWindow render_window;
	std::vector<UIButton> buttons;	// button class

public:
	UIWindow(int width, int height);
	void AddButton(UIButton new_button);
	void Run();

private:
	void HandleInput(sf::Event evnt);

	friend class UIButton;
};