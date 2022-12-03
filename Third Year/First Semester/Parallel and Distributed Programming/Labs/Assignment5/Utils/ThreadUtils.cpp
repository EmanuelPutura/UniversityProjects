#include "ThreadUtils.h"

boost::asio::thread_pool ThreadUtils::threadPool(std::thread::hardware_concurrency());

boost::asio::thread_pool& ThreadUtils::getThreadPool() {
    return threadPool;
}
