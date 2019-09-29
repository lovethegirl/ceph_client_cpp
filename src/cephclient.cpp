#include"../include/cephclient.h"
CephClient::CephClient()
{
    std::cout<<"start a CephClient"<<std::endl;
}
CephClient::~CephClient()
{
    std::cout<<"exit a CephClient"<<std::endl;
}
int CephClient::Init(std::string pool_name,std::string cluster_name,std::string user_name,std::string path,std::string image_name)
{
    //初始化pool image 名字
    name.pool_name=pool_name;
    name.image_name=image_name;
    int ret=0;
    //初始化集群
    ret = rados.init2(user_name.c_str(),cluster_name.c_str(),0);
    if(ret < 0)
    {
        std::cout<<"Couldn't initialize the cluster handle! error " << ret << std::endl;
        return EXIT_FAILURE;
    }
    else 
    {
        /* code */
         std::cout << "Created a cluster handle." << std::endl;
    }
    //读取配置文件
    ret = rados.conf_read_file(path.c_str());
    if(ret<0) {
        std::cout << "Couldn't read the Ceph configuration file! error " << ret << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Read the Ceph configuration file." << std::endl;
    } 
    /* {
   ret = rados.conf_parse_argv(argc, argv);
    if (ret < 0) {
        std::cerr << "Couldn't parse command line options! error " << ret << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Parsed command line options." << std::endl;
        }
    }*/
    //链接集群，初始化RadosClient
    ret = rados.connect();
    if(ret<0)
    {
        std::cout << "Couldn't connect to cluster! error " << ret << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Connected to the cluster." << std::endl;
    }
    
    // 初始化iotcx
    ret = rados.ioctx_create(pool_name.c_str(),io_ctx);
    if(ret<0)
    {
        ret=EXIT_FAILURE;
        std::cout<<"ioctx_create fail"<<std::endl;
        rados.shutdown();
        return ret;
    }
    std::cout<<"we just create an ioctx for out pool"<<std::endl;
    return 0;
}
int CephClient::Exit()
{
    rados.shutdown();
    return 0;
}

int CephClient::ImageCreate(uint64_t size,int order)
{
    return 0;
}
int CephClient::ObjectWriet(std::string object_name,std::string buff)
{
    librados::bufferlist bl;
    bl.append(buff);
    int ret = io_ctx.write_full(object_name,bl);
    if(ret<0)
    {
                std::cout<<"count't write object "<<std::endl;
                ret =  EXIT_FAILURE;
                rados.shutdown();
                return ret;
    }
    ret= EXIT_SUCCESS;
    return ret;
}
int CephClient::ObjectRead(std::string object_name,std::string & read_buff)
{
    librados::bufferlist read_buf;
    int read_len = 4194304; // this is way more than we need
    // allocate the completion from librados
    librados::AioCompletion *read_completion = librados::Rados::aio_create_completion();
    // send off the request.
    int ret = io_ctx.aio_read(object_name, read_completion, &read_buf, read_len, 0);
    if (ret < 0) {
      std::cerr << "couldn't start read object! error " << ret << std::endl;
      ret = EXIT_FAILURE;
      rados.shutdown();
      return ret;
    }
    // wait for the request to complete, and check that it succeeded.
    read_completion->wait_for_complete();
    ret = read_completion->get_return_value();
    if (ret < 0) {
      std::cerr << "couldn't read object! error " << ret << std::endl;
      ret = EXIT_FAILURE;
      rados.shutdown();
      return ret;
    }
    std::cout << "we read our object " << object_name
              << ", and got back " << ret << " bytes with contents\n";
    read_buf.copy(0, ret, read_buff);
    std::cout << read_buff << std::endl;
    return EXIT_SUCCESS;
}

int CephClient::ObjectRemove(std::string object_name)
{
     std::cout<<"start remove object "<<object_name<<std::endl;
  int ret=io_ctx.remove(object_name);
  {
          if(ret<0)
          {
                  std::cout<<"remove object fail"<<std::endl;
                  ret=EXIT_FAILURE;
                  rados.shutdown();
                  return ret;
          }
  }
  std::cout<<"remove obejct sucessful"<<std::endl;
  ret = EXIT_SUCCESS;
  return ret;
}

