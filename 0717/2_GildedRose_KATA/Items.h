#pragma once
#include "gilded_rose.h"

class AgedBrieItem{
private:
	Item *item_;

public:
	AgedBrieItem(Item * item_): item_(item_) {}

	void updateQualityForAgedBrie() {
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
