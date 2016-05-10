#pragma once

#include <map>

#include "SFML/Graphics.hpp"

using namespace sf;

//====================================================================================================

class ResourcesManager
{
public:
	static ResourcesManager& getInstance()
	{
		static ResourcesManager instance;
		return instance;
	}

	void loadTexture(const String& name, const String& path);
	void loadFont(const String& name, const String& path);

	const Texture& getTexture(const String& name) const;
	const Font& getFont(const String& name) const;

private:
	ResourcesManager() = default;
	ResourcesManager(const ResourcesManager&) = default;

	std::map<String, Texture> mTextures;
	std::map<String, Font> mFonts;
};