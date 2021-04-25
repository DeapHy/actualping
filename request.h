#pragma once
int assembling(IcmpHeader&, IcmpHeader*&, char*&);
int request(IcmpHeader*, SOCKET, SOCKADDR_IN);