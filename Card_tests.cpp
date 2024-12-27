

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_get_rank) {
    Card c(Card::RANK_SEVEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::RANK_SEVEN, c.get_rank());
}

TEST(test_get_suit){
    Card c(Card::RANK_SIX, Card::SUIT_HEARTS);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, d.get_suit(Card::SUIT_DIAMONDS));
}

TEST(test_face){
    Card c(Card::RANK_SEVEN, Card::SUIT_SPADES);
    Card d(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_face());
    ASSERT_TRUE(d.is_face());
}

TEST(test_is_trump){
    Card a(Card::RANK_SEVEN, Card::SUIT_HEARTS);
    Card b(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c(Card::RANK_FIVE, Card::SUIT_CLUBS);
    Card d(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(a.is_trump(Card::SUIT_HEARTS));
    ASSERT_FALSE(b.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(d.is_trump(Card::SUIT_CLUBS));
}

TEST(test_operators){
    Card c(Card::RANK_SEVEN, Card::SUIT_HEARTS);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card e(Card::RANK_FIVE, Card::SUIT_CLUBS);
    Card f(Card::RANK_FIVE, Card::SUIT_DIAMONDS);
    Card g(Card::RANK_ACE, Card::SUIT_SPADES);
    
    ASSERT_TRUE(e < c);
    ASSERT_TRUE(e < f);
    ASSERT_FALSE(e < e);
    ASSERT_FALSE(g < e);

    ASSERT_TRUE(e <= e);
    ASSERT_FALSE(g <= e);
    
    ASSERT_TRUE(d > c);
    ASSERT_TRUE(f > e);
    ASSERT_FALSE(e > g);
    
    ASSERT_TRUE(e >= e);
    ASSERT_TRUE(g > f);
    
    ASSERT_FALSE(e == f);
    ASSERT_TRUE(c == c);
    
    ASSERT_TRUE(c != f);
    ASSERT_FALSE(f != f);
}

TEST(test_right_bower){
    Card c(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_HEARTS));
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(d.is_right_bower(Card::SUIT_HEARTS));
}

TEST(test_left_bower) {
    Card c(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_HEARTS));
    Card d(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(d.is_left_bower(Card::SUIT_HEARTS));
}

TEST(test_suit_next){
    ASSERT_EQUAL(Card::SUIT_HEARTS, Suit_next(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(Card::SUIT_CLUBS, Suit_next(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_SPADES, Suit_next(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, Suit_next(Card::SUIT_HEARTS));
}

TEST(card_less) {
    
    Card js(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jh(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jc(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jd(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ad(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    
    
    ASSERT_TRUE(Card_less(jh, jc, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ad, jh, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(js, ad, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(ad, jd, Card::SUIT_DIAMONDS));
}

TEST_MAIN()

