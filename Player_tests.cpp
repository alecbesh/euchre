

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_get_name) {
    Player* p1 = Player_factory("p1", "Simple");
    Player* p2 = Player_factory("p2", "Human");
    ASSERT_EQUAL("p1", p1->get_name());
    ASSERT_EQUAL("p2", p2->get_name());

    delete p1;
    delete p2;
}

TEST(test_print_players) {
    Player* p1 = Player_factory("p1", "Simple");
    Player* p2 = Player_factory("p2", "Human");
    ostringstream out;
    out << *p1;
    ASSERT_EQUAL(out.str(), "p1");
    out.str("");
    out << *p2;
    ASSERT_EQUAL(out.str(), "p2");

    delete p1;
    delete p2;
}

TEST(test_lead) {
    Player* p1 = Player_factory("p1", "Simple");
    string trump = Card::SUIT_DIAMONDS;
    Card nc(Card::RANK_SEVEN, Card::SUIT_CLUBS);
    Card qc(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card qh(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card jh(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    p1->add_card(nc);
    p1->add_card(qc);
    p1->add_card(qh);
    p1->add_card(jh);
    ASSERT_EQUAL(p1->lead_card(trump), qc);
    delete p1;
}

TEST(test_lead2) {
    Player* p1 = Player_factory("p1", "Simple");
    string trump = Card::SUIT_SPADES;
    Card ns(Card::RANK_NINE, Card::SUIT_SPADES);
    Card qd(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card kh(Card::RANK_KING, Card::SUIT_HEARTS);
    Card nh(Card::RANK_NINE, Card::SUIT_HEARTS);
    p1->add_card(ns);
    p1->add_card(qd);
    p1->add_card(kh);
    p1->add_card(nh);
    p1->lead_card(trump);
    ASSERT_EQUAL(p1->lead_card(trump), qd);
    delete p1;
}

TEST(test_lead3) {
    
    Player * oliver = Player_factory("Oliver", "Simple");
    Player * alec = Player_factory("Alec", "Simple");
    Card jc(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ks(Card::RANK_KING, Card::SUIT_SPADES);
    Card jh(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ad(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    string trump = Card::SUIT_SPADES;
    
    oliver->add_card(jc);
    oliver->add_card(ks);
    alec->add_card(jh);
    alec->add_card(ad);

    Card card_o = oliver->lead_card(trump);
    Card card_a = alec->lead_card(trump);
    
    ASSERT_EQUAL(card_o, jc);
    ASSERT_EQUAL(card_a, ad);
    
    delete oliver;
    delete alec;
}

TEST(test_add_and_discard) {
    Player* p = Player_factory("p", "Simple");
    string trump = Card::SUIT_HEARTS;
    Card card_one(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card card_two(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card card_three(Card::RANK_JACK, Card::SUIT_HEARTS);
    p->add_card(card_one);
    p->add_card(card_two);
    p->add_and_discard(card_three);

    ASSERT_EQUAL(p->lead_card(trump), card_three);
    delete p;
}

TEST(test_add_and_discard_2) {
    Player* oliver = Player_factory("Oliver", "Simple");
    Player* alec = Player_factory("Alec", "Simple");

    Card jc(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ks(Card::RANK_KING, Card::SUIT_SPADES);
    Card js(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;

    oliver -> add_card(jc);
    oliver -> add_card(ks);

    alec -> add_card(jc);
    alec -> add_card(js);

    oliver -> add_and_discard(js);
    alec -> add_and_discard(ks);

    Card one = oliver -> lead_card(trump);
    Card two = oliver -> lead_card(trump);
    Card three = alec -> lead_card(trump);
    Card four = alec -> lead_card(trump);

    ASSERT_EQUAL(one, js);
    ASSERT_EQUAL(two, jc);
    ASSERT_EQUAL(three, js);
    ASSERT_EQUAL(four, jc);

    delete oliver;
    delete alec;
}

TEST(test_init) {
    Player* p = Player_factory("p", "Simple");
    string trump = Card::SUIT_HEARTS;
    Card card_one(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card card_two(Card::RANK_TWO, Card::SUIT_CLUBS);
    Card card_three(Card::RANK_FIVE, Card::SUIT_CLUBS);
    Card card_four(Card::RANK_JACK, Card::SUIT_HEARTS);
    p->add_card(card_one);
    p->add_card(card_two);
    p->add_card(card_three);
    ASSERT_FALSE(p->make_trump(card_four, false, 1, trump));
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);
    delete p;
}

TEST(test_play) {
    Player* p = Player_factory("player3", "Simple");
    Card card_one(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card card_two(Card::RANK_KING, Card::SUIT_HEARTS);
    Card card_three(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card card_four(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card card_five(Card::RANK_FIVE, Card::SUIT_SPADES);
    Card card_led(Card::RANK_ACE, Card::SUIT_SPADES);
    p->add_card(card_one);
    p->add_card(card_two);
    p->add_card(card_three);
    p->add_card(card_four);
    p->add_card(card_five);
    ASSERT_EQUAL(p->play_card(card_led, Card::SUIT_HEARTS), card_four);
    delete p;
}

TEST(test_play_2){
    Player* p = Player_factory("player3", "Simple");
    Card one(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card two(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card three(Card::RANK_KING, Card::SUIT_CLUBS);
    Card four(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card five(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card led(Card::RANK_ACE, Card::SUIT_HEARTS);
    p->add_card(one);
    p->add_card(two);
    p->add_card(three);
    p->add_card(four);
    p->add_card(five);
    ASSERT_EQUAL(p->play_card(led, Card::SUIT_CLUBS), one);
    delete p;
}

TEST(test_play_3) {   
    Player * oliver = Player_factory("Oliver", "Simple");
    Player * alec = Player_factory("Alec", "Simple");
    Card jc(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card qs(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card js(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jh(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ac(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card ed(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
    
    string trump = Card::SUIT_SPADES;
    
    oliver->add_card(jc);
    alec->add_card(qs);
    oliver->add_card(jh);
    alec->add_card(ac);
    
    Card oliver1 = oliver->play_card(ed, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(oliver1, jh);
    oliver->add_card(jc);
    
    Card oliver2 = oliver->play_card(js, Card::SUIT_SPADES);
    ASSERT_EQUAL(oliver2, jc);
    oliver->add_card(jc);
    
    Card alec1 = alec->play_card(js, Card::SUIT_CLUBS);
    ASSERT_EQUAL(alec1, ac);
    alec->add_card(jh);
    
    delete oliver;
    delete alec;
}

TEST(test_make_trump) {
    
    Player * oliver = Player_factory("Oliver", "Simple");
    Player * alec = Player_factory("Alec", "Simple");
    Card ns(Card::RANK_NINE, Card::SUIT_SPADES);
    Card th(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card ts(Card::RANK_TEN, Card::SUIT_SPADES);
    Card jc(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ks(Card::RANK_KING, Card::SUIT_SPADES);
    Card js(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    
    alec->add_card(ns);
    alec->add_card(ts);
    oliver->add_card(jc);
    oliver->add_card(ks);
    
    bool order1 = oliver->make_trump(js, true, 1, trump);
    bool order2 = alec->make_trump(js, true, 1, trump);
    bool order3 = alec->make_trump(jc, true, 2, trump);
    bool order4 = oliver->make_trump(th, true, 2, trump);
    ASSERT_TRUE(order1);
    ASSERT_FALSE(order2);
    ASSERT_TRUE(order3);
    ASSERT_TRUE(order4);
    
    delete oliver;
    delete alec;
}



TEST_MAIN()

