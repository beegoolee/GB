#include <iostream>
#include <vector>
#include <iomanip>

//task1
int getSomeInt() {
	int iInput;
	bool isFailed = false;

	std::cout << "Enter some integer: " << std::endl;

	do {
		std::cin >> iInput;
		isFailed = std::cin.fail();

		if (isFailed) {
			std::cout << "Invalid value, enter another data" << std::endl;

			std::cin.clear(); 
			std::cin.ignore(32767, '\n');
		}

	} while (isFailed);

	return iInput;
}

//task 2
namespace std {
	std::ostream& endll(std::ostream& stream) {
		stream << std::endl << std::endl;
		return stream;
	}
}


int main() {
	
	//task 1
	int iResult = getSomeInt();

	//task 2
	std::cout << "Row 1" << std::endll << "Row 4";

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
	const size_t HOUSE_STOP_SCORE = 16;

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

		//task 5
		Blackjack::E_CardSuit getCardSuit() const {
			return this->cardSuit;
		}

		bool getVisibility() const {
			return this->isVisible;
		}

		std::ostream& operator<< (std::ostream& stream) {
			if (this->getVisibility()) {
				stream << "XX";
			}
			else {
				stream << this->getCardNominal() << " " << this->getCardSuit();
			}

			return stream;
		}
	};

	class Hand {
	protected:
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

	class GenericPlayer : public Hand {
	protected:
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

		//task 5
		std::ostream& operator<< (std::ostream& stream) {
			stream << this->sName << " ";

			for (size_t i = 0; i < this->cards.size(); i++) {
				stream << this->cards[i];
			}

			stream << std::endl <<"Total score is " << this->GetValue() << " ";
			
			return stream;
		}
	};

	//task 3
	class Player : protected GenericPlayer {
	public:

		Player(std::string sName = "Player") {
			this->sName = sName;
		}

		virtual bool isHitting() const override {
			bool isFailed = false;
			bool iNeedOneMore = false;
			char cAnswer;

			std::cout << "Do you need one more card? (Y\N): " << std::endl;

			do {
				std::cin >> cAnswer;
				isFailed = (cAnswer == 'Y' || cAnswer == 'N');

				if (isFailed) {
					std::cout << "Invalid answer, use Y or N" << std::endl;

					std::cin.clear();
					std::cin.ignore(32767, '\n');
				}

			} while (isFailed);


			if (cAnswer == 'Y') {
				iNeedOneMore = true;
			}
			else if(cAnswer == 'N') {
				iNeedOneMore = false;
			}

			return iNeedOneMore;
		}

		void Win() const {
			std::cout << this->sName << " win!" << std::endl;
		}

		void Lose() const {
			std::cout << this->sName << " lose!" << std::endl;
		}

		void Push() const {
			std::cout << this->sName << " draw!" << std::endl;
		}
	};

	//task 4
	class House : protected GenericPlayer {
	public:

		virtual bool isHitting() const override {
			bool iNeedOneMore = (this->GetValue() < HOUSE_STOP_SCORE); // if hand score is more than 16 - we should stop
			return iNeedOneMore;
		}

		void FlipFirstCard() {
			this->cards[0]->Flip();
		}
	};
}