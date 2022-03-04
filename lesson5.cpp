#include <iostream>
#include <vector>
#include <set>

using namespace std;

//task 1

template <class T>
class Pair1 {

private:
	T Tfirst;
	T Tsecond;

public:
	Pair1(T a, T b){
		this->Tfirst = a;
		this->Tsecond = b;
	}

	T first() const {
		return this->Tfirst;
	}

	T second() const {
		return this->Tsecond;
	}

};


//task 2

template <class T1, class T2>
class Pair {

protected:
	T1 Tfirst;
	T2 Tsecond;

public:
	Pair(T1 a, T2 b) {
		this->Tfirst = a;
		this->Tsecond = b;
	}

	T1 first() const {
		return this->Tfirst;
	}

	T2 second() const {
		return this->Tsecond;
	}

};


//task 3

template <class T2>
class StringValuePair: public Pair<std::string, T2> {

public:
	StringValuePair(std::string a, T2 b) : Pair<std::string, T2>(a, b) {}

};


int main() {

	//task 1

	Pair1<int> p1(6, 9);
	cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	cout << endl;


	//task 2

	Pair<int, double> p3(6, 7.8);
	cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

	const Pair<double, int> p4(3.4, 5);
	cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';
	cout << endl;


	//task 3

	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';


	return 0;
}


//task 4

namespace Blackjack {

	enum E_CardSuit {
		DIAMONDS, HEARTS, CLUBS, SPADES
	};

	enum E_CardNominal {
		TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
	};

	const size_t TARGET_SCORE = 21;

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

		int getValue() const {
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

		Blackjack::E_CardNominal getCardNominal() const {
			return this->cardNominal;
		}
	};

	class Hand {
	private:
		std::vector<Blackjack::Card*> cards;
		size_t iAcesCount = 0;

	public:
		void Add(Blackjack::Card* card) {
			this->cards.push_back(card);
			if (card->getCardNominal() == Blackjack::E_CardNominal::ACE) this->iAcesCount++;
		}

		void Clear() {
			this->cards.clear();
			
			for (size_t i = 0; i < this->cards.size(); i++) {
				delete this->cards[i];
			};
		}

		size_t GetValue() const {
			size_t iTotalScore = 0;

			for (size_t i = 0; i < this->cards.size(); i++) {
				iTotalScore += cards[i]->getCardNominal();
			}

			if ((iTotalScore < Blackjack::TARGET_SCORE) && (this->iAcesCount > 0)) {
				for (size_t j = 0; j < this->iAcesCount; j++) {
					if (iTotalScore + 10 < Blackjack::TARGET_SCORE) {
						iTotalScore += 10;
					}
				}
			}

			return iTotalScore;
		}

	};


	//task 4

	class GenericPlayer : public Hand {
	private:
		std::string sName;

	public:

		virtual bool isHitting() const = 0;

		bool isBoosted() const{
			const size_t iHandScore = this->GetValue();
			const bool isBoosted = iHandScore > TARGET_SCORE;
			
			return isBoosted;
		};

		void Bust() const {
			if (this->isBoosted()) std::cout << this->sName << " is boosted" << std::endl;
		};
	};
}