//built-in libraries
#include <iostream>
#include <thread>
#include <chrono>
#include<string>
#include<fstream>
#include<vector>

//sfml libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//user-defined libraries
#include"snake.h"
#include"sfmlFunctions.h"

//namespaces
using namespace std;
using namespace sf;

//------------------------------------------------*
// FUNCTION PROTOTYPES----------------------------*
//------------------------------------------------*

bool loadEverything();
void menu();
void handleEvents(GameState& gameState);
void decideScreen(GameState& gameState);
void modeSelect();
void gamePlayBox(GameState gameState);
void handleKeys(GameState gameState);
void handleKeysUnlim(GameState gameState);
void gamePlayUnlim(GameState gameState);
void settingsReader();
void settingsUpdater();
void scoreReader(int arr[5]);
void scoreUpdater(int score);
void leaderBoard();
bool loadScreen();

//------------------------------------------------+
// GLOBAL VARIABLES-------------------------------+
//------------------------------------------------+

VideoMode desktop = VideoMode::getDesktopMode();

RenderWindow window(desktop, "SapAliGame", Style::Fullscreen);

Font firstFont;
Font secondFont;

Texture mainBG;
Texture muteTexture;
Texture modeSelectTexture;
Texture gameBgTexture;

FloatRect button1;
FloatRect button2;
FloatRect button3;
FloatRect button4;
FloatRect button5;

int lims = 40;

Snake snake({lims-1, lims-1});
UnlimSnake unlimsnake({lims-1, lims-1});

bool sound = 1; //index 0 = darkTheme. 1 = Sound

//make it true later .................................
bool inverseColors = false;
bool oneTimeUse = false;
bool highPerformance = true;
bool unlimitedMode = false;
bool gameOver = false;
int difficultINT = 0;
int scoreAchieved = 0;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+


int main() {

	loadScreen();
	
	GameState gameState = MAINMENU;

	settingsReader();

	while (window.isOpen()) {
		decideScreen(gameState);
		if(gameOver || (gameState != BOXGAME && gameState!=UNLIMGAME))
			handleEvents(gameState);
	}
	
}

//Load all textures, fonts and sounds before 
//logic starts. preferably during loading screen
bool loadEverything() {
	if (!firstFont.loadFromFile("39335_UniversCondensed.ttf"))
    {
       return 1;
	}
	if (!secondFont.loadFromFile("Game Of Squids.otf"))
    {
       return 1;
	}
	if (!mainBG.loadFromFile("mainBG.png"))
    {
       return 1;
	}
	if (!muteTexture.loadFromFile("mute.png"))
    {
       return 1;
	}
	if (!modeSelectTexture.loadFromFile("modeSelect.png"))
    {
       return 1;
	}
	if (!gameBgTexture.loadFromFile("gameBg.png"))
    {
       return 1;
	}

	//cerr << "Files Loaded\n";
	//returns zero after success
	return 0;
}

void handleEvents(GameState& gameState) {
	//cerr << "Events Handled";
   Event event;
    while (window.pollEvent(event)) {
		if (event.type == event.KeyPressed ) {
			if (event.key.code == Keyboard::Escape) {
				settingsUpdater();
				window.close();
			}

		}
		if (event.type == event.MouseButtonPressed) {
			sf::Vector2i mousePosDum = sf::Mouse::getPosition(window);
			sf::Vector2f mousePos = window.mapPixelToCoords(mousePosDum);

			if (gameState == MAINMENU && event.mouseButton.button == Mouse::Left) {
				if (button1.contains(mousePos)) {
					gameState = MODESELECT;
					oneTimeUse = false;
				}
				else if (button2.contains(mousePos)) {
					gameState = LEADERBOARD;
					oneTimeUse = false;
				}
				else if (button3.contains(mousePos)) {
					settingsUpdater();
					window.close();
				}
				else if (button5.contains(mousePos)) {
					sound = !sound;
				}

			
			}

			else if (gameState == MODESELECT && event.mouseButton.button == Mouse::Left) {
				if (button1.contains(mousePos)) {
					unlimitedMode = !unlimitedMode;
					oneTimeUse = false;
				}
				else if (button2.contains(mousePos)) {
					if (difficultINT < 2) {
						difficultINT++;
					}
					else
					{
						difficultINT = 0;
					}
				}
				else if (button3.contains(mousePos)) {
					if (unlimitedMode)
						gameState = UNLIMGAME;
					else
						gameState = BOXGAME;
				}
				else if (button4.contains(mousePos)) {
					gameState = MAINMENU;
				}
				else if (button5.contains(mousePos)) {
					sound = !sound;
				}
			}

			else if (gameState == BOXGAME && event.mouseButton.button == Mouse::Left) {
				
				if (button1.contains(mousePos)) {
					gameOver = false;
					scoreUpdater(scoreAchieved);
					snake.constructor();
					cout<<"BRO>>>";
				}
				else if (button2.contains(mousePos)) {
					gameOver = false;
					scoreUpdater(scoreAchieved);
					snake.constructor();
					gameState = MAINMENU;
					cout<<"BROYO Im back BABY>>>";
				}

			}
			else if (gameState == UNLIMGAME && event.mouseButton.button == Mouse::Left) {
				
				if (button1.contains(mousePos)) {
					gameOver = false;
					scoreUpdater(scoreAchieved);
					unlimsnake.constructor();
					cout<<"BRO>>>";
				}
				else if (button2.contains(mousePos)) {
					gameOver = false;
					scoreUpdater(scoreAchieved);
					gameState = MAINMENU;
					unlimsnake.constructor();
					cout << "BROYO Im back BABY>>>";
				}
			}
		}
    }
}

void decideScreen(GameState& gameState) {
	switch(gameState)
	{
	case MAINMENU:
		//cerr << "MainMenu khul jana chahye... nai?";
		menu();
		break;
	case MODESELECT:
		modeSelect();
		break;
	case BOXGAME:
		gamePlayBox(gameState);
		break;
	case UNLIMGAME:
		gamePlayUnlim(gameState);
		break;
	case LEADERBOARD:
		leaderBoard();
		break;
	}
	//cerr << "Screen Decided\n";
}

//All logic on the mainMenu
void menu() {

	// 0 means darkMode OFF

	if (highPerformance) {

		window.clear();


		Sprite mainMenuBgSprite;
		Sprite mute;

		mainMenuBgSprite.setTexture(mainBG);
		mute.setTexture(muteTexture);

		mainMenuBgSprite.scale(Vector2f((desktop.width / 1920.0), (desktop.height / 1080.0)));
		mute.scale(Vector2f((desktop.width / 1920.0), (desktop.height / 1080.0)));

		mainMenuBgSprite.setPosition(0,0);

		mute.setPosition(Vector2f(desktop.width / 1.17647, desktop.height / 13.1707));

		//do single time done tasks here
		if (oneTimeUse == false) {
			button5 = mute.getGlobalBounds();
			oneTimeUse = true;
		}

		window.draw(mainMenuBgSprite);
		window.draw(mute);

		writeText(window, "SAP AALI GAME", secondFont, 100, -1, desktop.height / 3.6, 0, 0, 1, Color::White);

		int buttonHeight = 90, vertical =  desktop.height / 1.9;
		button1 = makeButtons(window, firstFont, 45, Color::White, "PLAY", 450, buttonHeight, desktop.width/2, vertical,
			Color(0,0,0,50), Color::White, Color(0,0,0,100), Color::White);

		button2 = makeButtons(window, firstFont, 45, Color::White , "STATS", 450, buttonHeight, desktop.width / 2, vertical + buttonHeight * 1.4,
			Color(0, 0, 0, 50), Color::White, Color(0, 0, 0, 100), Color::White);

		button3 = makeButtons(window, firstFont, 45, Color::White , "EXIT", 450, buttonHeight, desktop.width / 2, vertical + 2 * (buttonHeight * 1.4),
			Color(0, 0, 0, 50), Color::White, Color(0, 0, 0, 100), Color::White);

		window.display();
		highPerformance = false;
		cout << "R";
	}
	sf::Vector2i mousePosDum = sf::Mouse::getPosition(window);
	sf::Vector2f mousePos = window.mapPixelToCoords(mousePosDum);
	if (button1.contains(mousePos) || button2.contains(mousePos) || button3.contains(mousePos) || button4.contains(mousePos)) {
		highPerformance = true;
	}
}

void modeSelect() {
	if (highPerformance) {
		window.clear();
		Sprite modeSelectBg;
		Sprite mute;

		modeSelectBg.setTexture(modeSelectTexture);
		modeSelectBg.setScale(Vector2f((desktop.width / 1920.0), (desktop.height / 1080.0)));
		modeSelectBg.setPosition(0, 0);

		window.draw(modeSelectBg);

		mute.setTexture(muteTexture);

		mute.setScale(Vector2f((desktop.width / 1920.0), (desktop.height / 1080.0)));

		mute.setPosition(Vector2f(desktop.width / 1.17647, desktop.height / 13.1707));

		window.draw(mute);

		int buttonHeight = 60;

		//first option
		writeText(window, "CHOOSE GAME MODE", secondFont, 50, -1 ,270 , 0, 0, 1, Color::White );
		button1 = makeButtons(window, firstFont, 40, Color::White, unlimitedMode?"UNLIMITED":"BOXED", 220, buttonHeight, desktop.width / 2, desktop.height / 2.84210526,
			Color(0, 0, 0, 150), Color::White, Color(0, 0, 0, 200), Color::White);
		
		//second option
		string difficulty;
		if (difficultINT == 0) {
			difficulty = "EASY";
		}
		else if (difficultINT == 1) {
			difficulty = "MEDIUM";
		}
		else {
			difficulty = "HARD";
		}

		writeText(window, "CHOOSE DIFFICULTY", secondFont, 50, -1, 500, 0, 0, 1, Color::White );
		button2 = makeButtons(window, firstFont, 40, Color::White, difficulty, 220, buttonHeight, desktop.width / 2,desktop.height / 1.8,
			Color(0, 0, 0, 150), Color::White, Color(0, 0, 0, 200), Color::White);

		button3 = makeButtons(window, firstFont, 50, Color::White, "PLAY", 350, buttonHeight * 1.5, desktop.width / 2, desktop.height / 1.2,
			Color(0, 0, 0, 150), Color::White, Color(0, 0, 0, 200), Color::White);

		window.display();
		highPerformance = false;
		cout << "Shown once only";
	}
	sf::Vector2i mousePosDum = sf::Mouse::getPosition(window);
	sf::Vector2f mousePos = window.mapPixelToCoords(mousePosDum);
	if (button1.contains(mousePos) || button2.contains(mousePos) || button3.contains(mousePos) || button4.contains(mousePos)) {
		highPerformance = true;
	}
}

void gamePlayUnlim(GameState gameState) {

	window.clear(Color::Black);

	handleKeysUnlim(gameState);

	Sprite gameBg;
	gameBg.setTexture(gameBgTexture);
	window.draw(gameBg);

	if (gameOver) {

		scoreAchieved = unlimsnake.size;

		writeText(window, "GAME OVER", secondFont, 100, 1920 / 2, 1080 / 3, 0, 0, 1, Color::White);

		button1 = makeButtons(window, firstFont, 40, Color::White, "PLAY AGAIN", desktop.height / 4.32, 75, desktop.width / 1.7, desktop.height / 1.75,
			Color(0, 0, 0, 50), Color::White, Color(0, 0, 0, 100), Color::White);
		button2 = makeButtons(window, firstFont, 40, Color::White, "BACK TO MENU", desktop.height / 4.32, 75, desktop.width / 2.3, desktop.height / 1.75,
			Color(0, 0, 0, 50), Color::White, Color(0, 0, 0, 100), Color::White);
	}
	else{

		int boxSize = 25;

		int startingPointX = 1920 / 4;
		int startingPointY = (1080 / 4) - 100 - (boxSize * 5);

		RectangleShape rect;
		rect.setOutlineThickness(1);
		rect.setSize(Vector2f(boxSize, boxSize));
		rect.setPosition(Vector2f(-100, -100));

		RectangleShape outerRect(Vector2f(boxSize * lims + 5, boxSize * lims + 5));
		outerRect.setOutlineThickness(2);
		outerRect.setOutlineColor(Color::White);
		outerRect.setFillColor(Color(0, 0, 0, 150));
		outerRect.setPosition(Vector2f(startingPointX - 2, startingPointY - 2));
		window.draw(outerRect);

		for (int i = 0; i < lims; i++) {
			for (int j = 0; j < lims; j++) {
				if (!unlimsnake.getIndexState({ i, j })) {
					rect.setPosition(Vector2f(startingPointX + (boxSize * j), startingPointY + (boxSize * i)));
					rect.setFillColor(Color(0, 0, 0, 220));
					rect.setOutlineColor(Color::White);
					window.draw(rect);
				}
				else if (unlimsnake.getAppleState({ i, j })) {
					rect.setPosition(Vector2f(startingPointX + (boxSize * j), startingPointY + (boxSize * i)));
					rect.setOutlineColor(Color::Black);
					rect.setFillColor(Color::White);
					window.draw(rect);
				}
			}
		}

		string scoreString;
		scoreString = "SCORE: " + to_string(unlimsnake.size);

		writeText(window, scoreString, firstFont, 50, 1920 / 8, 1080 / 2, 0, 0, 1, Color::White);

		if (difficultINT == 0) {
			this_thread::sleep_for(chrono::milliseconds(50));
		}
		else if (difficultINT == 1) {
			this_thread::sleep_for(chrono::milliseconds(40));
		}
		else {
			this_thread::sleep_for(chrono::milliseconds(30));
		}

	}

	if (!unlimsnake.move()) {
		gameOver = true;
	}

	window.display();
}

void gamePlayBox(GameState gameState) {

	window.clear(Color::Black);

	handleKeys(gameState);

	Sprite gameBg;
	gameBg.setTexture(gameBgTexture);
	window.draw(gameBg);

	if (gameOver) {

		scoreAchieved = snake.size;

		writeText(window, "GAME OVER", secondFont, 100, desktop.width / 2, desktop.height / 3, 0, 0, 1, Color::White);

		button1 = makeButtons(window, firstFont, 40, Color::White , "PLAY AGAIN", desktop.height / 4.32, 75, desktop.width / 1.7, desktop.height / 1.75,
			Color(0, 0, 0, 50), Color::White, Color(0, 0, 0, 100), Color::White);
		button2 = makeButtons(window, firstFont, 40, Color::White, "BACK TO MENU", desktop.height / 4.32, 75, desktop.width / 2.3, desktop.height / 1.75,
			Color(0, 0, 0, 50), Color::White, Color(0, 0, 0, 100), Color::White);
	}
	else{

		int boxSize = 25;

		int startingPointX = 1920 / 4;
		int startingPointY = (1080 / 4) - 100 - (boxSize * 5);

		RectangleShape rect;
		rect.setOutlineThickness(1);
		rect.setSize(Vector2f(boxSize, boxSize));
		rect.setPosition(Vector2f(-100, -100));

		RectangleShape outerRect(Vector2f(boxSize * lims + 5, boxSize * lims + 5));
		outerRect.setOutlineThickness(2);
		outerRect.setOutlineColor(Color::White);
		outerRect.setFillColor(Color(0,0,0,150));
		outerRect.setPosition(Vector2f(startingPointX - 2, startingPointY - 2));
		window.draw(outerRect);

		for (int i = 0; i < lims; i++) {
			for (int j = 0; j < lims; j++) {
				if (!snake.getIndexState({ i, j })) {
					rect.setPosition(Vector2f(startingPointX + (boxSize * j), startingPointY + (boxSize * i)));
					rect.setFillColor(Color(0,0,0,220));
					rect.setOutlineColor(Color::White);
					window.draw(rect);
				}
				else if (snake.getAppleState({ i, j })) {
					rect.setPosition(Vector2f(startingPointX + (boxSize * j), startingPointY + (boxSize * i)));
					rect.setFillColor(Color::Black);
					window.draw(rect);
				}
			}
		}
		handleKeys(gameState);

		string scoreString;
		scoreString = "SCORE: " + to_string(snake.size);

		writeText(window, scoreString, firstFont, 50, 1920 / 8, 1080 / 2, 0, 0, 1, Color::White);

		if (difficultINT == 0) {
			this_thread::sleep_for(chrono::milliseconds(50));
		}
		else if (difficultINT == 1) {
			this_thread::sleep_for(chrono::milliseconds(40));
		}
		else {
			this_thread::sleep_for(chrono::milliseconds(30));
		}

	}

	if (!snake.move()) {
		gameOver = true;
	}

	window.display();
}

void handleKeys(GameState gameState) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == event.KeyPressed) {
			if (event.key.code == Keyboard::Escape) {
				window.close();
			}
			else if (gameState == BOXGAME) {
				if (event.type == Event::KeyPressed) {
					// Check for key presses and handle direction changes
					if (event.key.code == Keyboard::W && snake.getDirection() != 1) {
						snake.changeDirection(UP); // Up
					}
					else if (event.key.code == Keyboard::S && snake.getDirection() != 0) {
						snake.changeDirection(DOWN); // Down
					}
					else if (event.key.code == Keyboard::A && snake.getDirection() != 3) {
						snake.changeDirection(LEFT); // Left
					}
					else if (event.key.code == Keyboard::D && snake.getDirection() != 2) {
						snake.changeDirection(RIGHT); // Right
					}
				}
			}
		}
	}
}

void handleKeysUnlim(GameState gameState) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == event.KeyPressed) {
			if (event.key.code == Keyboard::Escape) {
				window.close();
			}
			else if (gameState == UNLIMGAME) {
				if (event.type == Event::KeyPressed) {
					// Check for key presses and handle direction changes
					if (event.key.code == Keyboard::W && unlimsnake.getDirection() != 1) {
						unlimsnake.changeDirection(UP); // Up
					}
					else if (event.key.code == Keyboard::S && unlimsnake.getDirection() != 0) {
						unlimsnake.changeDirection(DOWN); // Down
					}
					else if (event.key.code == Keyboard::A && unlimsnake.getDirection() != 3) {
						unlimsnake.changeDirection(LEFT); // Left
					}
					else if (event.key.code == Keyboard::D && unlimsnake.getDirection() != 2) {
						unlimsnake.changeDirection(RIGHT); // Right
					}
				}
			}
		}
	}
}

void settingsReader() {
	ifstream file("settings.txt");

	cout << "IM IN THE READER\n";
	file >> sound;
	file >> unlimitedMode;
	file >> difficultINT;
	file.close();
}

void settingsUpdater() {
	ofstream file("settings.txt");

	file << sound << endl;
	file << unlimitedMode << endl;
	file << difficultINT << endl;
	file.close();
}

void scoreReader(int arr[5]) {
	std::ifstream file("score.txt");

	// Check if file is open
	if (!file.is_open()) {
		std::cerr << "Error: Could not open score.txt" << std::endl;
		return;
	}

	std::vector<int> score;
	int temp;

	// Read scores from file
	while (file >> temp) {
		score.push_back(temp);
	}
	file.close();

	// Sort the scores
	std::sort(score.begin(), score.end());

	// Copy the smallest 5 scores to arr
	for (size_t i = 0; i < 5 && i < score.size(); i++) {
		arr[i] = score[i];
	}

	// Fill remaining spots in arr with 0 if there are fewer than 5 scores
	for (size_t i = score.size(); i < 5; i++) {
		arr[i] = 0;
	}
}

void scoreUpdater(int score) {
	ofstream file("score.txt", ios::app);

	file << score << endl;

}

void leaderBoard() {
	window.clear(Color::Black);
	int arr[5];
	scoreReader(arr);
	string score;
	score = "1.\t\t" + to_string(arr[0]) + "\n2.\t\t" + to_string(arr[1]) + "\n3.\t\t" + to_string(arr[2]) + 
		"\n4.\t\t" + to_string(arr[3]) + "\n5.\t\t" + to_string(arr[4]);

	writeText(window, score, firstFont, 70, desktop.width / 2.1, desktop.height / 1.7, 0, 0, 1, Color::White);
	
	window.display();
}

bool loadScreen() {

	window.clear(Color::Black); 

	Texture loadScreenTexture;
	Texture loadScreenBhambiriTexture;
	if (!loadScreenTexture.loadFromFile("loadScreen.png"))
	{
		return 0;
	}
	Sprite loadScreenS;
	loadScreenS.setTexture(loadScreenTexture);
	window.draw(loadScreenS);

	window.display();

	if (loadEverything())
		return 0; // crashes if failed to load any single thing

	if (!loadScreenBhambiriTexture.loadFromFile("loadScreenBhambiri.png"))
	{
		return 0;
	}

	Sprite loadScreenBhambiri;
	loadScreenBhambiri.setTexture(loadScreenBhambiriTexture);
	loadScreenBhambiri.setPosition(Vector2f(desktop.width / 23, desktop.height / 1.2));


	int duration = 3;

	// Get the start time
	auto start_time = std::chrono::steady_clock::now();

	// Loop until the specified duration has passed
	while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(duration)) {

		window.clear();

		window.draw(loadScreenS);
		
		loadScreenBhambiri.setPosition(loadScreenBhambiri.getPosition().x + 3, loadScreenBhambiri.getPosition().y);

		window.draw(loadScreenBhambiri);

		window.display();

		// Optional: Add a small delay to reduce CPU usage
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}