// ItemManager.cpp
#include "ItemManager.h"
#include "Item.h"

void ItemManager::display(std::ostream& os, bool more) const {
	// ItemManager IS the vector - so we can
	// access the base member functions without
	// specifying a vector object
	for (auto i = 0; i < size(); i++)
		at(i).display(os, more);
}