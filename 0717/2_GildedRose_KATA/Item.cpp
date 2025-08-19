#include "Item.h"

#include "GildedRoseConfig.h"

Item::Item(std::string name, int sell_in, int quality)
	: name{ name }, sell_in{ sell_in }, quality{ quality } {
}

bool Item::operator==(const Item &rhs) const {
	return name == rhs.name && sell_in == rhs.sell_in && quality == rhs.quality;
}

AgedBrieItem::AgedBrieItem(const std::string &name, int sell_in, int quality)
	: Item(name, sell_in, quality) {
}

LegendaryItem::LegendaryItem(const std::string &name, int sell_in, int quality)
	: Item(name, sell_in, quality) {
}

ConcertTicketItem::ConcertTicketItem(const std::string &name, int sell_in,
	int quality)
	: Item(name, sell_in, quality) {
}

NormalItem::NormalItem(const std::string &name, int sell_in, int quality)
	: Item(name, sell_in, quality) {
}

#if 1  // UpdateSellIn
void Item::UpdateSellIn() { sell_in--; }
void LegendaryItem::UpdateSellIn() {}
#endif

void AgedBrieItem::UpdateQuality() {
	if(sell_in < 0)
		quality += 2;
	else
		quality += 1;
}
void LegendaryItem::UpdateQuality() {}
void ConcertTicketItem::UpdateQuality() {
	if(sell_in < 5) {
		quality += 3;
	}
	else if(sell_in < 10) {
		quality += 2;
	}
	else {
		quality += 1;
	}

	if(sell_in < 0) quality = gilded_rose_config.MIN_QUALITY;
}
void NormalItem::UpdateQuality() {
	if(sell_in < 0) {
		quality -= 2;
	}
	else {
		quality -= 1;
	}
}

void Item::ClampToQualityLimit() {
	if(quality < gilded_rose_config.MIN_QUALITY) quality = gilded_rose_config.MIN_QUALITY;
	if(quality > gilded_rose_config.MAX_QUALITY) quality = gilded_rose_config.MAX_QUALITY;
}
