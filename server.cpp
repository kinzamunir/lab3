#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <time.h>
#include <string.h>

// adds wsock32.lib to the linker
#pragma comment(lib, "wsock32.lib")
using namespace std;

void main() {
	while (true){
		WSADATA wdata; // variable containing details of winsock connection
		// specifies winsock version 2.0
		if (WSAStartup(MAKEWORD(2, 0), &wdata) != 0) {
			cout << "Error initializing winsock version 2.0" << endl;
			WSACleanup(); // terminates the use of the winsock 2 DLL
			return;
		}

		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET) {
			cout << "Error creating socket" << endl;
			WSACleanup();
			return;
		}

		SOCKADDR_IN server_info;
		server_info.sin_family = AF_INET;
		server_info.sin_addr.s_addr = INADDR_ANY;
		server_info.sin_port = htons(55556);
		if (bind(sock, (SOCKADDR *)(&server_info), sizeof(server_info)) == SOCKET_ERROR) {
			cout << "Error binding socket" << endl;
			WSACleanup();
			return;
		}

		listen(sock, 1);

		SOCKET sock_temp = SOCKET_ERROR;
		while (sock_temp == SOCKET_ERROR)
		{
			cout << "Waiting for connection . . ." << endl;
			sock_temp = accept(sock, NULL, NULL);
		}
		sock = sock_temp;


		char *welcome = "Welcome to the server!\r\n";
		send(sock, welcome, strlen(welcome), 0);

		cout << "Client connected" << endl;

		char buffer[3000]; //message written in this
		memset(buffer, 0, 2999);

		int rec = recv(sock, buffer, 3000, 0);

		if (rec < 0){
			cout << "Error uploading file" << endl;
		}
		cout << "File is being uploaded..." << endl;
		cout << "File received!" << endl;

		ofstream myfile("newFile.txt");
		if (myfile.is_open())
		{
			myfile << buffer;
			myfile.close();
		}
		else cout << "Unable to open file";

		shutdown(sock, SD_SEND);
		closesocket(sock);
		WSACleanup();
	}
}