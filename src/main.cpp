// #include <iostream>
// #include <string>
// #include <rados/librados.hpp>
#include"../include/cephclient.h"
#include<stdlib.h>
#include<iostream>
int main(int argc, const char **argv)
{
std::string pool_name="rbd";
std::string cluster_name="ceph";
std::string user_name="client.admin";
std::string image_name="rbd_10";
std::string path="/etc/ceph/ceph.conf";
CephClient *client = new CephClient(pool_name,cluster_name,user_name,path,image_name)
int ret;
ret = client->InitPool();
if(ret!=0)
{
        std::cout<<"Cluster Init failed"<<std::endl;
        return EXIT_FAILURE;
}

ret = client->ImageOpen();
if(ret!=0)
{
   return 0;
}
client->Exit();
delete client;
return 0;
}
