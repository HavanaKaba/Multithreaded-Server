#pragma once
#ifndef M3_TASKMANAGER_H
#define M3_TASKMANAGER_H

// Manager Milestone - TaskManager Interface
// TaskManager.h
// Chris Szalwinski
// v1.0 - 14/11/2015
// v2.0 - 23/02/2016
#include <iostream>
#include <vector>
#include <algorithm>
#include "Task.h"
#include "ItemManager.h"

class Task;
class ItemManager;

class TaskManager : public std::vector<Task> {
	//std::vector<Task> tasks;
public:
	void validate(std::ostream&);
	void validate(const ItemManager&, std::ostream&);
	void display(std::ostream&) const;
};

#endif