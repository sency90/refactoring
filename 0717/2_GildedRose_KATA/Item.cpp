#include "Item.h"

#include "GildedRoseConfig.h"

Item::Item(std::string name, int sellIn, int quality)
    : name{name}, sellIn{sellIn}, quality{quality} {}

bool Item::operator==(const Item &rhs) const {
  return name == rhs.name && sellIn == rhs.sellIn && quality == rhs.quality;
}

AgedBrieItem::AgedBrieItem(const std::string &name, int sellIn, int quality)
    : Item(name, sellIn, quality) {}

LegendaryItem::LegendaryItem(const std::string &name, int sellIn, int quality)
    : Item(name, sellIn, quality) {}

ConcertTicketItem::ConcertTicketItem(const std::string &name, int sellIn,
                                     int quality)
    : Item(name, sellIn, quality) {}

NormalItem::NormalItem(const std::string &name, int sellIn, int quality)
    : Item(name, sellIn, quality) {}

#if 1  // UpdateSellIn
void Item::UpdateSellIn() { sellIn--; }
void LegendaryItem::UpdateSellIn() {}
#endif

void AgedBrieItem::UpdateQuality() {
  if (sellIn < 0)
    quality += 2;
  else
    quality += 1;
}
void LegendaryItem::UpdateQuality() {}
void ConcertTicketItem::UpdateQuality() {
  if (sellIn < 5) {
    quality += 3;
  } else if (sellIn < 10) {
    quality += 2;
  } else {
    quality += 1;
  }

  if (sellIn < 0) quality = MIN_QUALITY;
}
void NormalItem::UpdateQuality() {
  if (sellIn < 0) {
    quality -= 2;
  } else {
    quality -= 1;
  }
}

void Item::ClampToQualityLimit() {
  if (quality < MIN_QUALITY) quality = MIN_QUALITY;
  if (quality > MAX_QUALITY) quality = MAX_QUALITY;
}
