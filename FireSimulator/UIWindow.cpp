#include "UIWindow.h"

using namespace std;

UIWindow::UIWindow(int width, int height) {
	render_window.create(sf::VideoMode(width, height), "simulator");
	state = EditState::fire;
	simulating = false;
	radius = 10;
	wind_speed = 0;
	wind_angle = 0;
	
	// инициализация клеток
	tiles.resize(Constants::mesh_size);
	for (int i = 0; i < Constants::mesh_size; i++) {
		tiles[i].resize(Constants::mesh_size);
		for (int j = 0; j < Constants::mesh_size; j++) {
			tiles[i][j] = make_shared<Cell>(Tile::forest);
			tiles[i][j]->wind_angle = 0;
			tiles[i][j]->wind_speed = 0;
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
	// обработка нажатий на сетку
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		const int rect_size = render_window.getSize().x / Constants::mesh_size;
		int x = sf::Mouse::getPosition(render_window).x / rect_size;
		int y = sf::Mouse::getPosition(render_window).y / rect_size - 50;

		if (y > -1) {
			int x_min = (x - radius > 0) ? x - radius : 0;
			int x_max = (x + radius < Constants::mesh_size) ? x + radius : Constants::mesh_size;
			int y_min = (y - radius > 0) ? y - radius : 0;
			int y_max = (y + radius < Constants::mesh_size) ? y + radius : Constants::mesh_size;

			BurnState st = BurnState::not_burned;
			sf::Color clr;
			Tile tl;

			switch (state) {
			case EditState::fire:
				st = BurnState::on_fire;
				clr = sf::Color::Red;
				break;
			case EditState::empty:
				st = BurnState::not_burned;
				tl = Tile::empty;
				clr = sf::Color::White;
				break;
			case EditState::water:
				st = BurnState::not_burned;
				tl = Tile::water;
				clr = sf::Color::Blue;
				break;
			case EditState::forest:
				st = BurnState::not_burned;
				tl = Tile::forest;
				clr = sf::Color::Green;
				break;
			}

			// когда определено состояние, изменяем клетки в радиусе окружности
			for (int i = x_min; i < x_max; i++) {
				for (int j = y_min; j < y_max; j++) {
					if (((i - x) * (i - x)) + ((j - y) * (j - y)) < (radius * radius)) {
						tiles[j][i]->state = st;
						rectangles[i][j].setFillColor(clr);
						if (st != BurnState::on_fire) {
							tiles[j][i]->type = tl;
						}
					}
				}
			}
		}
	}
	
	// обработка нажатий на кнопку
	for (auto& button : buttons) {
		button.HandleInput(evnt);
	}
}

void UIWindow::StartSimulation() {
	if (simulating == true) {
		simulating = false;
	}
	else {
		simulating = true;
	}
}

void UIWindow::SetEditState(EditState st) {
	state = st;
}

void UIWindow::ChangeWindAngle(int angle) {
	wind_angle += angle;
	cout << wind_angle << endl;
	for (int i = 0; i < Constants::mesh_size; i++) {
		for (int j = 0; j < Constants::mesh_size; j++) {
			tiles[i][j]->wind_angle = wind_angle;
		}
	}
}

void UIWindow::ChangeWindSpeed(int speed) {
	wind_speed += speed;
	cout << wind_speed << endl;
	for (int i = 0; i < Constants::mesh_size; i++) {
		for (int j = 0; j < Constants::mesh_size; j++) {
			tiles[i][j]->wind_speed = wind_speed;
		}
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