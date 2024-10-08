/**
 * @file
 * @brief API for basic BACnet Access Rights Objects implementation.
 * @author Nikola Jelic <nikola.jelic@euroicc.com>
 * @date 2015
 * @copyright SPDX-License-Identifier: MIT
 */
#ifndef BACNET_BASIC_OBJECT_ACCESS_RIGHTS_H
#define BACNET_BASIC_OBJECT_ACCESS_RIGHTS_H

#include <stdbool.h>
#include <stdint.h>
/* BACnet Stack defines - first */
#include "bacnet/bacdef.h"
/* BACnet Stack API */
#include "bacnet/bacerror.h"
#include "bacnet/bacdevobjpropref.h"
#include "bacnet/access_rule.h"
#include "bacnet/rp.h"
#include "bacnet/wp.h"

#ifndef MAX_ACCESS_RIGHTSS
#define MAX_ACCESS_RIGHTSS 4
#endif

#ifndef MAX_NEGATIVE_ACCESS_RIGHTS_RULES
#define MAX_NEGATIVE_ACCESS_RIGHTS_RULES 4
#endif

#ifndef MAX_POSITIVE_ACCESS_RIGHTS_RULES
#define MAX_POSITIVE_ACCESS_RIGHTS_RULES 4
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
    uint32_t global_identifier;
    BACNET_RELIABILITY reliability;
    bool enable;
    uint32_t negative_access_rules_count, positive_access_rules_count;
    BACNET_ACCESS_RULE
    negative_access_rules[MAX_NEGATIVE_ACCESS_RIGHTS_RULES];
    BACNET_ACCESS_RULE
    positive_access_rules[MAX_POSITIVE_ACCESS_RIGHTS_RULES];
} ACCESS_RIGHTS_DESCR;

BACNET_STACK_EXPORT
void Access_Rights_Property_Lists(
    const int **pRequired, const int **pOptional, const int **pProprietary);
BACNET_STACK_EXPORT
bool Access_Rights_Valid_Instance(uint32_t object_instance);
unsigned Access_Rights_Count(void);
BACNET_STACK_EXPORT
uint32_t Access_Rights_Index_To_Instance(unsigned index);
BACNET_STACK_EXPORT
unsigned Access_Rights_Instance_To_Index(uint32_t instance);
BACNET_STACK_EXPORT
bool Access_Rights_Object_Instance_Add(uint32_t instance);

BACNET_STACK_EXPORT
bool Access_Rights_Object_Name(
    uint32_t object_instance, BACNET_CHARACTER_STRING *object_name);
BACNET_STACK_EXPORT
bool Access_Rights_Name_Set(uint32_t object_instance, char *new_name);

BACNET_STACK_EXPORT
int Access_Rights_Read_Property(BACNET_READ_PROPERTY_DATA *rpdata);
BACNET_STACK_EXPORT
bool Access_Rights_Write_Property(BACNET_WRITE_PROPERTY_DATA *wp_data);

BACNET_STACK_EXPORT
uint32_t Access_Rights_Create(uint32_t object_instance);
BACNET_STACK_EXPORT
bool Access_Rights_Delete(uint32_t object_instance);
BACNET_STACK_EXPORT
void Access_Rights_Cleanup(void);
BACNET_STACK_EXPORT
void Access_Rights_Init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
