## About
png-message is a CLI application for encoding and decoding ASCII text in PNG images. It uses least significant bit steganography, meaning the text is stored in the least significant bits of each image pixel. By only targeting the least significant bits, we ensure that the image is not visually altered during the encoding process. This program uses Hamming codes for error correction, so any single-bit errors during data transmission will be corrected before outputting the message. Two-bit errors will be detected, but cannot be fixed.

## Encoding
The most straightforward way to encode a message is by running the command below, where `image.png` is the input image, `encoded.png` is the encoded image file you want to create, and `[message]` is the message you want to encode in `image.png`.

```
bin/encode image.png encoded.png [message]
```

The encoder also accepts two flags, `-f` and `-n`. The `-f` flag takes input from a text file instead of the command line, which is useful for very long messages.

```
bin/encode image.png encoded.png -f message.txt
```

The `-n` flag can be used to simulate noise during data transmission. When `-n` is included, 1 or 2 bits will be flipped at random before encoding.

```
bin/encode image.png encoded.png -n [message]
```

Both flags may be used at the same time.

```
bin/encode image.png encoded.png -n -f message.txt
```

## Decoding
Running the command below will attempt to decode a message from `encoded.png`.

```
bin/decode encoded.png
```

By default, this will print the message to the terminal. You can use `-f` to direct the output to a text file.

```
bin/decode encoded.png -f message.txt
```

## Disclaimer
This program was developed and tested on Linux using version 11.2.0 of the GCC compiler. Other operating systems and compilers may not be supported. The `libpng` library is necessary for compilation.
