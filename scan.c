#include "stdafx.h"
#include <stdio.h>
#include<winsock.h>
#include<string.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"wsock32.lib")
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup  �޷���ʼ����" << endl;
		return 0;
	}
	// ��д��ַ��Ϣ
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	while (true)
	{
		char aim_ip[100];
		cout << "������Ŀ������IP��ַ��";
		cin >> aim_ip;
		cout << endl;
		//���û�ȡ���û�����IP��ַΪԶ��IP��ַ 
		addr.sin_addr.S_un.S_addr = inet_addr(aim_ip);
		int port_start;
		int port_end;
		cout << "��������ʼ�˿ںţ�";
		cin >> port_start;
		cout << endl;
		cout << "����������˿ںţ�";
		cin >> port_end;
		cout << endl;
		for (int i = port_start; i <= port_end; i++)
		{
			//ÿɨ��һ���˿ڴ���һ���µ��׽���
			SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (s == INVALID_SOCKET)
			{
				printf("Failed socket() %d \n", ::WSAGetLastError());
				//return -1;
			}
			//����Զ�̵�ַ��Ϣ�еĶ˿ں�Ϊ��Ҫɨ��ĵ�ǰ�˿ں�
			addr.sin_port = htons(i);
			int ret = connect(s, (LPSOCKADDR)&addr, sizeof(addr));
			if (ret ==0)
			{
				printf("%s:%d  �˿ڿ���\n", aim_ip, i);
			}
			else
			{
				printf("%s:%d  �˿ڹر�\n", aim_ip, i);
			}
			::closesocket(s);
		}
		cout << endl;
	}
	if (WSACleanup() == SOCKET_ERROR)
		cout << "WSACleanup ����" << endl;
	return 0;
}

