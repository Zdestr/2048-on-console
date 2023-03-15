#include <curses.h>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void print_field() {
	mvprintw(1, 1,  " ===== ===== ===== =====\n");
	mvprintw(2, 1,  "|     |     |     |     |\n");
	mvprintw(3, 1,  "|     |     |     |     |\n");
	mvprintw(4, 1,  "|     |     |     |     |\n");
	mvprintw(5, 1,  " ===== ===== ===== =====\n");
	mvprintw(6, 1,  "|     |     |     |     |\n");
	mvprintw(7, 1,  "|     |     |     |     |\n");
	mvprintw(8, 1,  "|     |     |     |     |\n");
	mvprintw(9, 1,  " ===== ===== ===== =====\n");
	mvprintw(10, 1, "|     |     |     |     |\n");
	mvprintw(11, 1, "|     |     |     |     |\n");
	mvprintw(12, 1, "|     |     |     |     |\n");
	mvprintw(13, 1, " ===== ===== ===== =====\n");
	mvprintw(14, 1, "|     |     |     |     |\n");
	mvprintw(15, 1, "|     |     |     |     |\n");
	mvprintw(16, 1, "|     |     |     |     |\n");
	mvprintw(17, 1, " ===== ===== ===== =====\n");
}

void print_nums(int field[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (field[i][j] != 0) {
				int x = 4 + 6 * j,
					y = 3 + 4 * i;
				move(y, x);
				printw("%d", field[i][j]);
			}
		}
	}
}

void resize (vector <int> &v) {
    vector <int> _v;
    int cnt = 0;
    for (int i : v) {
        _v.push_back(i);
        if (_v.size() > 1 and _v[_v.size() - 1] == _v[_v.size() - 2] and cnt == 0) {
            _v.pop_back();
            _v.pop_back();
            _v.push_back(2*i);
            cnt++;
        }
    }
    v = _v;
}

void updatePlaces (vector <int> &v, int x[4][4]) {
    v.clear();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (x[i][j] == 0)
                v.push_back(4*i + j);
}

int autosum (int field[4][4]) {
    int sum = 0;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++)
            sum += field[i][j];
    return sum;
}

int main() {
	srand(time(0));
	initscr();
	curs_set(0);
	noecho();
	keypad(stdscr, TRUE);
	
	int field[4][4] = {{0, 0, 0, 0},
					   {0, 0, 0, 0},
					   {0, 0, 0, 0},
					   {0, 0, 0, 0}};
	vector <int> freePlaces;
	vector <int> vals = {2, 2, 2, 4};
	updatePlaces(freePlaces, field);
	int place = freePlaces[rand() % freePlaces.size()];
	int val = vals[rand() % 4];
	field[place / 4][place % 4] = val;				   
	updatePlaces(freePlaces, field);
	place = freePlaces[rand() % freePlaces.size()];
	val = vals[rand() % 4];
	field[place / 4][place % 4] = val;				   
	updatePlaces(freePlaces, field);
	
	for (;;) {
		print_field();
		print_nums(field);
		move (8, 30);
		printw("Free places: %d", freePlaces.size());
		move (10, 30);
		printw("Score: %d", autosum(field));
		refresh();
		vector <int> cur;
		int _[4][4];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				_[i][j] = field[i][j];
		int ch = getch();
		//KEYS
		if (ch == KEY_LEFT) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					if (field[i][j] != 0)
						cur.push_back(field[i][j]);
				resize(cur);
				while (cur.size() < 4)
					cur.push_back(0);
				for (int j = 0; j < 4; j++)
					_[i][j] = cur[j];
				cur.clear();
			}
		}

		if (ch == KEY_RIGHT) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					if (field[i][j] != 0)
						cur.push_back(field[i][j]);
				resize(cur);
				reverse(cur.begin(), cur.end());
				while (cur.size() < 4)
					cur.push_back(0);
				reverse(cur.begin(), cur.end());
				for (int j = 0; j < 4; j++)
					_[i][j] = cur[j];
				cur.clear();
			}
		}
		
		if (ch == KEY_UP) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++)
					if (field[i][j] != 0)
						cur.push_back(field[i][j]);
				resize(cur);
				while (cur.size() < 4)
					cur.push_back(0);
				for (int i = 0; i < 4; i++)
					_[i][j] = cur[i];
				cur.clear();
			}
		}

		if (ch == KEY_DOWN) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++)
					if (field[i][j] != 0)
						cur.push_back(field[i][j]);
				resize(cur);
				reverse(cur.begin(), cur.end());
				while (cur.size() < 4)
					cur.push_back(0);
				reverse(cur.begin(), cur.end());
				for (int i = 0; i < 4; i++)
					_[i][j] = cur[i];
				cur.clear();
			}
		}

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				field[i][j] = _[i][j];
		updatePlaces(freePlaces, field);
		place = freePlaces[rand() % freePlaces.size()];
		val = vals[rand() % 4];
		field[place / 4][place % 4] = val;
		updatePlaces(freePlaces, field);
		clear();
		if (freePlaces.size() == 0)
		    mvprintw(1,1, "GAME OVER");
	}
	endwin();
}
