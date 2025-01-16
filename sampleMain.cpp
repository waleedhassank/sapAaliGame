//#include <iostream>
//#include <vector>
//#include <conio.h>
//#include <cstdlib>
//#include <ctime>
//#include <thread>
//#include <chrono>
//#include<string>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <filesystem>
//#include"sfmlFunctions.h"
//
//
//using namespace std;
//using namespace sf;
//
//// Constants
//const int boardSize = 40; // Size of the board
//
//VideoMode desktopsize = VideoMode::getDesktopMode();
//
//sf::Font mainFont;
//
//int screenManager = 0;
//
//// Game variables
//vector<pair<int, int>> snake; // Stores the snake's body (head at the front)
//pair<int, int> apple;         // Stores the apple's position
//int direction = 1;            // 1 = right, 2 = left, 3 = up, 4 = down
//bool gameOver = false;
//
//int loadEverything() {
//    std::cout << "Attempting to load font..." << std::endl;
//    if (!mainFont.loadFromFile("39335_UniversCondensed.ttf"))
//    {
//        std::cerr << "Error: Failed to load font. Ensure the path is correct and the file exists." << std::endl;
//        return -1;
//    }
//    return 0;
//}
//
//
//
//// Initializes the game
//void initializeGame() {
//    snake.clear();
//    snake.push_back({ boardSize / 2, boardSize / 2 }); // Snake starts in the center
//    apple = { rand() % boardSize, rand() % boardSize }; // Random apple position
//}
//
//// Generates a new apple, ensuring it does not overlap the snake
//void generateApple() {
//    do {
//        apple = { rand() % boardSize, rand() % boardSize };
//    } while (find(snake.begin(), snake.end(), apple) != snake.end());
//}
//
//
//
//// Displays the board
//void displayBoard(RenderWindow& window) {
//
//    window.clear(Color(0, 0, 10));
//
//    int boxsize = 25;
//    RectangleShape rect(Vector2f(boxsize, boxsize));
//    rect.setOutlineThickness(1);
//
//    RectangleShape outerRect(Vector2f(boxsize * boardSize + 5, boxsize * boardSize + 5));
//    outerRect.setOutlineThickness(2);
//    outerRect.setOutlineColor(Color::White);
//    outerRect.setFillColor(Color::Transparent);
//
//    int startingPointX = 1920 / 4;
//    int startingPointY = (1080 / 4)  - 100 - (boxsize * 5);
//
//    outerRect.setPosition(Vector2f(startingPointX - 2, startingPointY - 2));
//    window.draw(outerRect);
//
//    for (int i = 0; i < boardSize; ++i) {
//        for (int j = 0; j < boardSize; ++j) {
//            rect.setPosition(Vector2f(startingPointX + (boxsize * j), startingPointY + (boxsize * i)));
//
//            if (find(snake.begin(), snake.end(), make_pair(i, j)) != snake.end()) {
//                rect.setFillColor(Color::Transparent);
//                rect.setOutlineColor(Color(255, 255, 255));
//            }
//            else if (apple == make_pair(i, j)) {
//                rect.setFillColor(Color(255, 255, 255));
//                rect.setOutlineColor(Color::Transparent);
//            }
//            else {
//                rect.setFillColor(Color::Transparent);
//                rect.setOutlineColor(Color::Transparent);
//            }
//            window.draw(rect);
//        }
//        cout << endl;
//    }
//    string score = to_string(snake.size() - 1);
//    writeText(window, score, mainFont, 200, 540, 100, 100, 1, 0);
//    window.display();
//}
//
//// Handles input for direction
//void handleInput(RenderWindow& window) {
//    Event event;
//    while (window.pollEvent(event)) {
//        if (event.type == Event::KeyPressed) {
//            // Check for key presses and handle direction changes
//            if (event.key.code == Keyboard::W && direction != 4) {
//                direction = 3; // Up
//            }
//            else if (event.key.code == Keyboard::S && direction != 3) {
//                direction = 4; // Down
//            }
//            else if (event.key.code == Keyboard::A && direction != 1) {
//                direction = 2; // Left
//            }
//            else if (event.key.code == Keyboard::D && direction != 2) {
//                direction = 1; // Right
//            }
//        }
//        // Handle window close event
//        else if (event.type == Event::Closed) {
//            window.close();
//        }
//    }
//}
//
//
//// Updates the snake's position
//void updateSnake() {
//    pair<int, int> newHead = snake.front();
//    if (direction == 1) ++newHead.second;    // Right
//    else if (direction == 2) --newHead.second; // Left
//    else if (direction == 3) --newHead.first;  // Up
//    else if (direction == 4) ++newHead.first;  // Down
//
//    // Check for collisions with walls or itself
//    if (newHead.first < 0 || newHead.first >= boardSize ||
//        newHead.second < 0 || newHead.second >= boardSize ||
//        find(snake.begin(), snake.end(), newHead) != snake.end()) {
//        gameOver = true;
//        return;
//    }
//
//    // Add new head
//    snake.insert(snake.begin(), newHead);
//
//    // Check if apple is eaten
//    if (newHead == apple) {
//        generateApple();
//    }
//    else {
//        // Remove the tail if no apple is eaten
//        snake.pop_back();
//    }
//}
//
////Sets the button at center of screen in accordance to width
//int centerAlign(int screenWidth, int width) {
//    int center = (screenWidth / 2) - (width / 2);
//    return center;
//}
//
//
////Makes any type of Buttons(CENTER-ALIGNED)
//
//void handleMainScreen(RenderWindow& window) {
//    Event event;
//    while (window.pollEvent(event)) {
//
//        // Vector2i mousePos = Mouse::getPosition(window);
//
//        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
//            window.close();
//        }
//    }
//}
//
//void mainMenu(RenderWindow& window) {
//    window.clear(Color::Black);
//    makeButtons(window, mainFont, "PLAY", 400, 100, 500, 0);
//    window.display();
//    handleMainScreen(window);
//}
//
//void screenDecider(RenderWindow& window) {
//    switch (screenManager) {
//    case 0:
//        mainMenu(window);
//        break;
//
//    case 1:
//        srand(static_cast<unsigned>(time(0))); // Seed for random apple generation
//        initializeGame();
//        handleInput(window);
//        updateSnake();
//        displayBoard(window);
//        this_thread::sleep_for(chrono::milliseconds(100)); // Game speed
//        break;
//    }
//}
//
//// Main game loop
//void gameLoop(RenderWindow& window) {
//    while (!gameOver) {
//       
//       
//        handleInput(window);
//        updateSnake();
//        displayBoard(window);
//        this_thread::sleep_for(chrono::milliseconds(20)); // Game speed
//    }
//    cout << "Game Over! Final Score: " << snake.size() - 1 << endl;
//}
//
//
//int main() {
//   
//    if (loadEverything() == -1) {
//        std::cerr << "Error: Failed to load resources." << std::endl;
//        return -1;
//    }
//
//
//    VideoMode desktop = VideoMode::getDesktopMode();
//    RenderWindow window(desktop, "SAAMP", Style::Fullscreen);
//    window.clear(Color(0, 0, 0));
//    window.display();
//
//    srand(static_cast<unsigned>(time(0))); // Seed for random apple generation
//    initializeGame();
//    this_thread::sleep_for(chrono::seconds(2)); // Game speed
//    gameLoop(window);
//    return 0;
//}
//
