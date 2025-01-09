#ifndef TEXAS_H
#define TEXAS_H

#include <iostream>
using namespace std;
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include<set>
#include <chrono>
#include <stdlib.h>

class Card 
{
    public:

        enum Suit { Hearts, Diamonds, Clubs, Spades };

        enum Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

        enum HandRank {HIGH_CARD = 1, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT,FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};

        Card(Rank rank = Two, Suit suit = Hearts);
        string to_string() const;
        Rank get_rank() const;
        Suit get_suit() const;
        bool operator == (const Card& other) const;
        bool operator < (const Card& other) const;
    
    private:

        Rank rank;
        Suit suit;
};

class Deck 
{
    private:

        Card cards[52];
        int current_card_index;
        void generate_deck();

    public:

        Deck();
        void shuffle();
        Card deal_card();
        void print_deck() const;
};

class Player
{
    private:

        string name;
        Card hand[2];
        bool folded;

    public:

        Player(); 
        Player(const string& name);

        void add_card_to_hand(const Card& card);
        string get_hand() const;
        vector<Card> get_hand_vector() const
        {
            return {hand[0], hand[1]};
        }
        string get_name() const;
        bool is_folded() const;
        void fold();
};

class Game:public Card
{
    private:

        Player* players;
        int numPlayers;
        Deck deck;
        Card communityCards[5];
        void deal_starting_hands();
        void deal_community_cards(int num,int &prev_ind,int &cur_ind);
        void show_hands() const;
        void show_community_cards(int num) const;
        void play_round();
        Card::HandRank evaluate_hand(const vector<Card>& cards);
        bool is_straight_flush(const vector<Card>& cards);
        bool is_four_of_a_kind(const vector<Card>& cards);
        bool is_full_house(const vector<Card>& cards);
        bool is_flush(const vector<Card>& cards);
        bool is_straight(const vector<Card>& cards);
        bool is_three_of_a_kind(const vector<Card>& cards);
        bool is_two_pair(const vector<Card>& cards);
        bool is_one_pair(const vector<Card>& cards);
        void determine_winner();
        void prettiness();
        void folding(int planum,int comnum);

    public:

        void start();
        Game();
};

#endif