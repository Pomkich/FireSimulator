#include "UIWindow.h"

using namespace std;

UIWindow::UIWindow(int width, int height) {
	render_window.create(sf::VideoMode(width, height), "simulator");
	simulating = false;
	// инициализация клеток
	tiles.resize(Constants::mesh_size);
	for (int i = 0; i < Constants::mesh_size; i++) {
		tiles[i].resize(Constants::mesh_size);
		for (int j = 0; j < Constants::mesh_size; j++) {
			tiles[i][j] = make_shared<Cell>(Tile::forest);
			tiles[i][j]->wind_angle = 45;
			tiles[i][j]->wind_speed = 5;
		}
	}

	// инициализация графических элементов, представляющих клетки
	rectangles.resize(Constants::mesh_size);
	const int rect_size = render_window.getSize().x / Constants::mesh_size;
	for (int i = 0; i < Constants::mesh_size; i++) {
		rectangles[i].resize(Constants::mesh_size);
		for (int j = 0; j < Constants::mesh_size; j++) {
			rectangles[i][j].setPosition(i * rect_size, j * rect_size + 100);
			rectangles[i][j].setFillColor(sf::Color::Green);
			rectangles[i][j].setSize(sf::Vector2f(rect_size, rect_size));
		}
	}
}

void UIWindow::HandleInput(sf::Event evnt) {
	if (evnt.type == sf::Event::MouseButtonPressed) {
		const int rect_size = render_window.getSize().x / Constants::mesh_size;
		int x = sf::Mouse::getPosition(render_window).x / rect_size;
		int y = sf::Mouse::getPosition(render_window).y / rect_size - 50;
		if (y > -1) {
			tiles[y][x]->state = BurnState::on_fire;
			rectangles[x][y].setFillColor(sf::Color::Red);
		}
	}
	

	for (auto& button : buttons) {
		button.HandleInput(evnt);
	}
}

void UIWindow::StartSimulation() {
	simulating = true;
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
		for (int i = 0; i < Constants::mesh_size; i++) {
			for (int j = 0; j < Constants::mesh_size; j++) {
				render_window.draw(rectangles[i][j]);
			}
		}

		render_window.display();

		if (simulating) {
			// раскрашиваем клетки в зависимости от их состояния
			for (int y = 0; y < Constants::mesh_size; y++) {
				for (int x = 0; x < Constants::mesh_size; x++) {
					if (tiles[y][x]->state == BurnState::on_fire) {
						rectangles[x][y].setFillColor(sf::Color::Red);
					}
					else if (tiles[y][x]->state == BurnState::burned) {
						rectangles[x][y].setFillColor(sf::Color::Black);
					}
				}
			}

			// собираем список клеток, для которых нужно вычислить площадь горения
			// и помечаем их как сгоревшие
			for (int y = 0; y < Constants::mesh_size; y++) {
				for (int x = 0; x < Constants::mesh_size; x++) {
					if (tiles[y][x]->state == BurnState::on_fire) {
						fire_points.push_back(make_pair(x, y));
						tiles[y][x]->state = BurnState::burned;
					}
				}
			}

			// вычисляем фигуры горения для точек
			for (auto& point : fire_points) {
				calculateFront(tiles, point.first, point.second);
			}
		}
	}
}

void UIWindow::AddButton(UIButton new_button) {
	buttons.push_back(new_button);
}