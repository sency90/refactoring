#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "GildedRose.h"
#include "gmock/gmock.h"

using std::string;
using std::vector;
using UpItem = std::unique_ptr<Item>;
using namespace testing;

template <typename T>
std::vector<const T*> Raw(const std::vector<std::unique_ptr<T>>& v) {
  std::vector<const T*> result;
  result.reserve(v.size());
  for (const auto& up : v) {
    result.push_back(up.get());
  }
  return result;
}

// unique_ptr 전용: 포인터가 가리키는 '값' 비교
MATCHER_P(PtrRangeEqByValue, expected_ref,
          "compares *lhs == *rhs (unique_ptr)") {
  const vector<UpItem>& expected = expected_ref.get();

  if (arg.size() != expected.size()) {
    return false;
  }

  for (int i = 0; i < arg.size(); i++) {
    const Item* lhs = arg[i].get();
    const Item* rhs = expected[i].get();

    if (lhs == nullptr || rhs == nullptr) {
      return lhs == rhs;
    }
    if (!(*lhs == *rhs)) {
      return false;
    }
  }
  return true;
}

class GildedRoseTestFixture : public Test {
 public:
  const string AgedBrieItemStr = "Aged Brie";
  const string ConcertTicketItemStr =
      "Backstage passes to a TAFKAL80ETC concert";
  const string LegendaryItemStr = "Sulfuras, Hand of Ragnaros";
  const string EtcItemStr = "Foo";

  void updateQuality(vector<UpItem>& out_items) {
    GildedRose app(out_items);  // GildedRose가 vector<UpItem>& 받도록 수정 필요
    app.UpdateQuality();
  }
};

// === Normal(Etc) ===
TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn1Quality1_DecreaseQuality1) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<NormalItem>(EtcItemStr, 1, 1));

  updateQuality(items);

  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, 0);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn1Quality0_NoDecreaseQuality) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<NormalItem>(EtcItemStr, 1, 0));

  updateQuality(items);

  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, 0);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality0_NoDecreaseQuality) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<NormalItem>(EtcItemStr, 0, 0));

  updateQuality(items);

  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality1_DecreaseSellin1Quality1) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<NormalItem>(EtcItemStr, 0, 1));

  updateQuality(items);

  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality2_DecreaseSellin1Quality2) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<NormalItem>(EtcItemStr, 0, 2));

  updateQuality(items);

  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 0);
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture, EtcItemTest_WhenQualityNegative_ThrowException) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<NormalItem>(EtcItemStr, 0, -1));
  EXPECT_THROW({ updateQuality(items); }, std::invalid_argument);
}
#endif

// === AgedBrie ===
TEST_F(GildedRoseTestFixture,
       AgedBrieItemTest_WhenSellInPositive_IncreaeQuality2) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<AgedBrieItem>(AgedBrieItemStr, 1, 0));

  updateQuality(items);

  EXPECT_EQ(items[0]->sellIn, 0);
  EXPECT_EQ(items[0]->quality, 1);
}

TEST_F(GildedRoseTestFixture,
       AgedBrieItemTest_WhenSellIn0Quality0_DecreaseSellin1IncreaeQuality2) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<AgedBrieItem>(AgedBrieItemStr, 0, 0));

  updateQuality(items);

  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 2);
}

TEST_F(GildedRoseTestFixture, AgedBrieItemTest_MaxQuality50Check) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<AgedBrieItem>(AgedBrieItemStr, 0, 49));
  items.emplace_back(std::make_unique<AgedBrieItem>(AgedBrieItemStr, 0, 50));

  updateQuality(items);

  vector<UpItem> expected;
  expected.emplace_back(
      std::make_unique<AgedBrieItem>(AgedBrieItemStr, -1, 50));
  expected.emplace_back(
      std::make_unique<AgedBrieItem>(AgedBrieItemStr, -1, 50));

  EXPECT_THAT(items, PtrRangeEqByValue(std::cref(expected)));
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       AgedBrieItemTest_WhenQualityOver50_ThrowException) {
  vector<UpItem> items;
  items.emplace_back(std::make_unique<AgedBrieItem>(AgedBrieItemStr, 0, 51));
  EXPECT_THROW({ updateQuality(items); }, std::invalid_argument);
}
#endif

// === Legendary (불변) ===
// unique_ptr는 복사가 안되므로 'init_items를 복사'하지 말고
// input과 expected를 각각 따로 만들어 비교한다.
TEST_F(GildedRoseTestFixture, LegendaryItemTest_NoChangeSellInAndQuality) {
  vector<UpItem> input;
  input.emplace_back(std::make_unique<LegendaryItem>(LegendaryItemStr, 0, 0));
  input.emplace_back(std::make_unique<LegendaryItem>(LegendaryItemStr, -1, 0));
  input.emplace_back(std::make_unique<LegendaryItem>(LegendaryItemStr, 1, 0));
  input.emplace_back(std::make_unique<LegendaryItem>(LegendaryItemStr, 0, -1));
  input.emplace_back(std::make_unique<LegendaryItem>(LegendaryItemStr, 0, 1));
  input.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, (int)1e9, (int)1e9));
  input.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, -(int)1e9, -(int)1e9));

  vector<UpItem> expected;
  expected.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, 0, 0));
  expected.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, -1, 0));
  expected.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, 1, 0));
  expected.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, 0, -1));
  expected.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, 0, 1));
  expected.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, (int)1e9, (int)1e9));
  expected.emplace_back(
      std::make_unique<LegendaryItem>(LegendaryItemStr, -(int)1e9, -(int)1e9));

  updateQuality(input);

  EXPECT_THAT(input, PtrRangeEqByValue(std::cref(expected)));
}

// === Concert Ticket ===
TEST_F(GildedRoseTestFixture, ConcertTicketItemTest_BoundaryCheck) {
  vector<UpItem> input_items;
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 11, 0));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 10, 0));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 6, 0));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 5, 0));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 1, 0));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 0, 100));

  updateQuality(input_items);

  vector<UpItem> expected_items;
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 10, 1));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 9, 2));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 5, 2));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 4, 3));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 0, 3));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, -1, 0));

  EXPECT_THAT(input_items, PtrRangeEqByValue(std::cref(expected_items)));
}

TEST_F(GildedRoseTestFixture, ConcertTicketItemTest_MaxQuality50Check) {
  vector<UpItem> input_items;
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 11, 50));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 10, 49));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 6, 49));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 5, 49));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 1, 49));
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 0, 49));

  updateQuality(input_items);

  vector<UpItem> expected_items;
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 10, 50));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 9, 50));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 5, 50));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 4, 50));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 0, 50));
  expected_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, -1, 0));

  EXPECT_THAT(input_items, PtrRangeEqByValue(std::cref(expected_items)));
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       ConcertTicketItemTest_WhenNegativeQuality_ThorwException) {
  vector<UpItem> input_items;
  input_items.emplace_back(
      std::make_unique<ConcertTicketItem>(ConcertTicketItemStr, 0, -1));
  EXPECT_THROW({ updateQuality(input_items); }, std::invalid_argument);
}
#endif
