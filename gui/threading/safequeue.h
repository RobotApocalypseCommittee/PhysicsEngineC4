//
// Created by Attoa on 25/06/2020.
//

#ifndef PHYSICS_C4_SAFEQUEUE_H
#define PHYSICS_C4_SAFEQUEUE_H

#include <condition_variable>
#include <queue>
#include <mutex>

namespace threading {
    template<class T>
    class SafeQueue {
    public:
        SafeQueue();

        void enqueue(T item);

        T dequeue();

    private:
        mutable std::mutex m;
        std::condition_variable c;
        std::queue<T> q;
    };
}

#include "safequeue.tpp"

#endif //PHYSICS_C4_SAFEQUEUE_H
