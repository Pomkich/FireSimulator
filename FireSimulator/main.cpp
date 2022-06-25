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

void check(sf::Event, std::weak_ptr<UIWindow> window) {
	window.lock()->StartSimulation();
}

int main() {
	shared_ptr<UIWindow> wnd = make_shared<UIWindow>(600, 700);
	{
		UIButton test(wnd);
		test.SetSize(75, 50);
		test.SetTitle("test");
		test.SetPos(275, 0);
		test.SetColor(sf::Color::Green);
		test.SetInputHandler(&check);
		wnd->AddButton(test);
	}
	wnd->Run();
}