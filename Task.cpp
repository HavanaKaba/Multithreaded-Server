#include "Task.h"
size_t Task::field_width;
char Utilities::delimiter;

// Member Functions //

/* Single Argument Constructor */
Task::Task(const std::string& instr) {
	slots = "1";
	pNextTask[passed] = nullptr;
	pNextTask[redirect] = nullptr;

	Utilities utility;
	size_t nextPos = 0;
	bool more = true;

	name = utility.nextToken(instr, nextPos, more);

	if (more) {
		slots = utility.nextToken(instr, nextPos, more);

		if (more) {
			nextTask[passed] = utility.nextToken(instr, nextPos, more);

			if (more)
				nextTask[redirect] = utility.nextToken(instr, nextPos, more);
		}
	}

	if (utility.getFieldWidth() > getFieldWidth())
		field_width = utility.getFieldWidth();
}

/* returns true if both tasks are empty */
bool Task::validate(const Task& task) {
	bool isTrue = false;

	if (task.name == nextTask[passed]) {
		pNextTask[passed] = &task;
	}
	else if (task.name == nextTask[redirect]) {
		pNextTask[redirect] = &task;
	}

	if ((nextTask[passed].empty() || pNextTask[passed]) && (nextTask[redirect].empty() || pNextTask[redirect]))
		isTrue = true;

	return isTrue;
}

/* Returns # of product slots in current Task Object */
unsigned int Task::getSlots() const {
	unsigned int cast = std::stoi(slots);

	return cast;
}

/* Returns pointer to address of next empty Task object */
const Task* Task::getNextTask(Quality quality) const {
	if (pNextTask[quality] == nullptr)
		throw "*** Validate  [" + nextTask[quality] + "] @ [" + name + "] ***";
	
	return pNextTask[quality];
}

/* Display to console */
void Task::display(std::ostream& os) const {
	os << std::setw(13) << std::left << "Task Name" << " :  " 
		<< std::setw(Task::field_width + 2) << "[" + getName() + "]" << " [" << getSlots() << "]" << std::endl;

	if (!nextTask[passed].empty()) {
		if (pNextTask[passed]) {
			os << std::setw(13) << std::right << "Continue to" << " :  "
				<< std::left << std::setw(Task::field_width + 2) << "[" + nextTask[passed] + "]" << std::endl;
		}
		else {
			os << std::setw(13) << "Continue to" << " :  "
				<< std::left << std::setw(Task::field_width + 2) << "[" + nextTask[passed] + "]"
				<< " *** to be validated ***" << std::endl;
		}

		if (!nextTask[redirect].empty()) {
			if (pNextTask[redirect]) {
				os << std::setw(13) << "Redirect to" << " :  "
					<< std::left << std::setw(Task::field_width + 2) << "[" + nextTask[redirect] + "]" << std::endl;
			}
			else {
				os << std::setw(13) << "Redirect to" << " :  "
					<< std::left << std::setw(Task::field_width + 2) << "[" + nextTask[redirect] + "]"
					<< " *** to be validated ***" << std::endl;
			}
		}
	}
}

// Helper Functions

/* Returns true if names are the same */
bool operator==(const Task& a, const Task& b) {
	if (a.getName().compare(b.getName()) == 0)
		return true;
	else
		return false;
}