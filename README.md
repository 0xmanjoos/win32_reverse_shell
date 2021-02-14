# win32_reverse_shell
#### A reverse shell written in c++, supports DNS name resolution, so you can use this with NGROK.

As long as this program is running, it will constantly call back to the original listener in 5 second intervals, so accidentally SIGTERM'd netcat? 

No problem :D

Currently, this would probably be caught by any good antivirus, but in the future I plan to implement this into win32 shellcode, then ATTEMPT to make it polymorphic for AV/EDR evasion. I also plan to hopefully implement API unhooking in case those pesky AV's have some tricks up their sleeves.

* Compiling on Linux:
```bash
x86_64-w64-mingw32-g++ main.cpp -lws2_32 -static
```
* Compiling on Windows:
```
g++ main.cpp -lws2_32 -static
```
Note: I am using mingw compiler on windows as well, there may be some issues with compiling on something like vs studio but hey not my fault I dont use a terrible IDE.
