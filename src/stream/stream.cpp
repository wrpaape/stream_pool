#include <utility>           // std::move
#include "stream/stream.hpp" // Stream::*



// STATIC DATA
// =============================================================================
static const std::chrono::seconds Stream::max_lifespan(15);
static const std::chrono::seconds Stream::max_downtime(5);

// fail roughly 1 in 100 queries
static const unsigned int Stream::expected_query_lifespan(100);


Stream::Stream()
    : failure_box(expected_query_lifespan),
{}


Stream::~Stream()
{}


Stream::start()
{
    continue_writing = true;
    idle_timeout     = time_point::max();
    expiry           = now() + max_lifespan;
}


bool
Stream::read(std::string &message)
{
    const std::chrono::seconds &timeout = std::min(idle_timeout,
                                                   expiry);

    const bool success = failure_box.query()
                      && dequeue_wait_until(message,
                                            timeout);
    if (success)
        idle_timeout = now() + max_downtime; // update timeout
    else
        continue_writing = false;            // make sure not to reset to true

    return success;
}


bool
Stream::write(std::string &&payload)
{
    const bool success = continue_writing;

    if (success)
        enqueue(std::move(payload));

    return success;
}


Stream::time_point
Stream::now()
{
    return std::chrono::system_clock::now();
}
