#include <SFML/System.hpp>
#include <random>

class Food {
	public:
		Food():
			_position_index(sf::Vector2u(0, 0))
		{}

		sf::Vector2u GetPositionIndex() const {
			return _position_index;
		}

		void Reposition(unsigned int grid_size, std::mt19937& generator) {
			std::uniform_int_distribution<> distribution(0, grid_size - 1);
			_position_index = sf::Vector2u(distribution(generator), distribution(generator));
		}

	private:
		sf::Vector2u _position_index;


};