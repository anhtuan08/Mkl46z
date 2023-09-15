#ifndef HEADER_H
#define HEADER_H

/*******************************************************************************
*Includes
*******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
*enum definition
*******************************************************************************/
typedef enum {
    HEXA_VALID,
    HEXA_INVALID
} HexaCheckResult;


typedef enum {
    CHECKSUM_VALID,
    CHECKSUM_INVALID,
    DATA_FORMAT_ERROR
} ChecksumResult;


typedef enum {
    BYTE_COUNT_VALID,
    BYTE_COUNT_INVALID
} ByteCountResult;


/*******************************************************************************
*API
*******************************************************************************/


/**
 * @brief Converts a hexadecimal string to an integer.
 *
 * This function converts a hexadecimal string to an integer. The hexadecimal
 string must be a valid hexadecimal number, and it must not contain any
 whitespace characters.
 * @param[in] hex The hexadecimal string to be converted.
 * @return The integer representation of the hexadecimal string.
 */

uint32_t hex_to_int(char hex);


/**
 * @brief Calculates the checksum of a line of text.
 *
 * This function calculates the checksum of a line of text. The checksum is
 * calculated by adding the ASCII values of all the characters in the line and
 * then taking the remainder of the sum divided by 256.
 *
 * @param[in] line The line of text whose checksum is to be calculated.
 * @return The checksum of the line of text.
 */
uint32_t calculateChecksum(const char* line);

/**
 * @brief Checks the checksum of a line of text.
 *
 * This function checks the checksum of a line of text. The checksum is
 * checked by comparing it to the checksum that is stored in the line. If the
 * checksums match, then the function returns `true`. Otherwise, the function
 * returns `false`.
 *
 * @param[in] line The line of text whose checksum is to be checked.
 * @return `true` if the checksums match, `false` otherwise.
 */
ChecksumResult check_sum(const char* line);

/**
 * @brief Checks the byte count of a line of text.
 *
 * This function checks the byte count of a line of text. The byte count is
 * checked by comparing it to the byte count that is stored in the line. If the
 * byte counts match, then the function returns `true`. Otherwise, the function
 * returns `false`.
 *
 * @param[in] line The line of text whose byte count is to be checked.
 * @return `true` if the byte counts match, `false` otherwise.
 */
ByteCountResult checkByteCount(const char* line);

/**
 * @brief Parses an S-Record and writes the parsed data to a file.
 *
 * This function parses an S-Record and writes the parsed data to a file. The
 * S-Record is specified by the `record` pointer and the parsed data is written
 * to the file specified by the `output` pointer.
 *
 * @param[in] record The S-Record to be parsed.
 * @param[in] output The file to which the parsed data is to be written.
 * @return None.
 */
void parseSRecord(const char* record);

#endif /* HEADER_H */

/******************************************************************************
*End of header - EOH
******************************************************************************/


