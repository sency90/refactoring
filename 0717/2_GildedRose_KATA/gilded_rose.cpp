#include "gilded_rose.h"
#include "GildedRoseConfig.h"

using std::string;
using std::vector;

GildedRose::GildedRose(vector<Item*>& items) : items(items) {}


bool IsEtcItem(const std::string& item_name) {
  if (item_name == AGEDBRIE_ITEM_STR || item_name == CONCERT_TICKET_ITEM_STR ||
      item_name == LEGENDARY_ITEM_STR)
    return false;

  return true;
}

void GildedRose::UpdateQuality() {
  for (Item* item : items) {
    if (item->name == LEGENDARY_ITEM_STR) continue;

    item->sellIn--;

    UpdateQualityAgedBrieItem(*item);
    UpdateQualityConcertTicketItem(*item);
    UpdateLegendaryItem(*item);
    UpdateQualityEtcItem(*item);

    ClampToQualityLimit(item->quality);
  }
}

void GildedRose::UpdateQualityAgedBrieItem(Item& item) {
  if (item.name == AGEDBRIE_ITEM_STR) {
    if (item.sellIn < 0)
      item.quality += 2;
    else
      item.quality += 1;
  }
}

void GildedRose::UpdateLegendaryItem(Item& item) {}

void GildedRose::UpdateQualityConcertTicketItem(Item& item) {
  if (item.name == CONCERT_TICKET_ITEM_STR) {
    if (item.sellIn < 5) {
      item.quality += 3;
    } else if (item.sellIn < 10) {
      item.quality += 2;
    } else {
      item.quality += 1;
    }

    if (item.sellIn < 0) item.quality = MIN_QUALITY;
  }
}
void GildedRose::UpdateQualityEtcItem(Item& item) {
  if (IsEtcItem(item.name)) {
    if (item.sellIn < 0)
      item.quality -= 2;
    else
      item.quality -= 1;
  }
}

void GildedRose::ClampToQualityLimit(int& quality) {
  if (quality < MIN_QUALITY) quality = MIN_QUALITY;
  if (quality > MAX_QUALITY) quality = MAX_QUALITY;
}

void AgedBrieItem::UpdateQuality() {
  if (sellIn < 0)
    quality += 2;
  else
    quality += 1;
}

void LegendaryItem::UpdateQuality() {
}

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
