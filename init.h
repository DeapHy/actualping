#pragma once
int checkArgs(int, LOGINFO&);
int init(char*, SOCKADDR_IN&, SOCKADDR_IN&, SOCKADDR_IN&, WSADATA&, SOCKET&, LOGINFO&);
int dnsCheck(SOCKADDR_IN&, SOCKADDR_IN&, char*, SOCKET&, LOGINFO&);
void results();
void finish(char*, SOCKET);