#include "tuilib.h"
#include <ncurses.h>

int init_tui(){
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  bkgd(COLOR_PAIR(1));
  return 0;
}

int end_tui(){
  endwin();
  return 0;
}

string scanpr(const size_t &size, const string &prompt){
  char buff[size];
  echo();
  curs_set(1);
  printw("%s", prompt.c_str());
  refresh();
  getnstr(buff, size - 1);
  noecho();
  curs_set(0);
  return string(buff);
}

string mvscanpr(const int &x, const int &y, const size_t &size, const string &prompt){
  char buff[size];
  echo();
  curs_set(1);
  mvprintw(y, x, "%s", prompt.c_str());
  move(y, x + prompt.length());
  refresh();
  getnstr(buff, size - 1);
  noecho();
  curs_set(0);
  return string(buff);
}

void printcenter(string &text){
  if (text.length() > COLS - 4) {
    text = text.substr(0, COLS - 6) + "...";
  }
  mvprintw((LINES - (LINES - 5)), centertext(text), "%s", text.c_str());
}

void downprint(const int &x, const int &y, const int &pos, const string &text){
  mvprintw(y + pos, x, "%s", text.c_str());
}

void uppprint(const int &x, const int &y, const int &pos, const string &text){
  mvprintw(y - pos, x, "%s", text.c_str());
}

void msgbox(string &msg){
  if (msg.length() > COLS - 4) {
    msg = msg.substr(0, msg.length() - 6) + "...";
  }
  clear();
  box(stdscr, 0, 0);
  mvprintw((LINES / 2) - 2, centertext(msg), "%s", msg.c_str());
  mvprintw(LINES - 4, centertext(MSGBOX), "%s", MSGBOX);
  refresh();
  getch();
  clear();
  return;
}

void warnbox(string &msg){
  if (msg.length() > COLS - 4) {
    msg = msg.substr(0, msg.length() - 6) + "...";
  }
  init_pair(2, COLOR_RED, COLOR_YELLOW);
  clear();
  box(stdscr, 0 ,0);
  attron(COLOR_PAIR(2) | A_BOLD);
  mvprintw((LINES / 2) - 2, centertext(msg), "%s", msg.c_str());
  attroff(COLOR_PAIR(2) | A_BOLD);
  mvprintw(LINES - 4, centertext(MSGBOX), "%s", MSGBOX);
  refresh();
  getch();
  clear();
  return;
}

void reportbox(const vector<string> reportlist){
  clear();
  box(stdscr, 0 ,0);
  int MIN = (reportlist.size() > LINES - 5)? LINES - 6 : reportlist.size();
  for (int i = 0; i < MIN; i++) {
    string text = reportlist[i];
    if (text.length() > COLS - 2) {
      text = text.substr(0, text.length() - 4) + "...";
    }
    mvprintw((LINES - (LINES - 4)) + i, centertext(text), "%s", text.c_str());
  }
  mvprintw(LINES - 4, centertext(MSGBOX), "%s", MSGBOX);
  refresh();
  getch();
  clear();
  return;
}

void menubox(string &&item, const vector<string> &menu, const string &title) {
  int id = 0, ch;
  init_pair(3, COLOR_YELLOW, COLOR_BLUE);
  while (true) {
    clear();
    box(stdscr, 0, 0);
    mvprintw((LINES - (LINES - 3)), centertext(title), "%s", title.c_str());
    for (int i = 0; i < (int)menu.size(); i++) {
      if (id == i) {
        attron(A_REVERSE);
        mvprintw((LINES - (LINES - 5)) + i, centertext(menu[i]), "%s", menu[i].c_str());
        attroff(A_REVERSE);
      } else {
        mvprintw((LINES - (LINES - 5)) + i, centertext(menu[i]), "%s", menu[i].c_str());
      }
    }
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(LINES - 4, centertext(MENUBOXMSG), "%s", MENUBOXMSG);
    attroff(COLOR_PAIR(3) | A_BOLD);
    refresh();
    ch = getch();
    switch (ch) {
      case KEY_UP:
        id = (id - 1 + menu.size()) % menu.size();
        break;

      case KEY_DOWN:
        id = (id + 1) % menu.size();
        break;
    }
    if (ch == 10) {
      if (menu[id] == menu[menu.size() - 1]) break;
      item = menu[id];
      break;
    } else if (ch == 27) break;
  }
  clear();
  return;
}
