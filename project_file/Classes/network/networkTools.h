#pragma once
#include <string.h>
#include "cocos2d.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID

using namespace cocos2d;

#define MAX_CLIENTS 10
#define SERVER_PORT 60000

const unsigned char ID_GAME_MESSAGE_PROMPT = ID_USER_PACKET_ENUM + 1;
const unsigned char ID_GAME_MESSAGE_POS = ID_USER_PACKET_ENUM + 2;
const unsigned char ID_GAME_DISTRIBUTE_ID = ID_USER_PACKET_ENUM + 3;
const unsigned char ID_GAME_PLAYER_COUNT = ID_USER_PACKET_ENUM + 4;

class myNetwork
{
private:
	RakNet::RakPeerInterface* peer = RakNet::RakPeerInterface::GetInstance();
public:
	~myNetwork();
	int clientID;
	//start up the client
	void initClient();
	//send a string
	void sendPrompt(const char* str);
	//send data
	template<class dataType>
	void sendData(dataType& toSend, unsigned char messageType);
	//get data
	template<class dataType>
	void getData(dataType& dataRead, RakNet::Packet* packet);
	//wait till the message with given id arrived
	template<class messageRecvType>
	messageRecvType waitForMessage(const unsigned char messageID);
	//get the peer pointer
	RakNet::RakPeerInterface* getPeer();
	//show ip address
	void showIPAddress();
	//server initiative
	void initServer();
};
template<class messageRecvType>
messageRecvType  myNetwork::waitForMessage(const unsigned char messageID)
{
	bool getMessage = false;
	RakNet::Packet* packet;
	messageRecvType messageRecv;
	while (!getMessage)
	{
		for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			if (packet->data[0] == messageID)
			{
				getData(messageRecv, packet);
				peer->DeallocatePacket(packet);
				return messageRecv;
			}
			else
			{
				log("Message with identifier %i has arrived unexpectedly.\n", packet->data[0]);
			}
		}
	}
	return messageRecv;
}
template<class dataType>
void myNetwork::getData(dataType& dataRead, RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(dataRead);
}
template<class dataType>
void myNetwork::sendData(dataType& toSend, unsigned char messageType)
{
	RakNet::BitStream bsOut;
	bsOut.Write(messageType);
	bsOut.Write(toSend);
	peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}