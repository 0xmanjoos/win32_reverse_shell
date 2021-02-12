# win32_reverse_shell
#### A reverse shell written in c++, supports DNS name resolution, so you can use this with NGROK or whatever you use

As long as this program is running, it will constantly call back to the original listener in 5 second intervals, so accidentally SIGTERM'd netcat? 

No problem :D

Obviously, the includes.h is my general includes file that I use for basically every project. If you feel the need to lighten up the size of your binary feel free to strip the following headers out:
```
#include <iostream>
#include <time.h>
#include <queue>
#include <assert.h>
#include <fstream>
#include <algorithm>
#include <sstream>

using std::string;
using std::queue;
using std::vector;
using std::ostringstream;
```
Currently, this would probably be caught by any good antivirus, but in the future I plan to implement this into win32 shellcode, then ATTEMPT to make it polymorphic for AV/EDR evasion. I also plan to hopefully implement API unhooking in case those pesky AV's have some tricks up their sleeves.

Compile:
```bash
i686-w64-mingw32-g++ main.cpp -lws2_32 -static
```
