#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>

#define MAX_DEVICE           5   // Maximum number of meter
#define MAX_DATA_POINTS      10  // Maximum reading per meter
#define MAX_STR_LEN          32  // Maximum length for strings

/* For return status */

typedef enum
{
 JSON_OK = 0,              // Serialization Successful
 JSON_BUFFER_TOO_SMALL,    // Output buffer not enough
 JSON_INVALID_INPUT        // Invalid input Ex. Null Pointer Or bad input
}json_status_t;

/* Getway Information */

typedef struct
{
        char getway_id[MAX_STR_LEN];      // Gateway Identifier
        char date[11];                    // Format: YYYY-MM-DD
        char device_type[MAX_STR_LEN];    // Type of gateway
        unsigned int interval_minutes;        // Measurement interval
        unsigned int total_readings;          // Total readings count

}gateway_meta_t;

/* One measurement value */

typedef struct
{
        char timestamps[17];           // Gateway time stamp
        char meter_date_time[17];      // Meter time stamp
        float total_m3;                // Meter value
        char status[8];                // Status - OK / Error

}data_point_t;

/* One device data */

typedef struct
{
        char media[MAX_STR_LEN];             // Water / Gas / Electricity
        char meter[MAX_STR_LEN];             // Meter model
        char device_id[MAX_STR_LEN];         // Unique id
        char unit[8];                        // Measurement unit
        unsigned int data_count;                  // Number of readings
        data_point_t data[MAX_DATA_POINTS];  // Array of data points
}device_reading_t;

/* Full payload */

typedef struct
{
        gateway_meta_t meta;                    // Gateway level data
        unsigned int device_count;                   // Number of devices
        device_reading_t devices[MAX_DEVICE];  // All meter data
} meter_payload_t;

/* Function Prototype */

json_status_t serialize_meter_payload(const meter_payload_t *input, char *output_buffer, size_t buffer_size, size_t *bytes_used);




#endif
