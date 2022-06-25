#include "UIWindow.h"

using namespace std;

UIWindow::UIWindow(int width, int height) {
	render_window.create(sf::VideoMode(width, height), "simulator");

	// инициализация клеток
	tiles.resize(mesh_size);
	for (int i = 0; i < mesh_size; i++) {
		tiles[i].resize(mesh_size);
		for (int j = 0; j < mesh_size; j++) {
			tiles[i][j] = make_shared<Cell>(Tile::forest);
			tiles[i][j]->wind_angle = 45;
			tiles[i][j]->wind_speed = 4;
		}
	}

	// инициализация графических элементов, представляющих клетки
	rectangles.resize(mesh_size);
	const int rect_size = render_window.getSize().x / mesh_size;
	for (int i = 0; i < mesh_size; i++) {
		rectangles[i].resize(mesh_size);
		for (int j = 0; j < mesh_size; j++) {
			rectangles[i][j].setPosition(i * rect_size, j * rect_size + 100);
			rectangles[i][j].setFillColor(sf::Color::Green);
			rectangles[i][j].setSize(sf::Vector2f(rect_size, rect_size));
		}
	}
}

void UIWindow::HandleInput(sf::Event evnt) {
	for (auto& button : buttons) {
		button.HandleInput(evnt);
	}
}

void UIWindow::test() {
	std::cout << "ahahahah" << std::endl;
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

		// отрисовка кнопок
		for (auto& button : buttons) {
			render_window.draw(button.GetRect());
			render_window.draw(button.GetTitle());
		}

		// отрисовка клеток
		for (int i = 0; i < mesh_size; i++) {
			for (int j = 0; j < mesh_size; j++) {
				render_window.draw(rectangles[i][j]);
			}
		}

		render_window.display();
	}
}

void UIWindow::AddButton(UIButton new_button) {
	buttons.push_back(new_button);
}