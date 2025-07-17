#include "gmock/gmock.h"
#include "gilded_rose.h"

using std::vector;
using std::string;

TEST(GildedRoseTest, Foo){
	//Arrange
	vector<Item> items;
	//items.push_back(Item("Foo", 0, 0));
	items.emplace_back("Foo", 0, 0);
	GildedRose app(items);

	//Act
	app.updateQuality();

	//Arrange
	EXPECT_EQ("Foo", app.items[0].name);
}

TEST(GildedRoseTest, NoNameSellin0Quality0) {
	vector<Item> items;
	items.emplace_back("noname", 0,0);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(-1, items[0].sellIn);
	EXPECT_EQ(0, items[0].quality);
}

TEST(GildedRoseTest, NoNameSellin0Quality1) {
	vector<Item> items;
	items.emplace_back("noname", 0,1);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(-1, items[0].sellIn);
	EXPECT_EQ(0, items[0].quality);
}


TEST(GildedRoseTest, SulfurasSellin0Quality80) {
	vector<Item> items;
	items.emplace_back("Sulfuras, Hand of Ragnaros", 0,80);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(0, items[0].sellIn);
	EXPECT_EQ(80, items[0].quality);
}

