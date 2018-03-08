#include "CustomerOrder.h"
size_t CustomerOrder::field_width;

CustomerOrder::CustomerOrder(const std::string& str) {
	order = nullptr;
	nOrders = 0;

	Utilities utility;
	size_t nextPos = 0;
	bool more = true;
	std::vector<std::string> temp;
	
	name = utility.nextToken(str, nextPos, more);
	if (utility.getFieldWidth() > CustomerOrder::field_width)
		CustomerOrder::field_width = utility.getFieldWidth();
	if (name.empty())
		throw "No name specified";
	if (more) {
		product = utility.nextToken(str, nextPos, more);
		if (product.empty())
			throw "No product specified";
	}
	while (more) {
		temp.push_back(utility.nextToken(str, nextPos, more));
	}

	nOrders = temp.size();

	order = new CustomerItem[nOrders];

	for (int i = 0; i < nOrders; i++) {
		order[i] = CustomerItem(temp[i]);
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& src) {
	throw std::string("copying not allowed");
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) NOEXCEPT {
	order = nullptr;
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) NOEXCEPT {
	if (this != &src) {
		if (order != nullptr) {
			delete[] order;
			order = nullptr;
		}
		order = src.order;
		name = src.name;
		product = src.product;
		nOrders = src.nOrders;

		src.order = nullptr;
		src.name = std::string();
		src.product = std::string();
		src.nOrders = 0;
	}
	return *this;
}

CustomerOrder::~CustomerOrder() {
	if (order != nullptr) {
		delete[] order;
		order = nullptr;
	}
}

const std::string& CustomerOrder::operator[](unsigned int i) const {
	try {
		if (i >= nOrders)
			throw "Out of bounds";
	}
	catch (const char* msg) {
		throw;
	}

	return order[i].getName();
}

void CustomerOrder::fill(Item& item) {
	// doesn't need nested for loop - item is not an array
	for (int i = 0; i < nOrders; i++) {
		if (order[i].getName() == item.getName()) {
			if (order[i].isFilled() == false){
				order[i].fill(item.getCode());
				item++; // overloaded in Item definition
			}
		}
	}
}

void CustomerOrder::remove(Item& item) {
	for (int i = 0; i < nOrders; i++) {
		if (order[i].getName() == item.getName()) {
			order[i] = std::string();
			nOrders--;
		}
	}
}

bool CustomerOrder::empty() const {
	bool isEmpty = false;

	if (name.empty() && product.empty())
		isEmpty = true;

	return isEmpty;
}

void CustomerOrder::display(std::ostream& os) const {
	os << std::left << std::setfill(' ') << std::setw(CustomerOrder::field_width) <<
		name << " : " << std::setw(CustomerOrder::field_width) <<
		product << std::endl;
	for (int i = 0; i < nOrders; i++) {
		order[i].display(os);
	}
}