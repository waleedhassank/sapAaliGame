#ifndef SNAKE_h
#define SNAKE_h
#include<vector>
#include<utility>

using namespace std;

enum Direction {
	UP, DOWN, LEFT, RIGHT
};

//used for the Boxed Snake
class Snake {
private:

	//kept private because the derived class "unlimSnake" has to have its own such function
	bool collisionCheck(pair<int, int>& newHead) {
		if (newHead.first < 0 || newHead.first >= limits.first ||
			newHead.second < 0 || newHead.second >= limits.second ||
			find(snakeBody.begin(), snakeBody.end(), newHead) != snakeBody.end()) {
			return true;
		}
		return false;
	}

protected:

	Direction direction;
	std::vector<std::pair<int, int>> snakeBody;
	std::pair<int, int> limits;
	static std::pair<int, int> appleCoordinates;

	void eatApple();

public:

	int size; //used as score

	Snake(std::pair<int, int> lim);

	virtual bool move();

	//removes the tail of snake
	void tailSnap() {
		snakeBody.pop_back();
	}

	void changeDirection(Direction direction);

	bool getIndexState(pair<int, int> xy);

	bool getAppleState(pair<int, int> xy);

	void die();
};

//std::pair<int, int> Snake::appleCoordinates = { -1, -1 };

class UnlimSnake : public Snake {
private:
	//unique function from the base "Snake" class
	bool collisionCheck(pair<int, int>& newHead) {
		if (find(snakeBody.begin(), snakeBody.end(), newHead) != snakeBody.end()) {
			return true;
		}
		return false;
	}

	//all protected members of Snake class are in here
public:

	UnlimSnake(pair<int, int> lim) : Snake(lim) {
		// Any additional initialization specific to UnlimSnake
	}

	//overLoaded function from the base "Snake" class' move
	bool move() override {
		pair<int, int> newHead = snakeBody.front();
		if (direction == RIGHT) {
			if (newHead.second >= limits.second) {
				newHead.second = 0; // Wrap around horizontally
			}
			else {
				++newHead.second;
			}
		}
		else if (direction == LEFT) {
			if (newHead.second <= 0) {
				newHead.second = limits.second; // Wrap around horizontally
			}
			else {
				--newHead.second;
			}
		}
		else if (direction == UP) {
			if (newHead.first <= 0) {
				newHead.first = limits.first; // Wrap around vertically
			}
			else {
				--newHead.first;
			}
		}
		else if (direction == DOWN) {
			if (newHead.first >= limits.first) {
				newHead.first = 0; // Wrap around vertically
			}
			else {
				++newHead.first;
			}
		}

		if (collisionCheck(newHead)) {
			die();
			return false;
		}

		snakeBody.insert(snakeBody.begin(), newHead);

		if (newHead == appleCoordinates) {
			eatApple();
		}
		else {
			tailSnap();
		}

		return true;
	}

	//all public members of Snake class are in here
};


#endif
