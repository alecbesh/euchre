

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <array>
#include <vector>
#include <sstream>
#include <string>
#include "Pack.h"
#include "Card.h"

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
Pack::Pack() : next(0) {
//     next = 0;
     int index = 0;
     for (int s = 0; s < NUM_SUITS; ++s) {
         for (int r = 7; r < NUM_RANKS; ++r) {
             string rank = RANK_NAMES_BY_WEIGHT[r];
             string suit = SUIT_NAMES_BY_WEIGHT[s];
             cards[index] = Card(rank, suit);
             index++;
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) : next(0) {
//    next = 0;
    string rank;
    string junk;
    string suit;
    for (int i = 0; i < 24; i++) {
        pack_input >> rank;
        pack_input >> junk;
        pack_input >> suit;
        cards[i] = Card(rank, suit);
    }
}

// REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    Card nextCard = cards[next];
    next++;
    return nextCard;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}
// EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.

void Pack::shuffle() {
    array<Card, PACK_SIZE / 2> front;
    array<Card, PACK_SIZE / 2> back;
    int numShuffs = 0;
    int count = 0;
    
    while(numShuffs < 7) {
        for(int i = 0; i < PACK_SIZE / 2; i++) {
            back[i] = cards[i];
            front[i] = cards[(PACK_SIZE / 2 ) + i];
        }
        for(int i = 0; i < PACK_SIZE / 2; i++) {
            cards[count + i] = front[i];
            cards[count + i + 1] = back[i];
            count++;
        }
        numShuffs++;
        count = 0;
    }
    reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next == 24) {
      return true;
    }
    else {
        return false;
    }
}
