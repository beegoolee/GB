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

	// �� �������� ������� �� ������ ������, ��� ������� ���������������. 
	// ���� ����������� ������ ���� ��������, ��� �� ����������� ����������� ���, �� ���� �������. ��� ���� ����� �������� �����
	
	// ������������ ������ ��������� ������
	enum E_�ardSuit{ 
		CHERVI,
		KRESTI,
		PIKI,
		BUBY
	};

	// ������������ ���� ���� ������ �� 52 ����. ������� ���� ��-��������� ������� �� 11, ������������ ����� ������� ��� �������� �����. 
	enum E_�ardPicture : unsigned short{ 
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


	// �����, ����������� ��������� �����. ����� ��������: �����, ������� (���������� ����� �� ������ �����), "�������� (�����, �������, ��� - ��� ��� ���)"
	class Card {

	private:

		E_�ardPicture picture = E_�ardPicture::TWO;
		E_�ardSuit suit = E_�ardSuit::CHERVI;
		unsigned short iNominal = this->picture;
	
	public:
		Card(E_�ardSuit suit = CHERVI, E_�ardPicture picture = TWO) {
			this->suit = suit;
			this->picture = picture;
		}

		E_�ardSuit getCardSuit() {
			return this->suit;
		}
		
		E_�ardPicture getCardPicture() {
			return this->picture;
		}
	};


	// ����� ������. ������ ����� - ���� ������, ���������� "�����" (������ ���� � ����� ������������), � ������� ����������� ����� (�������������� �� ��������� "����")
	class Player {

	private:
		std::string sName = "";
		Card hand[2]; //� ������� ��� ������ ���� ������������ ������ �������� ������ Card. "����" ������
		unsigned short iCurrentScore; // ������� ����

	public:

		void getOneMoreCard() {
			// ����� ��� ���� ����� �� ������, ������ � ������ hand
		}

		void checkHand() {
			// �������� � ����� ���� ������, ����������� ���� iCurrentScore. ������� ���������, ������ �� ������� � 21 ����. 
			// ���� � ������ ���� ���(�), � ���������� ����� ��������� 21 - ������� ����������� � �����, �������� �������������� ������� ����� (�������)
			// ���� ����� �������� ����� � ���� � ������ �� ����� - ��������� ��� �����������. ����� - ���� ������������
		}

		void changeTurn() {
			// �������� ��� ������� ������ (�� ��� ������ �����-������� �������� ��� ������, ����������)
		}
	};


	// ����� ��� ��������������� ������ ���� � �������������� ����� �������� � ����� �������
	class Game {

	private:
		const unsigned short DECK_SIZE = 52;
		const unsigned short SUITS_COUNT = 4;
		const unsigned short PICTURES_COUNT = 13;

		E_�ardSuit arSuits[4] = {
			CHERVI,
			KRESTI,
			PIKI,
			BUBY
		};

		E_�ardPicture arPictures[13] = {
			TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, VALET, DAMA, KOROL, TUZ
		};

		// ������ ����. ������������, �� ���� ������� - ���������� ��������� ����� ����������� 
		Card deck[52];

		Player Dealer;
		Player Player;

	public:

		Game() {
			for (unsigned short i = 0; i < this->DECK_SIZE; i++) {
				for (unsigned short j = 0; j < this->SUITS_COUNT; j++) {
					for (unsigned short k = 0; k < this->PICTURES_COUNT; k++) {
						deck[i] = Card(arSuits[j], arPictures[k]); // �������������� ����� ������ ��� ������ ����
					}
				}
			}
		}

		Card getCard() {
			// ������ ��������� ���������� "����� - ��������". ���������, ���� �� ����� ����� � ������� deck. 
			// ���� ��� ���� - ������ ����� ����� ��� � ����, ������� ��������� �������� �������

			for (size_t i = 0; i < this->DECK_SIZE; i++) {
			
				if (true /*����� �����*/) {
					eraseCard(i);
					return Card(CHERVI, TWO);
				}
			}
		}

		void eraseCard(unsigned short iCardIndex) {
		 // ������� ����� �� ����� ������
		}

		void endGame(std::string sResultMessage) {
			// ���� ���-�� ��������/������� - �� �������� ��� ������� � ���������� � �������� ���������
			std::cout << sResultMessage << std::endl;

			//������� ������ �� ������������ ������ this->deck, ������� ������ �� "���" ������� Dealer � Player
		}
	};

	return 0;
}