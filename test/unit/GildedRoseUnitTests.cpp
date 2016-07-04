#include <gtest/gtest.h>
#include "GildedRose.h"


class GildedRoseTest : public ::testing::Test {
public:
    GildedRoseTest() : app(items) {};

public:
    vector<Item> items;
    GildedRose app;

    void GivenItemWithSellinAndQuality(const char *name, int sellIn, int quality);
    void WhenWeUpdateTheQuality(void);
    void ThenItemBecomes(const char *name, int sellIn, int quality);
    void backstagePassQuality(int sellIn, int startQuality, int expectedQuality);

};

void GildedRoseTest::GivenItemWithSellinAndQuality(const char *name, int sellIn, int quality) {
    items.push_back(Item(name, sellIn, quality));
}

void GildedRoseTest::WhenWeUpdateTheQuality(void) {
    app.updateQuality();
}

void GildedRoseTest::ThenItemBecomes(const char *name, int sellIn, int quality) {
    Item item = app.items[0];
    ASSERT_EQ(name, item.name);
    ASSERT_EQ(sellIn, item.sellIn) << "wrong sellIn";
    ASSERT_EQ(quality, item.quality) << "wrong quality";
}


TEST_F(GildedRoseTest, at_the_end_of_each_day_our_system_lowers_both_values_for_every_item) {
    GivenItemWithSellinAndQuality("Foo", 10, 10);
    WhenWeUpdateTheQuality();
    ThenItemBecomes("Foo", 9, 9);
}

TEST_F(GildedRoseTest, test_the_Quality_of_an_item_is_never_negative) {
    GivenItemWithSellinAndQuality("foo", 10, 0);
    WhenWeUpdateTheQuality();
    ThenItemBecomes("foo", 9, 0);
}

TEST_F(GildedRoseTest, once_the_sell_by_date_has_passed_Quality_degrades_twice_as_fast) {
    GivenItemWithSellinAndQuality("foo", 0, 10);
    WhenWeUpdateTheQuality();
    ThenItemBecomes("foo", -1, 8);
}


TEST_F(GildedRoseTest, once_the_sell_by_date_has_passed_Quality_degrades_twice_as_fast_2) {
    GivenItemWithSellinAndQuality("foo", 0, 1);
    WhenWeUpdateTheQuality();
    ThenItemBecomes("foo", -1, 0);
}

TEST_F(GildedRoseTest, Aged_Brie_actually_increases_in_Quality_the_older_it_gets) {
    GivenItemWithSellinAndQuality("Aged Brie", 10, 10);
    WhenWeUpdateTheQuality();
    ThenItemBecomes("Aged Brie", 9, 11);
}


TEST_F(GildedRoseTest, the_Quality_of_an_item_is_never_more_than_50) {
    GivenItemWithSellinAndQuality("Aged Brie", 10, 50);
    WhenWeUpdateTheQuality();
    ThenItemBecomes("Aged Brie", 9, 50);
}


TEST_F(GildedRoseTest, Sulfuras_being_a_legendary_item_never_has_to_be_sold_or_decreases_in_Quality) {
    const char *sulfuras = "Sulfuras, Hand of Ragnaros";
    GivenItemWithSellinAndQuality(sulfuras, 10, 80);
    WhenWeUpdateTheQuality();
    ThenItemBecomes(sulfuras, 10, 80);
}

void GildedRoseTest::backstagePassQuality(int sellIn, int startQuality, int expectedQuality) {
    const char *backstagePass = "Backstage passes to a TAFKAL80ETC concert";
    GivenItemWithSellinAndQuality(backstagePass, sellIn, startQuality );
    WhenWeUpdateTheQuality();
    Item item = app.items[app.items.size()-1];
    ASSERT_EQ(expectedQuality, item.quality);
    ASSERT_EQ(sellIn - 1, item.sellIn);
}

TEST_F(GildedRoseTest, backstage_passes_increases_in_Quality_as_its_SellIn_value_approaches) {
    backstagePassQuality(20, 10, 11);
    backstagePassQuality(11, 10, 11);
    backstagePassQuality(10, 10, 12);
    backstagePassQuality(9, 10, 12);
    backstagePassQuality(6, 10, 12);
    backstagePassQuality(5, 10, 13);
    backstagePassQuality(4, 10, 13);
    backstagePassQuality(1, 10, 13);
    backstagePassQuality(0, 10, 0);
    backstagePassQuality(-1, 10, 0);
    backstagePassQuality(20, 50, 50);
    backstagePassQuality(9, 50, 50);
    backstagePassQuality(3, 50, 50);
}
