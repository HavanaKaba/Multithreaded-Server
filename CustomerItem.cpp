#include "CustomerItem.h"

CustomerItem::CustomerItem(const std::string& str) {
	if (!str.empty())
		name = str;
	else
		name = "";

	filled = false;
	code = 0;
}

bool CustomerItem::asksFor(const Item& item) const {
	bool match = false;

	if (name == item.getName())
		match = true;
	
	return match;
		
}

void CustomerItem::fill(const unsigned int c) {
	code = c;
	filled = true;
}

void CustomerItem::clear() {
	code = 0;
	filled = false;
}

void CustomerItem::display(std::ostream& os) const {
	// + if filled, - if not
	if (isFilled()) {
		os << "+ [" << std::setw(CODE_WIDTH) << std::right <<
			std::setfill('0') << code << "] " << name << std::endl;
	}
	else {
		os << "- [" << std::setw(CODE_WIDTH) << std::right <<
			std::setfill('0') << "0" << "] " << name << std::endl;
	}
}