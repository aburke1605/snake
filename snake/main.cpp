#include <SFML/System.hpp>

#include "Grid.cpp"

#include <windows.h>

constexpr unsigned dt = 300; // milliseconds

int main() {

	unsigned int grid_dimension = 400;
	sf::RenderWindow window(sf::VideoMode(grid_dimension, grid_dimension), "snake");


	unsigned int grid_size = 10;
	Grid grid(window, grid_size);



	while (window.isOpen()) {

		window.clear(sf::Color::Black); // reset previous frame

		// check for keyboard interaction
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				sf::Vector2i new_velocity;
				if (event.key.code == sf::Keyboard::Up) {
					new_velocity = sf::Vector2i(0, -1);
				}
				else if (event.key.code == sf::Keyboard::Down) {
					new_velocity = sf::Vector2i(0, 1);
				}
				else if (event.key.code == sf::Keyboard::Left) {
					new_velocity = sf::Vector2i(-1, 0);
				}
				else if (event.key.code == sf::Keyboard::Right) {
					new_velocity = sf::Vector2i(1, 0);
				}

				// change direction only if one of the arrows is pressed
				if (new_velocity != sf::Vector2i())
					grid.ChangeDirection(new_velocity);
			}
		}

		// draw next frame
		grid.Render(window);
		window.display();

		// sleep before updating
		Sleep(dt);
	}

	return 0;
}