#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

class UIWindow;	// forward declaration

class UIButton
{
private:
	sf::RectangleShape rect;
	sf::Text title;
	std::weak_ptr<UIWindow> window_ptr;
	void (*input_handler)(sf::Event);

public:
	UIButton(std::shared_ptr<UIWindow> w_ptr);
	void SetSize(int width, int height);
	void SetPos(int x, int y);
	void SetColor(sf::Color color);
	void SetTitle(std::string str);
	void SetInputHandler(void (*inp_hndl)(sf::Event));

	sf::RectangleShape& GetRect();
	sf::Text& GetTitle();

private:
	void HandleInput(sf::Event evnt);

	friend class UIWindow;
};

