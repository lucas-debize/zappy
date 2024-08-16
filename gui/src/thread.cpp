/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-dorian.senecot
** File description:
** thread.cpp
*/

#include "thread.hpp"

void ThreadSafeQueue::push(const std::string &item) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(item);
    condition_.notify_one();
}

bool ThreadSafeQueue::pop(std::string &item) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return false;
    }
    item = queue_.front();
    queue_.pop();
    return true;
}

void ThreadSafeQueue::waitAndPop(std::string &item) {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this]() { return !queue_.empty(); });
    item = queue_.front();
    queue_.pop();
}
