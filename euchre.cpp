

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
#include "Pack.h"
#include "Card.h"
#include "Player.h"

using namespace std;

class Game {
public:
    // team1 consists of players 0 and 2
    // team2 consists of players 1 and 3
    int team1_tricks;
    int team2_tricks;
    int team1_hands;
    int team2_hands;
    int leader;
    bool ordered_up_team1;
    bool ordered_up_team2;
    Card upcard;
    Pack pack;
    int num_hand;
    string trump;
    int dealer_index;
    vector<Player*> players;
    string order_up_suit;

    void deal() {
        players[(dealer_index + 1) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 1) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 1) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 2) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 2) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 3) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 3) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 3) % 4]->add_card(pack.deal_one());
        players[dealer_index % 4]->add_card(pack.deal_one());
        players[dealer_index % 4]->add_card(pack.deal_one());

        players[(dealer_index + 1) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 1) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 2) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 2) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 2) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 3) % 4]->add_card(pack.deal_one());
        players[(dealer_index + 3) % 4]->add_card(pack.deal_one());
        players[dealer_index % 4]->add_card(pack.deal_one());
        players[dealer_index % 4]->add_card(pack.deal_one());
        players[dealer_index % 4]->add_card(pack.deal_one());
        
        upcard = pack.deal_one();
    }

    void add_player(Player *p) {
        players.push_back(p);
    }

    void update_dealer() {
        dealer_index = dealer_index + 1;
    }

    void announce_hand(int &hand, int &dealer_index, Card &upcard) {
        cout << "Hand " << hand << endl;
        cout << players[dealer_index % 4]->get_name() << " deals" << endl;
        cout << upcard << " turned up" << endl;
    }

    void decision_making(int &dealer_index, Card &upcard, string &order_up_suit) {
        int num_passes = 0;
        bool is_dealer = false;
        ordered_up_team1 = false;
        ordered_up_team2 = false;
        for (int i = (dealer_index + 1); i < (dealer_index + 5); ++i) {
            if (i == (dealer_index + 4)) {
                is_dealer = true;
            }
            if (players[(i) % 4]->make_trump(upcard, is_dealer, 1, order_up_suit)) {
                trump = order_up_suit;
                cout << players[(i) % 4]->get_name() << " orders up " << 
                trump << endl << endl;
                if ((i % 4) % 2 == 0) {
                    ordered_up_team1 = true;
                }
                else {
                    ordered_up_team2 = true;
                }
                players[dealer_index % 4]->add_and_discard(upcard);
                i = dealer_index + 5;
            }
            else {
                cout << players[i % 4]->get_name() << " passes" << endl;
                num_passes++;
            }
        }
        is_dealer = false;
        if (num_passes == 4) {
            for (int i = (dealer_index + 1); i < (dealer_index + 5); ++i) {
                if (i == (dealer_index + 4)) {
                    is_dealer = true;
                }
                if (players[(i) % 4]->make_trump(upcard, is_dealer, 2, order_up_suit)) {
                    trump = order_up_suit;
                    cout << players[(i) % 4]->get_name() << " orders up " << 
                    trump << endl << endl;
                    if ((i % 4) % 2 == 0) ordered_up_team1 = true;
                    else ordered_up_team2 = true;
                    i = dealer_index + 5;
                }
                else {
                    cout << players[(i) % 4]->get_name() << " passes" << endl;
                    num_passes++;
                }
            }
        }
        leader = (dealer_index + 1);
    }

    void play_trick(const std::string &trump) {
        string trick_winner;
        Card led_card;
        Card best_card;
        for (int i = leader; i < (leader + 4); i++) {
            if (i == (leader)) {
                led_card = players[i % 4]->lead_card(trump);
                cout << led_card << " led by " << players[i % 4]->get_name() << endl;
                best_card = led_card;
            }
            if (i > leader) {
                Card played_card = players[i % 4]->play_card(led_card, trump);
                cout << played_card << " played by " << 
                players[i % 4]->get_name() << endl;
                if (Card_less(best_card, played_card, led_card, trump)) {
                    best_card = played_card;
                    trick_winner = players[i % 4]->get_name();
                }
            }
        }
        if (best_card == led_card) {
            trick_winner = players[leader % 4]->get_name();
        }
        for (int i = 0; i < 4; i++) {
            if (trick_winner == players[i]->get_name()) {
                cout << trick_winner << " takes the trick" << endl << endl;
                leader = i;
                if ((i % 2) == 0) {
                    team1_tricks++;
                }
                else {
                    team2_tricks++;
                }
            }
        }
    }

    void hand_outcome(int &team1_tricks, int &team2_tricks, 
                        bool &ordered_up_team1, bool &ordered_up_team2) {
        if (team1_tricks == 5 && (ordered_up_team1)) {
            cout << players[0]->get_name() << " and " 
                << players[2]->get_name() << " win the hand" << endl;
            cout << "march!" << endl;
            team1_hands = team1_hands + 2;
        }
        if (team2_tricks == 5 && (ordered_up_team2)) {
            cout << players[1]->get_name() << " and " 
                << players[3]->get_name() << " win the hand" << endl;
            cout << "march!" << endl;
            team2_hands = team2_hands + 2;
        }
        else if (team1_tricks >= 3 && (ordered_up_team2)) {
            cout << players[0]->get_name() << " and " 
                << players[2]->get_name() << " win the hand" << endl;
            cout << "euchred!" << endl;
            team1_hands = team1_hands + 2;
        }
        else if (team2_tricks >= 3 && (ordered_up_team1)) {
            cout << players[1]->get_name() << " and " 
                << players[3]->get_name() << " win the hand" << endl;
            cout << "euchred!" << endl;
            team2_hands = team2_hands + 2;
        }
        else if (team1_tricks >= 3 && (ordered_up_team1)) {
            cout << players[0]->get_name() << " and " 
                << players[2]->get_name() << " win the hand" << endl;
            team1_hands = team1_hands + 1;
        }
        else if (team2_tricks >= 3 && (ordered_up_team2)) {
            cout << players[1]->get_name() << " and " 
                << players[3]->get_name() << " win the hand" << endl;
            team2_hands = team2_hands + 1;
        }
    }

    void print_score(int &team1_hands, int &team2_hands) {
        cout << players[0]->get_name() << " and " << players[2]->get_name() 
            << " have " << team1_hands << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name() 
            << " have " << team2_hands << " points" << endl << endl;
    }

    void update_hand() {
        num_hand = num_hand + 1;
    }
    
    void shuffle() {
        pack.shuffle();
    }    

private:
    // Card upcard;
    // Pack pack;
    // int round;
    // int num_hand;
    // string trump;
    // int dealer_index;
    // vector<Player> players;
};

void print_error_message() {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
}




int main(int argc, char *argv[]) {
    if (argc != 12) {
        print_error_message();
        return 1;
    }
    string filename = argv[1];
    string is_shuffle = argv[2];
    int points = atoi(argv[3]);
    if (points > 100 || points < 1) {
        print_error_message();
        return 1;
    }
    if (is_shuffle != "shuffle" && is_shuffle != "noshuffle") {
        print_error_message();
        return 1;
    }
    vector<string> type;
    type.push_back(argv[5]);
    type.push_back(argv[7]);
    type.push_back(argv[9]);
    type.push_back(argv[11]);
    string name0 = argv[4];
    string name1 = argv[6];
    string name2 = argv[8];
    string name3 = argv[10];
    for(int i = 0; i < 4; ++i) {
        if (type[i] != "Simple" && type[i] != "Human") {
            print_error_message();
            return 1; 
        }
    }
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        cout << "Error opening " << filename << endl;
        return 1;
    }
    Game euchre;
    Player* player0 = Player_factory(name0, type[0]);
    Player* player1 = Player_factory(name1, type[1]);
    Player* player2 = Player_factory(name2, type[2]);
    Player* player3 = Player_factory(name3, type[3]);
    euchre.add_player(player0);
    euchre.add_player(player1);
    euchre.add_player(player2);
    euchre.add_player(player3);

    euchre.num_hand = 0;
    euchre.dealer_index = 0;
    euchre.team1_hands = 0;
    euchre.team2_hands = 0;
    euchre.team1_tricks = 0;
    euchre.team2_tricks = 0;

    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;

    while (euchre.team1_hands < points && euchre.team2_hands < points) {
        euchre.pack.reset();
        if (is_shuffle == "shuffle") {
            euchre.shuffle();
            euchre.deal();
        }
        else {
            euchre.deal();
        }
        euchre.announce_hand(euchre.num_hand, euchre.dealer_index, euchre.upcard);
        euchre.decision_making(euchre.dealer_index, euchre.upcard, euchre.order_up_suit);
        for (int i = 0; i < 5; i++) {
            euchre.play_trick(euchre.trump);
        }
        euchre.hand_outcome(euchre.team1_tricks, 
            euchre.team2_tricks, euchre.ordered_up_team1, euchre.ordered_up_team2);
        euchre.team1_tricks = 0;
        euchre.team2_tricks = 0;
        euchre.print_score(euchre.team1_hands, euchre.team2_hands);
        euchre.update_hand();
        euchre.update_dealer();
    }
    if (euchre.team1_hands > euchre.team2_hands) {
        cout << *euchre.players[0] << " and " << *euchre.players[2] << " win!" << endl;
    }
    else {
        cout << *euchre.players[1] << " and " << *euchre.players[3] << " win!" << endl;
    }
    for (int i = 0; i < int(euchre.players.size()); ++i) {
        delete euchre.players[i];
    }

    return 0;
}
