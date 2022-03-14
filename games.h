// Chloe Holland
// Karla Fant: CS202 Program 2
//
//This file is where the games are made. We have a hand class that is a LLL that keeps track of the cards in your hand
//We have a deck of cards that does everything you need from a deck of cards from generating, storing in hand, keeping track 
//of suit, etc. We then have our games hierarchy that includes black jack, slap jack, and guess the value. 

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <unistd.h>

using namespace std;
const int SIZE = 100;
class hand {
	public:
		hand();
		~hand();
		void set_next();
		void set_next(hand * new_next);
		hand *& go_next();
		void set_data(int n_val, int n_suit);
		int get_value() const;
		int get_suit()const;
	protected:
		hand * next;
		int value; //keep track of value of card
		int suit; //keep track of suit of card (correlates to array index)
};
class deck_of_cards {
	public:
		deck_of_cards();
		~deck_of_cards();
		//void display_all() const;
		void generate_random();  //generates random cards to add to hand
		void display_cards()const; //display cards in hand
		int display_random()const; //generates random cards and displays them. Returns value of card
		void display_value(int val)const; //decodes value to convert to ace, jack-king so it can display properly
		int decipher_value(int val)const; //decodes value and coverts it to a value for black jack
		int add_hand()const;  //adds value of hand
		void destroy_hand();  //deletes LLL of hand

	protected:
		int num_of_values = 13;  //how many different type of cards
		int num_of_suits = 4; //how many different type of suits
		char ** suit; //array of char * suits
		hand * head; //keep track of cards in your hand
		//recursive functions:
		void add_to_hand(int val, int suit, hand *& head);  //adds cards to your hand at end of list
		void display_cards(hand * head)const; //displays cards recursively in hand
		int add_hand(hand * head)const;
		void destroy_hand(hand *& head);
};

class games {
	public:
		games();
		virtual ~games();
		virtual int deal()=0; //begins games
		virtual void display()const=0; //displays name of games
	protected:
		deck_of_cards cards;  //uses deck of card to play games
};

class slap_jack: public games {
	public: 
		slap_jack();
		~slap_jack();
		int deal(); //begins game
		void display()const; //displays title of game
		int slap_it(int val); //allows you to slap a card
		int winner(int jacks, int slaps); //compares right cards you slap from actual slaps to see if you won
};

class black_jack: public games {
	public:
		black_jack();
		~black_jack();
		int deal(); //begins game
		void display()const; //displays title of game
		void clear(); //rtti function since only one that uses hand class
		int hit(); //adds card to your hand
		int add_em(); //adds cards in your hand total
		int winner(int total); //determines your total and compares to 21 to see if you won
};

class guess_value: public games {
	public:
		guess_value();
		~guess_value();
		int deal(); //begins game
		void display()const; //displays title of game
};
