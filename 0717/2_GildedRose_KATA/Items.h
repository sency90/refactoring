#pragma once
#include "gilded_rose.h"

class AgedBrieItem: public GildedRoseItem {
private:
	Item *item_;

public:
	AgedBrieItem(Item * item_): item_(item_) {}

	void updateQuality() {
		Item & item = *item_;
		if(item.quality < 50) {
			item.quality = item.quality + 1;
		}
		if(item.sellIn < 1) {
			if(item.quality < 50) {
				item.quality = item.quality + 1;
			}
		}
	}
};

class BackstagePassesItem: public GildedRoseItem{
private:
	Item *item_;

public:
	BackstagePassesItem(Item * item_): item_(item_) {}

	void updateQuality() {
		Item & item = *item_;
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

};

class SulfurasItem: public GildedRoseItem{
private:
	Item *item_;

public:
	SulfurasItem(Item* item_): item_(item_) {}

	void updateQuality() {
		Item & item = *item_;
	}
};

class NormalItem: public GildedRoseItem{
private:
	Item *item_;

public:
	NormalItem(Item* item_): item_(item_) {}

	void updateQuality() {
		Item & item = *item_;
		if(item.quality > 0) {
			item.quality = item.quality - 1;
		}
		if(item.sellIn < 1) {
			if(item.quality > 0) {
				item.quality = item.quality - 1;
			}
		}
	}
};

