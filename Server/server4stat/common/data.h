#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <QString>

namespace tap {

typedef enum {
    _linux,
    _windows,
    _ios,
    _android,
    _webasm,
} platform;

const uint16_t PlayerInfomationId = 0x7370;
const uint16_t StatisticsDataId = 0x7371;

#pragma pack(push, 1)
typedef struct {
    uint16_t id;
    uint8_t platform;
} RequestHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    qint64 timestamp;
    QString platform;
    QString ip;
} StatisticsData;
#pragma pack(pop)

}

#endif // DATA_H
