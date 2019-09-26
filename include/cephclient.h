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
   int init(Name n);



   librados::Rados rados;
   librados::IoCtx io_ctx;
   librbd::RBD rbd;
   librbd::Image image;
};
#endif