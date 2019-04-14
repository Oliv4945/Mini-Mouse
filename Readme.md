This was an attempt to port Minimouse over Arduino Framework, to be used with an Atmega-328p.
Unfortunatly code does not fit in such small processor both for RAM and FLASH memory:

```
DATA:    [==========]  370.1% (used 7580 bytes from 2048 bytes)
PROGRAM: [==========]  119.8% (used 36798 bytes from 30720 bytes)
```

Some easy work would be to use another AES library, see [here](https://www.thethingsnetwork.org/forum/t/lmic-1-51-fitting-in-arduino-atmega-328/1239/11).  

Another way is to put all print messages to FLASH. Without printf() the FLASH code is correct, but not the RAM:

```
DATA:    [==========]  201.0% (used 4116 bytes from 2048 bytes)
PROGRAM: [========= ]  88.6% (used 27222 bytes from 30720 bytes)
```
