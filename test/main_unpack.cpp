
#include <iostream>

#include <unistd.h>
#include "Tlog.h"

#include "hv/TcpServer.h"
#include "hv/TcpClient.h"
#include "Ttimer.h"
#include "Ftime.h"
#include "Tunpack.h"

using namespace bhtools;
using namespace hv;



#define v1flogd(...) BHLOG_MAKE_L4D((*_v1file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
#define v1flogi(...) BHLOG_MAKE_L4I((*_v1file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
#define v1flogw(...) BHLOG_MAKE_L4W((*_v1file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
#define v1floge(...) BHLOG_MAKE_L4E((*_v1file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)

#define v2flogd(...) BHLOG_MAKE_L4D((*_v2file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
#define v2flogi(...) BHLOG_MAKE_L4I((*_v2file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
#define v2flogw(...) BHLOG_MAKE_L4W((*_v2file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)
#define v2floge(...) BHLOG_MAKE_L4E((*_v2file4_),(*_sp_end_),_sp_level4_,__VA_ARGS__)

Tlog_file4 *_v1file4_ = new Tlog_file4;
Tlog_file4 *_v2file4_ = new Tlog_file4;
static Ttimer<> *_sp_timer_ = new Ttimer<>;


struct TestTcpServer : public TcpServer
{
    int _port = 5555;
    // Tunpack_del t;
    Tunpack_len t;

    int Run()
    {
        int listenfd = this->createsocket(_port);
        if(listenfd >= 0)
        {

            t.read_cb([](const std::string &ctx){
                v1flogd("onMessage= " << ctx);
            });


            v1flogd("TestTcpServer=" $(_port) $(listenfd));
            this->onConnection = [](const SocketChannelPtr& channel) {
                v1flogd("onConnection= " $(channel->peeraddr()) $(channel->fd()));
            };
            this->onMessage = [=](const SocketChannelPtr& channel, Buffer* buf) {
                // v1flogd("onMessage= " << std::string((char*)buf->data(),buf->size()));
                t.unpack(std::string((char*)buf->data(),buf->size()),true);


            };

            this->setThreadNum(4);
            this->start();

            std::this_thread::sleep_for(std::chrono::seconds(10));
            this->closesocket();
        }
        return listenfd;
    }
};

struct TestTcpClient : public TcpClient
{
    int _port = 5555;
    // Tunpack_del t;
    Tunpack_len t;

    void Send()
    {
        std::string s = "helow world";
        for(int i=0;i<10000;i++)
        {
            this->send(t.make(s));
            // this->send(s);
        }
    }
    int Run()
    {
        int connfd = this->createsocket(_port);
        if(connfd >= 0)
        {
            v2flogd("TestTcpClient=" $(_port) $(connfd));
            this->onConnection = [=](const SocketChannelPtr& channel) {
                v2flogd("onConnection= " $(channel->peeraddr()) $(channel->fd()));
 
                _sp_timer_->push(2*1000,[=](size_t){
                    v2flogd("== Send ==");
                    Send();
                },5);
            };
            this->onMessage = [=](const SocketChannelPtr& channel, Buffer* buf) {
                v2flogd("onMessage= " << std::string((char*)buf->data(),buf->size()));
            };
            this->start();

            std::this_thread::sleep_for(std::chrono::seconds(10));
            this->closesocket();
        }
        return connfd;
    }
};

void test_1()
{
    vlogd("== begin ==");
    if(fork() == 0)
    {
        TestTcpServer sev;
        int ret = sev.Run();
        v1floge($(ret));

        // std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    else 
    {
        TestTcpClient cli;
        int ret = cli.Run();
        v2floge($(ret));
    }
}

void test_2()
{

    {
        vlogw($(Tunfd_delimit()._delimit));
        Tunf_delimit<Tunfd_delimit> t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });

        {
            std::string s = "11111" + Tunfd_delimit()._delimit;
            t.unpack(s);
        }
        {
            std::string s = "22222" + Tunfd_delimit()._delimit + "22222" + Tunfd_delimit()._delimit;
            t.unpack(s);
        }
        {
            std::string s = "33333" + Tunfd_delimit()._delimit + "33333";
            t.unpack(s);
        }
        {
            std::string s = Tunfd_delimit()._delimit + "44444" + Tunfd_delimit()._delimit + "44444";
            t.unpack(s);
        }
        {
            std::string s = Tunfd_delimit()._delimit;
            t.unpack(s);
        }
    }

    {
        struct Tunfd_delimit_v1
        {
            std::string _delimit = "##&&";
        };
        vlogw($(Tunfd_delimit_v1()._delimit));

        Tunf_delimit<Tunfd_delimit_v1> t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });

        {
            std::string s = "11111" + Tunfd_delimit_v1()._delimit;
            t.unpack(s);
        }
        {
            std::string s = "22222" + Tunfd_delimit_v1()._delimit + "22222" + Tunfd_delimit_v1()._delimit;
            t.unpack(s);
        }
        {
            std::string s = "33333" + Tunfd_delimit_v1()._delimit + "33333";
            t.unpack(s);
        }
        {
            std::string s = Tunfd_delimit_v1()._delimit + "44444" + Tunfd_delimit_v1()._delimit + "44444";
            t.unpack(s);
        }
        {
            std::string s = Tunfd_delimit_v1()._delimit;
            t.unpack(s);
        }
        {
            std::string s = "55555##55555&&55555##";
            t.unpack(s);
        }
        {
            std::string s = "&&66666##66666" + Tunfd_delimit_v1()._delimit;
            t.unpack(s);
        }
    }
}

void test_3()
{
    Tunf_length<> t;
    t.read_cb([](const std::string &ctx){
        vlogd("read: " $(ctx));
    });

    {
        std::string s = "111111";
        t.unpack(Tunfmake_length<>::make(s));
    }
    {
        std::string s = "11";
        t.unpack(Tunfmake_length<>::make(s));
    }
    {
        std::string s = "";
        t.unpack(Tunfmake_length<>::make(s));
    }
    {
        std::string s = "1";
        t.unpack(Tunfmake_length<>::make(s));
    }
    {
        std::string s = "asdoiahsdiuahsduagegbda27dyabshd";
        t.unpack(Tunfmake_length<>::make(s));
    }
}

void test_4()
{
    {
        Tunf_delimit<> t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });

        {
            std::string s = "111111";
            t.unpack(Tunfmake_delimit<>::make(s));
        }
        {
            std::string s = "11";
            t.unpack(Tunfmake_delimit<>::make(s));
        }
        {
            std::string s = "";
            t.unpack(Tunfmake_delimit<>::make(s));
        }
        {
            std::string s = "1";
            t.unpack(Tunfmake_delimit<>::make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduagegbda27dyabshd";
            t.unpack(Tunfmake_delimit<>::make(s));
        }
    }
    {
        struct Tunfd_delimit_v1
        {
            std::string _delimit = "##&&";
        };

        Tunf_delimit<Tunfd_delimit_v1> t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });

        {
            std::string s = "111111";
            t.unpack(Tunfmake_delimit<Tunfd_delimit_v1>::make(s));
        }
        {
            std::string s = "11";
            t.unpack(Tunfmake_delimit<Tunfd_delimit_v1>::make(s));
        }
        {
            std::string s = "";
            t.unpack(Tunfmake_delimit<Tunfd_delimit_v1>::make(s));
        }
        {
            std::string s = "1";
            t.unpack(Tunfmake_delimit<Tunfd_delimit_v1>::make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduagegbda27dyabshd";
            t.unpack(Tunfmake_delimit<Tunfd_delimit_v1>::make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduag##&&egbda27dyabshd";
            t.unpack(Tunfmake_delimit<Tunfd_delimit_v1>::make(s));
        }
    }
}

void test_5()
{
    {
        Tunpack<Tunf_length,Tunfmake_length,Tunfd_length> t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });

        {
            std::string s = "111111";
            t.unpack(t.make(s));
        }
        {
            std::string s = "11";
            t.unpack(t.make(s));
        }
        {
            std::string s = "";
            t.unpack(t.make(s));
        }
        {
            std::string s = "1";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduagegbda27dyabshd";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduag\n&&egbda27dyabshd";
            t.unpack(t.make(s));
        }
    }

    {
        Tunpack<Tunf_delimit,Tunfmake_delimit,Tunfd_delimit> t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });
        vlogw("");

        {
            std::string s = "111111";
            t.unpack(t.make(s));
        }
        {
            std::string s = "11";
            t.unpack(t.make(s));
        }
        {
            std::string s = "";
            t.unpack(t.make(s));
        }
        {
            std::string s = "1";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduagegbda27dyabshd";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduag\negbda27dyabshd";
            t.unpack(t.make(s));
        }
    }
}

void test_6()
{
    {
        Tunpack_del t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });
        vlogw("");

        {
            std::string s = "111111";
            t.unpack(t.make(s));
        }
        {
            std::string s = "11";
            t.unpack(t.make(s));
        }
        {
            std::string s = "";
            t.unpack(t.make(s));
        }
        {
            std::string s = "1";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduagegbda27dyabshd";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduag\negbda27dyabshd";
            t.unpack(t.make(s));
        }
    }

    {
        Tunpack_len t;
        t.read_cb([](const std::string &ctx){
            vlogd("read: " $(ctx));
        });
        vlogw("");

        {
            std::string s = "111111";
            t.unpack(t.make(s));
        }
        {
            std::string s = "11";
            t.unpack(t.make(s));
        }
        {
            std::string s = "";
            t.unpack(t.make(s));
        }
        {
            std::string s = "1";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduagegbda27dyabshd";
            t.unpack(t.make(s));
        }
        {
            std::string s = "asdoiahsdiuahsduag\negbda27dyabshd";
            t.unpack(t.make(s));
        }
    }
}

void test_7()
{
    int size = 1000*10000;

    // 一千万次大约6秒-Tunpack_len稍微快一点
    {

        Tunpack_len t;
        t.read_cb([](const std::string &ctx){
        });
        Ftimel time;
        for(int i=0;i<size;i++)
        {
            std::string s = "hellow world" + std::to_string(i);
            t.unpack(t.make(s));
        }
        vlogd($(time.to_string()));  
    }
    {
        Tunpack_del t;
        t.read_cb([](const std::string &ctx){
        });
        Ftimel time;
        for(int i=0;i<size;i++)
        {
            std::string s = "hellow world" + std::to_string(i);
            t.unpack(t.make(s));
        }
        vlogd($(time.to_string())); 
    }
}

int main(int argc, char *argv[])
{
    _v1file4_->_out.reopen("unpack_server.log");
    _v2file4_->_out.reopen("unpack_client.log");

    // test_1();   
    // test_2();   
    // test_3();   
    // test_4();   
    // test_5();   
    // test_6();   
    test_7();

    return 0;
}