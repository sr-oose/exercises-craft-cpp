#include <gtest/gtest.h>
#include "GildedRose.h"

using namespace std;

const string BACKSTAGE_PASSES = "Backstage passes to a TAFKAL80ETC concert";
const string SULFURAS_HAND_OF_RAGNAROS = "Sulfuras, Hand of Ragnaros";
const string AGED_BRIE = "Aged Brie";
const string DEXTERITY_VEST = "+5 Dexterity Vest";


class Fixture : public ::testing::Test {
public:
    Fixture() : gildedRose(items) {}

    void doUpdateQuality() {
        gildedRose.updateQuality();
    }

    void createItemWithSellinAndQuality(string name, int sellIn, int quality) {
        Item item = Item(name, sellIn, quality);
        if (gildedRose.items.empty()){
            gildedRose.items.push_back(item);
        } else {
            gildedRose.items[0] = item;
        }
    }

    void createBackstagePassWithSellinAndQuality(int sellIn, int quality) {
        createItemWithSellinAndQuality(BACKSTAGE_PASSES, sellIn, quality);
    }

    void verifyBackstagePassIs(int sellIn, int quality) {
        verifyItemIs(BACKSTAGE_PASSES, sellIn, quality);
    }

    void verifyItemIs(string name, int sellIn, int quality) {
        ASSERT_EQ(name, gildedRose.items[0].name);
        ASSERT_EQ(sellIn, gildedRose.items[0].sellIn);
        ASSERT_EQ(quality, gildedRose.items[0].quality);
    }
private:
    vector<Item> items;
   	GildedRose gildedRose;

};


TEST_F(Fixture, standard_items_lower_sellIn_and_quality){
    createItemWithSellinAndQuality(DEXTERITY_VEST, 10, 10);
    doUpdateQuality();
    verifyItemIs(DEXTERITY_VEST, 9, 9);
}

TEST_F(Fixture, the_quality_of_an_item_is_never_negative){
    createItemWithSellinAndQuality(DEXTERITY_VEST, 10, 0);
    doUpdateQuality();
    verifyItemIs(DEXTERITY_VEST, 9, 0);
}

TEST_F(Fixture, once_the_sell_by_date_has_passed_quality_degrades_twice_as_fast){
    createItemWithSellinAndQuality(DEXTERITY_VEST, 0, 10);
    doUpdateQuality();
    verifyItemIs(DEXTERITY_VEST, -1, 8);
}

TEST_F(Fixture, once_the_sell_by_date_has_passed_quality_degrades_twice_as_fast_but_never_becomes_negative){
    createItemWithSellinAndQuality(DEXTERITY_VEST, 0, 1);
    doUpdateQuality();
    verifyItemIs(DEXTERITY_VEST, -1, 0);
}

TEST_F(Fixture, aged_brie_actually_increases_in_quality_the_older_it_gets){
    createItemWithSellinAndQuality(AGED_BRIE, 10, 10);
    doUpdateQuality();
    verifyItemIs(AGED_BRIE, 9, 11);
}

TEST_F(Fixture, the_quality_of_an_item_is_never_more_than_50){
    createItemWithSellinAndQuality(AGED_BRIE, 10, 50);
    doUpdateQuality();
    verifyItemIs(AGED_BRIE, 9, 50);
}

TEST_F(Fixture, sulfuras_being_a_legendary_item_never_has_to_be_sold_or_decreases_in_quality){
    createItemWithSellinAndQuality(SULFURAS_HAND_OF_RAGNAROS, 10, 80);
    doUpdateQuality();
    verifyItemIs(SULFURAS_HAND_OF_RAGNAROS, 10, 80);
}

TEST_F(Fixture, backstage_passes_increases_in_quality_as_its_sellIn_value_approaches){
    createBackstagePassWithSellinAndQuality(20, 10);
    doUpdateQuality();
    verifyBackstagePassIs(19, 11);

    createBackstagePassWithSellinAndQuality(11, 10);
    doUpdateQuality();
    verifyBackstagePassIs(10, 11);
}

TEST_F(Fixture, backstage_passes_with_sellIn_value_less_than_or_equal_to_10_increases_in_quality_by_two) {
    createBackstagePassWithSellinAndQuality(10, 10);
    doUpdateQuality();
    verifyBackstagePassIs(9, 12);

    createBackstagePassWithSellinAndQuality(9, 10);
    doUpdateQuality();
    verifyBackstagePassIs(8, 12);

    createBackstagePassWithSellinAndQuality(6, 10);
    doUpdateQuality();
    verifyBackstagePassIs(5, 12);
}

TEST_F(Fixture, backstage_passes_with_sellIn_value_less_than_or_equal_to_5_increases_in_quality_by_three) {
    createBackstagePassWithSellinAndQuality(5, 10);
    doUpdateQuality();
    verifyBackstagePassIs(4, 13);

    createBackstagePassWithSellinAndQuality(4, 10);
    doUpdateQuality();
    verifyBackstagePassIs(3, 13);

    createBackstagePassWithSellinAndQuality(1, 10);
    doUpdateQuality();
    verifyBackstagePassIs(0, 13);
}

TEST_F(Fixture, backstage_passes_with_sellIn_value_less_than_or_equal_to_0_drop_quality_to_0) {
    createBackstagePassWithSellinAndQuality(0, 10);
    doUpdateQuality();
    verifyBackstagePassIs(-1, 0);

    createBackstagePassWithSellinAndQuality(-1, 10);
    doUpdateQuality();
    verifyBackstagePassIs(-2, 0);
}

TEST_F(Fixture, backstage_passes_quality_never_increases_beyond_50) {
    createBackstagePassWithSellinAndQuality(20, 50);
    doUpdateQuality();
    verifyBackstagePassIs(19, 50);

    createBackstagePassWithSellinAndQuality(9, 50);
    doUpdateQuality();
    verifyBackstagePassIs(8, 50);

    createBackstagePassWithSellinAndQuality(3, 50);
    doUpdateQuality();
    verifyBackstagePassIs(2, 50);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}