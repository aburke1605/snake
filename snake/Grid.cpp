#include <vector>

#include <SFML/Graphics.hpp>

#include "Snake.cpp"
#include "Food.cpp"

class Grid {
	public:
		Grid(sf::RenderWindow& window, unsigned int size = 15) {
			_size = size;

			_cell_width = (float)window.getSize().x / _size;
			_cell_height = (float)window.getSize().y / _size;

			for (unsigned int i = 0; i < _size; i++) {
				_x_coordinates.push_back(i * _cell_width);
				_y_coordinates.push_back(i * _cell_height);
			}


			_generator = std::mt19937(_rd()); // mersenne_twister_engine seeded with rd()

			_snake = new Snake(_size, _generator);
			_food = new Food();
			while (_snake->GetHeadPositionIndex() == (sf::Vector2i)_food->GetPositionIndex())
				_food->Reposition(_size, _generator);
		}

		void ChangeDirection(sf::Vector2i& new_velocity) {
			// I hate this.
			_snake->ChangeDirection(new_velocity);
		}

		bool Render(sf::RenderWindow& window) {
			/*
				returns: (bool) whether game is over
			*/

			// reset from previous frame
			window.clear(sf::Color::Black);

			// move snake along
			_snake->Slither(_size);

			// check for autophagia
			if (_snake->SelfConsumes())
				return true;

			// draw body segment positions
			for (auto& index : _snake->GetBodyPositionIndices()) {
				sf::RectangleShape segment(sf::Vector2f(_cell_width, _cell_height));
				segment.setPosition(sf::Vector2f(_x_coordinates[index.x], _y_coordinates[index.y]));
				segment.setFillColor(sf::Color(150, 50, 250));

				window.draw(segment);
			}

			// if snake eats food
			if (_snake->GetHeadPositionIndex() == (sf::Vector2i)_food->GetPositionIndex()) {
				// reposition the food, but not in any square that the snake occupies
				auto snake_body_indices = _snake->GetBodyPositionIndices();
				while (std::find(snake_body_indices.begin(), snake_body_indices.end(), (sf::Vector2i)_food->GetPositionIndex()) != snake_body_indices.end())
					_food->Reposition(_size, _generator);

				// grow the snakes tail
				_snake->Extend();
			}

			// check if game complete
			if (_snake->GetLength() == _size * _size)
				return true;

			// draw food
			sf::CircleShape bite((_cell_width + _cell_height) / 2 / 2);
			sf::Vector2u index = _food->GetPositionIndex();
			bite.setPosition(sf::Vector2f(_x_coordinates[index.x], _y_coordinates[index.y]));
			bite.setFillColor(sf::Color(100, 250, 50));
			window.draw(bite);

			return false;
		}

	private:
		unsigned int _size;

		float _cell_width;
		float _cell_height;

		std::vector<float> _x_coordinates;
		std::vector<float> _y_coordinates;

		std::random_device _rd; // a seed source for the random number engine
		std::mt19937 _generator;

		Snake* _snake;
		Food* _food;
};