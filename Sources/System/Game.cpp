#include "Game.h"

//====================================================================================================

Game::Game() :
mWindow(VideoMode::getDesktopMode(), "SpaceWalk [pre-ALPHA]", Style::Close),
mTimer()
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setFramerateLimit(60U);
	loadResources();
}

//====================================================================================================

Game::~Game()
{
}

//====================================================================================================

void Game::run()
{
	float time;
	mTimer.restart();
	while (mWindow.isOpen())
	{
		time = mTimer.restart().asSeconds();

		mWindow.clear();
		if (peekState())
		{
			peekState()->handleInput();
			peekState()->update(time);
			peekState()->draw(time);
		}
		mWindow.display();
	}
}

//====================================================================================================

void Game::pushState(const std::shared_ptr<GameState>& state)
{
	mStates.push(state);
}

//====================================================================================================

void Game::popState()
{
	mStates.pop();
}

//====================================================================================================

const std::shared_ptr<GameState>& Game::peekState() const
{
	if (mStates.empty())
		return nullptr;
	else
		return mStates.top();
}

//====================================================================================================

RenderWindow& Game::getWindow()
{
	return mWindow;
}

//====================================================================================================

void Game::loadResources() const
{
	ResourcesManager::getInstance().loadTexture("ship", "Media/space_walker.png");
	ResourcesManager::getInstance().loadTexture("dark_knight", "Media/dark_knight.png");
	ResourcesManager::getInstance().loadTexture("blue_bullet", "Media/blue_bullet.png");
	ResourcesManager::getInstance().loadTexture("red_bullet", "Media/red_bullet.png");
	ResourcesManager::getInstance().loadTexture("space_walk", "Media/space_walk.png");
	ResourcesManager::getInstance().loadTexture("space", "Media/space.png");

	ResourcesManager::getInstance().loadFont("arial", "Media/arial.ttf");
	ResourcesManager::getInstance().loadFont("galaktika", "Media/galaktika.ttf");
}