#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
using std::string, std::vector;

#define VERSION 1.0
#define AUTHOR "FU4Dxx28X"
#define MENUBOXMSG "press ↑↓ to select and ESC to exit"
#define MSGBOX "press enter"

int init_tui();
int end_tui();
inline int centertext(const string &text) { return (COLS - (int)text.length()) / 2; }
string scanpr(const size_t &size, const string &prompt);
string mvscanpr(const int &x, const int &y, const size_t &size, const string &prompt);
void printcenter(string &text);
void downprint(const int &x, const int &y, const int &pos, const string &text);
void uppprint(const int &x, const int &y, const int &pos, const string &text);
void msgbox(string &msg);
void warnbox(string &msg);
void reportbox(const vector<string> reportlist);
void menubox(string &&item, const vector<string> &menu, const string &title);
