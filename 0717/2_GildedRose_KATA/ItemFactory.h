#pragma once
#include "Item.h"
#include <memory>
class ItemFactory {
private:
	ItemFactory() = default;

public:
	static ItemFactory & GetInstance() {
		static ItemFactory item_factory;
		return item_factory;
	}

	template <typename TheItem>
	std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality) {
		return std::make_unique<TheItem>(name, sell_in, quality);
	}
};
