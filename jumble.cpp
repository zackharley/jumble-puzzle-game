#include <iostream>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include "jumble.h"

using namespace std;

JumblePuzzle::JumblePuzzle(const string word, const string difficulty) {

	if(word.empty()) {
		throw BadJumbleException("You must supply a word to add to the jumble!");
	}

	size = new int;
	srand(time(NULL)); // used for random number generation

	int modifier = 1;

	if(difficulty == "easy") {
		modifier = 2;
	} else if(difficulty == "medium") {
		modifier = 3;
	} else if(difficulty == "hard") {
		modifier = 4;
	} else {
		throw BadJumbleException("Invalid difficulty. Please select 'easy', 'medium', or 'hard'.");
	}

	*size = word.length() * modifier;

	jumble = new char*[*size];
	for(int i = 0; i < *size; i++) {
		jumble[i] = new char[*size];
	}

	emptyJumble();

	initializeJumble(word);
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& original) {
	size = new int;
	*size = original.getSize();

	jumble = new char*[*size];
	for(int i = 0; i < *size; i++) {
		jumble[i] = new char[*size];
	}
	
	charArrayPtr* originalJumble = original.getJumble();

	for(int i = 0; i < *size; i++) {
		for(int j = 0; j < *size; j++) {
			jumble[i][j] = originalJumble[i][j];
		}
	}

	rowPos = new int;
	*rowPos = original.getRowPos();

	colPos = new int;
	*colPos = original.getColPos();

	direction = new char;
	*direction = original.getDirection(); 
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& original) {
	if(this != &original) {
		size = new int;
		*size = original.getSize();

		jumble = original.getJumble();

		rowPos = new int;
		*rowPos = original.getRowPos();

		colPos = new int;
		*colPos = original.getColPos();

		direction = new char;
		*direction = original.getDirection(); 
	}

	return *this;
}

JumblePuzzle::~JumblePuzzle() {
	for(int i = 0; i < *size; i++) {
		delete[] jumble[i];
	}
	delete[] jumble;
	delete size;
	delete rowPos;
	delete colPos;
	delete direction;
}

int JumblePuzzle::getSize() const {
	return *size;
};

charArrayPtr* JumblePuzzle::getJumble() const {
	charArrayPtr* jumbleCopy = new char*[*size];

	for(int i = 0; i < *size; i++) {
		jumbleCopy[i] = new char[*size];
	}

	for(int i = 0; i < *size; i++) {
		for(int j = 0; j < *size; j++) {
			jumbleCopy[i][j] = jumble[i][j];
		}
	}

	return jumbleCopy;
}

int JumblePuzzle::getRowPos() const {
	return *rowPos;
}

int JumblePuzzle::getColPos() const {
	return *colPos;
}

char JumblePuzzle::getDirection() const {
	return *direction;
}

void JumblePuzzle::emptyJumble() {
	for(int i = 0; i < *size; i++) {
		for(int j = 0; j < *size; j++) {
			jumble[i][j] = NULL;
		}
	}
}

void JumblePuzzle::initializeJumble(const string word) {

	if(word.length() == 0) {
		throw BadJumbleException("You must supply a word to hide in thw jumble");
	}

	bool placed = false;
	pair<int, int> position;

	while(!placed) {
		position = generateRandomPosition();
		rowPos = new int;
		*rowPos = position.first;
		colPos = new int;
		*colPos = position.second;
		direction = new char;
		*direction = generateRandomDirection();
		for(int i = 0; i < word.length(); i++) {
			if(isPositionValid(position)) {
				jumble[position.second][position.first] = word.at(i);
				position = incrementPosition(position, *direction);
			} else {
				emptyJumble();
				break;
			}

			if(i + 1 == word.length()) {
				placed = true;
			}
		}
	}

	for(int i = 0; i < *size; i++) {
		for(int j = 0; j < *size; j++) {
			if(jumble[i][j] == NULL) {
				jumble[i][j] = generateRandomCharacter();
			}
		}
	}
	
}

pair<int, int> JumblePuzzle::generateRandomPosition() {
	return make_pair(int(rand() % *size), int(rand() % *size));
}

char JumblePuzzle::generateRandomDirection() {
	switch(rand() % 4) {
		case 0:
			return 'n';
			break;
		case 1:
			return 'e';
			break;
		case 2:
			return 's';
			break;
		case 3:
			return 'w';
			break;
	}
}

bool JumblePuzzle::isPositionValid(pair<int, int> position) {
	int x = position.first;
	int y = position.second;
	return (isCoordinateValid(x) && isCoordinateValid(y));
}

bool JumblePuzzle::isCoordinateValid(int coordinate) {
	return (coordinate >= 0 && coordinate < *size);
}

pair<int, int> JumblePuzzle::incrementPosition(pair<int, int> position, char direction) {
	switch(direction) {
		case 'n':
			position.second -= 1;
			break;
		case 'e':
			position.first += 1;
			break;
		case 's':
			position.second += 1;
			break;
		case 'w':
			position.first -= 1;
			break;
	}
	return position;
}

char JumblePuzzle::generateRandomCharacter() {
	return char(rand() % 26 + 97); 
}