#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "UIButton.h"
#include <vector>
#include "Cell.h"
#include <iostream>

class UIWindow
{
private:
	const double pi = 3.14159265;
	const int mesh_size = 300;
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;
	std::vector<std::vector<sf::RectangleShape>> rectangles;

	sf::RenderWindow render_window;
	std::vector<UIButton> buttons;

public:
	UIWindow(int width, int height);
	void AddButton(UIButton new_button);
	void test();
	void Run();

private:
	void HandleInput(sf::Event evnt);

	friend class UIButton;
};