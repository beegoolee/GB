#include <iostream>

namespace Counter {
	size_t iStudentsCount = 0;
};

class Person {

protected:
		
	std::string sName = "";
	unsigned short iAge = 0;
	unsigned short iWeight = 0;
	char cGender = 'M';
	
public:

	void __fastcall setName(std::string sNewName) {
		this->sName = sNewName;
	}

	void __fastcall setAge(unsigned short iNewAge) {
		this->iAge = iNewAge;
	}

	void __fastcall setWeight(unsigned short iNewWeight) {
		this->iWeight = iNewWeight;
	}

	void __fastcall setGender(char cNewGender) {
		this->cGender = cNewGender;
	}
};


class Student : public Person {
	
private:
		
	unsigned short iGrade = 0;

public:

	Student( std::string sName, unsigned short iAge, unsigned short iWeight, unsigned short iGrade, char cGender ) {
		this->setName(sName);
		this->setAge(iAge);
		this->setWeight(iWeight);
		this->setGrade(iGrade);
		this->setGender(cGender);

		Counter::iStudentsCount++;
	}

	void __fastcall setGrade(unsigned short iNewGrade) {
		this->iGrade = iNewGrade;
	}

	void gradeUp() {
		this->iGrade++;
	}
	
	void printInfo() {
		std::cout << "Name: " << this->sName << std::endl;
		std::cout << "Age: " << this->iAge << std::endl;
		std::cout << "Weight: " << this->iWeight << std::endl;
		std::cout << "Gender: " << this->cGender << std::endl;
		std::cout << "Grade: " << this->iGrade << std::endl << std::endl;
	}
};


class Fruit {

protected:

	std::string sName = "";
	std::string sColor = "";

public:

	Fruit(std::string sName = "", std::string sColor = "") {
		this->sName = sName;
		this->sColor = sColor;
	}

	std::string const getName() {
		return this->sName;
	}

	std::string const getColor() {
		return this->sColor;
	}
};

class Apple : public Fruit{

public:

	Apple(std::string sName = "apple", std::string sColor = "red") {
		this->sName = sName;
		this->sColor = sColor;
	}
};

class Banana : public Fruit {

public:

	Banana(std::string sName = "banana", std::string sColor = "yellow") {
		this->sName = sName;
		this->sColor = sColor;
	}
};

class GrannySmith : public Apple {

public:

	GrannySmith(std::string sName = "Granny Smith apple", std::string sColor = "green") {
		this->sName = sName;
		this->sColor = sColor;
	}
};

int main() {
	
	// task 1

	Student student1("Ivan", 20, 70, 3, 'M');
	Student student2("Elena", 21, 55, 4, 'F');
	Student student3("Sergey", 25, 80, 5, 'M');

	student1.printInfo();
	student2.printInfo();
	student3.printInfo();

	std::cout << "Students count is " << Counter::iStudentsCount << std::endl << std::endl;
	
	/**/
	//task 2

	Apple a("red");
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";







	/**/

	//task 3

	// За транслит просьба не ругать сильно, так удобнее ориентироваться. 
	// Ниже представлен своего рода прототип, это не законченный полноценный код, ни коим образом. Так было проще изложить мысль
	
	// Перечисление мастей карточной колоды
	enum E_СardSuit{ 
		CHERVI,
		KRESTI,
		PIKI,
		BUBY
	};

	// Перечисление всех карт колоды из 52 карт. Номинал туза по-умолчанию считаем за 11, альтернативу учтем позднее при просчете очков. 
	enum E_СardPicture : unsigned short{ 
		TWO = 2,
		THREE = 3,
		FOUR = 4,
		FIVE = 5,
		SIX = 6,
		SEVEN = 7,
		EIGHT = 8,
		NINE = 9,
		TEN = 10,
		VALET = 10,
		DAMA = 10,
		KOROL = 10,
		TUZ = 11
	};


	// класс, описывающий игральную карту. Имеет свойства: масть, номинал (количество очков за данную карту), "картинка (валет, десятка, туз - вот это все)"
	class Card {

	private:

		E_СardPicture picture = E_СardPicture::TWO;
		E_СardSuit suit = E_СardSuit::CHERVI;
		unsigned short iNominal = this->picture;
	
	public:
		Card(E_СardSuit suit = CHERVI, E_СardPicture picture = TWO) {
			this->suit = suit;
			this->picture = picture;
		}

		E_СardSuit getCardSuit() {
			return this->suit;
		}
		
		E_СardPicture getCardPicture() {
			return this->picture;
		}
	};


	// класс игрока. Каждый игрок - есть обьект, обладающий "рукой" (массив карт в своем распоряжении), и текущим количеством очков (просчитывается на основании "руки")
	class Player {

	private:
		std::string sName = "";
		Card hand[2]; //в будущем это должен быть динамический массив обьектов класса Card. "Рука" игрока
		unsigned short iCurrentScore; // текущий счет

	public:

		void getOneMoreCard() {
			// берем еще одну карту из колоды, кладем в массив hand
		}

		void checkHand() {
			// проходим в цикле руку игрока, рассчитывая очки iCurrentScore. Попутно проверяем, прошли ли границу в 21 очко. 
			// Если в колоде есть туз(ы), и количество очков превышает 21 - пробуем поместиться в лимит, применив альтернативный номинал тузов (единица)
			// Если игрок превысил лимит и финт с тузами не помог - обьявляем его проигравшим. Иначе - игра продолжается
		}

		void changeTurn() {
			// передаем ход другому игроку (ну тут только игрок-человек передает ход дилеру, получается)
		}
	};


	// класс для непосредственно работы игры и взаимодействия между игроками и общей колодой
	class Game {

	private:
		const unsigned short DECK_SIZE = 52;
		const unsigned short SUITS_COUNT = 4;
		const unsigned short PICTURES_COUNT = 13;

		E_СardSuit arSuits[4] = {
			CHERVI,
			KRESTI,
			PIKI,
			BUBY
		};

		E_СardPicture arPictures[13] = {
			TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, VALET, DAMA, KOROL, TUZ
		};

		// колода карт. Динамическая, по мере раздачи - количество элементов будет уменьшаться 
		Card deck[52];

		Player Dealer;
		Player Player;

	public:

		Game() {
			for (unsigned short i = 0; i < this->DECK_SIZE; i++) {
				for (unsigned short j = 0; j < this->SUITS_COUNT; j++) {
					for (unsigned short k = 0; k < this->PICTURES_COUNT; k++) {
						deck[i] = Card(arSuits[j], arPictures[k]); // инициализируем общую колоду при старте игры
					}
				}
			}
		}

		Card getCard() {
			// делаем рандомную комбинацию "масть - картинка". Проверяем, есть ли такая карта в массиве deck. 
			// Если уже есть - значит такая карта уже в игре, генерим следующий возможны вариант

			for (size_t i = 0; i < this->DECK_SIZE; i++) {
			
				if (true /*нашли карту*/) {
					eraseCard(i);
					return Card(CHERVI, TWO);
				}
			}
		}

		void eraseCard(unsigned short iCardIndex) {
		 // удаляем карту из общей колоды
		}

		void endGame(std::string sResultMessage) {
			// если кто-то проиграл/выиграл - он вызывает это событие с сообщением в качестве аргумента
			std::cout << sResultMessage << std::endl;

			//очищаем память от динамической колоды this->deck, очищаем память от "рук" игроков Dealer и Player
		}
	};

	return 0;
}