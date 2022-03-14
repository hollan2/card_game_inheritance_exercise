// Chloe Holland
// Karla Fant: CS202 Program 2
//
//This file includes the implementation of all the functions for the data structures that manage players and games. 

#include "user.h"
menu::menu(): head(NULL) {}
menu::~menu() {
	delete_players(head);
}

void menu::choices() {
	int choice = -1, val;
	while (choice != 0) {
		cout << "What would you like to do?\n";
		cout << "\t1. Create Player\n\t2. Display Players\n\t3. Remove Player"
			<< "\n\t4. Display specific player\n\t5. Remove specific player\n\t"
			<<"6. Add game to queue\n\t7. Remove game from queue\n\t8. Display queue\n\t9. Play!\n\t"
			<< "0. Quit ";
		cin >> choice;
		cin.ignore();
		switch(choice) {
			case 1:
				create_player(); //create new player
				break;
			case 2:
				val = display_players(head); //display all players
				if(val == 0) cout << "No players...\n";
				break;
			case 3:
				delete_players(head); //delete all players
				break;
			case 4:
				retrieve_player(); //display certain player
				break;
			case 5:
				remove_specific_player(); //delete specific player
				break;
			case 6:
				queue.choose_game(); //choose game to add to list
				break;
			case 7:
				// remove game from queue
				queue.remove_specific();
				break;
			case 8:
				queue.display(); //display game list
				break;
			case 9:
				play_game(head);
				queue.remove_game(); //remove played game
				adjust_rank();
				//adjust player rankings
				break;
			case 0:
				display_players(head); //show final standing
				cout << "quitting...\n";
				break;
			default:
				break;
		}
	}
	return;
}
void menu::create_player() {
	char name[SIZE];
	cout << "What would you like your username to be? ";
	cin.get(name, SIZE);
	cin.ignore();
	player * new_player = new player(name);
	if(head) {  //list 1+ items
		new_player->set_next(head);
		head = new_player;
	} else {  //list empty
		head = new_player;
		head->set_next();
	}
	return;
}
int menu::display_players(player * head)const {
	if(!head) return 0;
	int count = 0;
	++count;
	head->display();
	count += display_players(head->go_next());
	return count;
}
void menu::delete_players(player *& head) {
	if(!head) return;
	delete_players(head->go_next());
	head->destroy();
	delete head;
	head->set_next();
	head = NULL;
	return;	
}

void menu::retrieve_player() {
	char temp[SIZE];
	cout << "What player would you like to view? ";
	cin.get(temp, SIZE);
	cin.ignore();
	bool answer = retrieve_player(temp, head);
	if(!answer) 
		cout << "Couldn't find that player...\n";
	return;
}
bool menu::retrieve_player(char * name, player * head)const {
	if(!head) return false;
	if(head->compare_username(name)) {
		head->display();
		return true;
	}
	return retrieve_player(name, head->go_next());
}
void menu::remove_specific_player() {
	char temp[SIZE];
	cout << "What player would you like to remove? ";
	cin.get(temp, SIZE);
	cin.ignore();
	//check head:
	if(head->compare_username(temp)) { //does username match?
		player * cur = head;
		head = cur->go_next();
		cur->destroy();
		delete cur;
		cur = NULL;
	}else {//call recursive function
		bool answer = remove_specific_player(temp, head, head->go_next());
		if(!answer)
			cout << "I couldn't find that player...\n";
	}
	return;
}
bool menu::remove_specific_player(char * name, player *& previous, player *& cur) {
	if(!cur) return false;
	if(cur->compare_username(name)) {
		player * temp = cur;
		cur = temp->go_next();
		previous->set_next(cur);
		temp->destroy();
		delete temp;
		temp = NULL;
		return true;
	}
	return remove_specific_player(name, previous->go_next(), cur->go_next());
}
int menu::play_game(player * head) {
	if(!head) return 0;
	int count = 0;
	count += play_game(head->go_next());
	++count;
	head->display_username();
	cout << "Player " << count << " it is your turn!\n";
	int points = queue.play_game();
	head->add_points(points);
	queue.clear();
	return count;
}
void menu::adjust_rank() {
	return adjust_rank(head->go_next(),head);	
}
void menu::adjust_rank(player*&head, player *& previous) {
	if(!head) return;
	if(head->go_next()) {
		player * cur = head->go_next();
		if(head->get_points() < cur->get_points()){ //move if we are smaller than the one after us
			previous->set_next(cur);
			head->set_next(cur->go_next());
			cur->set_next(head);
		} 
	}
	return adjust_rank(head->go_next(), previous->go_next());
}

player::player(): points(0),next(NULL) {
	if(username)
		delete[] username;
	username = NULL;
}
player::~player() {
	destroy();
}
player::player(const player & source): points(source.points) {
	if(source.username) {
		username = new char[strlen(source.username)+1];
		strcpy(username, source.username);
	}
	next = NULL;	
}

player::player(char * name): points(0), next(NULL) {
	if(name) {
		if(username)
			delete[] username;
		username = new char[strlen(name) +1];
		strcpy(username, name);
	}
}
player *& player::go_next() {
	return next;
}
int player::get_points() const {
	return points;
}
void player::set_next() {
	next = NULL;
	return;
}

void player::set_next(player * new_next) {
	next = new_next;
	return;
}

void player::display()const {
	cout << "Username: " << username << endl;
	cout << "\tPoints: " << points << endl;
	return;
}
void player::destroy() {
	if(username){
		delete username;
		username = NULL;
	}
	points = 0;
	next = NULL;
}
int player::add_points(int add_these) {
	points += add_these;
	return points;
}

bool player::compare_username(char * name) {
	if(strcmp(username, name) == 0) return true;
	else return false;
}
void player::display_username()const {
	cout << username;
	return;
}

game_list::game_list(): rear(NULL) {
}

game_list::~game_list() {
}

void game_list::choose_game() {
	int choice;
	cout << "What game would you like to play?\n";
	cout << "\t1. Black Jack\n\t2. Slap Jack\n\t3. Guess the value ";
	cin >> choice;
	cin.ignore();
	
	slap_jack * s_ptr = new slap_jack;
	black_jack * b_ptr = new black_jack;
	guess_value * g_ptr = new guess_value;
	if(rear) {
		node * new_node = new node;
		new_node->set_next(rear->go_next());
		rear->set_next(new_node);
		rear = new_node;
	} else {
		rear = new node;
		rear->set_next(rear);
	}
	switch(choice) {
		case 1:
			rear->myGame = b_ptr;
			break;
		case 2:
			rear->myGame = s_ptr;
			break;
		case 3:
			rear->myGame = g_ptr;
			break;
		default:
			break;
	}	
	if(rear->myGame != b_ptr) {
		delete b_ptr;
	}
	if(rear->myGame != s_ptr) {
		delete s_ptr;
	}
	if(rear->myGame != g_ptr) {
		delete g_ptr;
	}
}
int game_list::play_game() {
	if(!rear) return 0;
	node * cur = rear->go_next();
	cur->myGame->display();
	int points = cur->myGame->deal();
	return points;
}
void game_list::remove_game() {
	if(!rear) return;
	if(rear->go_next() == rear) {
		delete rear;
		rear = NULL;
		return;
	}
	node * cur = rear->go_next();
	rear->set_next(cur->go_next());
	delete cur;
	cur = NULL;
	return;
}
void game_list::display()const {
	if(!rear) return;
	return display(rear->go_next());	
}

void game_list::display(node * rear) const{
	if(rear == this->rear) {
		rear->myGame->display();
		return;
	}
	rear->myGame->display();
	return display(rear->go_next());
}
void game_list::clear() {
	if(!rear) return;
	//rtti
	black_jack * b_ptr = dynamic_cast<black_jack *>(rear->go_next()->myGame);
	if(b_ptr)
		b_ptr->clear();
	return;
}
bool game_list::remove_specific() {
	if(!rear) return false;
	char temp;
	cout << "What game would you like to remove? 'B' black jack, 'S' slap jack, 'G' guess value ";
	cin >> temp;
	cin.ignore(100, '\n');
	temp = tolower(temp);
	return remove_specific(rear->go_next(), rear, temp);
}
bool game_list::remove_specific(node *& rear, node * previous, char  game) {
	if(rear == this->rear) return false;
	if(game == 'b') {
		black_jack * b_ptr = dynamic_cast<black_jack *>(rear->myGame);
		if(b_ptr) {
			node * temp = rear;
			rear = previous;
			rear->set_next(temp->go_next());
			delete temp;
			temp = NULL;
			return true;
		}
	}
	else if (game == 's') {
		slap_jack * s_ptr = dynamic_cast<slap_jack *>(rear->myGame);
		if(s_ptr) {
			node * temp = rear;
			rear = previous;
			rear->set_next(temp->go_next());
			delete temp;
			temp = NULL;
			return true;
		}
	}
	else if (game == 'g') {
		guess_value * g_ptr = dynamic_cast<guess_value *>(rear->myGame);
		if(g_ptr) {
			node * temp = rear;
			rear = previous;
			rear->set_next(temp->go_next());
			delete temp;
			temp = NULL;
			return true;
		}
	}
	return remove_specific(rear->go_next(), previous->go_next(), game);
	return false;
}

node::node(): next(NULL) {

}
node::~node() {

}
node *& node::go_next() {
	return next;
}
void node::set_next() {
	next = NULL;
	return;
}
void node::set_next(node * new_next) {
	next = new_next;
	return;
}
