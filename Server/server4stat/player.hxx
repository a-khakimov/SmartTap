// file      : player.hxx
// copyright :

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <string>
#include <odb/core.hxx>
#include <QtCore/QDateTime>

#pragma db object
class player
{
public:
    player(const std::string& ip,
            const QDateTime datetime,
            const std::string& platform)
        : ip_(ip), timestamp_(datetime), platform_(platform)
    {

    }

    const std::string& ip() const {
        return ip_;
    }

    QDateTime datetime() const {
        return timestamp_;
    }

    const std::string& platform() const {
        return platform_;
    }

private:
    friend class odb::access;
    player () {}

#pragma db id auto
    unsigned long id_;
    QDateTime timestamp_;
    std::string ip_;
    std::string platform_;
};

#pragma db view object(player)
struct player_stat
{
#pragma db column("count(" + player::id_ + ")")
    std::size_t count;
};

#endif // PLAYER_HXX
