#pragma once
#include "Item.h"
#include <memory>
#define interface struct
interface IItemFactory {
public:
	virtual std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality)=0;
};

template<typename T>
class ItemFactory: public IItemFactory {
public:
	std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality) override {
		return std::make_unique<T>(name, sell_in, quality);
	}
};
