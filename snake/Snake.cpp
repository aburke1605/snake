#include <SFML/System.hpp>
#include <random>




#include <iostream> // remove me


class Snake {
	public:
		Snake(unsigned int grid_size, std::mt19937& generator) {
			_body_position_indices = new std::vector<sf::Vector2i>;
			_velocities = new std::vector<sf::Vector2i>;

			// assign a random starting position within the grid
			std::uniform_int_distribution<> distribution(0, grid_size - 1);
			_body_position_indices->push_back(sf::Vector2i(distribution(generator), distribution(generator)));

			_velocities->push_back(sf::Vector2i(0, 0));
		}

		unsigned int GetLength() const {
			return (unsigned int)_body_position_indices->size();
		}

		sf::Vector2i GetHeadPositionIndex() const {
			return (*_body_position_indices)[0];
		}

		std::vector<sf::Vector2i>& GetBodyPositionIndices() const {
			return *_body_position_indices;
		}

		void Slither(unsigned int grid_size) {
			for (unsigned int i = 0; i < GetLength(); i++) {
				sf::Vector2i& index = (*_body_position_indices)[i];
				sf::Vector2i& velocity = (*_velocities)[i];

				index.x += velocity.x;
				index.y += velocity.y;

				// check the segment has not left the grid
				if (index.x < 0) index.x += (int)grid_size;
				if (index.x >= (int)grid_size) index.x -= (int)grid_size;
				if (index.y < 0) index.y += (int)grid_size;
				if (index.y >= (int)grid_size) index.y -= (int)grid_size;
			}

			// adjust the velocities from bottom up
			for (unsigned int i = GetLength() - 1; i > 0; i--) {
				(*_velocities)[i] = (*_velocities)[i - 1];
			}
		}

		void Extend() {
			// the new tail segment gets appended to the old tail segment in
			// the space adjacent and opposite to its velocity
			sf::Vector2i& tail_position_index = (*_body_position_indices).back();
			sf::Vector2i tail_velocity = (*_velocities).back();
			_body_position_indices->push_back(sf::Vector2i(tail_position_index.x - tail_velocity.x, tail_position_index.y - tail_velocity.y));
			_velocities->push_back(tail_velocity);
		}

		void ChangeDirection(sf::Vector2i& new_velocity) {
			// change only the head velocity
			// the others follow by the Slither() function
			_velocities->front() = new_velocity;
		}

	private:
		std::vector<sf::Vector2i>* _body_position_indices;

		std::vector<sf::Vector2i>* _velocities;

};