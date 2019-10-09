// #include <iostream>
// #include <string>
// #include <rados/librados.hpp>
#include"../include/cephclient.h"
int main(int argc, const char **argv)
{
std::string hello("hello wrold");
std::string object_name("hw");
std::string pool_name="pool1";
std::string cluster_name="ceph";
std::string user_name="client.admin";
std::string image_name="rbd2";
std::string path="/etc/ceph/ceph.conf";
CephClient client;
int ret;
ret = client.Init(pool_name,cluster_name,user_name,path,image_name);
if(ret!=0)
{
        std::cout<<"Cluster Init failed"<<std::endl;
        return EXIT_FAILURE;
}
// ret = client.ObjectWriet(object_name,hello);
// if(ret!=0)
// {
//         std::cout<<"objectwrite failed"<<std::endl;
//         return EXIT_FAILURE;
// }
// std::string buff;
// ret = client.ObjectRead(object_name,buff);
// if(ret != 0)
// {
//         std::cout<<"objectread failed"<<std::endl;
//         return EXIT_FAILURE;
// }
// std::cout<<buff<<std::endl;
// ret = client.ObjectRemove(object_name);
// if(ret!=0)
// {
//         std::cout<<"objectremove failed"<<std::endl;
//         return ret;
// }
std::string snap_name="rbd-ljw@snapshot1";
ret = client.ImageCreateSnap(snap_name);
if(ret!=0)
{
        return ret;
}
client.Exit();
}
