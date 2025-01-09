#include "texas.h"

Card :: Card(Rank rank, Suit suit) : rank(rank), suit(suit) //constructors
{

}

string Card :: to_string() const//converting variables to string 
{
    const string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    return ranks[rank - 2] + " of " + suits[suit];
}

Card :: Rank Card :: get_rank() const //to get rank of the card
{ 
    return rank; 
}

Card :: Suit Card :: get_suit() const //getting the suit of the card
{
    return suit; 
}

bool Card :: operator == (const Card& other) const 
{
    return rank == other.rank && suit == other.suit;
}

bool Card :: operator < (const Card& other) const //to compare ranks
{
    return rank < other.rank;
}

Deck :: Deck() : current_card_index(0) //constructor
{
    generate_deck();
    shuffle();
}

void Deck :: generate_deck() //generate the deck
{
    int index = 0;
    for (int suit = Card::Hearts; suit <= Card::Spades; ++suit) 
    {
        for (int rank = Card::Two; rank <= Card::Ace; ++rank) 
        {
            cards[index++] = Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
        }
    }
}

void Deck :: shuffle() //shuffles the deck
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(&cards[0], &cards[52], std::default_random_engine(seed));
    current_card_index = 0;
}

Card Deck :: deal_card() // deals cards
{
    return cards[current_card_index++];
}

void Deck :: print_deck() const // prints the whole deck
{
    for (int i = 0; i < 52; ++i) 
    {
        cout << cards[i].to_string() << ", ";
    }
    cout << endl;
}

Player :: Player() : name("Unknown"), folded(false) //default constructor
{

}

Player :: Player(const string& name) : name(name), folded(false) // constructor 
{

}

void Player :: add_card_to_hand(const Card& card) // gives one random card to a player
{
    if (hand[0].get_rank() == Card::Two && hand[0].get_suit() == Card::Hearts) 
    {
        hand[0] = card;
    } 
    else if (hand[1].get_rank() == Card::Two && hand[1].get_suit() == Card::Hearts) 
    {
        hand[1] = card;
    }
}


string Player :: get_hand() const // shows the hand the player has
{
    return hand[0].to_string() + ", " + hand[1].to_string();
}

string Player :: get_name() const // returns the players name
{
    return name;
}

bool Player :: is_folded() const // checks if the player has folded or not
{
    return folded;
}

void Player :: fold() // functionn for the player to fold
{
    folded = true;
}

Game :: Game() // default constructor
{

}
void Game::folding(int planum,int comnum)// its provides an option to the player to fold, continue or show hands
{
    int intp;
    cout<<players[planum].get_name()<<" choose"<<endl;
    cout<<"Enter to 1 show player cards"<<endl;
    cout<<"Enter 0 to fold"<<endl;
    cout<<"Enter anything else to continue"<<endl;
    cin>>intp;
    switch(intp){
        case 1:
            if (!players[planum].is_folded()) 
            {
                cout << players[planum].get_name() << "'s hand: " << players[planum].get_hand() << endl<< flush;
                system("pause");
                system("cls");
                if(comnum==3){
                    cout<<"\n----------THE FLOP----------\n"<<endl;
                }
                else if(comnum==4){
                    cout<<"\n----------THE FLIP----------\n"<<endl;
                }
                show_community_cards(comnum);
                cout<<endl;
            }
            else{
                cout<<"you have folded"<<endl;
                cout<<endl;
            }
            break;
        case 0:
            if (!players[planum].is_folded())
            {
                cout << players[planum].get_name() << " folds." << endl;
                players[planum].fold();
                cout<<endl;
            }
            else{
                cout<<"you have already folded"<<endl;
                cout<<endl;
            }
            break;
        default:
            cout<<"player "<<players[planum].get_name()<< " is continuing"<<endl;
            cout<<endl;
            break;

    }

}
void Game::start() // starts the game
{
    system("cls");
    cout<<endl;
    cout << "                                  TEXAS HOLD'EM                                         "<<endl;
    cout << "  -------------   -------------   -------------   -------------   ------------- " << endl;
    cout << " |A            | |K            | |10           | |J            | |J            |" << endl;
    cout << " |   -------   | |   -------   | |   -------   | |O  -------   | |   -------   |" << endl;
    cout << " |  |       |  | |  |       |  | |  |C     C|  | |K |       |  | |  |       |  |" << endl;
    cout << " |  |       |  | |  |       |  | |  |   C   |  | |E | J     |  | |  |       |  |" << endl;
    cout << " |  |       |  | |  |       |  | |  |C     C|  | |R |  O    |  | |  |       |  |" << endl; 
    cout << " |  |   S   |  | |  |   K   |  | |  |       |  | |  |   K   |  | |  |   J   |  |" << endl; 
    cout << " |  |       |  | |  |       |  | |  |C     C|  | |  |    E  | J| |  |       |  |" << endl; 
    cout << " |  |       |  | |  |       |  | |  |   C   |  | |  |     R | O| |  |       |  |" << endl; 
    cout << " |  |       |  | |  |       |  | |  |C     C|  | |  |       | K| |  |       |  |" << endl; 
    cout << " |   -------   | |   -------   | |   -------   | |   -------  E| |   -------   |" << endl; 
    cout << " |            A| |            K| |           10| |            R| |            J|" << endl; 
    cout << "  -------------   -------------   -------------   -------------   ------------- " << endl;
    cout<<endl;
    cout << "Enter the number of players: ";
    cin >> numPlayers;
    cin.ignore();

    players = new Player[numPlayers];

    for (int i = 0; i < numPlayers; ++i) 
    {
        string playerName;
        cout << "Enter name for player " << i + 1 << ": ";
        getline(cin, playerName);
        players[i] = Player(playerName);
    }

    play_round();
}

void Game :: deal_starting_hands() // assigns cards to a player 
{
    for (int i = 0; i < numPlayers; ++i) 
    {
        players[i].add_card_to_hand(deck.deal_card());
        players[i].add_card_to_hand(deck.deal_card());
    }
}

void Game :: deal_community_cards(int num,int &prev_ind,int &cur_ind) // gives the community cards
{   
    int i;
    for (i = prev_ind; i < prev_ind+num; i++) 
    {
        communityCards[i] = deck.deal_card();
    }
    cur_ind=prev_ind+num-1;
    prev_ind=cur_ind+1;
}

void Game :: show_hands() const // shows the cards that the player has
{
    for (int i = 0; i < numPlayers; ++i) 
    {
        if (!players[i].is_folded()) 
        {
            cout << players[i].get_name() << "'s hand: " << players[i].get_hand() << endl<< flush;
            system("pause");
            system("cls");
        }
    }
}

void Game :: show_community_cards(int num) const // shows community cards
{
    cout << "Community cards: ";
    for (int i = 0; i < num; ++i) 
    {
        cout << communityCards[i].to_string() << ", ";
    }
    cout << endl;
}

std::string handRankToString(Card::HandRank rank) // helper to display rank
{
    switch(rank) 
    {
        case Card::HandRank::HIGH_CARD: return "High Card";
        case Card::HandRank::ONE_PAIR: return "One Pair";
        case Card::HandRank::TWO_PAIR: return "Two Pair";
        case Card::HandRank::THREE_OF_A_KIND: return "Three of a Kind";
        case Card::HandRank::STRAIGHT: return "Straight";
        case Card::HandRank::FLUSH: return "Flush";
        case Card::HandRank::FULL_HOUSE: return "Full House";
        case Card::HandRank::FOUR_OF_A_KIND: return "Four of a Kind";
        case Card::HandRank::STRAIGHT_FLUSH: return "Straight Flush";
        default: return "Unknown Rank";
    }
}

void Game::determine_winner() // decides the winner of the game
{
    vector<pair<Player*, Card::HandRank>> player_hands;

    for (int i = 0; i < numPlayers; ++i) 
    {
        if (!players[i].is_folded()) 
        {
            vector<Card> combined_hand = players[i].get_hand_vector();
            combined_hand.insert(combined_hand.end(), communityCards, communityCards + 5);

            Card::HandRank best_rank = evaluate_hand(combined_hand);
            player_hands.emplace_back(&players[i], best_rank);
        }
    }

    sort(player_hands.begin(), player_hands.end(), [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

    vector<Player*> winners = {player_hands[0].first};
    for (size_t i = 1; i < player_hands.size(); ++i) 
    {
        if (player_hands[i].second == player_hands[0].second) 
        {
            winners.push_back(player_hands[i].first);
        } 
        else 
        {
            break;
        }
    }

    if (winners.size() == 1) 
    {
        cout << "Winner: " << winners[0]->get_name() << " with a " << handRankToString(player_hands[0].second) << endl;
    } 
    else 
    {
        cout << "It's a tie between: ";
        for (const auto& winner : winners) 
        {
            cout << winner->get_name() << " ";
        }
        cout << "with a " << handRankToString(player_hands[0].second) << endl;
    }
}

Card::HandRank Game::evaluate_hand(const vector<Card>& cards) // checks who has the highest rank
{
    if (is_straight_flush(cards)) return Card::STRAIGHT_FLUSH;
    if (is_four_of_a_kind(cards)) return Card::FOUR_OF_A_KIND;
    if (is_full_house(cards)) return Card::FULL_HOUSE;
    if (is_flush(cards)) return Card::FLUSH;
    if (is_straight(cards)) return Card::STRAIGHT;
    if (is_three_of_a_kind(cards)) return Card::THREE_OF_A_KIND;
    if (is_two_pair(cards)) return Card::TWO_PAIR;
    if (is_one_pair(cards)) return Card::ONE_PAIR;
    return Card::HIGH_CARD;
}

bool Game::is_straight_flush(const vector<Card>& cards) // helper function for determining winner
{
    return is_flush(cards) && is_straight(cards);
}

bool Game::is_four_of_a_kind(const vector<Card>& cards) // helper function for determining winner
{
    map<Card::Rank, int> rank_count;
    for (const auto& card : cards) 
    {
        rank_count[card.get_rank()]++;
    }
    return any_of(rank_count.begin(), rank_count.end(), [](const auto& entry) { return entry.second == 4; });
}

bool Game::is_full_house(const vector<Card>& cards) // helper function for determining winner
{
    map<Card::Rank, int> rank_count;
    for (const auto& card : cards) 
    {
        rank_count[card.get_rank()]++;
    }
    bool has_three = false, has_two = false;
    for (const auto& entry : rank_count) 
    {
        if (entry.second == 3) has_three = true;
        if (entry.second == 2) has_two = true;
    }
    return has_three && has_two;
}

bool Game::is_flush(const vector<Card>& cards) // helper function for determining winner
{
    map<Card::Suit, int> suit_count;
    for (const auto& card : cards) 
    {
        suit_count[card.get_suit()]++;
    }
    return any_of(suit_count.begin(), suit_count.end(), [](const auto& entry) { return entry.second >= 5; });
}

bool Game::is_straight(const vector<Card>& cards) // helper function for determining winner
{
    set<Card::Rank> unique_ranks;
    for (const auto& card : cards) 
    {
        unique_ranks.insert(card.get_rank());
    }
    if (unique_ranks.size() < 5) return false;

    vector<Card::Rank> sorted_ranks(unique_ranks.begin(), unique_ranks.end());
    for (size_t i = 0; i <= sorted_ranks.size() - 5; ++i) 
    {
        bool is_sequence = true;
        for (size_t j = 0; j < 4; ++j) 
        {
            if (sorted_ranks[i + j] + 1 != sorted_ranks[i + j + 1]) 
            {
                is_sequence = false;
                break;
            }
        }
        if (is_sequence) return true;
    }

    return sorted_ranks.size() >= 5 && sorted_ranks[0] == Card::Two &&
           sorted_ranks[1] == Card::Three && sorted_ranks[2] == Card::Four &&
           sorted_ranks[3] == Card::Five && sorted_ranks.back() == Card::Ace;
}

bool Game::is_three_of_a_kind(const vector<Card>& cards) // helper function for determining winner
{
    map<Card::Rank, int> rank_count;
    for (const auto& card : cards) 
    {
        rank_count[card.get_rank()]++;
    }
    return any_of(rank_count.begin(), rank_count.end(), [](const auto& entry) { return entry.second == 3; });
}

bool Game::is_two_pair(const vector<Card>& cards) // helper function for determining winner
{
    map<Card::Rank, int> rank_count;
    for (const auto& card : cards) 
    {
        rank_count[card.get_rank()]++;
    }
    int pair_count = 0;
    for (const auto& entry : rank_count) 
    {
        if (entry.second == 2) pair_count++;
    }
    return pair_count >= 2;
}

bool Game::is_one_pair(const vector<Card>& cards) // helper function for determining winner
{
    map<Card::Rank, int> rank_count;
    for (const auto& card : cards) 
    {
        rank_count[card.get_rank()]++;
    }
    return any_of(rank_count.begin(), rank_count.end(), [](const auto& entry) { return entry.second == 2; });
}

void Game::prettiness() // displays the code in a pretty manner
{
    cout << "\n==================== GAME OVER ====================\n";
    cout<<endl;
    cout << "Community cards: "<<endl;
    for (int i = 0; i < 5; ++i) 
    {
        cout << communityCards[i].to_string() << ", ";
    }
    cout<<endl;
    cout<<"Player hands"<<endl;
    for (int i = 0; i < numPlayers; ++i) 
    {
        if (!players[i].is_folded()) 
        {
            cout << players[i].get_name() << "'s hand: " << players[i].get_hand()  <<endl;
            cout<<endl;
            
        }
        else{
            cout<<players[i].get_name()<<" has folded"<<endl;
        }
    }
}
void Game::play_round() // commences the round
{
    int prev_ind=0,cur_ind=0;

    deck.shuffle();
    deal_starting_hands();
    cout<<"Showing player hands"<<endl;
    cout<<endl;
    show_hands();

    cout<<"\n----------THE FLOP----------\n"<<endl;
    deal_community_cards(3,prev_ind,cur_ind);
    show_community_cards(3);
    for(int s=0;s<numPlayers;s++){
        folding(s,3);
    }

    cout<<"\n----------THE TURN----------\n"<<endl;
    deal_community_cards(1,prev_ind,cur_ind); 
    show_community_cards(4);
    for(int s=0;s<numPlayers;s++){
        folding(s,4);
    }
    
    cout<<"\n----------THE RIVER----------\n"<<endl;
    deal_community_cards(1,prev_ind,cur_ind);
    show_community_cards(5);
    prettiness();
    determine_winner();
}