#include "tuilib/tuilib.h"
#include <string>
#include <vector>
using std::string, std::vector;

void menu_preview(){
  string result, msg = "this is message";
  vector<string> data{"input-preview", "msgbox-preview", "warnbox-preview", "reportbox-preview", "cancel"};
  menubox(std::move(result), data, "# MENUBOX REVIEW");
  if (result != "cancel") {
    if (result == "input-preview") {
      string inp = scanpr(50, "type anything : ");
    } else if (result == "msgbox-preview") {
      msgbox(msg);
    } else if (result == "warnbox-preview") {
      warnbox(msg);
    } else if (result == "reportbox-preview") {
      vector<string> report{"username : @user1337", "id : #1", "role : admin"};
      reportbox(report);
    }
  }
}

int main(){
  init_tui();
  menu_preview();
  end_tui();
  return 0;
}
