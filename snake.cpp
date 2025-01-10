#include"snake.h"
#include<iostream>

#include<vector>
#include<utility>

using namespace std;

std::pair<int, int> Snake::appleCoordinates = { -1, -1 }; // Initial value

void generateApple(pair<int, int>& apple, pair<int, int> boardSize, const vector <pair<int, int>>& snakeBody) {
	do {
		apple = { rand() % boardSize.first, rand() % boardSize.second };
	} while (find(snakeBody.begin(), snakeBody.end(), apple) != snakeBody.end());
}

//\brief Contructor to start off the game
//\param lim is the maximum number of available boxes
Snake::Snake(pair<int, int> lim) {
	direction = RIGHT;
	size = 0;
	limits = lim;
	snakeBody.push_back({ lim.first / 2, lim.second / 2 }); //get it to settle the snake on screen center
	snakeBody.push_back({ lim.first / 2, (lim.second / 2) + 1 });
	generateApple(appleCoordinates, limits, snakeBody);
}

//movement of the boxed snake
bool Snake::move() {
	pair<int, int> newHead = snakeBody.front();
	if (direction == RIGHT) ++newHead.second;    // Right
	else if (direction == LEFT) --newHead.second; // Left
	else if (direction == UP) --newHead.first;  // Up
	else if (direction == DOWN) ++newHead.first; // Down


	if (collisionCheck(newHead)) {
		die();
		return false;
	}

	snakeBody.insert(snakeBody.begin(), newHead);

	if (newHead == appleCoordinates) {
		eatApple(); // Grow and generate new apple
	}
	else {
		tailSnap(); // Remove the tail if no apple is eaten
	}

	return true; 
}

//use in if else with the tailsnap function to work properly
void Snake::eatApple() {
	size++;

	generateApple(appleCoordinates, limits, snakeBody);
}

//\brief Enter the Direction of snake in order UP 0, DOWN 1, LEFT 2, RIGHT 3
void Snake::changeDirection(Direction dir) {
	// Prevent reversing direction
	if ((direction == UP && dir != DOWN) ||
		(direction == DOWN && dir != UP) ||
		(direction == LEFT && dir != RIGHT) ||
		(direction == RIGHT && dir != LEFT)) {
		direction = dir;
	}
}

void Snake::die() {
	appleCoordinates.first = -1;
	appleCoordinates.second = -1;
}

bool Snake::getIndexState(pair<int, int> xy) {
	
		if (find(snakeBody.begin(), snakeBody.end(), xy) == snakeBody.end()) {
			return true;
		}
	return false;
}

bool Snake::getAppleState(pair<int, int> xy) {
	if (appleCoordinates == xy) {
		return true;
	}
	return false;
}

