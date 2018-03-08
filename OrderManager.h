#pragma once
#ifndef M3_ORDERMANAGER_H
#define M3_ORDERMANAGER_H
// Manager Milestone - OrderManager Interface
// OrderManager.h
// Chris Szalwinski
// v1.0 - 14/11/2015
// v2.0 - 23/02/2016
#include <iostream>
#include <vector>
#include <algorithm>
#include "CustomerOrder.h"
#include "ItemManager.h"

class ItemManager;
class CustomerOrder;

class OrderManager : public std::vector<CustomerOrder> {
public:
	CustomerOrder&& extract();
	void validate(const ItemManager&, std::ostream&);
	void display(std::ostream&) const;
};
#endif