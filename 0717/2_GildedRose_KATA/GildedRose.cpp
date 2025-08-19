#include "GildedRose.h"

#include "GildedRoseConfig.h"

using std::string;
using std::vector;
using UpItem = std::unique_ptr<Item>;

GildedRose::GildedRose(vector<UpItem> &items): items(items) {}

void GildedRose::UpdateQuality() {
	for(UpItem &item_up : items) {
		//Item* item = item_up.get();
		if(item_up->name == gilded_rose_config.LEGENDARY_ITEM_STR) continue;

		item_up->UpdateSellIn();
		item_up->UpdateQuality();
		item_up->ClampToQualityLimit();
	}
}
