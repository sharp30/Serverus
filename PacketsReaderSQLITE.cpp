#include "PacketsReaderSQLITE.h"

PacketsReaderSQLITE::PacketsReaderSQLITE(string filePath):PacketsReader(filePath)
{
    int status = 0; 
    status = sqlite3_open(filePath.c_str(), &this->_dbFile); 
  
    if (status) { 
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl; 
        throw std::exception(); 
    } 
    else
        std::cout << "Opened Database Successfully!" << std::endl; 

    this->_cursor = 1;
     
}

PacketsReaderSQLITE::~PacketsReaderSQLITE()
{
    sqlite3_close(this->dbFile);
}

Packet PacketsReaderSQLITE::getNextPacket() {
    //TODO: return the next packet
    return Packet();
}