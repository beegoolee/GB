#include <iostream>

// task 1
class Date {
private:
	short day;
	short month;
	size_t year;

public:
	Date(short d = 1, short m = 1, size_t y = 1970) { //default is Unix-epoch start time
		this->setDay(d);
		this->setMonth(m);
		this->setYear(y);
	}

	//setters
	void __fastcall setDay(short d) {
		this->day = d;
	}
	void __fastcall setMonth(short m) {
		this->month = m;
	}
	void __fastcall setYear(size_t y) {
		this->year = y;
	}

	//getters
	short getDay() const {
		return this->day;
	}
	short getMonth() const {
		return this->month;
	}
	size_t getYear() const {
		return this->year;
	}
};

std::ostream& operator << (std::ostream& stream, Date* date) {
	stream << date->getDay();
	stream << "/";
	stream << date->getMonth();
	stream << "/";
	stream << date->getYear();

	return stream;
}


// task 2

void __fastcall dateSwap(std::shared_ptr<Date>& date1, std::shared_ptr<Date>& date2) {
	std::shared_ptr<Date> dateTmp(new Date(date1->getDay(), date1->getMonth(), date1->getYear()));
	date1 = date2;
	date2 = dateTmp;
}

Date& __fastcall getLaterDate(const std::shared_ptr<Date>& date1, const std::shared_ptr<Date>& date2) {

	if (date1->getYear() != date2->getYear()) {
		if (date1->getYear() > date2->getYear()) {
			return *date1;
		}
		else {
			return *date2;
		}
	}

	if (date1->getMonth() != date2->getMonth()) {
		if (date1->getMonth() > date2->getMonth()) {
			return *date1;
		}
		else {
			return *date2;
		}
	}

	if (date1->getDay() != date2->getDay()) {
		if (date1->getDay() > date2->getDay()) {
			return *date1;
		}
		else {
			return *date2;
		}
	}

	return *date1; // dates are equal
}


int lesson7() {

	// task 1

	std::unique_ptr<Date> today(new Date(28, 2, 2022));

	std::cout << today->getDay() << std::endl;
	std::cout << today->getMonth() << std::endl;
	std::cout << today->getYear() << std::endl;
	std::cout << today << std::endl;

	std::unique_ptr<Date> date;


	if (today != nullptr) {
		std::cout << "today is nullptr" << std::endl;
	}
	else {
		std::cout << "today is: ";
		std::cout << today << std::endl;
	}

	if (date != nullptr) {
		std::cout << "date is nullptr" << std::endl;
	}
	else {
		std::cout << "date is: ";
		std::cout << today << std::endl;
	}

	// task 2
	std::cout << std::endl;

	std::shared_ptr<Date> date1(new Date(11, 12, 1999));
	std::shared_ptr<Date> date2(new Date(18, 5, 2005)); // is actually later then date1

	dateSwap(date1, date2);

	Date* laterDatePtr = &(getLaterDate(date1, date2));

	std::cout << laterDatePtr << " - is later date" << std::endl;
	std::cout << date1 << " - date 1" << std::endl;
	std::cout << date2 << " - date 2" << std::endl;

	return 0;
}
