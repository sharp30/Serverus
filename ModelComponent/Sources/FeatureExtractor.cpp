//
// Created by ofir on 30/12///

#include "../Headers/FeatureExtractor.h"


const vector<float> FeatureExtractor::DEFAULT_LAMBDAS= {0.01,0.1,1,3,5};
//constructors

FeatureExtractor::FeatureExtractor(TimeManager *timeManager) : FeatureExtractor(FeatureExtractor::DEFAULT_LAMBDAS,timeManager)
{

}
FeatureExtractor::FeatureExtractor(vector<float> lambdas,TimeManager* timeManager):_channelJitter(timeManager),_socketSize(timeManager),_channelSize(timeManager)
{
    this->_lambdas = lambdas;
}

/*
This function extracts the vector stats for a specific packet
Input: pack - the packet to add :Packet
Output: The statistics vector :Vector<float>
*/
vector<float> FeatureExtractor::extractNewFeaturesVector(Packet pack) {
    //update
    string channelKey = this->_channelJitter.getStreamKey(pack);
    string socketKey = this->_socketSize.getStreamKey(pack);
    //string channelForeignKey = this->_channelSize.getForeignKey(pack);
    //string socketForeignKey = this->_socketSize.getForeignKey(pack);

    this->_channelSize.insertPacket(channelKey, (float)pack.getLength(), pack.getArrivalTime());
    this->_channelJitter.insertPacket(channelKey,  pack.getArrivalTime());
    this->_socketSize.insertPacket(socketKey, (float)pack.getLength(), pack.getArrivalTime());

    vector<float> res;
    vector<float> tmp;

    //should be merged
    tmp = this->_channelSize.getStatsOneDimension(channelKey); // returns 15 features
    res.insert(res.begin(), tmp.begin(), tmp.end());

    tmp = this->_channelSize.getStatsTwoDimensions(channelKey); // returns 20 features
    res.insert(res.begin(), tmp.begin(), tmp.end());

    //Jitter --> 1D only
    tmp = this->_channelJitter.getStatsOneDimension(channelKey); // returns 15 features
    res.insert(res.begin(), tmp.begin(), tmp.end());


    tmp = this->_socketSize.getStatsOneDimension(socketKey); // returns 15 featurs
    res.insert(res.begin(), tmp.begin(), tmp.end());

    tmp = this->_socketSize.getStatsTwoDimensions(socketKey); // returns 20 features
    res.insert(res.begin(), tmp.begin(), tmp.end());

    return res;

}
/*
 This function deletes all the streams a packets is belong
 Input: pack - the packet to remove : Packet
 Output: None
 */
void FeatureExtractor::deleteFromIncStats(Packet pack) {
    string channelKey = this->_channelJitter.getStreamKey(pack);
    string socketKey = this->_socketSize.getStreamKey(pack);

    this->_channelSize.removeStream(channelKey);
    this->_channelJitter.removeStream(channelKey);
    this->_socketSize.removeStream(socketKey);
}

