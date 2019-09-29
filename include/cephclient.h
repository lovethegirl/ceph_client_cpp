#include <rados/librados.hpp>
#include <rbd/librbd.hpp>
#include <iostream>
#include <string>
#ifndef CEPH_CLIENT_H
#define CEPH_CLIENT_H
typedef struct  RBD_ID
{
    std::string pool_name;
    std::string image_name;
}Name;
class CephClient
{
   public:
   CephClient();
   ~CephClient();
   int Init(std::string pool_name,std::string cluster_name,std::string user_name,std::string path,std::string image_name);
   int Exit();
   /******Imgae operation********/
   int ImageCreate(uint64_t size,int order);
//    int ImageRemove(std::string image_name);
//    int ImageOpen();
//    int Imagewrite();
//    int Imageread();
//    int ImageCreateSnap(std::string snap_name);
   

   /********Rados Opearation *******/
   int ObjectWriet(std::string object_name,std::string buff);
   int ObjectRead(std::string object_name,std::string & read_buff);
   int ObjectRemove(std::string object_name);
 private:
   Name name;
   librados::Rados rados;
   librados::IoCtx io_ctx;
   librbd::RBD rbd;
   librbd::Image image;
   
};
#endif
