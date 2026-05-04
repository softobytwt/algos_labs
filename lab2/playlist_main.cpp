#include<iostream>
#include <string>
#include<vector>
#include<algorithm>
#include<random>
#include<fstream>
#include"base64.h"



//////////////////////
class song {
public:
	std::string title;
	int length;
	std::string genre;
	int rating;

};
class playlist {
public:
	std::vector<song>mysongs;
	int mode = 1;	// 0-off, 1-r.one, 2-r.all
	int current_track = 0;
	int next_track = 0;
	
	void add(song s1) {						//1.add
		mysongs.push_back(s1);
	}

	int find_index(std::string s) {
		int id = -1;
		for (int i = 0; i < size(); i++) {
			if (s == mysongs.at(i).title) {
				id = i;
				break;
			}
		}
		return id;

	}

	void deletetrack(std::string s) {			// 2. delete track
		int id = find_index(s);
		if (id == current_track && id == size()-1) {
			current_track = 0; next_track = 0; mode = 1;
			std::cout << "CAUTION: repeat mode set to one\n"; 
		}
		if (id >= 0) {
			mysongs.erase(mysongs.begin() + id);
			std::cout << "track deleted\n";
		}
		else {
			std::cout << "track not found in playlist" << std::endl;
		}
	}

	int size() {
		return mysongs.size();
	}

	void shuffle() {	//3. shuffle
		if (size()) {
			auto rng = std::default_random_engine{};
			std::shuffle(mysongs.begin(), mysongs.end(), rng);
			std::cout << "\nplaylist shuffled!\n";
		}
		else { std::cout << "\nplaylist empty\n"; }
	}

	void currentplist() {
		if (size()) {
			std::cout << "\ncurrent playlist: " << std::endl;
			std::cout << "num\ttitle\t\tlength (sec)\tgenre\t\trating(5 stars)\n\n";
			for (int i = 0; i < size(); ++i) {
				std::cout << i + 1 << ".\t";
				std::cout << mysongs.at(i).title << "\t";
				if (mysongs.at(i).title.size() < 8) {std::cout << "\t";}
				std::cout << mysongs.at(i).length << "\t\t";
				std::cout << mysongs.at(i).genre << "\t";
				if (mysongs.at(i).genre.size() < 8) { std::cout << "\t"; }
				std::cout << mysongs.at(i).rating << "\t";
				std::cout << std::endl;
			}
		}
		else {
			std::cout << "\nplaylist empty\n";
		}
		std::cout << std::endl;

	}



};
//////////////////////


//////////////////////	safety pillow for int input
void cinpillow() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void while_fail_int(int *r) {
	while (std::cin.fail()) {
		cinpillow();
		std::cout << "\nerror. try again: ";
		std::cin >> *r;
	}
}
//////////////////////


void adding_many(playlist &p) {
	int flag=1;
	int count = 0;
	while (flag) {
		song nsong;
		std::string pholder;

		

		std::cout << "input title: ";
		std::getline(std::cin, nsong.title, '\n');


		std::cout << "input length: ";
		std::cin >> nsong.length;
		while_fail_int(&nsong.length);


		std::cout << "input genre: ";
		std::getline(std::cin, pholder, '\n');
		std::getline(std::cin, nsong.genre, '\n');


		std::cout << "input rating: ";
		std::cin >> nsong.rating;
		
		while_fail_int(&nsong.rating);
		while (nsong.rating <1 || nsong.rating >5) {
			std::cout << "rate from 1 to 5 (included): ";
			std::cin >> nsong.rating;
			while_fail_int(&nsong.rating);
		}


		p.add(nsong);
		count++;
		std::cout << "\ncontinue adding? (1-yes, 0-no): ";
		std::cin >> flag;
		std::getline(std::cin, pholder, '\n');
		while_fail_int(&flag);
	}
	std::cout << "songs added: " << count << std::endl<<std::endl;

}

void add_from_file64(playlist& p) {
	std::cout << "input filename (with .txt): ";
	std::string filename;
	std::cin >> filename;
	std::string songdata64;

	std::ifstream myfile(filename);

	if (myfile.is_open()) {
		Base64 b64;
		while (std::getline(myfile, songdata64)) {
			song nsong;


			std::string songdata = b64.decode_str(songdata64);
			std::string del = ";";
			int start = 0;
			int end = songdata.find(del);
			std::vector<std::string> vectordata;


			while (end != -1) {
				vectordata.push_back(songdata.substr(start, end - start));
				start = end + del.size();
				end = songdata.find(del, start);
			}

			nsong.title = vectordata.at(0);
			nsong.length = std::stoi(vectordata.at(1));
			nsong.genre = vectordata.at(2);
			nsong.rating = std::stoi(vectordata.at(3));

			p.add(nsong);
		}

		myfile.close();
	}
	else std::cout << "ERROR: cant find file\n";

}

void deleting(playlist &p) {
	std::string titledel;
	std::cout << "input the title of the track: ";
	std::getline(std::cin, titledel);
	p.deletetrack(titledel);
}

void filter(playlist& p) {
	int size = p.size();
	if (size > 1) {
		for (int i = 0; i < size - 1; i++) {
			std::string alph_genre_first = p.mysongs.at(i).genre;
			int id = i;
			for (int j = i + 1; j < size; j++) {
				if (alph_genre_first > p.mysongs.at(j).genre) { alph_genre_first = p.mysongs.at(j).genre; id = j; }
			}
			song pholder = p.mysongs.at(i);
			p.mysongs.at(i) = p.mysongs.at(id);
			p.mysongs.at(id) = pholder;

		}
	}
	else {
		std::cout << "playlist has too little tracks to filter. add more tracks.\n";
	}
}

void header() {
	std::cout << "\ninstructions:\n1. add track(s)\n2. add from file\n3. delete a track\n4. output playlist\n5. shuffle playlist\n6. filter by genre\n7. repeat";
	std::cout << std::endl <<"8. exit program\n9. PLAY TRACK\n" << std::endl;
}

void repeat(playlist& p) {
	std::cout << "current repeat mode: ";
	if (p.mode == 0) {
		std::cout << "off\n";
	}
	else if (p.mode == 1) {
		std::cout << "one\n";
	}
	else {
		std::cout << "all\n";
	}


	if (p.size() == 1) {
		std::cout << "cannot change repeat mode currently. add more tracks.\n";
	}
	else {
		std::cout << "change repeat mode? (1-yes): ";
		int repeatyn;
		std::cin >> repeatyn;
		while_fail_int(&repeatyn);
		std::string phd;
		std::getline(std::cin, phd);

		if (repeatyn == 1) {
			std::cout << "repeat modes:\n";
			std::cout << "0. off\n1. one\n2. all\n";
			std::cout << "new repeat mode: ";
			std::cin >> p.mode;
			if (p.mode == 0) {
				if (p.size() > 1) { p.next_track = p.current_track + 1; }
				else { p.next_track = -1; }
			}
			else if (p.mode == 1) {
				if (p.size() > 1) { p.next_track = p.current_track; }
				else if (p.size() == 1) { p.next_track = p.current_track; }
			}
			else {
				if (p.size() >= 1) {
					if (p.current_track == p.size() - 1) { p.next_track = 0; }
					else { p.next_track = p.current_track + 1; }
				}
				else if (p.size() == 0) {
					p.next_track = -1;
				}
			}
		}
	}
}

void play(playlist& p) {

	if (p.size()) {
		int yn = 1;
		while (yn == 1) {
			std::cout << "~~~ IN PLAYER\n\n";

			std::cout << "currently playing: ";
			
			if (p.current_track>=0) {
				std::cout << p.mysongs.at(p.current_track).title << std::endl;
			}
			else {
				std::cout << "--- (playlist end reached. set repeat mode to all)\n";
			}
			std::cout << "1. play next\n2. EXIT PLAYER\n";

			std::cin >> yn;
			while_fail_int(&yn);
			if (yn != 1)break;
			
			if (p.size() == 1) {
				if (p.mode == 0) {
					p.next_track = -1;
					p.current_track = -1;
				}
				else {
					p.next_track = p.current_track;
				}
			}
			else {
				if (p.mode == 0) {
					if (p.next_track < p.size()) {
						p.current_track = p.next_track;
						p.next_track++;
					}
					else {
						p.next_track = -1;
						p.current_track = -1;

					}
				}
				else if (p.mode == 1) {
					p.next_track = p.current_track;
				}
				else {
					if (p.next_track < p.size()) {
						p.current_track = p.next_track;
						p.next_track++;
					}
					else {
						p.current_track = 0;
						p.next_track = 1;
					}

				}
			}

		}
		
	}
	else {
		std::cout << "no tracks in playlist\n\n";
	}
}



void main() {
	playlist mychem;
	int instruction = 0;
	std::string pholder;

	while(instruction!=8){
		header();

		std::cout << "input instruction number: ";
		std::cin >> instruction;
		cinpillow();
		

		switch (instruction) {
		case 1:
			adding_many(mychem);
			break;

		case 2:			// need to do
			add_from_file64(mychem);
			break;

		case 3:
			deleting(mychem);
			break;

		case 4:
			mychem.currentplist();
			break;

		case 5:
			mychem.shuffle();
			break;

		case 6:
			filter(mychem);
			break;

		case 7:
			repeat(mychem);
			break;

		case 9:
			play(mychem);
			break;

		default:
			std::cout << "ERROR: invalid instruction\n\n";
			break;

		}
	}
	


	std::cout << "\nprogram exited\n";
}
