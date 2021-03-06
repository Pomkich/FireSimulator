#include "UIButton.h"
#include "UIWindow.h"

UIButton::UIButton(std::shared_ptr<UIWindow> w_ptr) {
	window_ptr = w_ptr;
	input_handler = nullptr;

	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Black);
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


void UIButton::SetInputHandler(void (*inp_hndl)(sf::Event, std::weak_ptr<UIWindow> window)) {
	input_handler = inp_hndl;
}

sf::RectangleShape& UIButton::GetRect() {
	return rect;
}

void UIButton::HandleInput(sf::Event evnt) {
	if (input_handler != nullptr) {

		if (evnt.type == sf::Event::MouseButtonPressed &&
			rect.getGlobalBounds().contains(
				static_cast<sf::Vector2f>(sf::Mouse::getPosition(
					window_ptr.lock()->render_window)))
			)
		{
			input_handler(evnt, window_ptr);
		}
	}
}

