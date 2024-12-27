

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <array>
#include <vector>
#include <sstream>
#include <string>
#include "Card.h"


using namespace std;

constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

//EFFECTS Initializes Card to the Two of Spades
Card::Card()
    : rank(RANK_TWO), suit(SUIT_SPADES) { }

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in)
    : rank(rank_in), suit(suit_in) { }    

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}
 
//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    if (Card::is_left_bower(trump) == true) {
        return trump;
    }
    else {
        return suit;
    }
}

bool Card::is_face() const {
    if ((rank == RANK_JACK) || (rank == RANK_QUEEN) ||
    (rank == RANK_KING) || (rank == RANK_ACE)) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_right_bower(const std::string &trump) const {
    if ((suit == trump) && (rank == RANK_JACK)) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_left_bower(const std::string &trump) const {
    if (rank == RANK_JACK) {
        if ((trump == SUIT_HEARTS) && (suit == SUIT_DIAMONDS)) {
            return true;
        }
        else if ((trump == SUIT_DIAMONDS) && (suit == SUIT_HEARTS)) {
            return true;
        }
        else if ((trump == SUIT_SPADES) && (suit == SUIT_CLUBS)) {
            return true;
        }
        else if ((trump == SUIT_CLUBS) && (suit == SUIT_SPADES)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Card::is_trump(const std::string &trump) const {
    if ((suit == trump) || (Card::is_left_bower(trump) == true)) {
        return true;
    }
    else {
        return false;
    }
}


bool operator==(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<(const Card &lhs, const Card &rhs) {
    int leftindexR;
    int rightindexR;
    for (int i = 0; i < NUM_RANKS; i++) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            leftindexR = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            rightindexR = i;
        }
    }
    if (leftindexR < rightindexR) {
        return true;
    }
    else if (leftindexR == rightindexR) {
        int leftindexS;
        int rightindexS;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
                leftindexS = i;
            }
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
                rightindexS = i;
            }
        }
        if (leftindexS < rightindexS) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool operator<=(const Card &lhs, const Card &rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Card &lhs, const Card &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Card &lhs, const Card &rhs) {
    return !(lhs < rhs);
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
}

std::string Suit_next(const std::string &suit) {
    if (suit == SUIT_NAMES_BY_WEIGHT[0]) {
        return SUIT_NAMES_BY_WEIGHT[2];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[2]) {
        return SUIT_NAMES_BY_WEIGHT[0];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[1]) {
        return SUIT_NAMES_BY_WEIGHT[3];
    }
    else {
        return SUIT_NAMES_BY_WEIGHT[1];
    }
}

std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (a.is_left_bower(trump)) {
            if (b.is_right_bower(trump)) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (a.is_right_bower(trump)) {
            return false;
        }
        else if (b.is_right_bower(trump)) {
            return true;
        }
        else if (b.is_left_bower(trump)) {
            if (a.is_right_bower(trump)) {
                return false;
            }
            else {
                return true;
            }
        }
        if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if(!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else {
        if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    if (a.is_trump(trump) || b.is_trump(trump)) {
        return (Card_less(a, b, trump));
    }
    else {
        if (a.get_suit(trump) == led_card.get_suit(trump) 
                     && b.get_suit(trump) == led_card.get_suit(trump)) {
            if (a < b) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (a.get_suit(trump) == led_card.get_suit() 
                    && (b.get_suit(trump) != led_card.get_suit(trump))) {
            return false;
        }
        else if ((a.get_suit(trump) != led_card.get_suit(trump) 
                    && b.get_suit(trump) == led_card.get_suit(trump))) {
            return true;
        }
        else {
            if (a < b) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}
