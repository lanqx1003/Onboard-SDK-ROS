//
// Created by dji on 2020/5/8.
//

#include <dji_osdk_ros/dji_vehicle_node.h>
using namespace dji_osdk_ros;

void VehicleNode::SDKfromMobileDataCallback(Vehicle *vehicle, RecvContainer recvFrame, DJI::OSDK::UserData userData) {
  ((VehicleNode*)userData)->fromMobileDataCallback(recvFrame);
}

void VehicleNode::fromMobileDataCallback(RecvContainer recvFrame) {
  int dataLength = recvFrame.recvInfo.len - OpenProtocol::PackageMin - 2;
  if (dataLength <= 100) {
    DSTATUS( "Received mobile Data of len %d\n", recvFrame.recvInfo.len);
    dji_osdk_ros::MobileData mobile_data;
    mobile_data.data.resize(dataLength);
    for (int i=0; i<dataLength; i++)
    {
      mobile_data.data[i] = recvFrame.recvData.raw_ack_array[i];
    }
    from_mobile_data_publisher_.publish(mobile_data);
  }
}
