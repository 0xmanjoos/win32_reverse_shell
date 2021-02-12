#pragma once
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <time.h>
#include <queue>
#include <assert.h>
#include <fstream>
#include <algorithm>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")

#define BUFFER 1024
#define TIMELEN 5000

// debugging
using std::cout;
using std::endl;
using std::cin;
using std::cerr;


using std::string;
using std::queue;
using std::vector;
using std::ostringstream;
