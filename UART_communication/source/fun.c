/*******************************************************************************
*Icludes
*******************************************************************************/

#include "header.h"
#include <string.h>


/*******************************************************************************
*Function
*******************************************************************/


uint32_t hex_to_int(char hex) {
    uint32_t result = 0;

    if (hex >= '0' && hex <= '9') {
        result = hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        result = hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        result = hex - 'a' + 10;
    }

    return result;
}

uint32_t calculateChecksum(const char* line) {
    uint32_t sum = 0;
    uint32_t i = 2;

    uint32_t expectedByteCount = (hex_to_int(line[2]) << 4) + hex_to_int(line[3]);
    uint32_t length = expectedByteCount * 2;

    for (i = 2; i <= length; i += 2) {
        uint32_t value = (hex_to_int(line[i]) << 4) + hex_to_int(line[i + 1]);
        sum += value;
    }

    uint32_t check_sum = 0xFF - (sum & 0xFF);

    return check_sum;
}

ChecksumResult check_sum(const char* line) {
    uint32_t byte_count = hex_to_int(line[2]) * 16 + hex_to_int(line[3]);

    char checksum[3];

    char data[1024];
    strncpy(data, line + 8, byte_count * 2);

    uint32_t expected_checksum = calculateChecksum(line);

    uint32_t data_length = strlen(data);
    if (data_length >= 2) {

        strncpy(checksum, data + data_length - 2, 2);
        checksum[2] = '\0';
        uint32_t checksum_value = (hex_to_int(checksum[0]) << 4) + hex_to_int(checksum[1]);

        if (checksum_value != expected_checksum) {
            return CHECKSUM_INVALID;
        }
    } else {
        return DATA_FORMAT_ERROR;
    }

    return CHECKSUM_VALID;
}


ByteCountResult checkByteCount(const char* line) {
        int expectedByteCount = (hex_to_int(line[2])) * 16 + hex_to_int(line[3]);
        int expected_length = expectedByteCount * 2 + 4;

        int actual_length = 0;
        while (line[actual_length] != '\0') {
            actual_length++;
        }
        if (actual_length != expected_length) {
            return BYTE_COUNT_INVALID;
      }

    return BYTE_COUNT_VALID;
}

void parseSRecord( const char* record) {
    char recordType = record[1];
    uint32_t address = 0;
    uint8_t addressLength = 0;
    char data[1024];
    static long long line_number = 0;

    switch (recordType) {
        case '0':
            addressLength = 0;
            break;
        case '1':
            addressLength = 2;
            break;
        case '2':
            addressLength = 3;
            break;
        case '3':
            addressLength = 4;
            break;
        case '5':
            addressLength = 2;
            break;
        default:

            return;
    }

    if (addressLength > 0) {
        char addressHex[9];
        strncpy(addressHex, record + 4, addressLength * 2);
        addressHex[addressLength * 2] = '\0';
        sscanf(addressHex, "%X", &address);
    }

    strncpy(data, record + 4 + addressLength * 2, strlen(record) - 4 - addressLength * 2 - 2);
    data[strlen(record) - 4 - addressLength * 2 - 2] = '\0';



    ChecksumResult isChecksumValid = check_sum(record);

    ByteCountResult byteCountResult = checkByteCount(record);

}

HexaCheckResult check_hexa(const char* hex_string) {
    uint32_t length_string;
    uint32_t index;

    length_string = strlen(hex_string) - 1;
    for (index = 1; index < (length_string - 1); index++) {
        if ((hex_string[index] < '0') || ((hex_string[index] > '9')
        && (hex_string[index] < 'A')) || (hex_string[index] > 'F')) {
            return HEXA_INVALID;
        }
    }

    return HEXA_VALID;
}

/******************************************************************************
*End of file - EOM
******************************************************************************/
