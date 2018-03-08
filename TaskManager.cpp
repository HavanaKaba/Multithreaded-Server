#include "TaskManager.h"

void TaskManager::validate(std::ostream& os) {
	// validate each task against the other tasks in the base class
	// SO: check the derived vector vs. the base - kind of recursive
	for (auto i = 0; i < size(); i++) {
		for (auto j = 0; j < size(); j++)
			at(i).validate(at(j));
	}
}

// tbd: this function is crashing < only output is "Memory is unavailable"
void TaskManager::validate(const ItemManager& itemManager, std::ostream& os) {
	// like orderManager with a lambda that compares
	// two strings (== overloaded in Task class)
		for (int j = 0; j < itemManager.size(); j++) {
			iterator it = end();
			auto isTask = [=](Task& task) { return (task.getName() == itemManager[j].getRemover()); };

			it = std::find_if(begin(), end(), isTask); // iterator to task object

			if (it == end())
				os << itemManager[j].getRemover() << " is unavailable" << std::endl;
		}
}

void TaskManager::display(std::ostream& os) const {
	for (auto i = 0; i < size(); i++)
		at(i).display(os);
}

