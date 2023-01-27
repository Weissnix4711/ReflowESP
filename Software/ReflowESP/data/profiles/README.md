# Profiles

[dronecz/ESP32-Reflow-Controller](https://github.com/dronecz/ESP32-Reflow-Controller)

- [Sn42Bi57.6Ag04](Sn42Bi576Ag04.json)
- [Sn63Pb37](sn63pb37.json)
- [Sn96.5Ag30Cu05](sn965ag30cu05.json)

## Format

```json
{
    "title": "Title Of Profile",
    "alloy": "Th3/Al10/Y",
    "melting_point": 999,
    "temp_range": [10,165],
    "time_range": [0,390],
    "reference": "http://www.chipquik.com/datasheets/TS391LT50.pdf",
    "stages": {
        "preheat": [90,90],
        "soak": [180,130],
        "reflow": [210,138],
        "cool": [270,138]
        },
    "profile": [
        [0,30],
        [90,150],
        [180,150],
        [240,165],
        [270,138],
        [390,50]
    ]
}
```
