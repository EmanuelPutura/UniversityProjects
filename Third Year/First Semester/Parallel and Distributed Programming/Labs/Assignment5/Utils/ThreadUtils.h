#pragma once

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

class ThreadUtils {
private:
    static boost::asio::thread_pool threadPool;
public:
    static boost::asio::thread_pool& getThreadPool();
};

