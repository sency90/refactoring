#include "gilded_rose.h"
#include "items.h"

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
			updateQualityForAgedBrie(item);
		}
		else if(item.name == BACKSTAGE_PASS) {
			updateQualityForBackstagePasses(item);
		}
		else if(item.name == SULFURAS) {
			updateQualityForSulfuras(item);
		}
		else {
			updateQualityForNormalItem(item);
		}

		updateSellIn(item);

	}
}

void GildedRose::updateSellIn(Item & item) {
	if(item.name != SULFURAS) {
		item.sellIn = item.sellIn - 1;
	}
}

void GildedRose::updateQualityForAgedBrie(Item & item) {
	if(item.quality < 50) {
		item.quality = item.quality + 1;
	}
	if(item.sellIn < 1) {
		if(item.quality < 50) {
			item.quality = item.quality + 1;
		}
	}
}

void GildedRose::updateQualityForBackstagePasses(Item & item) {
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
	if(item.sellIn < 1) {
		item.quality = item.quality - item.quality;
	}
}

void GildedRose::updateQualityForSulfuras(Item & item) {
}

void GildedRose::updateQualityForNormalItem(Item & item) {
	if(item.quality > 0) {
		item.quality = item.quality - 1;
	}
	if(item.sellIn < 1) {
		if(item.quality > 0) {
			item.quality = item.quality - 1;
		}
	}
}
