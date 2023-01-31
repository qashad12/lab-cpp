/* Introduction class.
 * @file
 * @date 2021-09-04
 * @author Anonymous
 */

#ifndef __INTRODUCTION_HPP__
#define __INTRODUCTION_HPP__

#include <string>

class lol {};
//{
class introduction
{
public:
    std::string_view name() const
    {
        return "Gleb";
    }

    std::string_view surename() const
    {
        return "Moroz";
    }

    std::string fullname() const
    {
        return _full_name;
    }

private:
    const char *_full_name = "Gleb Moroz";
};
//}

#endif // __INTRODUCTION_HPP__
