# JSON Serializer in C (Embedded-Ready)

## Overview
This project implements a **JSON serialization module in C** designed for **embedded systems**.  
It converts structured meter/device data into a JSON string using **safe buffer handling**.

The code is **platform-independent** and was verified using **GCC on a PC**, making it suitable for STM32 and other microcontrollers.

---

## Features
- JSON serialization without external libraries
- Safe buffer handling using `snprintf`
- Overflow protection with buffer size checks
- Supports multiple devices and readings
- Embedded-friendly (no dynamic memory allocation)
- Portable across PC and microcontroller environments

---

## Data Structure
The serializer converts C structures into JSON format.

### Example Fields
- Gateway ID
- Timestamp
- Device list
- Media type
- Meter type
- Device ID
- Unit
- Data readings

---

## JSON Output Example
```json
[{"gatewayId":"gateway_1234",
"date":"1970-01-01",
"deviceType":"stromleser",
"interval_minutes":15,
"total_readings":1,
"values":{
        "device_count":1,
        "readings":[
        {
                "media":"water",
                "meter":"waterstarm",
                "deviceId":"stromleser_50898527",
                "unit":"m3",
                "data":[
                {
                        "timestamp":"1970-01-01 00:00",
                        "meter_datetime":"1970-01-01 00:00",
                        "total_m3":107.752,
                        "status":"OK"
                }
            ]
         }
      ]
    }
  }
]
