#ifndef BPOOL_H
#define BPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>

#include "Btype.h"

namespace bh {

// 线程池-可获取任务函数的返回值
template <uint64 Tnum = 4>
class Bpool
{
public:
    // 加入并运行线程任务
    Bpool()
    {
        _run = true;
        for(uint64 i = 0; i < Tnum; i++) {
            _workers.emplace_back([=]() {
                while(true) {
                    std::function<void()> task = nullptr;
                    {
                        // 独占锁--获取队列任务
                        std::unique_lock<std::mutex> lock(_mut);

                        // 判断假唤醒--退出且队列为空
                        while(_tasks.empty() && _run) {
                            _cond.wait(lock);
                        }
                        if(_run == false && _tasks.empty()) {
                            return;
                        }
                        task = std::move(_tasks.front());
                        _tasks.pop();
                    }
                    if(task) {
                        task();
                    }
                }
            });
        }
    }

    // 释放线程池
    ~Bpool()
    {
        // 唤醒所有线程准备退出
        _run = false;
        _cond.notify_all();

        // 等待所有线程完成任务后释放
        for(std::thread &worker : _workers) {
            worker.join();
        }
    }

    // 加入任务
    template <typename Tfunc, typename... Targs>
    auto push(Tfunc &&func, Targs &&...args)
        -> std::future<typename std::result_of<Tfunc(Targs...)>::type>
    {
        // 分析任务函数返回类型
        using ret_type = typename std::result_of<Tfunc(Targs...)>::type;

        // 打包任务函数
        auto pack = std::bind(std::forward<Tfunc>(func), std::forward<Targs>(args)...);

        // 生成可执行的任务函数指针
        auto task = std::make_shared<std::packaged_task<ret_type()>>(pack);

        // 提前获取执行结果声明-从传入任务的线程延迟获取结果
        auto res = task->get_future();
        {
            // 包装成统一可执行的任务函数
            std::unique_lock<std::mutex> lock(_mut);
            std::function<void()> func = [task]() {
                (*task)();
            };
            if(_run) {
                _tasks.emplace(func);
            }
        }

        // 通知随机一个线程去执行任务
        _cond.notify_one();
        return res;
    }

protected:
    std::atomic<bool> _run;                   // 运行标记
    std::mutex _mut;                          // 线程池锁
    std::condition_variable _cond;            // 条件变量
    std::vector<std::thread> _workers;        // 线程容器
    std::queue<std::function<void()>> _tasks; // 任务队列
};

} // namespace bh

#endif // BPOOL_H
