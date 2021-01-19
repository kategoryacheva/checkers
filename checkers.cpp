#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

vector<vector<int> > field;
string player = "none";


int check_lose() {
	return 0;
}

int check_command(string from, string to, string color) {
	if (from.size() != 2 || to.size() != 2)
		return 1;
	if (from[0] < 'a' || from[0] > 'h' || to[0] < 'a' || to[0] > 'h')
		return 1;
	if (from[1] < '1' || from[1] > '8' || to[1] < '1' || to[1] > '8')
		return 1;
	if (field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 1 && color == "black")
		return 3;
	if (field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 3 && color == "black")
		return 3;
	if (field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 2 && color == "white")
		return 3;
	if (field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 4 && color == "white")
		return 3;
	if (from[0] == to[0] || from[1] == to[1])
		return 2;
	if (abs(int(from[1]) - int(to[1])) > 2 && field[int(from[0]) - int('a')][int(from[1]) - int('1')] < 3)
		return 2;
	if (abs(int(from[1]) - int(to[1])) == 1 && field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 1 && (int(from[1]) - int(to[1]) > 0 || field[int(to[0]) - int('a')][int(to[1]) - int('1')] != 0))
		return 2;
	if (abs(int(from[1]) - int(to[1])) == 1 && field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 2 && (int(from[1]) - int(to[1]) < 0 || field[int(to[0]) - int('a')][int(to[1]) - int('1')] != 0))
		return 2;
	if (abs(int(from[1]) - int(to[1])) == 2 && field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 1) {
		int coord1 = (int(from[0]) + int(to[0])) / 2 - int('a');
		int coord2 = (int(from[1]) + int(to[0])) / 2 - int('1');
		if (field[coord1][coord2] == 1 || field[coord1][coord2] == 3)
			return 2;
		if (field[int(to[0]) - int('a')][int(to[1]) - int('1')] != 0)
			return 2;
	}
	if (abs(int(from[1]) - int(to[1])) == 2 && field[int(from[0]) - int('a')][int(from[1]) - int('1')] == 2) {
		int coord1 = (int(from[0]) + int(to[0])) / 2 - int('a');
		int coord2 = (int(from[1]) + int(to[0])) / 2 - int('1');
		if (field[coord1][coord2] == 2 || field[coord1][coord2] == 4)
			return 2;
		if (field[int(to[0]) - int('a')][int(to[1]) - int('1')] != 0)
			return 2;
	}
	if (field[int(from[0]) - int('a')][int(from[1]) - int('1')] > 3) {
		if (field[int(to[0]) - int('a')][int(to[1]) - int('1')] != 0)
			return 2;
		int count_white = 0;
		int count_black = 0;
		for (int i = int(from[0]) - int('a'), j = int(from[1]) - int('1'); i != int(to[0]) - int('a'), j != int(to[1]) - int('1'); ) {
			if (field[i][j] == 1 || field[i][j] == 3)
				count_white++;
			if (field[i][j] == 2 || field[i][j] == 4)
				count_black++;
			if (int(from[0]) > int(to[0])) i--; else i++;
			if (int(from[1]) > int(to[1])) j--; else j++;
		}
		if (count_white > 1 || count_black > 1)
			return 2;
	}
	return 0;
}

vector<string> check_eat(string color) {
	vector<string> ans = {};
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j) {
			if (color == "white" && (field[i][j] == 1 || field[i][j] == 3)) {
				if (i - 2 >= 0) {
					if (j - 2 >= 0) {
						if (field[i - 2][j - 2] == 0)
							if (field[i - 1][j - 1] == 2 || field[i - 1][j - 1] == 4) {
								int j1 = j + 1, j2 = j - 1;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i - 2) + to_string(j2));
							}
					}
					if (j + 2 <= 7) {
						if (field[i - 2][j + 2] == 0)
							if (field[i - 1][j + 1] == 2 || field[i - 1][j + 1] == 4) {
								int j1 = j + 1, j2 = j + 3;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i - 2) + to_string(j2));
							}
					}
				}
				if (i + 2 <= 7) {
					if (j - 2 >= 0) {
						if (field[i + 2][j - 2] == 0)
							if (field[i + 1][j - 1] == 2 || field[i + 1][j - 1] == 4) {
								int j1 = j + 1, j2 = j - 1;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i + 2) + to_string(j2));
							}
					}
					if (j + 2 <= 7) {
						if (field[i + 2][j + 2] == 0)
							if (field[i + 1][j + 1] == 2 || field[i + 1][j + 1] == 4) {
								int j1 = j + 1, j2 = j + 3;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i + 2) + to_string(j2));
							}
					}
				}
			}
			if (color == "black" && (field[i][j] == 2 || field[i][j] == 2)) {
				if (i - 2 >= 0) {
					if (j - 2 >= 0) {
						if (field[i - 2][j - 2] == 0)
							if (field[i - 1][j - 1] == 1 || field[i - 1][j - 1] == 3) {
								int j1 = j + 1, j2 = j - 1;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i - 2) + to_string(j2));
							}
					}
					if (j + 2 <= 7) {
						if (field[i - 2][j + 2] == 0)
							if (field[i - 1][j + 1] == 1 || field[i - 1][j + 1] == 3) {
								int j1 = j + 1, j2 = j + 3;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i - 2) + to_string(j2));
							}		
					}
				}
				if (i + 2 <= 7) {
					if (j - 2 >= 0) {
						if (field[i + 2][j - 2] == 0)
							if (field[i + 1][j - 1] == 1 || field[i + 1][j - 1] == 3) {
								int j1 = j + 1, j2 = j - 1;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i + 2) + to_string(j2));
							}
					}
					if (j + 2 <= 7) {
						if (field[i + 2][j + 2] == 0)
							if (field[i + 1][j + 1] == 1 || field[i + 1][j + 1] == 3) {
								int j1 = j + 1, j2 = j + 3;
								ans.push_back(char(int('a') + i) + to_string(j1) + char(int('a') + i + 2) + to_string(j2));
							}
					}
				}
			}
			if (color == "white" && field[i][j] == 3) {
				int i1 = i + 1, j1 = j + 1, i2 = i - 1, j2 = j - 1;
				while(i1 < 7 || j1 < 7 || i2 > 0 || j2 > 0) {
					if (i1 < 7) {
						if (j1 < 7) {
							if (field[i][j] == 2 || field[i][j] == 4 && field[i1 + 1][j1 + 1] == 0) {
								int j3 = j + 1, j4 = j1 + 2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i1 + 1) + to_string(j4));
							}
						}
						if (j2 > 0) {
							if (field[i][j] == 2 || field[i][j] == 4 && field[i1 + 1][j2 - 1] == 0) {
								int j3 = j + 1, j4 = j2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i1 + 1) + to_string(j4));
							}
						}
					}
					if (i2 > 0) {
						if (j1 < 7) {
							if (field[i][j] == 2 || field[i][j] == 4 && field[i2 - 1][j1 + 1] == 0) {
								int j3 = j + 1, j4 = j1 + 2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i2 - 1) + to_string(j4));
							}
						}
						if (j2 > 0) {
							if (field[i][j] == 2 || field[i][j] == 4 && field[i2 - 1][j2 - 1] == 0) {
								int j3 = j + 1, j4 = j2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i2 - 1) + to_string(j4));
							}
						}
					}
					i1++;
					j1++;
					i2--;
					j2--;
				}
			}
			if (color == "black" && field[i][j] == 4) {
				int i1 = i + 1, j1 = j + 1, i2 = i - 1, j2 = j - 1;
				while(i1 < 7 || j1 < 7 || i2 > 0 || j2 > 0) {
					if (i1 < 7) {
						if (j1 < 7) {
							if (field[i][j] == 1 || field[i][j] == 3 && field[i1 + 1][j1 + 1] == 0) {
								int j3 = j + 1, j4 = j1 + 2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i1 + 1) + to_string(j4));
							}
						}
						if (j2 > 0) {
							if (field[i][j] == 1 || field[i][j] == 3 && field[i1 + 1][j2 - 1] == 0) {
								int j3 = j + 1, j4 = j2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i1 + 1) + to_string(j4));
							}
						}
					}
					if (i2 > 0) {
						if (j1 < 7) {
							if (field[i][j] == 1 || field[i][j] == 3 && field[i2 - 1][j1 + 1] == 0) {
								int j3 = j + 1, j4 = j1 + 2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i2 - 1) + to_string(j4));
							}
						}
						if (j2 > 0) {
							if (field[i][j] == 1 || field[i][j] == 3 && field[i2 - 1][j2 - 1] == 0) {
								int j3 = j + 1, j4 = j2;
								ans.push_back(char(int('a') + i) + to_string(j3) + char(int('a') + i2 - 1) + to_string(j4));
							}
						}
					}
					i1++;
					j1++;
					i2--;
					j2--;
				}
			}
		}
	return ans;			
}

void change_field(string from, string to) {
	int i1 = int(from[0]) - int('a'), j1 = int(from[1]) - int('1');
	int i2 = int(to[0]) - int('a'), j2 = int(to[1]) - int('1');
	int tmp = field[i1][j1];
	for (int i = i1, j = j1; i != i2, j != j2; ) {
		field[i][j] = 0;
		if (i1 > i2) i--; else i++;
		if (j1 > j2) j--; else j++;
	}
	if (tmp == 1 && i2 == 0)
		tmp = 3;
	if (tmp == 2 && i2 == 7)
		tmp = 4;
	field[i2][j2] = tmp;
}

int move(string from, string to, string color) {
	vector<string> ch = check_eat(color);
	string m = from + to;
	for (int i = 0; i < ch.size(); ++i) {
		if (ch[i] == m) {
			change_field(from, to);
			return 0;
		}
	}
	if (ch.size() > 0)
		return 1;
	change_field(from, to);		
	return 0;
}

void go(string color) {
	if (color == player) {
		string from = "", to = "";
		cout << "Your move (from to): " << endl;
		cin >> from >> to;
		while (check_command(from, to, color)) {
			if (check_command(from, to, color) == 1)
				cout << "Invalid command" << endl;
			if (check_command(from, to, color) == 2)
				cout << "Invalid move" << endl;
			if (check_command(from, to, color) == 3)
				cout << "You are trying to move opponent's checker" << endl;
			
			from = "", to = "";
			cout << "Your move (from to): " << endl;
			cin >> from >> to;
		}
		while(move(from, to, color)) {
			from = "", to = "";
			cout << "You must eat" << endl;
			cout << "Your move (from to): " << endl;
			cin >> from >> to;
		}
		for (int i = 0; i < 8; ++i) {
			cout << char(int('a') + i)<< "   ";
			for (int j = 0; j < 8; ++j) 
				cout << field[i][j] << ' ';
			cout << endl ;
		}
		cout <<endl << ' ' << "   "<< '1' << " 2" << " 3" << " 4" << " 5" << " 6" << " 7" << " 8" << endl<<endl;
		int k = 1;
		while(k) {
			from = to;
			vector<string> ch = check_eat(color);
			vector<string> options = {};
			for (int i = 0; i < ch.size(); ++i) {
				string str = ch[i].substr(0, 2);
				if (from == str) {
					str = ch[i].substr(2, 2);
					options.push_back(str);
				}
			}
			if (options.size() == 0)
				k = 0;
			else {
				to = "";
				while(find(options.begin(), options.end(), to) == options.end()) {
					cout << "Next step (to):" << endl;
					cin >> to;
				}
				move(from, to, color);
				for (int i = 0; i < 8; ++i) {
					cout << char(int('a') + i)<< "   ";
					for (int j = 0; j < 8; ++j) 
						cout << field[i][j] << ' ';
					cout << endl ;
				}
				cout <<endl << ' ' << "   "<< '1' << " 2" << " 3" << " 4" << " 5" << " 6" << " 7" << " 8" << endl<< endl;
			}
		}	
					
	} else {
		
		for (int i = 0; i < 8; ++i) {
		cout << char(int('a') + i)<< "   ";
		for (int j = 0; j < 8; ++j) 
			cout << field[i][j] << ' ';
		cout << endl ;
	}
	cout <<endl << ' ' << "   "<< '1' << " 2" << " 3" << " 4" << " 5" << " 6" << " 7" << " 8" << endl<<endl;
	}
}



int main() {
	field.push_back({0, 2, 0, 2, 0, 2, 0, 2});
	field.push_back({2, 0, 2, 0, 2, 0, 2, 0});
	field.push_back({0, 2, 0, 2, 0, 2, 0, 2});
	field.push_back({0, 0, 0, 0, 0, 0, 0, 0});
	field.push_back({0, 0, 0, 0, 0, 0, 0, 0});
	field.push_back({1, 0, 1, 0, 1, 0, 1, 0});
	field.push_back({0, 1, 0, 1, 0, 1, 0, 1});
	field.push_back({1, 0, 1, 0, 1, 0, 1, 0});
	for (int i = 0; i < 8; ++i) {
		cout << char(int('a') + i)<< "   ";
		for (int j = 0; j < 8; ++j) 
			cout << field[i][j] << ' ';
		cout << endl ;
	}
	cout <<endl << ' ' << "   "<< '1' << " 2" << " 3" << " 4" << " 5" << " 6" << " 7" << " 8" << endl;
	while (player != "white" && player!= "black") {
		cout << "Choose color (white / black): " << endl;	
		cin >> player;
	}
	int lose = 0;
	while (!(lose = check_lose())) {
		go("white");
		go("black");
	}
	cout << lose;

	return 0;
}
