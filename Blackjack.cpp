#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>        
#include <cstdlib>  
#include <random>   

// BLACKJACK

enum E_CardSuit {
	DIAMONDS, HEARTS, CLUBS, SPADES
};

enum E_CardNominal {
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
};

const size_t TARGET_SCORE = 21;
const size_t HOUSE_STOP_SCORE = 16;
const size_t DECK_SIZE = 52;

class Card {

private:
	E_CardSuit cardSuit;
	E_CardNominal cardNominal;
	bool isVisible = false;

public:

	Card(E_CardSuit suit, E_CardNominal nominal) {
		this->cardSuit = suit;
		this->cardNominal = nominal;
	}

	void Flip() {
		this->isVisible = !(this->isVisible);
	}

	int getCardNominal() const {
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

	std::string getCardPicture() const {
		switch (this->cardNominal) {
		case TWO:
			return "2";
		case THREE:
			return "3";
		case FOUR:
			return "4";
		case FIVE:
			return "5";
		case SIX:
			return "6";
		case SEVEN:
			return "7";
		case EIGHT:
			return "8";
		case NINE:
			return "9";
		case TEN:
			return "10";
		case JACK:
			return "J";
		case QUEEN:
			return "Q";
		case KING:
			return "K";
		case ACE:
			return "A";
		default:
			return " ";
		}
	}

	std::string getCardSuit() const {
		switch (this->cardSuit) {
		case DIAMONDS:
			return "Diamonds";
		case HEARTS:
			return "Hearts";
		case CLUBS:
			return "Clubs";
		default:
		case SPADES:
			return "Spades";
		}
	}

	bool getVisibility() const {
		return this->isVisible;
	}

	void print() const {
		if (this->getVisibility()) {
			std::cout << "XX" << " ";
		}
		else {
			std::cout << " | Card picture: " << this->getCardPicture() << " Suit: " << this->getCardSuit() << " | ";
		}
	}

	std::ostream& operator<< (std::ostream& stream) {
		if (this->getVisibility()) {
			stream << "XX";
		}
		else {
			stream << this->getCardPicture() << " " << this->getCardSuit();
		}

		return stream;
	}
};

class Hand {
protected:
	std::vector<Card*> cards;
	size_t iAcesCount = 0;

public:
	void Add(Card* card) {
		this->cards.push_back(card);
		if (card->getCardNominal() == E_CardNominal::ACE) this->iAcesCount++;
	}

	void Clear() {
		this->cards.clear();
	}

	size_t GetValue() const {
		size_t iTotalScore = 0;

		for (size_t i = 0; i < this->cards.size(); i++) {
			iTotalScore += cards[i]->getCardNominal();
		}

		if ((iTotalScore < TARGET_SCORE) && (this->iAcesCount > 0)) {
			for (size_t j = 0; j < this->iAcesCount; j++) {
				if (iTotalScore + 10 < TARGET_SCORE) {
					iTotalScore += 10;
				}
			}
		}

		return iTotalScore;
	}

	~Hand() {
		this->Clear();
	}
};

class GenericPlayer : public Hand {
protected:
	std::string sName;

public:

	virtual bool isHitting() const = 0;

	bool isBoosted() const {
		const size_t iHandScore = this->GetValue();
		const bool isBoosted = iHandScore > TARGET_SCORE;

		return isBoosted;
	};

	std::string getPlayerName() const {
		return this->sName;
	}

	void Bust() const {
		if (this->isBoosted()) std::cout << this->sName << " is boosted" << std::endl;
	};

	void print() const {
		std::cout << std::endl << this->sName << " ";
		for (size_t i = 0; i < this->cards.size(); i++) {
			this->cards[i]->print();
		}

		std::cout << std::endl << "Total score is " << this->GetValue() << " " << std::endl;
	}

	std::ostream& operator << (std::ostream& stream) {
		stream << this->sName << " ";

		for (size_t i = 0; i < this->cards.size(); i++) {
			stream << this->cards[i];
		}

		stream << std::endl << "Total score is " << this->GetValue() << " ";

		return stream;
	}
};

class Player : public GenericPlayer {
public:

	Player(std::string sName = "Player") {
		this->sName = sName;
	}

	virtual bool isHitting() const override {
		bool isFailed = false;
		bool iNeedOneMore = false;
		char cAnswer;

		if (!this->isBoosted()) {

			std::cout << "Do you need one more card? (Y or N): " << std::endl;

			do {
				std::cin >> cAnswer;
				isFailed = std::cin.fail();

				if (isFailed) {
					std::cout << "Invalid answer, use Y or N" << std::endl;

					std::cin.clear();
					std::cin.ignore(32767, '\n');
				}
				else {
					if (cAnswer == 'Y') {
						iNeedOneMore = true;
					}
					else if (cAnswer == 'N') {
						iNeedOneMore = false;
					}
					else {
						isFailed = true;
					}
				}

			} while (isFailed);

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

class House : public GenericPlayer {
public:
	House() {
		this->sName = "Dealer (House)";
	}

	virtual bool isHitting() const override {
		bool iNeedOneMore = (this->GetValue() < HOUSE_STOP_SCORE); // if hand score is more than 16 - we should stop
		return iNeedOneMore;
	}

	void FlipFirstCard() {
		this->cards[0]->Flip();
	}
};

//task 3

class Deck : protected Hand {
private:
	std::vector<Card*>::iterator deckIter;

public:
	Deck() {
		this->Populate();
	}

	std::vector<Card*>::iterator getDeckIter() const {
		return this->deckIter;
	}

	void moveDeckIter() {
		this->deckIter++;
	}

	Card& takeCardFromDeck() {
		Card& cardFromDeck = **getDeckIter();
		this->moveDeckIter();

		return cardFromDeck;
	}

	void resetDeckIter() {
		this->deckIter = this->cards.begin();
	}

	void Populate() {
		const short SUITS_COUNT = 4;
		const short NOMINALS_COUNT = 13;

		E_CardSuit arSuits[SUITS_COUNT] = {
			DIAMONDS, HEARTS, CLUBS, SPADES
		};

		E_CardNominal arNominals[NOMINALS_COUNT] = {
			TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
		};

		for (size_t i = 0; i < SUITS_COUNT; i++) {
			for (size_t j = 0; j < NOMINALS_COUNT; j++) {
				this->cards.push_back(new Card(arSuits[i], arNominals[j]));
			}
		}

		this->Shuffle();
		this->resetDeckIter();
	}

	void Shuffle() {

		std::shuffle(this->cards.begin(), this->cards.end(), std::random_device());
	}

	void Deal(Hand& aHand) {
		aHand.Add(&(this->takeCardFromDeck()));
	}

	void AdditionalCards(GenericPlayer& aGenericPlayer) {
		if (aGenericPlayer.isHitting()) {
			aGenericPlayer.Add(&(this->takeCardFromDeck()));
		}
	}

	~Deck() {
		for (size_t i = 0; i < DECK_SIZE; i++) {
			delete this->cards[i];
		}
		this->cards.clear();
	}
};

// task 4

class Game {
private:
	Deck mainDeck;
	House dealer;
	std::vector<Player*> vPlayers;
	bool isGameProceed = true;

public:
	Game(std::vector<std::string> vStrPlayerNames) {
		for (size_t i = 0; i < vStrPlayerNames.size(); i++) {
			vPlayers.push_back(new Player(vStrPlayerNames[i]));
		}
	}

	void stopGame() {
		this->isGameProceed = false;
	}

	bool getIsGameProceed() const {
		return this->isGameProceed;
	}

	void printTable() const {
		std::cout << "\x1B[2J\x1B[H";

		this->dealer.print();

		for (size_t l = 0; l < this->vPlayers.size(); l++) {
			this->vPlayers[l]->print();
		}
	}

	void play() {
		for (size_t i = 0; i < this->vPlayers.size(); i++) {
			for (size_t j = 0; j < 2; j++) {
				this->vPlayers[i]->Add(&(this->mainDeck.takeCardFromDeck()));
			}
		}

		for (size_t k = 0; k < 2; k++) {
			this->dealer.Add(&(this->mainDeck.takeCardFromDeck()));
		}
		this->dealer.FlipFirstCard();

		this->printTable();

		for (size_t m = 0; m < this->vPlayers.size(); m++) {
			if (this->vPlayers[m]->isBoosted()) {
				continue;
			}
			else {
				std::cout << std::endl << "Player " << this->vPlayers[m]->getPlayerName() << std::endl;

				while (this->vPlayers[m]->isHitting()) {
					this->vPlayers[m]->Add(&(this->mainDeck.takeCardFromDeck()));
					this->printTable();
				};
			}
		}

		this->dealer.FlipFirstCard();
		this->printTable();

		while (this->dealer.isHitting()) {
			this->dealer.Add(&(this->mainDeck.takeCardFromDeck()));
			this->printTable();
		};

		unsigned short iCurMaxScore = 0;
		int iMaxScoreHolders = 0;

		for (size_t n = 0; n < this->vPlayers.size(); n++) {
			if ((this->vPlayers[n]->GetValue() > iCurMaxScore) && !this->vPlayers[n]->isBoosted()) {
				iCurMaxScore = this->vPlayers[n]->GetValue();
				iMaxScoreHolders = 1;
			}
			else if (this->vPlayers[n]->GetValue() == iCurMaxScore) {
				iMaxScoreHolders++;
			}
		}


		std::cout << std::endl << std::endl;

		for (size_t o = 0; o < this->vPlayers.size(); o++) {
			if ((this->dealer.GetValue() >= iCurMaxScore) && !this->dealer.isBoosted()) {
				this->vPlayers[o]->Lose();
			}
			else {
				if (this->vPlayers[o]->isBoosted() || (this->vPlayers[o]->GetValue() < iCurMaxScore)) {
					this->vPlayers[o]->Lose();
				}
				else if (iMaxScoreHolders > 1) {
					if (this->vPlayers[o]->GetValue() == iCurMaxScore) {
						this->vPlayers[o]->Push();
					}
				}
				else {
					this->vPlayers[o]->Win();
				}
			}
		}
	}

	~Game() {
		this->vPlayers.clear();
	}
};

// task 5

int main() {
	std::cout << std::endl << "Blackjack starts HERE" << std::endl << std::endl;

	std::vector<std::string> vPlayerNames;

	bool isCinNeedMoreFailed = false;
	bool isNeedMorePlayers = false;

	do {

		bool isNameCinFailed = false;

		if (!isCinNeedMoreFailed) {
			do {
				std::string sPlayerName;

				std::cout << "Enter player name" << std::endl;
				std::cin >> sPlayerName;

				isNameCinFailed = std::cin.fail();

				if (isNameCinFailed) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
				}
				else {
					vPlayerNames.push_back(sPlayerName);
				}

			} while (isNameCinFailed);
		}

		char cNeedMorePlayers = 'Y';

		std::cout << "Add one more player? Y/N" << std::endl;
		std::cin >> cNeedMorePlayers;

		isCinNeedMoreFailed = std::cin.fail();

		if (isCinNeedMoreFailed) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else {
			if (cNeedMorePlayers == 'Y') {
				isNeedMorePlayers = true;
			}
			else if (cNeedMorePlayers == 'N') {
				break;
			}
			else {
				isCinNeedMoreFailed = true;
			}
		}

	} while (isCinNeedMoreFailed || isNeedMorePlayers);



	char cPlayAgain = 'N';
	bool isPlayAgainCinFailed = false;

	do {
		std::cout << "Want to start a new round? Y/N" << std::endl;
		std::cin >> cPlayAgain;

		isPlayAgainCinFailed = std::cin.fail();

		if (isPlayAgainCinFailed) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else {
			if (cPlayAgain == 'N') break;

			if (cPlayAgain == 'Y') {
				Game game(vPlayerNames);
				game.play();
			}
		}
	} while (cPlayAgain == 'Y' || isPlayAgainCinFailed);

	return 0;
}