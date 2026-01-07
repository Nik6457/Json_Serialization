#include "json_serializer.h"
#include <stdio.h>
#include <string.h>


static void sample_data(meter_payload_t *payload)
{
        strcpy(payload->meta.getway_id, "gateway_1234");
        strcpy(payload->meta.date, "1970-01-01");
        strcpy(payload->meta.device_type, "stromleser");
        payload->meta.interval_minutes = 15;
        payload->meta.total_readings = 1;

        payload->device_count = 1;

        device_reading_t *dev = &payload->devices[0];

        strcpy(dev->media, "water");
        strcpy(dev->meter, "waterstarm");
        strcpy(dev->device_id, "stromleser_50898527");
        strcpy(dev->unit, "m3");

        dev->data_count = 1;
        strcpy(dev->data[0].timestamps, "1970-01-01 00:00");
        strcpy(dev->data[0].meter_date_time, "1970-01-01 00:00");
        dev->data[0].total_m3 = 107.752f;
        strcpy(dev->data[0].status, "OK");
}


int main(void)
{
    meter_payload_t payload;
        char json_buffer[2048];
        size_t written;

        sample_data(&payload);

        if(serialize_meter_payload(&payload, json_buffer, sizeof(json_buffer), &written) == JSON_OK)
        {
                printf("%s\n", json_buffer);
        }
        else
        {
                printf("JSON serialization failed\n");
        }



}
