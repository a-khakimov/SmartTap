#ifndef DATA_H
#define DATA_H

#include <stdint.h>

namespace tap {

typedef enum {
    _linux,
    _windows,
    _ios,
    _android,
    _webasm,
} platform;

const uint16_t StatisticsDataId = 0x7370;

#pragma pack(push, 1)
typedef struct {
    const uint16_t id = StatisticsDataId;
    uint8_t platform;
} StatisticsData;
#pragma pack(pop)

}


#endif // DATA_H
