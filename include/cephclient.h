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
   CephClient(std::string pool_name,std::string cluster_name,std::string user_name,std::string path,std::string image_name);
   ~CephClient();
   int InitPool();
   int Exit();
   /******Imgae operation********/
   int ImageCreate(uint64_t size,int order);
   int ImageCreate(uint64_t size,int order,uint64_t features);
   int ImageRemove(std::string image_name);
   int ImageOpen();
   int Imagewrite(uint64_t setoff,const char *p_ch);
   int Imageread(std::string &buf,int buf_size);
   int Imagediscard(uint64_t offset,uint64_t len);
   int Imageaiodiscard(uint64_t offset,uint64_t len,void *arg,librbd::callback_t cb);
   int Imageaiowrite(std::string &buf,uint64_t off,size_t len,void *arg,librbd::callback_t cb);
   int Imageaioread(std::string &buf,uint64_t off,size_t len,void *arg,librbd::callback_t cb);
   /*********Image Snapshot Operation*****/
   int ImageCreateSnap(std::string snap_name);
   int ImageRemoveSnap(std::string snap_name);
   int ImageCloneSnap(std::string p_snap_name, std::string c_name, uint64_t features,int *c_order);
   int ImageSnapUnprotect(std::string p_snap_name);
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
   std::string pool_name;
   std::string cluster_name;
   std::string user_name;
   std::string path;
   std::string image_name;
};
#endif
