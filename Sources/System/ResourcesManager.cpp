#pragma once

#include "ResourcesManager.h"

//====================================================================================================

void ResourcesManager::loadTexture(const String& name, const String& path)
{
	mTextures[name].loadFromFile(path);
}

//====================================================================================================

void ResourcesManager::loadFont(const String& name, const String& path)
{
	mFonts[name].loadFromFile(path);
}

//====================================================================================================

const Texture& ResourcesManager::getTexture(const String& name) const
{
	return mTextures.at(name);
}

//====================================================================================================

const Font& ResourcesManager::getFont(const String& name) const
{
	return mFonts.at(name);
}