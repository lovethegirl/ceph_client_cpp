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
    std::cout<<"we just create an ioctx for rbd pool"<<std::endl;
    return 0;
}
int CephClient::Exit()
{
    image.close();
    rados.shutdown();
    return 0;
}


/*************************************************************************
 * 
 * 
 *                      image operation
 * 
 * 
 *************************************************************************/

int CephClient::ImageCreate(uint64_t size,int order)//order   
{
    int ret=rbd.create(io_ctx,name.image_name.c_str(),size,&order);
    if(ret<0)
    {
        std::cout<<"couldn't create an rbd image! error " << ret << std::endl;
        rados.shutdown();
        ret=EXIT_FAILURE;//1
        return ret;
    }
    else
    {
        std::cout << "we just created an rbd image" << std::endl;
    }
   /* ret = rbd.open(io_ctx,image,name.image_name.c_str(),NULL);
    if(ret<0)
    {
       std::cout << "couldn't open the rbd image! error " << ret << std::endl;
       rados.shutdown();
       ret = EXIT_FAILURE;
       return ret;
    }*/
    return 0;
}
int CephClient::ImageCreate(uint64_t size,int order,uint64_t features)
{
     int ret=rbd.create2(io_ctx,name.image_name.c_str(),size,features,&order);
    if(ret<0)
    {
        std::cout<<"couldn't create an rbd image! error " << ret << std::endl;
        rados.shutdown();
        ret=EXIT_FAILURE;//1
        return ret;
    }
    else
    {
        std::cout << "we just created an rbd image" << std::endl;
    }

    return 0;
}
//pool存在直接打开
int CephClient::ImageOpen()
{
    int ret = rbd.open(io_ctx,image,name.image_name.c_str(),NULL);
    if(ret<0)
    {
       std::cout << "couldn't open the rbd image! error " << ret << std::endl;
       rados.shutdown();
       ret = EXIT_FAILURE;
       return ret;
    }
    return 0;
}
int CephClient::ImageRemove(std::string imagename)
{
    int ret = rbd.remove(io_ctx,imagename.c_str());
    if(ret<0)
    {
        std::cout<<"couldn't remove an rbd image! error " << ret << std::endl;
        image.close();
        rados.shutdown();
        ret=EXIT_FAILURE;//1
        return ret;
    }
    return 0;
}


int CephClient::Imagewrite(const char *p_ch)
{
    size_t len = strlen(p_ch);
    ceph::bufferlist bl;
    bl.append(p_ch, len);

    int ret = image.write(0,len,bl);
    if(ret <0)
    {
        std::cout<<"could't write rbd to rados"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret=EXIT_FAILURE;
        return ret;
    }
    ret=0;
    return ret;
}

int CephClient::Imageread(std::string &buf,int buf_size)
{
     ceph::bufferlist bl;
     int ret;
     ret = image.read(0,buf_size,bl);
     if(ret<0)
     {
         std::cout<<"could't read rbd from rados"<<ret<<std::endl;
         image.close();
         rados.shutdown();
         ret = EXIT_FAILURE;
         return ret;
     }
     std::string tmp(bl.c_str(),ret);
     return 0;
}

/*************************************************************************
 * 
 * 
 *                      snapshot operation
 * 
 * 
 *************************************************************************/


int CephClient::ImageCreateSnap(std::string snap_name)
{
    std::cout<<"start create snap"<<std::endl;
    int ret = image.snap_create(snap_name.c_str());
    if(ret<0)
    {
        std::cout<<"could't create a snapshot"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret = EXIT_FAILURE;
        return ret;
    }
    return 0;
}

int CephClient::ImageRemoveSnap(std::string snap_name)
{
    std::cout<<"start remove snap"<<std::endl;
    int ret = image.snap_remove(snap_name.c_str());
    if(ret<0)
    {
        std::cout<<"could't remove a snapshot"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret = EXIT_FAILURE;
        return ret;
    }
    return 0;
}


int CephClient::ImageCloneSnap(std::string p_snap_name, std::string c_name, uint64_t features,int *c_order)
{
    /*****************
     * protect snapshot
     * ****************/
    int ret = image.snap_protect(p_snap_name.c_str());
    if(ret<0)
    {
        std::cout<<"could't protect a snapshot"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret = EXIT_FAILURE;
        return ret;
    }
    librados::IoCtx c_io_ctx;
    ret = rbd.clone(io_ctx,name.image_name.c_str(),p_snap_name.c_str(),
    c_io_ctx,c_name.c_str(),features,c_order);
    if(ret<0)
    {
        std::cout<<"could't clone a snapshot"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret = EXIT_FAILURE;
        return ret;
    }
    ret = image.flatten();
    if(ret<0)
    {
        std::cout<<"could't flatten a snapshot"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret = EXIT_FAILURE;
        return ret;
    }
    ret = image.snap_unprotect(p_snap_name.c_str());
    if(ret<0)
    {
        std::cout<<"could't unprotect a snapshot"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret = EXIT_FAILURE;
        return ret;        
    }
    return 0;
}
int CephClient::ImageSnapUnprotect(std::string p_snap_name)
{
    int ret = image.snap_unprotect(p_snap_name.c_str());
    if(ret<0)
    {
        std::cout<<"could't unprotect a snapshot"<<ret<<std::endl;
        image.close();
        rados.shutdown();
        ret = EXIT_FAILURE;
        return ret;        
    }
    return 0;
}
/*************************************************************************
 * 
 * 
 *                      object operation
 * 
 * 
 *************************************************************************/
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
    std::cout<<"we just write "<<object_name<<" to "<<name.pool_name<<std::endl;
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

