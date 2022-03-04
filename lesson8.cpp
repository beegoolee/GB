#include <iostream>

// task 1
class DivisionByZero : public std::invalid_argument {
public:
	DivisionByZero(std::string description) : std::invalid_argument(description) {}

	const char* what() const noexcept override {
		return std::invalid_argument::what();
	}
};

template <typename T1, typename T2>
float div(T1 numerator, T2 denominator) {
	if (denominator == 0.0f) {
		throw DivisionByZero("Denominator can not be equal to zero");
	}
	else {
		return (static_cast<float>(numerator) / denominator);
	}
}




// task 2

class Ex {
private:
	int x;
public:
	Ex(int number) {
		this->x = number;
	}
};


class Bar {
private:
	int y;
public:
	Bar(int number = 0) {
		this->y = number;
	}

	void set(int a) {
		if (this->y + a > 100) {
			throw Ex(this->y * a);
		}
		else {
			this->y = a;
		}
	}

	int getY() const {
		return this->y;
	}
};




// task 3

class OffTheField : public std::logic_error {
private:
	int tryX;
	int tryY;
	int curX;
	int curY;

public:
	OffTheField(std::string description, int tryX, int tryY, int curX, int curY ) : std::logic_error(description) {
		this->tryX = tryX;
		this->tryY = tryY;

		this->curX = curX;
		this->curY = curY;
	};

	void getInfo() const {
		std::cout << "Tried to allocate coordinats:" << this->tryX << ":" << this->tryY << " from " << this->curX << ":" << this->curY << std::endl;
	}

	const char* what() const noexcept override {
		return std::logic_error::what();
	}
};

class IllegalCommand : public std::invalid_argument {

public:
	IllegalCommand(std::string description) : std::invalid_argument(description) {};

	const char* what() const noexcept override {
		return std::invalid_argument::what();
	}
};

enum E_Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

const size_t FIELD_SIZE = 10;

class Robot {
private:
	int xCoord = 5;
	int yCoord = 5;
	char field[FIELD_SIZE][FIELD_SIZE];

public:
	Robot() {
		for (size_t i = 0; i < FIELD_SIZE; i++) {
			for (size_t j = 0; j < FIELD_SIZE; j++) {
				this->field[i][j] = '_';
			}
		}

		this->field[this->yCoord][this->xCoord] = this->getSignature();
	};

	void moveTo(int deltaX, int deltaY) {
		this->field[this->getY()][this->getX()] = '_';
		int iNewX = this->xCoord + deltaX;
		int iNewY = this->yCoord + deltaY;

		try {
			if (iNewX < 0 || iNewX >= FIELD_SIZE || iNewY < 0 || iNewY >= FIELD_SIZE) {
				throw OffTheField("Tried to get off the field", iNewX, iNewY, this->xCoord, this->yCoord);
			}
			else {
				this->xCoord = iNewX;
				this->yCoord = iNewY;
			}
		}
		catch (const OffTheField& e) {
			e.getInfo();
			std::cout << e.what() <<std::endl;
		}

		this->field[this->yCoord][this->xCoord] = this->getSignature();
	}

	void printField() const{
		std::cout << " __________" << std::endl;
		for (size_t i = 0; i < FIELD_SIZE; i++) {
			std::cout << '|';
			for (size_t j = 0; j < FIELD_SIZE; j++) {
				std::cout << this->field[i][j];
			}
			std::cout << '|' << std::endl;
		}
	}

	size_t getX() const {
		return this->xCoord;
	}

	size_t getY() const {
		return this->yCoord;
	}

	char getSignature() const {
		return 'X';
	}
};



int main() {

	
	// task 1
	try {
		float result = div<int, int>(12, 5); //success
		result = div<int, int>(12, 0); //throw error
		std::cout << result << std::endl;
	}
	catch (const DivisionByZero& e) {
		std::cout << e.what() << std::endl;
	}

	// task 2
	int n = 1;
	Bar bar(n);

	std::cout << "Input some integer";

	try {
		while (true) {
			std::cin >> n;
			bar.set(n);

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			else if (n == 0) {
				throw bar;
			}
		}
	}
	catch (...) {
		std::cout << "bar.Y equals " << bar.getY() << std::endl;
	}

	// task 3 

	Robot robot;

	int iDirectionIndex;
	bool isInputFailed;
	const size_t DIRECTIONS_COUNT = 8;
	E_Direction directions[DIRECTIONS_COUNT] = {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT
	};

	do {
		std::cout << "1. Up" << std::endl << "2. Down" << std::endl << "3. Left" << std::endl << "4. Right" << std::endl;
		std::cout << "5. UP_LEFT" << std::endl << "6. UP_RIGHT" << std::endl << "7. DOWN_LEFT" << std::endl << "8. DOWN_RIGHT" << std::endl << std::endl;
		std::cout << "Choose the direction to move (1-9): " << std::endl;
		std::cin >> iDirectionIndex;

		isInputFailed = std::cin.fail();

		std::cout << "\x1B[2J\x1B[H";

		if (isInputFailed) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else {
			short deltaX = 0;
			short deltaY = 0;

			try {
				iDirectionIndex--; // index in arrays starts from 0

				switch (directions[iDirectionIndex]) {
				case UP:
					deltaY = -1;
					break;
				case UP_LEFT:
					deltaX = -1;
					deltaY = -1;
					break;
				case UP_RIGHT:
					deltaX = 1;
					deltaY = -1;
					break;
				case LEFT:
					deltaX = -1;
					break;
				case RIGHT:
					deltaX = 1;
					break;
				case DOWN:
					deltaY = 1;
					break;
				case DOWN_LEFT:
					deltaX = -1;
					deltaY = 1;
					break;
				case DOWN_RIGHT:
					deltaX = 1;
					deltaY = 1;
					break;
				default:
					throw IllegalCommand("Invalid direction index");
					break;
				}
			}
			catch (const IllegalCommand& e) {
				std::cout << e.what() << std::endl;
			}


			robot.moveTo(deltaX, deltaY);

			robot.printField();
		}

	} while (true);




	return 0;
}