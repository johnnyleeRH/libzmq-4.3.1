#include <sys/time.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

struct timeval * cost = NULL;

const int bufsize = 409600;
const int kcheckcnt = 1000;

void tminit(int size) {
  cost = (struct timeval*)malloc(sizeof(struct timeval) * size);
  memset((char*)cost, 0, sizeof(struct timeval) * size);
}

void loggertime(string path) {
  ofstream tmfile(path.c_str());
  if (tmfile.is_open()) {
    int cnt = 0;
    while (cnt < kcheckcnt) {
      tmfile << cost[cnt].tv_sec << " " << cost[cnt].tv_usec << endl;
      cnt++;
    }
    tmfile.close();
  }
}

void timefree() {
  free (cost);
}