## Hardware Connections
```
┌────────────────────────────────────────────────────────────────┐
│                                                                │
│                  ┌────────────┐   ┌──────────────────────────┐ │
│                  │            │   │         PCF8574          │ │
│               ┌──┤       HI2C2├───┤                          │ │
│               │  │            │   │ P0 P1 P2 P3 P4 P5 P6 P7  │ │
│    Add      │ o  │GPIO        │   └──┬──┬──┬─────┬──┬──┬──┬──┘ │
│ PushButton ─┤    │PC08        │      │  │  │     │  │  │  │    │
│             │ o  │            │   ┌──┴──┴──┴─────┴──┴──┴──┴──┐ │
│               │  │            │   │ RS RW  E    D4 D5 D6 D7  │ │
│               └──┤   NUCLEO   │   │                          │ │
│                  │            │   │         HD44780          │ │
│               ┌──┤   F429ZI   │   └──────────────────────────┘ │
│               │  │            │                ___  ___        │
│   Delete    │ o  │GPIO        │   ┌─────────┐  \ /  \ / ┌────┐ │
│ PushButton ─┤    │PC09        │   │         │   │    │  │    │ │
│             │ o  │            │   │         │   │    │  │RFID│ │
│               │  │       HI2C1├───┤  PN532  ├───┘    └──┤    │ │
│               └──┤            │   │         │           │TAG │ │
│                  │   UART3    │   │         │           │    │ │
│                  └─────┬──────┘   └─────────┘           └────┘ │
│                        │                                       │
│        To PC ◄─────────┘                                       │
│                                                                │
└────────────────────────────────────────────────────────────────┘
```

## Finite State Machine

```mermaid
stateDiagram-v2 
[*] --> WT
state "WAITING TAG" as WT: do / wait for tag.
state "VERIFY TAG" as VT: do / verify current tag.
VT: do / if valid check delete pushbutton.
state "INVALID TAG" as IT: do / check add pushbutton.
state "ADD TAG" as AT: do / add current tag.
state "DELETE TAG" as DT: do / delete current tag.
WT --> VT : Tag found
WT --> WT : No Tag
VT --> WT : No Tag
VT --> VT : Valid Tag
AT --> WT : Timeout
IT --> AT : Add PB clicked
IT --> WT : No Tag
IT --> IT : Invalid Tag
VT --> IT : Invalid Tag
VT --> DT : Delete PB clicked
DT --> WT : Timeout
```
