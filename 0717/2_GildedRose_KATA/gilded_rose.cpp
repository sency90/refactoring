#include "gilded_rose.h"

using std::string;
using std::vector;

GildedRose::GildedRose(vector<Item>& items) : items(items) {}

namespace {
const string AGEDBRIE_ITEM_STR = "Aged Brie";
const string CONCERT_TICKET_ITEM_STR =
    "Backstage passes to a TAFKAL80ETC concert";
const string LEGENDARY_ITEM_STR = "Sulfuras, Hand of Ragnaros";
const int MAX_QUALITY = 50;
const int MIN_QUALITY = 0;
};  // namespace

bool IsEtcItem(const std::string& item_name) {
  if (item_name == AGEDBRIE_ITEM_STR || item_name == CONCERT_TICKET_ITEM_STR ||
      item_name == LEGENDARY_ITEM_STR)
    return false;

  return true;
}

void GildedRose::UpdateQuality() {
  for (Item& item : items) {
    if (item.name == LEGENDARY_ITEM_STR) continue;

    item.sellIn--;

    UpdateQualityAgedBrieItem(item);
    UpdateQualityConcertTicketItem(item);
    UpdateLegendaryItem(item);
    UpdateQualityEtcItem(item);

    ClampToQualityLimit(item.quality);
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
