//
// Created by Attoa on 25/06/2020.
//

#ifndef PHYSICS_C4_SAFEQUEUE_TPP
#define PHYSICS_C4_SAFEQUEUE_TPP

namespace threading {
    template<class T>
    SafeQueue<T>::SafeQueue() : q(), m(), c() {}

    template<class T>
    void SafeQueue<T>::enqueue(T item) {
        std::lock_guard<std::mutex> lockGuard(m);
        q.push(item);
        c.notify_one();
    }

    template<class T>
    T SafeQueue<T>::dequeue() {
        std::unique_lock<std::mutex> uniqueLock(m);
        c.wait(uniqueLock, [=] { return !q.empty(); });

        T item = q.front();
        q.pop();
        return item;
    }
}

#endif //PHYSICS_C4_SAFEQUEUE_TPP
