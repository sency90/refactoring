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
			AgedBrieItem* agedBrieItem = new AgedBrieItem(&item);
			agedBrieItem->updateQuality();
		}
		else if(item.name == BACKSTAGE_PASS) {
			BackstagePassesItem* backstagePassesItem = new BackstagePassesItem(&item);
			backstagePassesItem->updateQuality();
		}
		else if(item.name == SULFURAS) {
			SulfurasItem* sulfurasItem = new SulfurasItem(&item);
			sulfurasItem->updateQuality();
		}
		else {
			NormalItem* normalItem = new NormalItem(&item);
			normalItem->updateQuality();
		}

		updateSellIn(item);

	}
}

void GildedRose::updateSellIn(Item & item) {
	if(item.name != SULFURAS) {
		item.sellIn = item.sellIn - 1;
	}
}
