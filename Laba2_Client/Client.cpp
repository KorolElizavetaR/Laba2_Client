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
	int requiredlength; char requiredlengthchar[3];

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
	char line[100];
	const int bufsize = sizeof(line);
	char sizeofline[3]; int size;

	cout << "Input line : ";
	cin.getline(line, bufsize);
	//cin >> buf;
	if (sendto(Connection, line, bufsize, 0, (SOCKADDR*)&addr, sizeofaddr) == SOCKET_ERROR) //send line
	{
		cout << "Sendto failed. " << WSAGetLastError() << endl;
		return -1;
	}
	else
	{
		cout << "Server received line!" << endl;
	}

	if (recvfrom(Connection, sizeofline, 3, 0, (SOCKADDR*)&addr, &sizeofaddr) == SOCKET_ERROR) //receive line length
	{
		cout << "Recv from server failed. " << WSAGetLastError() << endl;
		return -1;
	}
	else
	{
		size = atoi(sizeofline);
		cout << "Line length: " << size << endl;
	}

	if (recvfrom(Connection, requiredlengthchar, sizeof(requiredlengthchar), 0, (SOCKADDR*)&addr, &sizeofaddr) == SOCKET_ERROR) //receive recomended length
	{
		cout << "Recv from server failed. " << WSAGetLastError() << endl;
		return -1;
	}
	else
	{
		requiredlength = atoi(requiredlengthchar);
		cout << "Recommended length: " << requiredlength << endl;
	}

	if (size == requiredlength)
	{
		char newline[100];
		char difference_char[3];
		if (recvfrom(Connection, newline, sizeof(newline), 0, (SOCKADDR*)&addr, &sizeofaddr) == SOCKET_ERROR) //receive newline
		{
			cout << "Recv from server failed. " << WSAGetLastError() << endl;
			return -1;
		}
		else
		{
			cout << "New line: " << newline << endl;
		}
		if (recvfrom(Connection, difference_char, sizeof(difference_char), 0, (SOCKADDR*)&addr, &sizeofaddr) == SOCKET_ERROR) //receive difference
		{
			cout << "Recv from server failed. " << WSAGetLastError() << endl;
			return -1;
		}
		else
		{
			cout << "Difference: " << difference_char << endl;
		}
	}

	closesocket(Connection);
	WSACleanup();
}