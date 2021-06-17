#pragma once
#include "networkTools.h"
void myNetwork::initClient()
{
	RakNet::SocketDescriptor sd;
	peer->Startup(1, &sd, 1);
	char str[255];
	printf("Enter server IP or hit enter for 127.0.0.1\n");
	gets_s(str);
	if (str[0] == 0) {
		strcpy_s(str, "127.0.0.1");
	}
	printf("Starting the client.\n");
	peer->Connect(str, SERVER_PORT, 0, 0);
}


void  myNetwork::sendPrompt(const char* str)
{
	RakNet::BitStream bsOut;
	bsOut.Write(ID_GAME_MESSAGE_PROMPT);
	bsOut.Write(str);
	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}


RakNet::RakPeerInterface* myNetwork::getPeer()
{
	return peer;
}
myNetwork::~myNetwork()
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}
void myNetwork::showIPAddress()
{
	printf("\nMy IP addresses:\n");
	for (unsigned int i = 0; i < peer->GetNumberOfAddresses(); i++)
	{
		RakNet::SystemAddress sa = peer->GetInternalID(RakNet::UNASSIGNED_SYSTEM_ADDRESS, i);
		printf("%i. %s (LAN=%i)\n", i + 1, sa.ToString(false), sa.IsLANAddress());
		/*if (sa.IsLANAddress())
		{
			printf("%i. %s (LAN=%i)\n", i + 1, sa.ToString(false), sa.IsLANAddress());
		}*/
	}
}
void myNetwork::initServer()
{
	//starting the network object on the given port
	RakNet::SocketDescriptor sd(SERVER_PORT, 0);
	peer->Startup(MAX_CLIENTS, &sd, 1);
	// We need to let the server accept incoming connections from the clients
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	printf("the server started successfully.\n");
}
