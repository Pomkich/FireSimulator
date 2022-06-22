#include "UIButton.h"

UIButton::UIButton(std::shared_ptr<UIWindow> w_ptr) {
	window_ptr = w_ptr;
	input_handler = nullptr;
}

void UIButton::SetSize(int width, int height) {
	rect.setSize(sf::Vector2f(width, height));
}

void UIButton::SetPos(int x, int y) {
	rect.setPosition(sf::Vector2f(x, y));
}

void UIButton::SetColor(sf::Color color) {
	rect.setFillColor(color);
}

void UIButton::SetTitle(std::string str) {
	title.setString(str);
}

void UIButton::SetInputHandler(void (*inp_hndl)(sf::Event)) {
	input_handler = inp_hndl;
}

sf::RectangleShape& UIButton::GetRect() {
	return rect;
}

sf::Text& UIButton::GetTitle() {
	return title;
}

void UIButton::HandleInput(sf::Event evnt) {
	if (input_handler != nullptr) {
		input_handler(evnt);
	}
}

