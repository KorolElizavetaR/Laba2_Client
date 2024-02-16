#define PORT 1234

#include <iostream>
#include <ws2tcpip.h>
#include <stdio.h>
// #include <winsock2.h>


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

int main(int args, char * argv[])
{
	WSADATA data;
	WORD DDLversion = MAKEWORD(2, 2);
	if (WSAStartup(DDLversion, &data) != 0)
	{
		cout << "Start winsock failed." << endl;
		return -1;
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_DGRAM, 0);
	char buf[100];
	const int bufsize = sizeof(buf);

	cout << "Input line : ";
	cin.getline(buf, bufsize);
	//cin >> buf;
	if (sendto(Connection, buf, bufsize, 0, (SOCKADDR*)&addr, sizeofaddr) == SOCKET_ERROR)
	{
		cout << "Sendto failed. " << WSAGetLastError() << endl;
		return -1;
	}

	closesocket(Connection);
	WSACleanup();
}