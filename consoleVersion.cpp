//#include<iostream>
//#include"snake.h"
//
//#include <thread>
//#include <chrono>
//
//#include<conio.h>
//
//#include<vector>
//#include<utility>
//
//using namespace std;
//
//int input() {
//	char ch = _getch();
//	switch (ch) {
//	case 'w': return 0;
//	case 's': return 1;
//	case 'a': return 2;
//	case 'd': return 3;
//	default: return -1; // Invalid input
//	}
//}
//
//
//int main() {
//	int limit = 10;
//	Snake snake({ limit - 1, limit - 1 });
//	do {
//		system("cls");
//		for (int i = 0; i < limit; i++) {
//			for (int j = 0; j < limit; j++) {
//				if (!snake.getIndexState({ i, j })) {
//					cout << "0 ";
//				}
//				else if (snake.getAppleState({i, j})) {
//					cout << "1 ";
//				}
//				else {
//					cout << ". ";
//				}
//				
//			}
//			cout << endl;
//		}
//
//		snake.changeDirection(static_cast<Direction>(input()));
//
//		this_thread::sleep_for(chrono::milliseconds(60));
//
//	} while (snake.move());
//
//}