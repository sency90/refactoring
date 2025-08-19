#pragma once
#include <string>
#include <memory>
#include "GildedRoseConfig.h"

class Item {
public:
	Item() = default;
	Item(std::string name, int sell_in, int quality);
	virtual ~Item() = default;

	virtual std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality)=0;

	bool operator==(const Item &rhs) const;
	virtual void UpdateSellIn();
	virtual void UpdateQuality() = 0;
	void ClampToQualityLimit();

public:
	std::string name;
	int sell_in;   // 상품 판매가능기간
	int quality;  // sell_in이 줄어들수록 quality는 떨어진다.

protected:
	const GildedRoseConfig &gilded_rose_config = GildedRoseConfig::GetInstance();
};

class AgedBrieItem: public Item {
public:
	AgedBrieItem() = default;
	AgedBrieItem(const std::string &name, int sellIn, int quality);

	std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality) override {
		std::unique_ptr<AgedBrieItem> aged_brie_item_ptr = std::make_unique<AgedBrieItem>(name, sell_in, quality);
		return aged_brie_item_ptr;
	}

	void UpdateQuality() override;
};

class LegendaryItem: public Item {
public:
	LegendaryItem() = default;
	LegendaryItem(const std::string &name, int sellIn, int quality);

	std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality) override {
		std::unique_ptr<LegendaryItem> legendary_item_ptr = std::make_unique<LegendaryItem>(name, sell_in, quality);
		return legendary_item_ptr;
	}

	void UpdateQuality() override;
	void UpdateSellIn() override;
};

class ConcertTicketItem: public Item {
public:
	ConcertTicketItem() = default;
	ConcertTicketItem(const std::string &name, int sellIn, int quality);

	std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality) override {
		std::unique_ptr<ConcertTicketItem> concert_ticket_item_ptr = std::make_unique<ConcertTicketItem>(name, sell_in, quality);
		return concert_ticket_item_ptr;
	}

	void UpdateQuality() override;
};

class NormalItem: public Item {
public:
	NormalItem() = default;
	NormalItem(const std::string &name, int sellIn, int quality);

	std::unique_ptr<Item> Create(const std::string &name, int sell_in, int quality) override {
		std::unique_ptr<NormalItem> normal_item_ptr = std::make_unique<NormalItem>(name, sell_in, quality);
		return normal_item_ptr;
	}

	void UpdateQuality() override;
};
