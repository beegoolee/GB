#include <iostream>
#include "ArrayInt.h"
#include <vector>
#include <set>


int main() {
	//task 1 

	ArrayInt arInt(10);
	arInt.erase();

	arInt.push_back(12);
	arInt.push_back(78);
	arInt.push_back(3);
	arInt.push_back(256);
	arInt.push_back(250);
	arInt.push_back(1);
	arInt.push_back(13);
	arInt.push_back(12);
	arInt.push_back(78);
	arInt.push_back(99);

	arInt.pop_front(); // сносим 12 в начале
	arInt.pop_back(); // сносим 99 в конце

	std::cout << "Unsorted:" << std::endl;
	arInt.print(); // выводим содержимое до сортировки

	arInt.sort(); // сортируем, по возрастанию значений

	std::cout << std::endl << "Sorted:" << std::endl;
	arInt.print(); // выводим содержимое после сортировки
	
	//task 2
	
	std::vector<int> vector = {12, 77, 34, 12, 34, 77, 67}; // 7 элементов, уникальных - 4

	const size_t SIZE = vector.size();

	std::cout << "Vector size is "  << SIZE << std::endl;


	std::set<int> uniques;

	for (size_t i = 0; i < SIZE; i++) {
		uniques.insert(vector[i]);
	}

	std::cout << "Unique elements count is " << uniques.size() << std::endl;

	return 0;
}

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

		//task 3
		Blackjack::E_CardNominal getCardNominal() const {
			return this->cardNominal;
		}
	};

	//task 3

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
		}

		size_t GetValue() const {
			size_t iTotalScore = 0;

			for (size_t i = 0; i < this->cards.size(); i++) {
				iTotalScore += cards[i]->getCardNominal();
			}
			
			if ((iTotalScore < Blackjack::TARGET_SCORE) && (this->iAcesCount > 0)) {
				for (size_t j = 0; j < this->iAcesCount; j++) {
					if (iTotalScore + 10 < Blackjack::TARGET_SCORE) {
						iTotalScore += 10; // поочередно пересчитываем все тузы по номиналу 11 вместо 1 (+10)
					}
				}
			}

			return iTotalScore;
		}
	};
}
