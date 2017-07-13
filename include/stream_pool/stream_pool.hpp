#ifndef STREAM_POOL_STREAM_POOL_HPP
#define STREAM_POOL_STREAM_POOL_HPP

// EXTERNAL DEPENDENCIES
// =============================================================================
#include <string>                            // std::string
#include <blocking_queue/blocking_queue.hpp> // BlockingQueue
#include <stream_session/stream_session.hpp> // StreamSession
#include <stream_worker/stream_worker.hpp>   // StreamWorker

#ifdef BUILD_TESTING
#   include <gtest/gtest.h>                       // FRIEND_TEST
#else
#   define FRIEND_TEST(TEST_CASE_NAME, TEST_NAME) // disable
#endif // ifdef BUILD_TESTING



class StreamPool
{
public:
    StreamPool();
    ~StreamPool();
    void listen();


private:
    friend StreamSession;
    friend StreamWorker;

    void handle(const std::string &event);
    void start();
    void stop();
    void route(const std::string &id, const std::string &payload);
    void start_session(const std::string &id);
    void stop_session(const std::string &id);

    void withdraw(StreamSession::Record &entry);

    static const sd::size_t worker_count;


    BlockingQueue<StreamSession *> starting;
    StreamSession::Register        sessions;
    StreamWorker                   workers[worker_count];
}; // class StreamPool

#endif // ifndef STREAM_POOL_STREAM_POOL_HPP
