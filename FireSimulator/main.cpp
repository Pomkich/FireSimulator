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

}

void SetWater(sf::Event, std::weak_ptr<UIWindow> window) {

}

void SetEmpty(sf::Event, std::weak_ptr<UIWindow> window) {
	
}

void SetFire(sf::Event, std::weak_ptr<UIWindow> window) {

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
	}
	wnd->Run();
}