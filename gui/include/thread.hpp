/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** thread.hpp
*/

#ifndef THREAD_HPP
#define THREAD_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class ThreadSafeQueue {
public:
    void push(const std::string &item);
    bool pop(std::string &item);
    void waitAndPop(std::string &item);

private:
    std::queue<std::string> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

#endif // THREAD_HPP
