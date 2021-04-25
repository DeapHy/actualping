#pragma once
unsigned int analyze(int, char*, SOCKADDR_IN*);
int response(SOCKET, char[], SOCKADDR_IN&, int);
USHORT crc2(USHORT*, int);