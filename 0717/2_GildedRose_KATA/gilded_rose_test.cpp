#include "gmock/gmock.h"
#include "gilded_rose.h"

using std::vector;
using std::string;

namespace{
	const char* SULFURAS = "Sulfuras, Hand of Ragnaros";
	const char* NONAME = "noname";
	const char* AGED_BRIE = "Aged Brie";
	const char* BACKSTAGE_PASS = "Backstage passes to a TAFKAL80ETC concert";
};

TEST(GildedRoseTest, Foo){
	//Arrange
	vector<Item> items;
	//items.push_back(Item("Foo", 0, 0));
	items.emplace_back("Foo", 0, 0);
	GildedRose app(items);

	//Act
	app.updateQuality();

	//Assert
	EXPECT_EQ("Foo", app.items[0].name);
}

//quality�� 0������ �������� �ʴ´�.
TEST(GildedRoseTest, NoNameSellin0Quality0) {
	//Arrange
	vector<Item> items;
	items.emplace_back(NONAME, 0,0);
	GildedRose app{ items };

	//Act
	app.updateQuality();

	//Assert
	EXPECT_EQ(-1, items[0].sellIn);
	EXPECT_EQ(0, items[0].quality);
}

TEST(GildedRoseTest, NoNameSellin0Quality1) {
	vector<Item> items;
	items.emplace_back(NONAME, 0,1);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(-1, items[0].sellIn);
	EXPECT_EQ(0, items[0].quality);
}

//���� Item�� SULFURAS�� sellIn�� quality�� ���� �������� �ʴ´�.
TEST(GildedRoseTest, SulfurasSellin0Quality80) {
	vector<Item> items;
	items.emplace_back(SULFURAS, 0, 80);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(0, items[0].sellIn);
	EXPECT_EQ(80, items[0].quality);
}


//���� Item�� SULFURAS�� sellIn�� quality�� ���� �������� �ʴ´�.
TEST(GildedRoseTest, SulfurasSellinM2Quality80) {
	vector<Item> items;
	items.emplace_back(SULFURAS, -2, 80);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(-2, items[0].sellIn);
	EXPECT_EQ(80, items[0].quality);
}

//ġ���� sellin�� ������ �Ǹ� quality�� 2�� �����ؾ� �ϳ�,
//ġ���� quality max�� 50�̹Ƿ� �Ϸ簡 ������ 50�̴�.
TEST(GildedRoseTest, AgedBrieSellin0Quality50) {
	vector<Item> items;
	items.emplace_back(AGED_BRIE, 0, 50);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(-1, items[0].sellIn);
	EXPECT_EQ(50, items[0].quality);
}

//�ܼ�Ʈ Ƽ���� sellIn�� �������Ǹ�, quality�� 0�� �ȴ�.
TEST(GildedRoseTest, BackstagePassSellin0Quality49) {
	vector<Item> items;
	items.emplace_back(BACKSTAGE_PASS, 0, 49);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(-1, items[0].sellIn);
	EXPECT_EQ(0, items[0].quality);
}

TEST(GildedRoseTest, BackstagePassSellin12Quality0) {
	vector<Item> items;
	items.emplace_back(BACKSTAGE_PASS, 12, 0);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(11, items[0].sellIn);
	EXPECT_EQ(1, items[0].quality);
}

TEST(GildedRoseTest, BackstagePassSellin10Quality0) {
	vector<Item> items;
	items.emplace_back(BACKSTAGE_PASS, 10, 0);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(9, items[0].sellIn);
	EXPECT_EQ(2, items[0].quality);
}

TEST(GildedRoseTest, BackstagePassSellin5Quality0) {
	vector<Item> items;
	items.emplace_back(BACKSTAGE_PASS, 5, 0);
	GildedRose app{ items };

	app.updateQuality();

	EXPECT_EQ(4, items[0].sellIn);
	EXPECT_EQ(3, items[0].quality);
}

