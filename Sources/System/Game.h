#pragma once

#include <stack>
#include <memory>

#include "SFML\Graphics.hpp"
#include "ResourcesManager.h"
#include "GameState.h"
#include "DarkKnight.h"

using namespace sf;

//====================================================================================================

class Game
{
public:
	Game();
	~Game();
	void run();
	void pushState(const std::shared_ptr<GameState>& state);
	void popState();
	const std::shared_ptr<GameState>& peekState() const;

	RenderWindow& getWindow();

private:
	void loadResources() const;
	void showLoading() const;

	RenderWindow mWindow;
	Clock mTimer;
	std::stack<std::shared_ptr<GameState>> mStates;
};

