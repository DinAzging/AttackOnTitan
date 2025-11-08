#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

#include <string>
#include <vector>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/ContextSettings.hpp>

class GraphicsSettings
{
public:
	GraphicsSettings();

	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

    void loadFromFile(const::std::string path);
    void saveToFile(const::std::string path);
};

#endif