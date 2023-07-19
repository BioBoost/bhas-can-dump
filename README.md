# BHAS - CAN Dump

Dumps all received CAN messages via serial port.

Example:

```
.______    __    __       ___           _______.                             
|   _  \  |  |  |  |     /   \         /       |                             
|  |_)  | |  |__|  |    /  ^  \       |   (----`                             
|   _  <  |   __   |   /  /_\  \       \   \                                 
|  |_)  | |  |  |  |  /  _____  \  .----)   |                                
|______/  |__|  |__| /__/     \__\ |_______/                                 
                                                                             
  ______     ___      .__   __.     _______   __    __  .___  ___. .______   
 /      |   /   \     |  \ |  |    |       \ |  |  |  | |   \/   | |   _  \  
|  ,----'  /  ^  \    |   \|  |    |  .--.  ||  |  |  | |  \  /  | |  |_)  | 
|  |      /  /_\  \   |  . `  |    |  |  |  ||  |  |  | |  |\/|  | |   ___/  
|  `----./  _____  \  |  |\   |    |  '--'  ||  `--'  | |  |  |  | |  |      
 \______/__/     \__\ |__| \__|    |_______/  \______/  |__|  |__| | _|      

----------------------------------------------------------------------------------

_5900ms_ (5899ms since previous) CAN message received: [CANID = 1337]: 0x01 0x02 0x03 
_10957ms_ (5057ms since previous) CAN message received: [CANID = 1337]: 0x02 0x03 0x04
```

There is currently no message parsing or what ever implemented. Pure message dump.

This little firmware is part of Bio Home Automator System - BHAS (pronounced BeeHas) and is designed for the LPC1768.
