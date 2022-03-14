// Chloe Holland
// Karla Fant: CS202 Program 2
//
// This file includes two data structures. 1 that manages the player of the games and
// one to manage the games themselves. The menu class holds interface for client. 

#include "games.h"

//keeps track of game we are playing
class game_list {  //CLL manager
	public:
		game_list();
		~game_list();
		void choose_game();  //chooses game from list
		void add_game();  //adds game to CLL
		void remove_game(); //removes all games from CLL
		int play_game(); //activates game at top of list
		void display()const; //displays all games in list
		void clear(); //clears hand for a game
		bool remove_specific(); //removes specific game from list
	protected:
		class node * rear;
		void display(node * rear)const; //recursive functions:
		bool remove_specific(node *&rear, node * previous, char  game);
};

//For client program to navigate through options
class menu {  //LLL manager
	public:
		menu();
		~menu();
		void choices(); //start program
		void create_player(); //creates player for LLL
		void retrieve_player(); //retrieves and displays character
		void remove_specific_player(); //removes specific player from LLL
		void adjust_rank(); //adjust players in LLL according to rank

	protected:
		class player * head;  //Start of LLL
		game_list queue; //object that holds CLL of games
		//recursive functions:
		int display_players(player * head)const;
		void delete_players(player *& head);
		bool retrieve_player(char * name, player * head) const;
		bool remove_specific_player(char * name, player *& previous, player *& cur);
		int play_game(player * head);
		void adjust_rank(player*&head, player *& previous);
		bool in_order(player * head, int largest_points);
};
//Users of program. 
class player {  //LLL node
	public:
		player();
		~player();
		player(const player & source);
		player(char * name);
		player *& go_next();
		void set_next();  //sets next ptr to null
		void set_next(player * new_next);  //sets next ptr to arg passed in
		void display()const; //displays player information
		void display_username()const; //displays player's username
		void destroy(); //destroys data in node;
		int add_points(int add_these); //adds points to player information.
		int get_points()const;  //return point value
		bool compare_username(char * name);  //compare username with passed in char *

	protected:
		char * username; //names user
		int points;  //keeps track of players points
		player * next;
		
};


class node {  //CLL node
	public:
		node();
		~node();
		node *& go_next();
		void set_next();
		void set_next(node * new_next);
		class games * myGame;
	protected:
		node * next;
};
