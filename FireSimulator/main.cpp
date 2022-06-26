#include <iostream>
#include <array>
#include <vector>
#include "Constants.h"
#include "Cell.h"
#include "SFML/Graphics.hpp"
#include <thread>
#include <algorithm>
#include "UIWindow.h"

using namespace std;

void Simulate(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->StartSimulation();
}

void SetForest(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->SetEditState(EditState::forest);
}

void SetWater(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->SetEditState(EditState::water);
}

void SetEmpty(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->SetEditState(EditState::empty);
}

void SetFire(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->SetEditState(EditState::fire);
}

void IncreaseWindSpeed(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->ChangeWindSpeed(1);
}

void DecreaseWindSpeed(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->ChangeWindSpeed(-1);
}

void IncreaseWindAngle(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->ChangeWindAngle(15);
}

void DecreaseWindAngle(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->ChangeWindAngle(-15);
}

int main() {
	shared_ptr<UIWindow> wnd = make_shared<UIWindow>(600, 700);
	{
		UIButton simulate(wnd);
		simulate.SetSize(75, 50);
		simulate.SetTitle("simulate");
		simulate.SetPos(275, 5);
		simulate.SetColor(sf::Color::Green);
		simulate.SetInputHandler(&Simulate);
		wnd->AddButton(simulate);

		UIButton fire(wnd);
		fire.SetSize(30, 30);
		fire.SetTitle("simulate");
		fire.SetPos(100, 5);
		fire.SetColor(sf::Color::Red);
		fire.SetInputHandler(&SetFire);
		wnd->AddButton(fire);

		UIButton water(wnd);
		water.SetSize(30, 30);
		water.SetTitle("simulate");
		water.SetPos(160, 5);
		water.SetColor(sf::Color::Blue);
		water.SetInputHandler(&SetWater);
		wnd->AddButton(water);

		UIButton empty(wnd);
		empty.SetSize(30, 30);
		empty.SetTitle("simulate");
		empty.SetPos(100, 65);
		empty.SetColor(sf::Color::White);
		empty.SetInputHandler(&SetEmpty);
		wnd->AddButton(empty);

		UIButton forest(wnd);
		forest.SetSize(30, 30);
		forest.SetTitle("simulate");
		forest.SetPos(160, 65);
		forest.SetColor(sf::Color::Green);
		forest.SetInputHandler(&SetForest);
		wnd->AddButton(forest);

		UIButton increase_wind_speed(wnd);
		increase_wind_speed.SetSize(30, 30);
		increase_wind_speed.SetTitle("simulate");
		increase_wind_speed.SetPos(550, 20);
		increase_wind_speed.SetColor(sf::Color::White);
		increase_wind_speed.SetInputHandler(&IncreaseWindSpeed);
		wnd->AddButton(increase_wind_speed);

		UIButton decrease_wind_speed(wnd);
		decrease_wind_speed.SetSize(30, 30);
		decrease_wind_speed.SetTitle("simulate");
		decrease_wind_speed.SetPos(500, 20);
		decrease_wind_speed.SetColor(sf::Color::Black);
		decrease_wind_speed.SetInputHandler(&DecreaseWindSpeed);
		wnd->AddButton(decrease_wind_speed);

		UIButton increase_wind_angle(wnd);
		increase_wind_angle.SetSize(30, 30);
		increase_wind_angle.SetTitle("simulate");
		increase_wind_angle.SetPos(550, 60);
		increase_wind_angle.SetColor(sf::Color::White);
		increase_wind_angle.SetInputHandler(&IncreaseWindAngle);
		wnd->AddButton(increase_wind_angle);

		UIButton decrease_wind_angle(wnd);
		decrease_wind_angle.SetSize(30, 30);
		decrease_wind_angle.SetTitle("simulate");
		decrease_wind_angle.SetPos(500, 60);
		decrease_wind_angle.SetColor(sf::Color::Black);
		decrease_wind_angle.SetInputHandler(&DecreaseWindAngle);
		wnd->AddButton(decrease_wind_angle);
	}
	wnd->Run();
}