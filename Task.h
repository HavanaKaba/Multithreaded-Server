#ifndef M1_TASK_H
#define M1_TASK_H
#pragma once
// Task Milestone - Task Interface
// Task.h
// Chris Szalwinski
// v1.0 - 24/10/2015
// v2.0 - 23/02/2016
#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"

class Task {
	std::string name;          // name of the task
	std::string slots;         // number of slots
	std::string nextTask[2];   // names of the next tasks
	const Task* pNextTask[2];  // addresses of the next tasks
	static size_t field_width; // current maximum field width 
public:
	enum Quality {
		passed,
		redirect
	};
	Task(const std::string&);
	bool validate(const Task&);
	const std::string& getName() const			{ return name; }
	unsigned int getSlots() const;
	const Task* getNextTask(Quality) const;
	void display(std::ostream&) const;
	static size_t getFieldWidth()				{ return field_width; }
};

bool operator==(const Task&, const Task&);

#endif