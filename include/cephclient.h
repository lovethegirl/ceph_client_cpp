/*******************************************
 * 
 * Create at 9.27 2019 
 * Auth David Lee
 * Work Test for Ceph Client 
 * 
 * *****************************************/
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
   int ImageCreate(uint64_t size,int order,uint64_t features);
   int ImageRemove(std::string image_name);
   int ImageOpen();
   int Imagewrite(const char *p_ch);
   int Imageread(std::string &buf,int buf_size);
   /*********Image Snapshot Operation*****/
   int ImageCreateSnap(std::string snap_name);
   int ImageRemoveSnap(std::string snap_name);

   /********Rados Operation *******/
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
