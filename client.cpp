#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <time.h>

// adds wsock32.lib to the linker
#pragma comment(lib, "wsock32.lib")
using namespace std;

void main() {
	WSADATA wdata; // this variable will contain the details of the winsock connection
	if (WSAStartup(MAKEWORD(2, 0), &wdata) != 0) {
		cout << "Error initializing winsock version 2.0" << endl;
		WSACleanup(); // terminates the use of the winsock 2 DLL
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cout << "Error creating socket" << endl;
		WSACleanup(); // terminates the use of the winsock 2 DLL
		return;
	}

	char server_addr[100];
	int port;
	char filepath[1024] = "C:\\Users\\MG C\\Documents\\Visual Studio 2013\\Projects\\lab3\\lab3\\a.txt";
	long size;


	cout << "Enter the server address:" << endl;
	cin >> server_addr;
	char *hostname = server_addr;
	cout << "Enter the server port:" << endl;
	cin >> port;
	

	//resolves the hostname to an IP address, stored in the hostent structure
	struct hostent *server = gethostbyname(hostname);
	if (server == NULL) {
		cout << "Error resolving hostname to an IP address" << endl;
		WSACleanup(); // terminates the use of the winsock 2 DLL
		return;
	}

	SOCKADDR_IN server_info;
	server_info.sin_port = htons(port);
	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = *((unsigned long *)server->h_addr);

	if (connect(sock, (SOCKADDR*)(&server_info), sizeof(server_info)) != 0) {
		cout << "Error connecting to server" << endl;
		WSACleanup(); // terminates the use of the winsock 2 DLL
		return;
	}

	char buffer[3000];
	memset(buffer, 0,2999);

	int Length = recv(sock, buffer, 3000, 0);

	ifstream file;
	file.open(filepath);		//open file

	if (file.is_open()){
		file.seekg(0, ios::end);
		size = file.tellg();	//file size! 

		file.seekg(0, ios::beg);		//sets location back to beginning of file

		char * buff = new char[size];
		file.read(buff, size);		//write file to buffer
		
		int sen = send(sock, buff, strlen(buff), 0);	//send file to server
	
		if (sen == -1){
			cout << "Error uploading file to server " << endl;
		}
		file.close();
	}

	cout << "Thank you for using program!" << endl;
	shutdown(sock, SD_SEND);
	closesocket(sock);
	WSACleanup();
}