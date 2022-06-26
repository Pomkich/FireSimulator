#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "UIButton.h"
#include <vector>
#include "Cell.h"
#include "Calculating.h"
#include <iostream>

enum class EditState {
	fire, water, empty, forest
};

class UIWindow
{
private:
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;
	std::vector<std::vector<sf::RectangleShape>> rectangles;
	std::vector<std::pair<int, int>> fire_points;
	EditState state; 
	bool simulating;

	sf::RenderWindow render_window;
	std::vector<UIButton> buttons;

public:
	UIWindow(int width, int height);
	void AddButton(UIButton new_button);
	void StartSimulation();
	void SetEditState(EditState st);
	void Run();

private:
	void HandleInput(sf::Event evnt);

	friend class UIButton;
};