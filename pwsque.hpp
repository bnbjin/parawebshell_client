#pragma once

#include <deque>
#include <mutex>


namespace pws {

/*
FIFO
*/
template <typename value_type>
class pwsque
{
    pwsque(const pwsque&) = delete;
    pwsque(const pwsque&&) = delete;
    pwsque& operator=(const pwsque&) = delete;
    pwsque&& operator=(const pwsque&&) = delete;

public:
    pwsque(size_t sz) : _que(sz), _que_mtx() {}

    ~pwsque() {}

    void push(const value_type &val)
    {
        std::lock_guard<std::mutex>(mtx);

        _que.push_back(val);
    }

    value_type&& pop()
    {
        std::lock_guard<std::mutex>(mtx);

        value_type&& result = _que.front();
        _que.pop_front();

        return result;
    }

private:
    std::deque<value_type> _que;
    std::mutex _que_mtx;
};

}
