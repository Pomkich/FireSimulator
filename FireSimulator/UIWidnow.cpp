#include "UIWidnow.h"

UIWindow::UIWindow(int width, int height) {
	render_window.create(sf::VideoMode(width, height), "simulator");
}

void UIWindow::HandleInput(sf::Event evnt) {
	for (auto& button : buttons) {
		button.HandleInput(evnt);
	}
}

void UIWindow::Run() {
	while (render_window.isOpen()) {
		sf::Event evnt;
		while (render_window.pollEvent(evnt)) {
			HandleInput(evnt);
			if (evnt.type == sf::Event::Closed) {
				render_window.close();
			}
		}
		render_window.clear(sf::Color::White);
		render_window.display();
	}
}