#pragma once
#include "archmq-prereq.hpp"

namespace archmq
{
    class RandomUtil
    {
    public:
        static std::string alphabet_string(size_t length)
        {
            static std::uniform_int_distribution<int> rnddis(0, 51);
            static const std::string elements = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

            _ensure_random_engine();
            std::string result;

            for (size_t i = 0; i < length; ++i)
            {
                result.push_back(elements[rnddis(*_rndeng)]);
            }

            return result;
        }

        static std::string alphabet_string_variable_length(size_t maxlength, size_t minlength = 1)
        {
            std::uniform_int_distribution<size_t> rnddis(minlength, maxlength);

            _ensure_random_engine();
            size_t len = rnddis(*_rndeng);

            return alphabet_string(len);
        }

    private:
        static void _ensure_random_engine()
        {
            if (_rndeng == nullptr)
            {
                _rndeng = new std::default_random_engine(std::mt19937((unsigned int)std::time(0)));
            }
        }

    private:
        static std::default_random_engine* _rndeng;
    };
}
