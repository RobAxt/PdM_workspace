## Hardware Connections
```
                   ┌────────────┐   ┌──────────────────────────┐ 
                   │            │   │         PCF8574          │ 
                ┌──┤GPIO   HI2C2├───┤                          │ 
                │  │PC08        │   │ P0 P1 P2 P3 P4 P5 P6 P7  │ 
     Add      │ o  │            │   └──┬──┬──┬─────┬──┬──┬──┬──┘ 
  PushButton ─┤    │            │      │  │  │     │  │  │  │    
              │ o  │            │   ┌──┴──┴──┴─────┴──┴──┴──┴──┐ 
                │  │            │   │ RS RW  E    D4 D5 D6 D7  │ 
                └──┤   NUCLEO   │   │                          │ 
                   │            │   │         HD44780          │ 
                ┌──┤   F429ZI   │   └──────────────────────────┘ 
                │  │            │                ___  ___        
    Delete    │ o  │            │   ┌─────────┐  \ /  \ / ┌────┐ 
  PushButton ─┤    │            │   │         │   │    │  │    │ 
              │ o  │            │   │         │   │    │  │RFID│ 
                │  │       HI2C1├───┤  PN532  ├───┘    └──┤    │ 
                └──┤GPIO        │   │         │           │TAG │ 
                   │PC09        │   │         │           │    │ 
                   └────────────┘   └─────────┘           └────┘  
```

## Finite State Machine

```mermaid 
stateDiagram-v2 
[*] --> WT
state "WAITING TAG" as WT: do / wait for tag.
state "VERIFY TAG" as VT: do / verify current tag.
VT: do / if valid check delete pushbutton.
VT: do / if invalid check add pushbutton.
state "INVALID TAG" as IT: infom / invalid Tag.
state "ADD TAG" as AT: do / add current tag.
state "DELETE TAG" as DT: do / delete current tag.
WT --> VT : Tag found
VT --> WT : No Tag
VT --> AT : Add PB clicked
AT --> WT : Timeout
IT --> WT : No Tag
VT --> IT : Invalid Tag
VT --> DT : Delete PB clicked
DT --> WT : Timeout
```
