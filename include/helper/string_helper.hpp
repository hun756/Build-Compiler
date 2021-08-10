#ifndef STRING_HELPER_HPP
#define STRING_HELPER_HPP

#include <string>
#include <algorithm>

namespace Helper
{
    class String
    {
    public:
        static bool isNullOrWhiteSpace(const std::string &str)
        {
            return str.empty() || std::all_of(
                                      str.begin(),
                                      str.end(),
                                      [](char c)
                                      {
                                          return ::isspace(c);
                                      });
        }
    };
} // namespace sTRİNG

#endif /* end of include guard :  STRING_HELPER_HPP */
