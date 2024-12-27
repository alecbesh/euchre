

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <array>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "Card.h"
#include "Player.h"

using namespace std;

class Simple : public Player {
  public:
    Simple(const std::string &name_in)
    : name(name_in) { }

    const std::string & get_name() const override {
      return name;
    }

    void add_card(const Card &c) override {
      hand.push_back(c);
      sort(hand.begin(), hand.end());
    }


    virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
      int num_trump = 0;
      if (round == 1) {
        for (int i = 0; i < (int) hand.size(); ++i) {
          if ((hand[i].is_trump(upcard.get_suit()) && hand[i].is_face())) {
            num_trump = num_trump + 1;
          }
        }
        if (num_trump >= 2) {
          order_up_suit = upcard.get_suit();
          return true;
        }
        else {
          return false;
        }
      }

      else if (round == 2) {
        num_trump = 0;
        for (int i = 0; i < (int) hand.size(); ++i) {
          if (hand[i].is_trump(Suit_next(upcard.get_suit())) && hand[i].is_face()) {
            num_trump = num_trump + 1;
          }
        }
        if (num_trump >= 1) {
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        }
        if (is_dealer){
          order_up_suit = Suit_next(upcard.get_suit());
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

    

    virtual void add_and_discard(const Card &upcard) override {
      add_card(upcard);
      int index = 0;
      Card lowestCard = hand[0];

      for (int i = 0; i < (int) hand.size(); i++) {
        if (Card_less(hand[i], lowestCard, upcard.get_suit())) {
          lowestCard = hand[i];
          index = i;
        }
      }
      if (hand.size() > 0) {
        Card returncard = hand[index];
        hand.erase(hand.begin() + index);
      }
    }


    
    virtual Card lead_card(const std::string &trump) override {
      assert(hand.size() > 0);
      Card highestCardlead = hand[0];
      int index = 0;
      int numTrumps = 0;
      for (int i = 0; i < (int) hand.size(); i++) {
        if (hand[i].is_trump(trump)) {
          numTrumps++;
        }
      }
      if (numTrumps == ((int) hand.size())) {
        for (int i = 0; i < (int) hand.size(); i++) {
          if (Card_less(highestCardlead, hand[i], trump)) {
            highestCardlead = hand[i];
            index = i;
          }
        }
        Card returnCard = hand[index];
        hand.erase(hand.begin() + index);
        return returnCard;
      }
      else {
        for (int i = 0; i < (int) hand.size(); i++) {
          if (!hand[i].is_trump(trump) && highestCardlead < hand[i]) {
            highestCardlead = hand[i];
            index = i;
          }
        }
        Card returnCard = hand[index];
        hand.erase(hand.begin() + index);
        return returnCard;
      }
    }






    virtual Card play_card(const Card &led_card, const std::string &trump) override {
      assert(hand.size() > 0);
      
      Card highlead = hand[0];
      Card lowCard = hand[0];
      int highleadindex = 0;
      int lowindex = 0;
      
      for(int i = 0; i < (int) hand.size(); i++) {
          if(hand[i].get_suit(trump) == led_card.get_suit(trump)) {
              if(i == 0 ||
                highlead.get_suit(trump) != led_card.get_suit(trump)) {
                  highlead = hand[i];
                  highleadindex = i;
              } 
              else if(Card_less(highlead, hand[i], trump)) {
                highlead = hand[i];
                highleadindex = i;
              }
          } 
          else { 
              if(Card_less(hand[i], lowCard, trump)) {
                lowCard = hand[i];
                lowindex = i;
              }
          }
      }
      if(highlead.get_suit(trump) == led_card.get_suit(trump))  {
          
          hand.erase(hand.begin() + highleadindex);
          return highlead;
      } 
      else {
        hand.erase(hand.begin() + lowindex);
        return lowCard;
      }
    }



  private:
    string name;
    vector<Card> hand;
};






class Human : public Player {
  public:
    Human(const std::string &name_in)
    : name(name_in) { }

    const std::string & get_name() const override {
      return name;
    }

    void add_card(const Card &c) override {
      hand.push_back(c);
      sort(hand.begin(), hand.end());
    }

    
    virtual bool make_trump(const Card &upcard, bool is_dealer, int round, std::string &order_up_suit) const override {
      vector<Card> temp;
      Card lowestCard(Card::RANK_ACE, Card::SUIT_DIAMONDS);
      

      for (int i = 0; i < (int) hand.size(); i++) {
        cout << "Human player " << name 
              << "'s hand: [" << i << "] " << hand[i] << endl;
      }
      cout << "Human player " << name 
            << ", please enter a suit, or \"pass\":" << endl;
      string humanMakeTrump;
      cin >> humanMakeTrump;
      if (humanMakeTrump == "pass") {
        return false;
      }
      else {
        order_up_suit = humanMakeTrump;
        return true;
      }
    }



    virtual void add_and_discard(const Card &upcard) override {

      for (int i = 0; i < (int) hand.size(); i++) {
        cout << "Human player " << name << "'s hand: [" << i << "] " << hand[i] << endl;
      }
      cout << "Discard upcard: [-1]" << endl;
      cout << "Human player " << name << ", please select a card to discard:" << endl;

      int choice;
      cin >> choice;
      int position;
      for (int i = 0; i < (int) hand.size(); i++) {
        if (hand[i] == upcard) {
          position = i;
        }
      }
      if (choice == -1 && (hand.size() > 0)) {
        hand.erase(hand.begin() + position);
      }
      else {
        if (hand.size() > 0) {
          hand.erase(hand.begin() + choice);
        }
      }
      add_card(upcard);
    }


    virtual Card lead_card(const std::string &trump) override {
      assert(hand.size() > 0);
      for (int i = 0; i < (int) hand.size(); i++) {
        cout << "Human player " << name 
              << "'s hand: [" << i << "] " << hand[i] << endl;
      }
      cout << "Human player " << name << ", please select a card:" << endl;
      int choice;
      cin >> choice;
      Card leadCard = hand[choice];
      hand.erase(hand.begin() + choice);
      return leadCard;
    }
    
    virtual Card play_card(const Card &led_card, const std::string &trump) override {
      assert(hand.size() > 0);
      for (int i = 0; i < (int) hand.size(); i++) {
        cout << "Human player " << name << "'s hand: [" << i << "] " << hand[i] << endl;
      }
      cout << "Human player " << name << ", please select a card:" << endl;
      int choice;
      cin >> choice;
      Card playCard = hand[choice];
      hand.erase(hand.begin() + choice);
      return playCard;
    }




  private:
    string name;
    vector<Card> hand;
};







Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Simple") {
    return new Simple(name);
  }

  else if (strategy == "Human") {
    return new Human(name);
  }
  assert(false);
  return nullptr;
}




std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}


