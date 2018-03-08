#include "OrderManager.h"

CustomerOrder&& OrderManager::extract() {
	// return an rvalue of the last order
	// of the vector Customer, but where is it supposed
	// to move to??
	return std::move(back());
}

void OrderManager::validate(const ItemManager& itemManager, std::ostream& os) {
	// overloaded [] operator in Customer Order to access order name
	// can't make an iterator for itemManager for some reason
	for (int i = 0; i < size(); i++) {
		for (int j = 0; j < at(i).noOrders(); j++) {
			auto isAvail = [=](const Item& item) {
				bool match = false;
				for (int k = 0; k < itemManager.size() && match == false; k++) {
					if (at(i)[j] == itemManager.at(k).getName())
						match = true;
				}
				return match;
			};

			if (std::find_if(itemManager.cbegin(), itemManager.cend(), isAvail) == itemManager.cend())
				os << at(i)[j] << " is unavailable" << std::endl;
		}
	}
}

// Only displays first customer order 
void OrderManager::display(std::ostream& os) const {
	for (auto i = 0; i < size(); i++) 
		at(i).display(os);
}