# UARTaudio
A program to play mono audio through a serial port

## Compilation:
``$ make all``

## Usage:
See the UARTplay.sh script as an example.\
Besides the compiled program, the script requires ffmpeg and python with pyserial installed.

## Connection diagram:

```
Headphone jack  <=|=|==||---------Headphones d(-_-)b
                 | |
         10uF    | |
GND ------||-----| |
          1k       |
TX  ----/\/\/------|
```

## Limitations
* No interpolation. The upsampling is done by simply repeating the same sample as many times as needed.
* No endianness (byte order) conversion. The audio samples must arrive in native byte order.\
If the source is ffmpeg, like in the example script it can do the conversion.
* Command line arguments are not checked/validated.
* No buffering (other than what libc does). The output is written byte-by-byte.
