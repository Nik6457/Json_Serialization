#include "json_serializer.h"
#include <stdio.h>
#include <string.h>

#define CHECK_SPACE() \
do { if(index >= buffer_size) return JSON_BUFFER_TOO_SMALL; } while(0)

json_status_t serialize_meter_payload(const meter_payload_t *input, char *output_buffer, size_t buffer_size, size_t *bytes_used)
{
        size_t index = 0;

        if(input == NULL || output_buffer == NULL)
        {
                return JSON_INVALID_INPUT;
        }


        /* Start outer array */

        index = index + snprintf(output_buffer + index, buffer_size - index, "[{");
        CHECK_SPACE();

        /* Gateway metadata */

        index = index + snprintf(output_buffer + index, buffer_size - index, "\"gatewayId\":\"%s\",\n"   "\"date\":\"%s\",\n"  "\"deviceType\":\"%s\",\n"  "\"interval_minutes\":%u,\n" "\"total_readings\":%u,\n",  input->meta.getway_id, input->meta.date, input->meta.device_type, input->meta.interval_minutes, input->meta.total_readings);
        CHECK_SPACE();

        /* Object Values */

        index = index + snprintf(output_buffer + index, buffer_size - index, "\"values\":{\n"   "\t\"device_count\":%u,\n"   "\t\"readings\":[\n", input->device_count);
        CHECK_SPACE();

        /* Devices */

        for(unsigned int i = 0; i < input->device_count; i++)
        {
                const device_reading_t *dev = &input->devices[i];

                index = index + snprintf(output_buffer + index, buffer_size - index, "\t{\n" "\t\t\"media\":\"%s\",\n"    "\t\t\"meter\":\"%s\",\n"   "\t\t\"deviceId\":\"%s\",\n"    "\t\t\"unit\":\"%s\",\n"   "\t\t\"data\":[\n",  dev->media, dev->meter, dev->device_id, dev->unit);
                CHECK_SPACE();

                /* Data points */

                for(unsigned int j = 0; j < dev->data_count; j++)
                {
                        const data_point_t *dp = &dev->data[j];

                        index = index + snprintf(output_buffer + index, buffer_size - index, "\t\t{\n" "\t\t\t\"timestamp\":\"%s\",\n"   "\t\t\t\"meter_datetime\":\"%s\",\n"  "\t\t\t\"total_m3\":%.3f,\n"   "\t\t\t\"status\":\"%s\"\n"  "\t\t}\n",  dp->timestamps, dp->meter_date_time, dp->total_m3, dp->status);
                        CHECK_SPACE();

                        if(j < dev->data_count - 1)
                        {
                                index = index + snprintf(output_buffer + index, buffer_size - index, ",");
                                        CHECK_SPACE();
                        }
                }

                index = index + snprintf(output_buffer + index, buffer_size - index, "\t    ]\n\t }\n");
                CHECK_SPACE();

                if(i < input->device_count - 1)
                {
                        index = index + snprintf(output_buffer + index, buffer_size - index, ",");
                    CHECK_SPACE();
                }
        }

        /* Close JSON */

        index = index + snprintf(output_buffer + index, buffer_size - index, "      ]\n    }\n  }\n]\n");
        CHECK_SPACE();

        if(bytes_used)
        {
                *bytes_used = index;
        }

        return JSON_OK;

}
