// file      : player.hxx
// copyright :

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <string>
#include <cstddef>
#include <odb/core.hxx>

#pragma db object
class player
{
public:
    player (const std::string& ip,
            const unsigned long long datetime,
            const std::string& platform)
        : ip_(ip), datetime_(datetime), platform_(platform)
    {

    }

    const std::string& ip () const {
        return ip_;
    }

    const unsigned long long& datetime () const {
        return datetime_;
    }

    const std::string& platform () const {
        return platform_;
    }

private:
    friend class odb::access;
    player () {}

#pragma db id auto
    unsigned long id_;
    std::string ip_;
    unsigned long long datetime_;
    std::string platform_;
};

#pragma db view object(player)
struct person_stat
{
#pragma db column("count(" + player::id_ + ")")
    std::size_t count;
};

#endif // PLAYER_HXX
