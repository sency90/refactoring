#include "gilded_rose.h"
#include <stdexcept>

#include "gmock/gmock.h"

using std::string;
using std::vector;
using namespace testing;

class GildedRoseTestFixture : public Test {
 public:
  const string AgedBrieItemStr = "Aged Brie";
  const string ConcertTicketItemStr =
      "Backstage passes to a TAFKAL80ETC concert";
  const string LegendaryItemStr = "Sulfuras, Hand of Ragnaros";
  const string EtcItemStr = "Foo";

  void updateQuality(vector<Item>& out_items) {
    GildedRose app(out_items);
    app.UpdateQuality();
  }
};

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn1Quality1_DecreaseQuality1) {
  // Arrange
  vector<Item> items = {{EtcItemStr, 1, 1}};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0].name);
  EXPECT_EQ(items[0].sellIn, 0);
  EXPECT_EQ(items[0].quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn1Quality0_NoDecreaseQuality) {
  // Arrange
  vector<Item> items = {{EtcItemStr, 1, 0}};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0].name);
  EXPECT_EQ(items[0].sellIn, 0);
  EXPECT_EQ(items[0].quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality0_NoDecreaseQuality) {
  // Arrange
  vector<Item> items = {{EtcItemStr, 0, 0}};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0].name);
  EXPECT_EQ(items[0].sellIn, -1);
  EXPECT_EQ(items[0].quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality1_DecreaseSellin1Quality1) {
  // Arrange
  vector<Item> items = {{EtcItemStr, 0, 1}};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0].name);
  EXPECT_EQ(items[0].sellIn, -1);
  EXPECT_EQ(items[0].quality, 0);
}

TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenSellIn0Quality2_DecreaseSellin1Quality2) {
  // Arrange
  vector<Item> items = {{EtcItemStr, 0, 2}};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(EtcItemStr, items[0].name);
  EXPECT_EQ(items[0].sellIn, -1);
  EXPECT_EQ(items[0].quality, 0);
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       EtcItemTest_WhenQualityNegative_ThrowException) {
  // Arrange
  vector<Item> items = {{EtcItemStr, 0, -1}};

  // Act
  EXPECT_THROW({ updateQuality(items); }, std::invalid_argument);
}
#endif

//AgedBrie: sellIn>0 -> quality++;
TEST_F(GildedRoseTestFixture, AgedBrieItemTest_WhenSellInPositive_IncreaeQuality2) {
  // Arrange
  vector<Item> items = {{AgedBrieItemStr, 1, 0}};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(items[0].sellIn, 0);
  EXPECT_EQ(items[0].quality, 1);
}

//AgedBrie: sellIn<=0 -> quality+=2;
TEST_F(GildedRoseTestFixture,
       AgedBrieItemTest_WhenSellIn0Quality0_DecreaseSellin1IncreaeQuality2) {
  // Arrange
  vector<Item> items = {{AgedBrieItemStr, 0, 0}};

  // Act
  updateQuality(items);

  // Assert
  EXPECT_EQ(items[0].sellIn, -1);
  EXPECT_EQ(items[0].quality, 2);
}

// AgedBrie: max quality == 50
TEST_F(GildedRoseTestFixture, AgedBrieItemTest_MaxQuality50Check) {
  // Arrange
  vector<Item> items = {{AgedBrieItemStr, 0, 49}, {AgedBrieItemStr, 0, 50}};

  // Act
  updateQuality(items);

  vector<Item> expected = {{AgedBrieItemStr, -1, 50},
                           {AgedBrieItemStr, -1, 50}};

  EXPECT_EQ(items, expected);
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       AgedBrieItemTest_WhenQualityOver50_ThrowException) {
  // Arrange
  vector<Item> items = {{AgedBrieItemStr, 0, 51}};

  // Act
  EXPECT_THROW({ updateQuality(items); }, std::invalid_argument);
}
#endif

TEST_F(GildedRoseTestFixture, LegendaryItemTest_NoChangeSellInAndQuality) {
  const vector<Item> init_items = {{LegendaryItemStr, 0, 0},
                                   {LegendaryItemStr, -1, 0},
                                   {LegendaryItemStr, 1, 0},
                                   {LegendaryItemStr, 0, -1},
                                   {LegendaryItemStr, 0, 1},
                                   {LegendaryItemStr, (int)1e9, (int)1e9},
                                   {LegendaryItemStr, -(int)1e9, -(int)1e9}};
  vector<Item> items = init_items;

  updateQuality(items);

  EXPECT_EQ(items, init_items);
}

TEST_F(GildedRoseTestFixture, ConcertTicketItemTest_BoundaryCheck) {
  vector<Item> input_items = {
      {ConcertTicketItemStr, 11, 0}, {ConcertTicketItemStr, 10, 0},
      {ConcertTicketItemStr, 6, 0},  {ConcertTicketItemStr, 5, 0},
      {ConcertTicketItemStr, 1, 0},  {ConcertTicketItemStr, 0, 100}};

  updateQuality(input_items);

  vector<Item> expected_items = {
      {ConcertTicketItemStr, 10, 1}, {ConcertTicketItemStr, 9, 2},
      {ConcertTicketItemStr, 5, 2},  {ConcertTicketItemStr, 4, 3},
      {ConcertTicketItemStr, 0, 3},  {ConcertTicketItemStr, -1, 0}};

  EXPECT_EQ(input_items, expected_items);
}

TEST_F(GildedRoseTestFixture, ConcertTicketItemTest_MaxQuality50Check) {
  vector<Item> input_items = {
      {ConcertTicketItemStr, 11, 50}, {ConcertTicketItemStr, 10, 49},
      {ConcertTicketItemStr, 6, 49},  {ConcertTicketItemStr, 5, 49},
      {ConcertTicketItemStr, 1, 49},  {ConcertTicketItemStr, 0, 49}};

  updateQuality(input_items);

  vector<Item> expected_items = {
      {ConcertTicketItemStr, 10, 50}, {ConcertTicketItemStr, 9, 50},
      {ConcertTicketItemStr, 5, 50},  {ConcertTicketItemStr, 4, 50},
      {ConcertTicketItemStr, 0, 50},  {ConcertTicketItemStr, -1, 0}};

  EXPECT_EQ(input_items, expected_items);
}

#ifdef EXCEPTION_SETTING
TEST_F(GildedRoseTestFixture,
       ConcertTicketItemTest_WhenNegativeQuality_ThorwException) {
  vector<Item> input_items = {{ConcertTicketItemStr, 0, -1}};

  EXPECT_THROW({ updateQuality(input_items); }, std::invalid_argument);
}
#endif
