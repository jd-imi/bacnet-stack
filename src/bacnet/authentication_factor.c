/**
 * @file
 * @brief BACnet BACnetAuthenticationFactor structure and codecs
 * @author Nikola Jelic <nikola.jelic@euroicc.com>
 * @date 2015
 * @copyright SPDX-License-Identifier: MIT
 */
#include <stdint.h>
#include "bacnet/authentication_factor.h"
#include "bacnet/bacdcode.h"

/**
 * @brief Encode the BACnetAuthenticationFactor complex data
 * @param apdu  Pointer to the buffer for encoding into, or NULL for length
 * @param data  Pointer used for encoding the value
 * @return number of bytes encoded, or zero if unable to encode
 */
int bacapp_encode_authentication_factor(
    uint8_t *apdu, const BACNET_AUTHENTICATION_FACTOR *af)
{
    int len;
    int apdu_len = 0;

    len = encode_context_enumerated(apdu, 0, af->format_type);
    if (len < 0) {
        return -1;
    } else {
        apdu_len += len;
        if (apdu) {
            apdu += len;
        }
    }
    len = encode_context_unsigned(apdu, 1, af->format_class);
    if (len < 0) {
        return -1;
    } else {
        apdu_len += len;
        if (apdu) {
            apdu += len;
        }
    }
    len = encode_context_octet_string(apdu, 2, &af->value);
    if (len < 0) {
        return -1;
    } else {
        apdu_len += len;
    }

    return apdu_len;
}

/**
 * @brief Encode the BACnetAuthenticationFactor context tagged complex data
 * @param apdu  Pointer to the buffer for encoding into, or NULL for length
 * @param data  Pointer used for encoding the value
 * @return number of bytes encoded, or zero if unable to encode
 */
int bacapp_encode_context_authentication_factor(
    uint8_t *apdu, uint8_t tag, const BACNET_AUTHENTICATION_FACTOR *af)
{
    int len;
    int apdu_len = 0;

    len = encode_opening_tag(apdu, tag);
    apdu_len += len;
    if (apdu) {
        apdu += len;
    }
    len = bacapp_encode_authentication_factor(apdu, af);
    apdu_len += len;
    if (apdu) {
        apdu += len;
    }
    len = encode_closing_tag(apdu, tag);
    apdu_len += len;

    return apdu_len;
}

/**
 * @brief Decode the BACnetAuthenticationFactor complex data
 * @param apdu  Pointer to the buffer for decoding.
 * @param af  Pointer to the property decoded data to be stored
 * @return Bytes decoded or BACNET_STATUS_REJECT on error.
 */
int bacapp_decode_authentication_factor(
    const uint8_t *apdu, BACNET_AUTHENTICATION_FACTOR *af)
{
    int len;
    int apdu_len = 0;
    uint32_t format_type = af->format_type;
    BACNET_UNSIGNED_INTEGER unsigned_value = 0;

    if (decode_is_context_tag(&apdu[apdu_len], 0)) {
        len = decode_context_enumerated(&apdu[apdu_len], 0, &format_type);
        if (len < 0) {
            return -1;
        } else if (format_type < AUTHENTICATION_FACTOR_MAX) {
            apdu_len += len;
            af->format_type = (BACNET_AUTHENTICATION_FACTOR_TYPE)format_type;
        } else {
            /* FIXME: Maybe this should return BACNET_STATUS_REJECT */
            return -1;
        }
    } else {
        return -1;
    }

    if (decode_is_context_tag(&apdu[apdu_len], 1)) {
        len = decode_context_unsigned(&apdu[apdu_len], 1, &unsigned_value);
        if (len < 0) {
            return -1;
        } else {
            af->format_class = unsigned_value;
            apdu_len += len;
        }
    } else {
        return -1;
    }

    if (decode_is_context_tag(&apdu[apdu_len], 2)) {
        len = decode_context_octet_string(&apdu[apdu_len], 2, &af->value);
        if (len < 0) {
            return -1;
        } else {
            apdu_len += len;
        }
    } else {
        return -1;
    }

    return apdu_len;
}

/**
 * @brief Decode the context tagged BACnetAuthenticationFactor complex data
 * @param apdu  Pointer to the buffer for decoding.
 * @param tag  context tag number wrapping the complex data
 * @param af  Pointer to the property decoded data to be stored
 * @return Bytes decoded or BACNET_STATUS_REJECT on error.
 */
int bacapp_decode_context_authentication_factor(
    const uint8_t *apdu, uint8_t tag, BACNET_AUTHENTICATION_FACTOR *af)
{
    int len = 0;
    int section_length;

    if (decode_is_opening_tag_number(&apdu[len], tag)) {
        len++;
        section_length = bacapp_decode_authentication_factor(&apdu[len], af);

        if (section_length == -1) {
            len = -1;
        } else {
            len += section_length;
            if (decode_is_closing_tag_number(&apdu[len], tag)) {
                len++;
            } else {
                len = -1;
            }
        }
    } else {
        len = -1;
    }
    return len;
}
