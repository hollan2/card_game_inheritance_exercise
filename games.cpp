// Chloe Holland
// Karla Fant: CS202 Program 2
//
//This file includes the implementation of all of the functions that pertain to the games

#include "games.h"

hand::hand() {
	next = NULL;
	suit = value = 0;
}
hand::~hand() {
	next = NULL;
	suit = value = 0;
}

void hand::set_next() {
	next = NULL;
	return;
}
void hand::set_next(hand * new_next) {
	next = new_next;
	return;
}

hand *& hand::go_next() {
	return next;
}

void hand::set_data(int n_val, int n_suit) {
	value = n_val;
	suit = n_suit;
	return;
}
int hand::get_value()const {
	return value;
}
int hand::get_suit()const {
	return suit;
}

deck_of_cards::deck_of_cards() {
	//value = new int[num_of_values];
	suit = new char*[num_of_suits];
	//for(int i = 0; i < num_of_values; i++) {
	//	value[i] = i+1;
	//}
	suit[0] = new char[strlen("Clubs")+1];
	strcpy(suit[0], "Clubs");
	suit[1] = new char[strlen("Diamonds")+1];
	strcpy(suit[1], "Diamonds");
	suit[2] = new char[strlen("Hearts")+1];
	strcpy(suit[2], "Hearts");
	suit[3] = new char[strlen("Spades")+1];
	strcpy(suit[3], "Spades");
}

deck_of_cards::~deck_of_cards() {
	//if(value)
	//	delete[] value;
	if(*suit) {
		for(int i = 0; i < num_of_suits; ++i) {
			if(suit[i])
				delete[] suit[i];
		}
		delete[] suit;
	}
	destroy_hand(head);
}

void deck_of_cards::generate_random() {
	srand(time(NULL));
	int r_value = rand() % num_of_values + 1;
	int r_suit = rand() % num_of_suits;			
	add_to_hand(r_value, r_suit, head);
	return;
}

void deck_of_cards::add_to_hand(int val, int suit, hand *& head) {
	if(!head) {
		head = new hand;
		head->set_data(val, suit);
		head->set_next();
		return;
	}
	add_to_hand(val, suit, head->go_next());
	return;
}

void deck_of_cards::display_cards() const {
	display_cards(head);
}
void deck_of_cards::display_cards(hand * head) const {
	if(!head) return;
	int val = head->get_value();
	int suit_num = head->get_suit();
	display_value(val);
	cout << suit[suit_num] << endl;
	display_cards(head->go_next());
	return;
}
int deck_of_cards::display_random()const {
	srand(time(NULL));
	int r_value = rand() % num_of_values + 1;
	int r_suit = rand() % num_of_suits;			
	display_value(r_value);
	cout << suit[r_suit] << endl;
	return r_value;
}

void deck_of_cards::display_value(int val) const {
	switch(val) {
		case 1:
			cout << "Ace of ";
			break;
		case 11:
			cout << "Jack of ";
			break;
		case 12:
			cout << "Queen of ";
			break;
		case 13:
			cout << "King of ";
			break;
		default:
			cout << val << " of ";
			break;
	}
	return;
}
int deck_of_cards::decipher_value(int val) const {
	int answer;
	switch(val) {
		case 1:
			cout << "Would you like your ace to be a 1 or a 11? Type answer ";
			cin >> answer;
			cin.ignore();
			if(answer == 1)
				val = 1;
			else
				val = 11;
			break;
		case 11:
			val = 10;
			break;
		case 12:
			val = 10;
			break;
		case 13:
			val = 10;
			break;
		default:
	
			break;
	}
	return val;
}

int deck_of_cards::add_hand()const {
	return add_hand(head);
}
int deck_of_cards::add_hand(hand * head)const {
	if(!head) return 0;
	int val = head->get_value();
	int total = decipher_value(val); 
	total +=add_hand(head->go_next());
	return total;
}

void deck_of_cards::destroy_hand() {
	return destroy_hand(head);
}
void deck_of_cards::destroy_hand(hand *& head) {
	if(!head) return;
	destroy_hand(head->go_next());
	delete head;
	head = NULL;
	return;
}

int slap_jack::deal() {
	int val = 0, count = 0, slap = 0, num_of_jacks = 0, num_of_slaps = 0;
	while(count != 20) {
		sleep(1);
		val = cards.display_random();	
		if(val == 11)
			++num_of_jacks;
		slap = slap_it(val);
		if(slap == 0)
			++num_of_slaps;
		else if(slap == -1)
			--num_of_slaps;
		++count;
	}
	int points = winner(num_of_jacks, num_of_slaps);	
	cout << "You hit " << num_of_slaps <<" out of " << num_of_jacks << "!\n";
	cout << "You win " << points << "points!\n";
	return points;
}
void slap_jack::display()const {
	cout << "Slap Jack:\n";
}
int slap_jack::winner(int num_jacks, int num_slaps) {
	int points = 0;
	int value = num_jacks - num_slaps;
	switch(value) {
		case 0:
			points = 5;
			break;
		case 1:
			points = 3;
			break;
		case 2:
			points = 1;
			break;
		default:
			break;
	}
	return points;
}

int slap_jack::slap_it(int val) {
	char answer = 0;
	cin >> answer;
	cin.ignore();
	if(answer == 's') {
		if(val == 11){
			cout << "You slapped the jack! Great Job!\n";
			return 0;
		}else{ 
			cout << "You slapped the wrong card!!! D:\n";
			return -1;
		}
	} else 
		return 1;
}

//deals two cards
int black_jack::deal() {
	int answer= 1;
	cards.generate_random();
	sleep(1);
	cards.generate_random();
	while (answer == 1){
		cards.display_cards();
		answer = hit();
		if(answer == 1)
			cards.generate_random();
	}
	int total = add_em();
	int points = winner(total);
	cout << "You got " << total << endl;
	cout << "You win " << points << endl;
	return points;
}
int black_jack::winner(int total) {
	int points = 0;
	int value = 21 - total;
	switch(value) {
		case 0:
			points = 5;
			break;
		case 1:
			points = 4;
			break;
		case 2:
			points = 3;
			break;
		case 3:
			points = 2;
			break;
		case 4: 
			points = 1;
			break;
		default:
			break;
	}
	return points;
}
void black_jack::display()const {
	cout << "Black Jack:\n";
}
int black_jack::hit() {
	int answer = -1;
	cout << "Would you like another card? 1: yes 0: no ";
	cin >> answer;
	cin.ignore();
	return answer;
}

int black_jack::add_em() {
	int total = cards.add_hand();
	return total;
}

void black_jack::clear() {
	cards.destroy_hand();
	return;
}

int guess_value::deal() {
	int guess=0, value=0, points = 0;
	cout << "What value do you think the card will have?\n";
	cout << "\tAce is 1, Jack 11, Queen 12, King 13\n";
	cin >> guess;
	cin.ignore();
	value = cards.display_random();
	if(value == guess) {
		cout << "You guessed correctly!!! Yea!!! :D\n";
		cout << "You win 5 points!\n";
		points = 5;
	} else 
		cout << "You a loser bro. Guess better next time.\n";
	return points;
}
void guess_value::display()const {
	cout << "Guess Value:\n";
}

//I used these for debugging purposes and never got rid of them... Since my program works imma keep it.	
games::games() { }
slap_jack::slap_jack() { }
black_jack::black_jack() { }
guess_value::guess_value() { }
games::~games() { }
slap_jack::~slap_jack() { }
black_jack::~black_jack() { }
guess_value::~guess_value() { }

