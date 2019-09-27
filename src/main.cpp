// #include <iostream>
// #include <string>
// #include <rados/librados.hpp>
#include"../include/cephclient.h"
int main(int argc, const char **argv)
{
//         int ret = 0;
//         /* Declare the cluster handle and required variables. */
//         librados::Rados rados;
//         char cluster_name[] = "ceph";
//         char user_name[] = "client.admin";
//         uint64_t flags = 0;
//         const char * pool_name="pool1";
//         std::string hello("hello wrold");
//         std::string object_name("hw");
//         librados::IoCtx io_ctx;
//         /* Initialize the cluster handle with the "ceph" cluster name and "client.admin" user */
//         {
//                 ret = rados.init2(user_name, cluster_name, flags);
//                 if (ret < 0) {
//                         std::cerr << "Couldn't initialize the cluster handle! error " << ret << std::endl;
//                         return EXIT_FAILURE;
//                 } else {
//                         std::cout << "Created a cluster handle." << std::endl;
//                 }
//         }

//         /* Read a Ceph configuration file to configure the cluster handle. */
//         {
//                 ret = rados.conf_read_file("/etc/ceph/ceph.conf");
//                 if (ret < 0) {
//                         std::cerr << "Couldn't read the Ceph configuration file! error " << ret << std::endl;
//                         return EXIT_FAILURE;
//                 } else {
//                         std::cout << "Read the Ceph configuration file." << std::endl;
//                 }
//         }

//         /* Read command line arguments */
//         {
//                 ret = rados.conf_parse_argv(argc, argv);
//                 if (ret < 0) {
//                         std::cerr << "Couldn't parse command line options! error " << ret << std::endl;
//                         return EXIT_FAILURE;
//                 } else {
//                         std::cout << "Parsed command line options." << std::endl;
//                 }
//         }

//         /* Connect to the cluster */
//         {
//                 ret = rados.connect();
//                 if (ret < 0) {
//                         std::cerr << "Couldn't connect to cluster! error " << ret << std::endl;
//                         return EXIT_FAILURE;
//                 } else {
//                         std::cout << "Connected to the cluster." << std::endl;
//                 }
//         }
//         std::cout<<"this is a start"<<std::endl;

//        /* ret = rados.pool_create(pool_name);
//         if(ret<0)
//         {
//            std::cout<<"countn't create pool"<<std::endl;
//            return EXIT_FAILURE;                
//         }*/
//         //std::cout<<"we jsut create a new pool named"<<pool_name<<std::endl;

//         ret = rados.ioctx_create(pool_name,io_ctx);
//         if(ret<0)
//         {
//                 std::cout<<"ioctx_create fail"<<std::endl;
//                 ret = EXIT_FAILURE;
//               //  rados.pool_delete(pool_name);
//                 rados.shutdown();
//                 return ret;
//         }
//         std::cout<<"we just create an ioctx for out pool"<<std::endl;

//         librados::bufferlist bl;
//         bl.append(hello);

//         ret = io_ctx.write_full(object_name,bl);
//         if(ret<0)
//         {
//                 std::cout<<"count't write object "<<std::endl;
//                 ret =  EXIT_FAILURE;
//                // rados.pool_delete(pool_name);
//                 rados.shutdown();
//                 return ret;
//         }
//         std::cout<<"we jsut crote new object"<<object_name<<std::endl;

//         {
//     librados::bufferlist read_buf;
//     int read_len = 4194304; // this is way more than we need
//     // allocate the completion from librados
//     librados::AioCompletion *read_completion = librados::Rados::aio_create_completion();
//     // send off the request.
//     ret = io_ctx.aio_read(object_name, read_completion, &read_buf, read_len, 0);
//     if (ret < 0) {
//       std::cerr << "couldn't start read object! error " << ret << std::endl;
//       ret = EXIT_FAILURE;
//      // rados.pool_delete(pool_name); 
//       rados.shutdown();
//       return ret;
//     }
//     // wait for the request to complete, and check that it succeeded.
//     read_completion->wait_for_complete();
//     ret = read_completion->get_return_value();
//     if (ret < 0) {
//       std::cerr << "couldn't read object! error " << ret << std::endl;
//       ret = EXIT_FAILURE;
//     //  rados.pool_delete(pool_name);
//       rados.shutdown();
//       return ret;
//     }
//     std::cout << "we read our object " << object_name
//               << ", and got back " << ret << " bytes with contents\n";
//     std::string read_string;
//     read_buf.copy(0, ret, read_string);
//     std::cout << read_string << std::endl;
//   }

//   std::cout<<"start remove object "<<object_name<<std::endl;
//   ret=io_ctx.remove(object_name);
//   {
//           if(ret<0)
//           {
//                   std::cout<<"remove object fail"<<std::endl;
//                   ret=EXIT_FAILURE;
//                   rados.shutdown();
//                   return ret;
//           }
//   }
//   std::cout<<"remove obejct sucessful"<<std::endl;
//   ret = EXIT_SUCCESS;
//  /* int delete_ret=rados.pool_delete(pool_name);
//   if(delete_ret<0)
//   {
//           std::cout<<"we faild to delete our test pool"<<std::endl;
//           ret=EXIT_FAILURE;
//   }*/
//   rados.shutdown();
//   return ret;

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
client.Exit();
}
