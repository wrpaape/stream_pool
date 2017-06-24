#include "stream_pool/stream_pool.hpp" // StreamPool::*
#include <iostream>                    // std::cout



// STATIC DATA
// =============================================================================
const std::size_t StreamPool::worker_count = 10;



StreamPool::StreamPool()
    : ouput(std::cout.rdbuf())
{
    ouput << "StreamPool::StreamPool()" << std::endl;

    for (StreamSession &session : sessions)
        session(&output);
}

StreamPool::~StreamPool()
{
    ouput << "StreamPool::~StreamPool()" << std::endl;
}

void
StreamPool::start()
{


}