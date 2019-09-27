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
    name.pool_name=pool_name;
    name.image_name=image_name;
    int ret=0;
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
    ret = rados.conf_read_file(path.c_str());
    if(ret<0) {
        std::cout << "Couldn't read the Ceph configuration file! error " << ret << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Read the Ceph configuration file." << std::endl;
    }
    //{
/*    ret = rados.conf_parse_argv(argc, argv);
    if (ret < 0) {
        std::cerr << "Couldn't parse command line options! error " << ret << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "Parsed command line options." << std::endl;
        }
    }*/
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
