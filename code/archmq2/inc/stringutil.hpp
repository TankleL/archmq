#pragma once
#include <string>
#include <string_view>

namespace archmq2
{
    class StringUtil
    {
    public:
        static std::string_view readutil(const std::string& origin, char endchar, size_t beg = 0, size_t* end = nullptr)
        {
            size_t idx = beg;
            while (idx < origin.size() && origin[idx] != endchar)
            {
                ++idx;
            }

            if (end)
            {
                *end = idx;
            }

            return std::string_view(origin.c_str() + beg, idx - beg);
        }
    };
}

