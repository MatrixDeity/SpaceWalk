#include "SpaceWalkState.h"
#include <iostream>

//====================================================================================================

SpaceWalkState::SpaceWalkState(RenderWindow& window) :
GameState(window),
mPlayer(window, ResourcesManager::getInstance().getTexture("ship"), ResourcesManager::getInstance().getTexture("blue_bullet")),
mControl(),
mEnemies(),
mEmblem(ResourcesManager::getInstance().getTexture("space_walk")),
mBackground(ResourcesManager::getInstance().getTexture("space")),
mCamera(mPlayer.getPosition(), window.getView().getSize()),
mPanel()
{
	mEmblem.setScale(3.0F, 3.0F);
	mBackground.setScale(2.0F, 2.0F);
	mPlayer.setPosition(Vector2f(1500.0F, 1500.0F));		
}

//====================================================================================================

SpaceWalkState::~SpaceWalkState()
{
	mEnemies.clear();
}

//====================================================================================================

void SpaceWalkState::update(float time)
{
	mPlayer.updateControl(mControl);
	mPlayer.update(time);
	while (mEnemies.size() < 3)
	{
		std::shared_ptr<DarkKnight> ship = std::make_shared<DarkKnight>(mWindow, ResourcesManager::getInstance().getTexture("dark_knight"),
			ResourcesManager::getInstance().getTexture("red_bullet"), &mPlayer); // MB better a reference to mPlayer?
		ship->setPosition(static_cast<Vector2f>(GameMath::generateRandomVector(Vector2i(0, 0), Vector2i(4000, 4000))));
		mEnemies.push_back(ship);
	}
	for (auto& ship : mEnemies)
			ship->update(time);

	for (auto it = mEnemies.begin(); it != mEnemies.end();)
		if ((*it)->isAlive())
		{
			(*it)->update(time);
			++it;
		}
		else
			it = mEnemies.erase(it);
	mCamera.setCenter(mPlayer.getPosition());
	mWindow.setView(mCamera);
}

//====================================================================================================

void SpaceWalkState::draw(float time) const
{
	mWindow.draw(mBackground);
	if (mPlayer.isAlive())
		mPlayer.draw(time);
	for (const auto& ship : mEnemies)
		ship->draw(time);
	mWindow.draw(mEmblem);
}

//====================================================================================================

void SpaceWalkState::handleInput()
{
	mControl.cursorPosition = mWindow.mapPixelToCoords(Mouse::getPosition());
	while (mWindow.pollEvent(mEvent))
	{
		switch (mEvent.type)
		{
		case Event::Closed:
			mWindow.close();
			break;
		case Event::KeyPressed:
			switch (mEvent.key.code)
			{
			case Keyboard::W:
				mControl.isUpPressed = true;
				break;
			case Keyboard::S:
				mControl.isDownPressed = true;
				break;
			case Keyboard::A:
				mControl.isLeftPressed = true;
				break;
			case Keyboard::D:
				mControl.isRightPressed = true;
				break;
			}
			break;
		case Event::KeyReleased:
			switch (mEvent.key.code)
			{
			case Keyboard::W:
				mControl.isUpPressed = false;
				break;
			case Keyboard::S:
				mControl.isDownPressed = false;
				break;
			case Keyboard::A:
				mControl.isLeftPressed = false;
				break;
			case Keyboard::D:
				mControl.isRightPressed = false;
				break;
			case Keyboard::Escape:
				mWindow.close();
				break;
			case Keyboard::BackSpace:
				mPlayer.setPosition({ 0.0F, 0.0F });
				break;
			}
			break;
		case Event::MouseButtonPressed:
			switch (mEvent.mouseButton.button)
			{
			case Mouse::Left:
				mControl.isNabPressed = true;
				break;
			}
			break;
		case Event::MouseButtonReleased:
			switch (mEvent.mouseButton.button)
			{
			case Mouse::Left:
				mControl.isNabPressed = false;
				break;
			}
			break;
		}
	}
}
