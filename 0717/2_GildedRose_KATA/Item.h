#pragma once
#include <string>

class Item {
 public:
  Item() = default;
  Item(std::string name, int sellIn, int quality);
  virtual ~Item() = default;

  bool operator==(const Item &rhs) const;
  virtual void UpdateSellIn();
  virtual void UpdateQuality() = 0;
  void ClampToQualityLimit();

 public:
  std::string name;
  int sellIn;   // 상품 판매가능기간
  int quality;  // sellIn이 줄어들수록 quality는 떨어진다.
};

class AgedBrieItem : public Item {
 public:
  AgedBrieItem() = default;
  AgedBrieItem(const std::string &name, int sellIn, int quality);

  void UpdateQuality() override;
};

class LegendaryItem : public Item {
 public:
  LegendaryItem() = default;
  LegendaryItem(const std::string &name, int sellIn, int quality);

  void UpdateQuality() override;
  void UpdateSellIn() override;
};

class ConcertTicketItem : public Item {
 public:
  ConcertTicketItem() = default;
  ConcertTicketItem(const std::string &name, int sellIn, int quality);

  void UpdateQuality() override;
};

class NormalItem : public Item {
 public:
  NormalItem() = default;
  NormalItem(const std::string &name, int sellIn, int quality);

  void UpdateQuality() override;
};
