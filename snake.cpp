#include "snake.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

std::pair<int, int> Snake::appleCoordinates = { -1, -1 }; // Initial value

void Snake::generateApple() {
    do {
        appleCoordinates = { rand() % limits.first, rand() % limits.second };
    } while (find(snakeBody.begin(), snakeBody.end(), appleCoordinates) != snakeBody.end());
}

//\brief Constructor to start off the game
//\param lim is the maximum number of available boxes
Snake::Snake(pair<int, int> lim) {
    direction = RIGHT;
    size = 0;
    limits = lim;
    snakeBody.push_back({ lim.first / 2, (lim.second / 2) + 1 });
    snakeBody.push_back({ lim.first / 2, lim.second / 2 }); //get it to settle the snake on screen center

    generateApple();
}

void Snake::constructor() {
    direction = RIGHT;
    size = 0;
    snakeBody.clear();
    snakeBody.push_back({ limits.first / 2, (limits.second / 2) + 1 });
    snakeBody.push_back({ limits.first / 2, limits.second / 2 }); //get it to settle the snake on screen center

    generateApple();
}

//movement of the boxed snake
bool Snake::move() {
    pair<int, int> newHead = snakeBody.front();
    switch (direction) {
    case RIGHT: ++newHead.second; break;
    case LEFT: --newHead.second; break;
    case UP: --newHead.first; break;
    case DOWN: ++newHead.first; break;
    }

    if (collisionCheck(newHead) || outOfBounds(newHead)) {
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


bool Snake::outOfBounds(const pair<int, int>& pos) const {
    return pos.first < 0 || pos.first >= limits.first || pos.second < 0 || pos.second >= limits.second;
}

//use in if else with the tailsnap function to work properly
void Snake::eatApple() {
    size++;
    generateApple();
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
    return find(snakeBody.begin(), snakeBody.end(), xy) == snakeBody.end();
}

bool Snake::getAppleState(pair<int, int> xy) {
    return appleCoordinates == xy;
}

Direction Snake::getDirection() {
    return direction;
}
