#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

SceneID scene1;
ObjectID ship, obstacle[100], arrow[2];
int enemyX[100], enemyY[100];
int shipspeed = 0;
int enemyspeed = 1;
TimerID timer1;
int shipX = 600;
int score = 0;
float obsize[100];
int checka, checkb, checkc;
bool pointInRectangle(int x, int y, int rx, int ry, int size) {
	return ((rx <= x <= rx + size) && (ry <= y <= ry + size));
}
void mousecallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == arrow[0]) {
		shipspeed--;
	}
	if (object == arrow[1]) {
		shipspeed++;
	}
}
void timercallback(TimerID timer) {
	if (timer == timer1) {
		shipX += shipspeed;
		if (0 <= shipX && shipX <= 1230) {
			locateObject(ship, scene1, shipX, 0);
		}
		for (int i = 0; i < 100; i++) {
			enemyY[i] -= enemyspeed;
			locateObject(obstacle[i], scene1, enemyX[i], enemyY[i]);
			if (pointInRectangle(shipX + 10, 20, enemyX[i], enemyY[i], 200) == 1) {
				char buff[50];
				sprintf(buff, "게임종료\n 얻은 점수는 %d", score);
				showMessage(buff);
			}
			else if (pointInRectangle(shipX + 40, 20, enemyX[i], enemyY[i], 200) == 1) {
				char buff[50];
				sprintf(buff, "게임종료\n 얻은 점수는 %d", score);
				showMessage(buff);
			}
			else if (pointInRectangle(shipX + 25, 45, enemyX[i], enemyY[i], 200) == 1) {
				char buff[50];
				sprintf(buff, "게임종료\n 얻은 점수는 %d", score);
				showMessage(buff);
			}
			if (enemyY[i] <= 0) {
				score++;
				enemyX[i] = rand() % 1280;
				enemyY[i] = (rand() % (1000 - score)) + 1000;
				locateObject(obstacle[i], scene1, enemyX[i], enemyY[i]);
			}
		}
		enemyspeed = (score / 100) + 1;
		setTimer(timer1, 0.01);
		startTimer(timer1);
	}
}
ObjectID createobject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return object;
}
int main() {
	scene1 = createScene("");
	timer1 = createTimer(0.01f);
	ship = createobject("Images/ship.png", scene1, shipX, 0, true);
	for (int i = 0; i < 100;i++) {
		char buff[50];
		sprintf(buff, "Images/F%d.png", (i % 4) + 1);
		enemyX[i] = rand() % 1280;
		enemyY[i] = (rand() % 1280 + 720);
		obsize[i] = 1.f / (rand() % 10 + 1);
		obstacle[i] = createobject(buff, scene1, enemyX[i], enemyY[i], true);
		scaleObject(obstacle[i], obsize[i]);
	}
	arrow[0] = createobject("Images/left-arrow.png", scene1, 0, 0, true);
	arrow[1] = createobject("Images/right-arrow.png", scene1, 1100, 0, true);
	setTimerCallback(timercallback);
	setMouseCallback(mousecallback);
	startTimer(timer1);
	startGame(scene1);
}
// f size 200 x 200