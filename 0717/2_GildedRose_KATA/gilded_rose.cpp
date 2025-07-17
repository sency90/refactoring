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
		updateQuality(item);
		updateSellIn(item);
	}
}

void GildedRose::updateQuality(Item & item)
{
	GildedRoseItem* gildedRoseItem = getGildedRoseItem(item);
	gildedRoseItem->updateQuality();
}

GildedRoseItem * GildedRose::getGildedRoseItem(Item & item)
{
	if(item.name == AGED_BRIE) return new AgedBrieItem(&item);
	else if(item.name == BACKSTAGE_PASS) return new BackstagePassesItem(&item);
	else if(item.name == SULFURAS) return new SulfurasItem(&item);
	else return new NormalItem(&item);
}

void GildedRose::updateSellIn(Item & item) {
	if(item.name != SULFURAS) {
		item.sellIn = item.sellIn - 1;
	}
}

