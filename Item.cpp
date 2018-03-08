#include "Item.h"
#include "Utilities.h"
size_t Item::field_width;

Item::Item(const std::string& str) {
	this->code = 1;

	Utilities utility;
	size_t nextPos = 0;
	bool more = true;
	size_t tempfw;
	try {
		name = utility.nextToken(str, nextPos, more);
		if (name.empty())
			throw "No name specified";
		if (more) {
			filler = utility.nextToken(str, nextPos, more);
			if (filler.empty())
				throw "No filler specified";
		}
		if (more) {// store original fieldwith
			tempfw = utility.getFieldWidth();
			remover = utility.nextToken(str, nextPos, more);
			utility.setFieldWidth(tempfw);
			// resets utilities object field width
			// so it only sets field_width to name
			if (remover.empty())
				throw "No remover specifed";
		}
		if (more) {
			code = std::stoi(utility.nextToken(str, nextPos, more));
			// no need to throw; initialized at beginning
		}
		if (more) {
			// store original fieldwith
			tempfw = utility.getFieldWidth();
			description = utility.nextToken(str, nextPos, more);
			// reset utilities object field width
			utility.setFieldWidth(tempfw);
		}
	}
	catch (const char* msg) {
		std::cout << msg << std::endl;
		throw;
	}
	catch (...) {
		throw;
	}

	if (utility.getFieldWidth() > Item::field_width)
		Item::field_width = utility.getFieldWidth();

	if (description.empty())
		this->description = "no detailed description";
	
}

bool Item::empty() const {
	bool isEmpty = false;

	if (name.empty() && filler.empty() &&
		remover.empty() && description.empty())
		isEmpty = true;
	else
		isEmpty = false;

	return isEmpty;
}

Item& Item::operator++(int incre) {
	Item b4Increment = *this;

	code++;

	return b4Increment;
}

void Item::display(std::ostream& os, bool full) const {
	// redundant instructions: why have bool full
	// when description is initialized in constructor 
	// and is displayed anyways?
	os << std::setfill(' ') << std::left << std::setw(field_width) <<
		name << std::right << " " << "[" << std::setw(CODE_WIDTH) <<
		std::setfill('0') << code << "] From " << std::setw(field_width) <<
		std::setfill(' ') << std::left << name << " To " << remover;
	os << std::endl;
	if (full)
		os << std::setw(field_width + CODE_WIDTH + 1) << " " << " : " + description << std::endl;
	else
		os << std::setw(field_width + CODE_WIDTH + 1) << " " << " : " + description << std::endl;
}