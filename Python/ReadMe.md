## Little endian

Magic number is `504B0304`,but binary data in X86(or X86-64) is coded in little endian, so set hex data reversed in program code.
Note that initial zero is omitted, so `504B0304` is `0x4034b50` in program code.

## Read binary data

 - Pack codes "H" and "I" represent two and four byte unsigned numbers respectively. 
   The "<" indicates that they are standard size and in little-endian byte order.
   Extracted data fields are Integer type.

```Python
import struct
fields = struct.unpack('<HHHHH', binary_data[0:10])
version,bit_flag,compression_method,int_last_modification_time,int_last_modification_date = fields
```

 - Decode binary data with specified encoding

```Python
str_filename = filename.decode("utf_8")
```
