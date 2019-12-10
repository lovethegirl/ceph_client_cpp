// #include <iostream>
// #include <string>
// #include <rados/librados.hpp>
#include"../include/cephclient.h"
#include<stdlib.h>
int main(int argc, const char **argv)
{
std::string hello("hello wrold");
std::string object_name("hw");
std::string pool_name="rbd-com";
std::string cluster_name="ceph";
std::string user_name="client.admin";
std::string image_name="disk01";
std::string path="/etc/ceph/ceph.conf";
CephClient client;
int ret;
ret = client.Init(pool_name,cluster_name,user_name,path,image_name);
if(ret!=0)
{
        std::cout<<"Cluster Init failed"<<std::endl;
        return EXIT_FAILURE;
}
/*****************************************
 * object write and read
 * **************************************/
/*ret = client.ObjectWriet(object_name,hello);
if(ret!=0)
{
        std::cout<<"objectwrite failed"<<std::endl;
        return EXIT_FAILURE;
}
std::string buff;
ret = client.ObjectRead(object_name,buff);
if(ret != 0)
{
        std::cout<<"objectread failed"<<std::endl;
        return EXIT_FAILURE;
}*/
//std::cout<<buff<<std::endl;
//ret = client.ObjectRemove(object_name);

ret = client.ImageOpen();
if(ret!=0)
{
	return 0;
}
for(int i=0;i<10;++i)
{
        for(int j=0;j<256;++j)
        {
        //string object=object_name+to_string(i)+"_"+to_string(j);
        srand(i+j);
        string str;
        for(int y=0;y<4096*1024;++y)
        {
                str=str+('A'+rand()%26);
        }
        ret = client.Imagewrite(i*1024*1024*1024+j*4096*1024,str.c_str());
        }
        if(ret!=0)
        {
        return ret;
        }
}
// const char * name = "my name is ljw";
// ret = client.Imagewrite(name);
// if(ret!=0)
// {
//         return ret;
// }
/**************************************************************
 *   image create 
 * *************************************************************/
/*ret = client.ImageCreate(1<<30,22,1);
ret = client.ImageCreate(1<<30,22);
ret = client.ImageOpen();
if(ret!=0)
{
	return 0;<<<<<<< HEAD
}*/
/*ret = client.ImageRemove(image_name);
}
 // ret = client.ImageOpen();
/* ret = client.ImageRemove(image_name);
if(ret!=0)
{
        return EXIT_FAILURE;
}*/




/*********************************************
 * create snapshot
 * ***********************************************/
/*ret = client.ImageOpen();
std::string snap_name="@snapshot1";
ret = client.ImageCreateSnap(snap_name);
if(ret!=0)
{
         return EXIT_FAILURE;
}*/

/*ret = client.ImageOpen();
ret =client.ImageRemoveSnap(snap_name);*/



// std::string ima_clo_name="ljw-rbd4";
// ret = client.ImageCloneSnap(snap_name,ima_clo_name,1,22);
// if(ret!=0)
// {
//         return EXIT_FAILURE;
// }
// ret = client.ImageRemove(name_s);
client.Exit();
return 0;
}
