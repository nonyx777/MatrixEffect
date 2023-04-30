#include<iostream>
#include<SFML/Graphics.hpp>


constexpr int MaxLetterCount = 1200;
constexpr int FontSize = 30u;
constexpr int Speed = 9.f;
constexpr float SpawnTimer = 0.035f;
const std::string AllMatrixChars = "01";
const int HighestBrightness = 130;
const int StringSize = 20;
const int MaxCollums = MaxLetterCount / StringSize;
const int MaxYSpawnValue = 400;
const int LightValue = HighestBrightness / StringSize;


float deltaTime = 0;
float SpawnTimerValue = 0.f;
int main()
{
	srand(unsigned(time(0)));
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Matrix", sf::Style::Close);
	window.setFramerateLimit(144);
	sf::Event evnt;
	sf::Text Letter;
	sf::Font font;
	font.loadFromFile("fonts/dejavu-sans/ttf/DejaVuSansCondensed.ttf");
	Letter.setCharacterSize(FontSize);
	Letter.setFont(font);

	std::vector<std::string> stringRows;
	std::vector<sf::Vector2f> stringRowsPos;


    

	sf::Clock clock;
	while (window.isOpen())
	{
		deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
		}

		SpawnTimerValue += deltaTime;

		if (SpawnTimerValue >= SpawnTimer && stringRows.size() < MaxCollums)
		{
			SpawnTimerValue = 0.f;

			std::string collum = "";
			for (size_t j = 0; j < StringSize; j++)
				collum.push_back(AllMatrixChars[rand() % AllMatrixChars.length()]);

			stringRows.push_back(collum);

			stringRowsPos.push_back({ float(rand() % window.getSize().x + 1), float( -rand() % MaxYSpawnValue + 1) });
		}

		for (size_t i = 0; i < stringRowsPos.size(); i++)
		{
			if (stringRowsPos[i].y - StringSize * FontSize >= window.getSize().y)
			{
				stringRows.erase(stringRows.begin() + i);
				stringRowsPos.erase(stringRowsPos.begin() + i);
			}
			stringRowsPos[i].y += Speed;
		}

		window.clear();

		for (size_t i = 0; i < stringRows.size(); i++)
		{
			for (size_t j = 0; j < StringSize; j++)
			{
				Letter.setString(stringRows[i][j]);
				Letter.setFillColor(sf::Color(0, 255, 0, HighestBrightness - LightValue * j));
				Letter.setPosition(stringRowsPos[i].x, stringRowsPos[i].y - FontSize * j);

				window.draw(Letter);
			}
		}

		window.display();
	}
}