#include "gilded_rose.h"
#include <stdexcept>

#include "gmock/gmock.h"

using std::string;
using std::vector;
using namespace testing;

MATCHER(PtrEqByValue, "compares *lhs == *rhs") {
  // arg is std::tuple<LhsElement, RhsElement>
    const Item *lhs = std::get<0>(arg);
    const Item *rhs = std::get<1>(arg);;
    if(lhs == nullptr || rhs == nullptr) return lhs == rhs;
    return *lhs == *rhs;
}

class GildedRoseTestFixture : public Test {
 public:
  const string AgedBrieItemStr = "Aged Brie";
  const string ConcertTicketItemStr =
      "Backstage passes to a TAFKAL80ETC concert";
  const string LegendaryItemStr = "Sulfuras, Hand of Ragnaros";
  const string EtcItemStr = "Foo";

  void updateQuality(vector<Item*>& out_items) {
    GildedRose app(out_items);
    app.UpdateQuality();
  }
};

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn1Quality1_DecreaseQuality1) {
  // Arrange
  vector<Item*> items = {new NormalItem(EtcItemStr, 1, 1)};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, 0);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn1Quality0_NoDecreaseQuality) {
  // Arrange
  vector<Item*> items = {new NormalItem(EtcItemStr, 1, 0)};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, 0);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality0_NoDecreaseQuality) {
  // Arrange
  vector<Item*> items = {new NormalItem(EtcItemStr, 0, 0)};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality1_DecreaseSellin1Quality1) {
  // Arrange
  vector<Item*> items = {new NormalItem(EtcItemStr, 0, 1)};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality2_DecreaseSellin1Quality2) {
  // Arrange
  vector<Item*> items = {new NormalItem(EtcItemStr, 0, 2)};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0]->name);
  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 0);
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenQualityNegative_ThrowException) {
  // Arrange
  vector<Item*> items = {{EtcItemStr, 0, -1}};

  // Act
  EXPECT_THROW({ updateQuality(items); }, std::invalid_argument);
}
#endif

//AgedBrie: sellIn>0 -> quality++;
TEST_F(GildedRoseTestFixture, AgedBrieItemTest_WhenSellInPositive_IncreaeQuality2) {
  // Arrange
  vector<Item*> items = {new AgedBrieItem(AgedBrieItemStr, 1, 0)};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(items[0]->sellIn, 0);
  EXPECT_EQ(items[0]->quality, 1);
}

//AgedBrie: sellIn<=0 -> quality+=2;
TEST_F(GildedRoseTestFixture,
       AgedBrieItemTest_WhenSellIn0Quality0_DecreaseSellin1IncreaeQuality2) {
  // Arrange
  vector<Item*> items = {new AgedBrieItem(AgedBrieItemStr, 0, 0)};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(items[0]->sellIn, -1);
  EXPECT_EQ(items[0]->quality, 2);
}

// AgedBrie: max quality == 50
TEST_F(GildedRoseTestFixture, AgedBrieItemTest_MaxQuality50Check) {
  // Arrange
  vector<Item*> items = {new AgedBrieItem(AgedBrieItemStr, 0, 49),
                         new AgedBrieItem(AgedBrieItemStr, 0, 50)};

  // Act
  updateQuality(items);

  vector<Item*> expected = {new AgedBrieItem(AgedBrieItemStr, -1, 50),
                            new AgedBrieItem(AgedBrieItemStr, -1, 50)};

  EXPECT_THAT(items, Pointwise(PtrEqByValue(), expected));
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       AgedBrieItemTest_WhenQualityOver50_ThrowException) {
  // Arrange
  vector<Item*> items = {{AgedBrieItemStr, 0, 51}};

  // Act
  EXPECT_THROW({ updateQuality(items); }, std::invalid_argument);
}
#endif

TEST_F(GildedRoseTestFixture, LegendaryItemTest_NoChangeSellInAndQuality) {
  const vector<Item*> init_items = {
      new LegendaryItem(LegendaryItemStr, 0, 0),
      new LegendaryItem(LegendaryItemStr, -1, 0),
      new LegendaryItem(LegendaryItemStr, 1, 0),
      new LegendaryItem(LegendaryItemStr, 0, -1),
      new LegendaryItem(LegendaryItemStr, 0, 1),
      new LegendaryItem(LegendaryItemStr, (int)1e9, (int)1e9),
      new LegendaryItem(LegendaryItemStr, -(int)1e9, -(int)1e9)};
  vector<Item*> items = init_items;

  updateQuality(items);

  EXPECT_EQ(items, init_items);
}

TEST_F(GildedRoseTestFixture, ConcertTicketItemTest_BoundaryCheck) {
  vector<Item*> input_items = {
      new ConcertTicketItem(ConcertTicketItemStr, 11, 0),
      new ConcertTicketItem(ConcertTicketItemStr, 10, 0),
      new ConcertTicketItem(ConcertTicketItemStr, 6, 0),
      new ConcertTicketItem(ConcertTicketItemStr, 5, 0),
      new ConcertTicketItem(ConcertTicketItemStr, 1, 0),
      new ConcertTicketItem(ConcertTicketItemStr, 0, 100)};

  updateQuality(input_items);

  vector<Item*> expected_items = {
      new ConcertTicketItem(ConcertTicketItemStr, 10, 1),
      new ConcertTicketItem(ConcertTicketItemStr, 9, 2),
      new ConcertTicketItem(ConcertTicketItemStr, 5, 2),
      new ConcertTicketItem(ConcertTicketItemStr, 4, 3),
      new ConcertTicketItem(ConcertTicketItemStr, 0, 3),
      new ConcertTicketItem(ConcertTicketItemStr, -1, 0)};

  EXPECT_THAT(input_items, Pointwise(PtrEqByValue(), expected_items));
}

TEST_F(GildedRoseTestFixture, ConcertTicketItemTest_MaxQuality50Check) {
  vector<Item*> input_items = {
      new ConcertTicketItem(ConcertTicketItemStr, 11, 50),
      new ConcertTicketItem(ConcertTicketItemStr, 10, 49),
      new ConcertTicketItem(ConcertTicketItemStr, 6, 49),
      new ConcertTicketItem(ConcertTicketItemStr, 5, 49),
      new ConcertTicketItem(ConcertTicketItemStr, 1, 49),
      new ConcertTicketItem(ConcertTicketItemStr, 0, 49)};

  updateQuality(input_items);

  vector<Item*> expected_items = {
      new ConcertTicketItem(ConcertTicketItemStr, 10, 50),
      new ConcertTicketItem(ConcertTicketItemStr, 9, 50),
      new ConcertTicketItem(ConcertTicketItemStr, 5, 50),
      new ConcertTicketItem(ConcertTicketItemStr, 4, 50),
      new ConcertTicketItem(ConcertTicketItemStr, 0, 50),
      new ConcertTicketItem(ConcertTicketItemStr, -1, 0)};

  EXPECT_THAT(input_items, Pointwise(PtrEqByValue(), expected_items));
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       ConcertTicketItemTest_WhenNegativeQuality_ThorwException) {
  vector<Item*> input_items = {{ConcertTicketItemStr, 0, -1}};

  EXPECT_THROW({ updateQuality(input_items); }, std::invalid_argument);
}
#endif
