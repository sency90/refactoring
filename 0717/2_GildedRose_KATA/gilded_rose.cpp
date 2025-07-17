#include "gilded_rose.h"

using std::vector;
using std::string;

namespace {
	const char* SULFURAS = "Sulfuras, Hand of Ragnaros";
	const char* AGED_BRIE = "Aged Brie";
	const char* BACKSTAGE_PASS = "Backstage passes to a TAFKAL80ETC concert";
};

GildedRose::GildedRose(vector<Item>& items) : items(items) {
}

void GildedRose::updateQuality() {
	for(int i = 0; i < items.size(); i++) {
		Item & item = items[i];
		if(item.name == AGED_BRIE) {
			if(item.quality < 50) {
				item.quality = item.quality + 1;
			}
		}
		else if(item.name == BACKSTAGE_PASS) {
			if(item.quality < 50) {
				item.quality = item.quality + 1;

				if(item.sellIn < 11) {
					if(item.quality < 50) {
						item.quality = item.quality + 1;
					}
				}

				if(item.sellIn < 6) {
					if(item.quality < 50) {
						item.quality = item.quality + 1;
					}
				}
			}
		}
		else if(item.name == SULFURAS) {
		}
		else if(item.name != SULFURAS) {
			if(item.quality > 0) {
				item.quality = item.quality - 1;
			}
		}

		if(item.name == AGED_BRIE) {
			if(item.sellIn < 1) {
				if(item.quality < 50) {
					item.quality = item.quality + 1;
				}
			}
		}
		else if(item.name == BACKSTAGE_PASS) {
			if(item.sellIn < 1) {
				item.quality = item.quality - item.quality;
			}
		}
		else if(item.name == SULFURAS) {
		}
		else {
			if(item.sellIn < 1) {
				if(item.quality > 0) {
					item.quality = item.quality - 1;
				}
			}
		}

		if(item.name != SULFURAS) {
			item.sellIn = item.sellIn - 1;
		}

	}
}
