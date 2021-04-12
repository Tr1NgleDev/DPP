#pragma once

#include <dpp/json_fwd.hpp>

namespace dpp {

/** @brief Returns a snowflake id from a json field value, if defined, else returns 0 
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
uint64_t SnowflakeNotNull(nlohmann::json* j, const char *keyname);

/** @brief Returns a string from a json field value, if defined, else returns an empty string.
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
std::string StringNotNull(nlohmann::json* j, const char *keyname);

/** @brief Returns a 64 bit unsigned integer from a json field value, if defined, else returns 0.
 * DO NOT use this for snowflakes, as usually snowflakes are wrapped in a string!
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
uint64_t Int64NotNull(nlohmann::json* j, const char *keyname);

/** @brief Returns a 32 bit unsigned integer from a json field value, if defined, else returns 0
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
uint32_t Int32NotNull(nlohmann::json* j, const char *keyname);

/** @brief Returns a 16 bit unsigned integer from a json field value, if defined, else returns 0
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
uint16_t Int16NotNull(nlohmann::json* j, const char *keyname);

/** @brief Returns an 8 bit unsigned integer from a json field value, if defined, else returns 0
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
uint8_t Int8NotNull(nlohmann::json* j, const char *keyname);

/** @brief Returns a boolean value from a json field value, if defined, else returns false
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
bool BoolNotNull(nlohmann::json* j, const char *keyname);

/** @brief Returns a time_t from an ISO8601 timestamp field in a json value, if defined, else returns
 * epoch value of 0.
 * @param j nlohmann::json instance to retrieve value from
 * @param keyname key name to check for a value
 */
time_t TimestampNotNull(nlohmann::json* j, const char *keyname);

/** @brief Base64 encode data.
 * @param buf Raw buffer
 * @param buffer_length Buffer length to encode
 */
std::string base64_encode(unsigned char const* buf, unsigned int buffer_length);

};