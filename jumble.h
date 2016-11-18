#pragma once

#include <string>

using namespace std;

typedef char* charArrayPtr;

class JumblePuzzle {
public:
	JumblePuzzle(const string, const string);
	JumblePuzzle& operator=(const JumblePuzzle& rhs);
	JumblePuzzle(const JumblePuzzle&);
	~JumblePuzzle();
	int getSize() const;
	charArrayPtr* getJumble() const;
	int getRowPos() const;
	int getColPos() const;
	char getDirection() const;
private:
	int* size;
	charArrayPtr* jumble;
	int* rowPos;
	int* colPos;
	char* direction;
	void emptyJumble();
	void initializeJumble(const string);
	pair<int, int> generateRandomPosition();
	char generateRandomDirection();
	bool isPositionValid(pair<int, int>);
	bool isCoordinateValid(int);
	pair<int, int> incrementPosition(pair<int, int>, char);
	char generateRandomCharacter();
};

class BadJumbleException : public exception {
public:
	explicit BadJumbleException(const string& message) : msg(message) {}
	virtual ~BadJumbleException() throw() {}
	virtual const char* what() const throw() {
		return msg.c_str();
	}
protected:
	string msg;
};
