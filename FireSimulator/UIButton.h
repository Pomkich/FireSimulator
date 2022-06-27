#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

class UIWindow;	// forward declaration

class UIButton
{
private:
	sf::RectangleShape rect;
	std::weak_ptr<UIWindow> window_ptr;
	void (*input_handler)(sf::Event, std::weak_ptr<UIWindow>);

public:
	UIButton(std::shared_ptr<UIWindow> w_ptr);
	void SetSize(int width, int height);
	void SetPos(int x, int y);
	void SetColor(sf::Color color);
	void SetInputHandler(void (*inp_hndl)(sf::Event, std::weak_ptr<UIWindow>));

	sf::RectangleShape& GetRect();

private:
	void HandleInput(sf::Event evnt);

	friend class UIWindow;
};

