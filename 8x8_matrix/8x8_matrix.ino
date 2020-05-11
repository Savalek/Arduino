#include <Arduino.h>

const int MATRIX_SIZE = 8;
int DELAY_MS = 100;

const int row[MATRIX_SIZE] = {2, 3, 4, 5, 6, 7, 8, 9};
const int col[MATRIX_SIZE] = {12, 13, A2, A3, A4, A5, 10, 11};
const int joyXPin = A0;
const int joyYPin = A1;

struct Point {
  int x;
  int y;
};

int areaMain[MATRIX_SIZE][MATRIX_SIZE] = {
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0, 1},
  {1, 0, 0, 1, 1, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
};


void setup() {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  showArea(areaMain);
//  int allLedOff[MATRIX_SIZE][MATRIX_SIZE];
//  for (int i = 0; i < MATRIX_SIZE; i++) {
//    for (int j = 0; j < MATRIX_SIZE; j++) {
//      allLedOff[i][j] = 0;
//    }
//  }
//
//  Point headPos = {3, 3};
//  Point deltaVec = {1, 0};
//  int snakeLength = 3;
//  auto area = allLedOff;
//  initArea(area, headPos, snakeLength);
//  Point nummyPos = createNummy(area);
//  Serial.println(area[1][7]);
//
//  int gameTicks = 0;
//
//  while (true) {
//    gameTicks++;
//    showArea(area);
//    deltaVec = getNewDelta(deltaVec);
//    if (gameTicks % 50 == 0) {
//      headPos = calculateNewHeadPos(headPos, deltaVec, area);
//
//      if (headPos.x == nummyPos.x && headPos.y == nummyPos.y) {
//        snakeLength++;
//        area[nummyPos.y][nummyPos.x] = 0;
//        nummyPos = createNummy(area);
//      }
//      Serial.println("x=" + String(deltaVec.x) + " | y=" + String(deltaVec.y));
//      if (area[headPos.y][headPos.x] > 0) {
//        gameOver();
//        break;
//      }
//      area[headPos.y][headPos.x] = snakeLength + 1;
//      decrementAllCells(area);
//    }
//  }

  //  Serial.println("x=" + String(analogRead(joyXPin)) + " | y=" + String(analogRead(joyXPin)));
  //  Serial.println("x=" + String(x) + " | y=" + String(y));
}

Point calculateNewHeadPos(Point oldHeadPos, Point deltaVec, int area[][MATRIX_SIZE]) {
  Point newHeadPos;
  newHeadPos.x = oldHeadPos.x + deltaVec.x;
  newHeadPos.y = oldHeadPos.y + deltaVec.y;
  if (newHeadPos.x >= MATRIX_SIZE) {
    newHeadPos.x = 0;
  }
  if (newHeadPos.y >= MATRIX_SIZE) {
    newHeadPos.y = 0;
  }
  if (newHeadPos.x < 0) {
    newHeadPos.x = MATRIX_SIZE - 1;
  }
  if (newHeadPos.y < 0) {
    newHeadPos.y = MATRIX_SIZE - 1;
  }
  return newHeadPos;
}

Point getNewDelta(Point oldDeltaVec) {
  int y = -constarinMap(joyXPin, -10, 10);
  int x = constarinMap(joyYPin, -10, 10);

  if (x == 0 && y == 0) {
      return oldDeltaVec;
  }
  if (x != 0 && y != 0) {
      if (abs(x) > abs(y)) {
          y = 0;
      } else {
          x = 0;
      }
  }

  x = x != 0 ? x / abs(x) : 0;
  y = y != 0 ? y / abs(y) : 0;

  Point newDeltaVec = {oldDeltaVec.x, oldDeltaVec.y};
  if (x != -oldDeltaVec.x && x != 0) {
    newDeltaVec.x = x;
    newDeltaVec.y = 0;
    return newDeltaVec;
  }
  if (y != -oldDeltaVec.y && y != 0) {
    newDeltaVec.x = 0;
    newDeltaVec.y = y;
    return newDeltaVec;
  }

  return newDeltaVec;
}

void decrementAllCells(int area[][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      if (area[i][j] > 0) {
        area[i][j]--;
      }
    }
  }
}

Point createNummy(int area[][MATRIX_SIZE]) {
  Point nummy;
  while (true) {
    nummy = {random(MATRIX_SIZE), random(MATRIX_SIZE)};
    if (area[nummy.y][nummy.x] == 0) {
      area[nummy.y][nummy.x] = 9999;
      return nummy;
    }
  }
}

void initArea(int area[][MATRIX_SIZE], Point headPos, int snakeLength) {
  int  snakeBlockCount = 0;
  while (snakeLength > 0 && (headPos.x - snakeBlockCount) >= 0) {
    area[headPos.y][headPos.x - snakeBlockCount++] = snakeLength--;
  }
}

void showArea(int area[][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      digitalWrite(col[j], area[i][j] > 0 ? HIGH : LOW);
    }
    digitalWrite(row[i], LOW);
    delay(1);
    digitalWrite(row[i], HIGH);
  }
}

void onLed(int rN, int cN) {
  digitalWrite(row[rN], LOW);
  digitalWrite(col[cN], HIGH);
}

int constarinMap(int pinNum, int minVal, int maxVal) {
  int val = analogRead(pinNum);
  val = constrain(val, 0, 1023);
  val = map(val, 0, 1023, minVal, maxVal);
  return val;
}

int gameOver() {
  showGameOver();
}

int showGameOver() {
  int allLedOn[MATRIX_SIZE][MATRIX_SIZE];
  int allLedOff[MATRIX_SIZE][MATRIX_SIZE];
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      allLedOn[i][j] = 1;
      allLedOff[i][j] = 0;
    }
  }
  for (int i = 0; i < 5; i++) {
    showAreaWithDelay(allLedOn, 25);
    showAreaWithDelay(allLedOff, 25);
  }
}

int showAreaWithDelay(int area[][MATRIX_SIZE], int ticksCount) {
  while (ticksCount-- > 0) {
    showArea(area);
  }
}
