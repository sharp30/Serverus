#include "Packet.h"


Packet::Packet(Time arrivalTime, string sourceIP, string destIP, int sourcePort, 
            int destPort, int length, bool protocol, string data)
{
    this->_arrivalTime = arrivalTime;
    this->_sourceIP = sourceIP;
    this->_destIP = destIP;
    this->_sourcePort = sourcePort;
    this->_destPort = destPort;
    this->_length = length;
    this->_protocol = protocol;
    this->_data = data;
}

void Packet::setArrivalTime(Time arrivalTime) { this->_arrivalTime = arrivalTime; } 
Time Packet::getArrivalTime() { return this->_arrivalTime; }
void Packet::setSourceIP(string sourceIP) { this->_sourceIP = sourceIP; } 
string Packet::getSourceIP() { return this->_sourceIP; }
void Packet::setDestIP(string destIP) { this->_destIP = destIP; } 
string Packet::getDestIP() { return this->_destIP; }
void Packet::setSourcePort(int sourcePort) { this->_sourcePort = sourcePort; } 
int Packet::getSourcePort() { return this->_sourcePort; }
void Packet::setDestPort(int destPort) { this->_destPort = destPort; } 
int Packet::getDestPort() { return this->_destPort; }
void Packet::setLength(int length) { this->_length = length; } 
int Packet::getLength() { return this->_length; }
void Packet::setProtocol(bool protocol) { this->_protocol = protocol; } 
bool Packet::getProtocol() { return this->_protocol; }
void Packet::setData(string data) { this->_data = data; } 
string Packet::getData() { return this->_data; }