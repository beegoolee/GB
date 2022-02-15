#include <iostream>

// task 1

class Figure {

protected:
	virtual float const area()  = 0;

};

class Parallelogram : public Figure {

protected:
	float fSide1;
	float fSide2;

public:
	Parallelogram(float const fSide1 = 0.0f, float const fSide2 = 0.0f) {
		setSide1(fSide1);
		setSide2(fSide2);
	}

	void setSide1(float const fValue) {
		this->fSide1 = fValue;
	}

	void setSide2(float const fValue) {
		this->fSide2 = fValue;
	}

	// эту функцию нет смысла переопределять в дочерних классах четырехугольников из данной задачи
	virtual float const area() override { 
		return (fSide1 * fSide2);
	}

};

class Rectangle : public Parallelogram {

public:
	Rectangle(float const fSide1 = 0.0f, float const fSide2 = 0.0f) {
		setSide1(fSide1);
		setSide2(fSide2);
	}
};

class Square : public Parallelogram {

public:
	Square(float const fSide1 = 0.0f, float const fSide2 = 0.0f) {
		setSide1(fSide1);
		setSide2(fSide2);
	}

};

class Rhombus : public Parallelogram {

public:
	Rhombus(float const fSide1 = 0.0f, float const fSide2 = 0.0f) {
		setSide1(fSide1);
		setSide2(fSide2);
	}

};

class Circle : public Figure {

private:
	float fRadius;
	float const fPi = 3.14f;

public:
	Circle(float const fRadius) {
		setRadius(fRadius);
	}

	void setRadius(float const fValue) {
		this->fRadius = fValue;
	}

	virtual float const area() override {
		return (this->fRadius * this->fRadius * this->fPi);
	}
};


// task 2

class Car {

protected:
	std::string sCompany = "";
	std::string sModel = "";

public:
	Car() {
		std::cout << "Car Class constructor. Company -  " << this->sCompany << ". Model - " << this->sModel << std::endl;
	}
	~Car() {
		std::cout << "Car Class destructor" << std::endl << std::endl;
	}
};

class PassengerCar : protected virtual Car {

protected:
	std::string sCompany = "BMW";
	std::string sModel = "320i";

public:
	PassengerCar() {
		std::cout << "PassengerCar Class constructor. Company -  " << this->sCompany << ". Model - " << this->sModel << std::endl;
	}
	~PassengerCar() {
		std::cout << "PassengerCar Class destructor" << std::endl << std::endl;
	}
};

class Bus : protected virtual Car {

protected:
	std::string sCompany = "LIAZ";
	std::string sModel = "677";

public:
	Bus() {
		std::cout << "Bus Class constructor. Company -  " << this->sCompany << ". Model - " << this->sModel << std::endl;
	}
	~Bus() {
		std::cout << "Bus Class destructor" << std::endl << std::endl;
	}
};

class Minivan : protected Bus, PassengerCar {
protected:
	std::string sCompany = "Mercedes";
	std::string sModel = "Viano";

public:
	Minivan() {
		std::cout << "Minivan Class constructor. Company -  " << this->sCompany << ". Model - " << this->sModel << std::endl;
	}
	~Minivan() {
		std::cout << "Minivan Class destructor" << std::endl << std::endl;
	}
};



// task 3

class Fraction {
private:
	int iInum; // числитель
	int iDenom; // знаменатель

public:
	Fraction(int const iInumerator, int const iDenominator) {
		this->iInum = iInumerator;

		if (iDenominator != 0) {
			this->iDenom = iDenominator;
		}
		else {
			std::cout << "Denominator can't be equal to zero, value was set up to '1'" << std::endl;
			this->iDenom = 1;
		}
	}

	const int getInum(){
		return this->iInum;
	}

	const int getDenom(){
		return this->iDenom;
	}

	const float getFloatValue() {
		return (float)(this->iInum) / this->iDenom;
	}

	const void print() {
		std::cout << this->iInum << " / " << this->iDenom << std::endl;
	}


	Fraction operator + (Fraction& frac) {
		int iInumSum = (this->getInum() * frac.getDenom()) + (this->getDenom() * frac.getInum());
		int iDenomSum = this->getDenom() * frac.getDenom();

		Fraction FracResult(iInumSum, iDenomSum);
		return FracResult;
	};

	// бинарный минус
	Fraction operator - (Fraction& frac) {
		int iInumSum = (this->getInum() * frac.getDenom()) - (this->getDenom() * frac.getInum());
		int iDenomSum = this->getDenom() * frac.getDenom();

		Fraction FracResult(iInumSum, iDenomSum);
		return FracResult;
	}

	Fraction operator * (Fraction& frac) {
		int iInumSum = this->getInum() * frac.getDenom();
		int iDenomSum = this->getDenom() * frac.getInum();

		Fraction FracResult(iInumSum, iDenomSum);
		return FracResult;
	}

	Fraction operator / (Fraction& frac) {
		int iInumSum = this->getInum() * frac.getInum();
		int iDenomSum = this->getDenom() * frac.getDenom();

		Fraction FracResult(iInumSum, iDenomSum);
		return FracResult;
	}

	//унарный минус
	Fraction operator - () {
		Fraction FracResult(-(this->getInum()), this->getDenom());
		return FracResult;
	}

	bool operator == (Fraction& frac) {
		return (this->getFloatValue() == frac.getFloatValue());
	}

	bool operator != (Fraction& frac) {
		return !(*this == frac);
	}

	bool operator > (Fraction& frac) {
		return (this->getFloatValue() > frac.getFloatValue());
	}

	bool operator <= (Fraction& frac) {
		return !(*this > frac);
	}

	bool operator < (Fraction& frac) {
		return (this->getFloatValue() < frac.getFloatValue());
	}

	bool operator >= (Fraction& frac) {
		return !(*this < frac);
	}

};



// task 4

namespace Blackjack {

	enum E_CardSuit { // соответственно - буби, черви, крести, пики
		DIAMONDS, HEARTS, CLUBS, SPADES
	};

	enum E_CardNominal { // соответственно - буби, черви, крести, пики
		TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
	};

	class Card {

	private:
		Blackjack::E_CardSuit cardSuit;
		Blackjack::E_CardNominal cardNominal;
		bool isVisible = false;

	public:

		Blackjack::Card(Blackjack::E_CardSuit suit, Blackjack::E_CardNominal nominal) {
			this->cardSuit = suit;
			this->cardNominal = nominal;
		}

		void Flip() {
			this->isVisible = !(this->isVisible);
		}

		int getValue() {
			switch (this->cardNominal) {
			case TWO:
				return 2;
			case THREE:
				return 3;
			case FOUR:
				return 4;
			case FIVE:
				return 5;
			case SIX:
				return 6;
			case SEVEN:
				return 7;
			case EIGHT:
				return 8;
			case NINE:
				return 9;
			case TEN:
			case JACK:
			case QUEEN:
			case KING:
				return 10;
			case ACE:
				return 1;
			default:
				return 0;
			}
		}
	};
}

int main() {

	//task 1

	Parallelogram shape1(5.1f, 25.3f);
	Rectangle shape2(7.11f, 3.90f);
	Square shape3(13.13f, 18.890f);
	Rhombus shape4(72.5f, 67.3f);
	Circle shape5(16.15f);

	std::cout << "Parallelogram area is " << shape1.area() << std::endl;
	std::cout << "Rectagle area is " << shape2.area() << std::endl;
	std::cout << "Square area is " << shape3.area() << std::endl;
	std::cout << "Phombus area is " << shape4.area() << std::endl;
	std::cout << "Circle area is " << shape5.area() << std::endl << std::endl;


	//task 2

	// Car* a = new Car();
	// PassengerCar* b = new PassengerCar();
	// Bus* c = new Bus();

	Minivan* d = new Minivan(); // конструктор и деструктор Car вызываются лишь один раз
	delete d;


	//task 3

	// генерим дробей для тестов
	Fraction frac1(2, 7);
	Fraction frac2(3, 4);
	Fraction frac3(6, 5);
	Fraction frac4(11, 12);

	// сложение дробей
	Fraction fracPlus = frac1 + frac2;
	fracPlus.print(); 

	// вычитание дробей
	Fraction fracMinus = frac3 - frac1;
	fracMinus.print(); 

	// умножение дробей
	Fraction fracMultiply = frac2 * frac3;
	fracMultiply.print();

	// деление дробей
	Fraction fracDivide = frac4 / frac2;
	fracDivide.print();

	//применяем унарный минус
	
	Fraction fracUnoMinus = -frac1;
	fracUnoMinus.print();

	std::cout << std::endl;

	// сравнения, выводим 0/1 - соответственно, false/true
	std::cout << (frac1 == frac1) << std::endl; 
	std::cout << (frac2 != frac2) << std::endl;
	std::cout << (frac3 > frac4) << std::endl;
	std::cout << (frac4 < frac1) << std::endl;
	std::cout << (frac1 <= frac2) << std::endl; 
	std::cout << (frac2 >= frac4) << std::endl;


	// task 4

	Blackjack::Card gameCard(Blackjack::HEARTS, Blackjack::ACE);

	return 0;
}
