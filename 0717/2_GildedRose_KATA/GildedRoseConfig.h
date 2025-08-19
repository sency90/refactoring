#pragma once
#include <string>

class GildedRoseConfig {
private:
	GildedRoseConfig() = default;

public:
	static const GildedRoseConfig &GetInstance() {
		static GildedRoseConfig instance;
		return instance;
	}

	const std::string AGEDBRIE_ITEM_STR = "Aged Brie";
	const std::string CONCERT_TICKET_ITEM_STR =
		"Backstage passes to a TAFKAL80ETC concert";
	const std::string LEGENDARY_ITEM_STR = "Sulfuras, Hand of Ragnaros";
	const int MAX_QUALITY = 50;
	const int MIN_QUALITY = 0;
};  // namespace
