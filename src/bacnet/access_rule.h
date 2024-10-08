/**
 * @file
 * @brief BACnetAccessRule service encode and decode
 * @author Nikola Jelic <nikola.jelic@euroicc.com>
 * @date 2015
 * @copyright SPDX-License-Identifier: MIT
 */
#ifndef BACNET_ACCESS_RULE_H
#define BACNET_ACCESS_RULE_H

#include <stdbool.h>
#include <stdint.h>
/* BACnet Stack defines - first */
#include "bacnet/bacdef.h"
/* BACnet Stack API */
#include "bacnet/bacdevobjpropref.h"

typedef enum {
    TIME_RANGE_SPECIFIER_SPECIFIED = 0,
    TIME_RANGE_SPECIFIER_ALWAYS = 1,
    TIME_RANGE_SPECIFIER_MAX = 2
} BACNET_ACCESS_RULE_TIME_RANGE_SPECIFIER;

typedef enum {
    LOCATION_SPECIFIER_SPECIFIED = 0,
    LOCATION_SPECIFIER_ALL = 1,
    LOCATION_SPECIFIER_MAX = 2
} BACNET_ACCESS_RULE_LOCATION_SPECIFIER;

typedef struct BACnetAccessRule {
    BACNET_ACCESS_RULE_TIME_RANGE_SPECIFIER time_range_specifier;
    BACNET_DEVICE_OBJECT_PROPERTY_REFERENCE time_range;
    BACNET_ACCESS_RULE_LOCATION_SPECIFIER location_specifier;
    BACNET_DEVICE_OBJECT_REFERENCE location;
    bool enable;
} BACNET_ACCESS_RULE;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

BACNET_STACK_EXPORT
int bacapp_encode_access_rule(uint8_t *apdu, const BACNET_ACCESS_RULE *rule);
BACNET_STACK_DEPRECATED("Use bacnet_access_rule_decode() instead")
BACNET_STACK_EXPORT
int bacapp_decode_access_rule(const uint8_t *apdu, BACNET_ACCESS_RULE *rule);

BACNET_STACK_EXPORT
int bacnet_access_rule_decode(
    const uint8_t *apdu, size_t apdu_size, BACNET_ACCESS_RULE *data);

BACNET_STACK_EXPORT
bool bacnet_access_rule_from_ascii(BACNET_ACCESS_RULE *value, const char *argv);
BACNET_STACK_EXPORT
bool bacnet_access_rule_same(
    const BACNET_ACCESS_RULE *value1, const BACNET_ACCESS_RULE *value2);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
