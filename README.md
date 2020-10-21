# Pack24
Ultra-small library to pack 32bits as 2 x ints and unsigned ints into 24 bits (lossy!) 

Edge case primarily for Arduino, to store two unsigned or signed short integers into one short and one byte. This arose from a need to hold screen co-ordinates in an array when memory was in exceptionally short supply. Since these coords broke the 1 byte width (but only just) with values typically in the high 300s on smaller LCDs and typically under 1024 for these tiny devices.

It's a super-short library with just four routines - in two pairs, one for unsigned integers and the other for signed - which (like all signed values) have a smaller range due to the sign bit.   
