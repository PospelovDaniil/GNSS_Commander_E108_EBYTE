#include <cstring>
#include <iostream>
#include "src/E108_Commander.h"

using namespace std;

int main()
{
    const char *cmd = "PGKC030,1,2";
    const auto *res = makeCmd(cmd, strlen(cmd));
    cout << cmd << " strlen cmd: " << strlen(cmd) << endl;
    cout << res << " strlen res: " << strlen(res) << endl;
    return 0;
}
