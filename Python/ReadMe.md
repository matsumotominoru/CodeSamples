Pack codes "H" and "I" represent two and four byte unsigned numbers respectively. 
The "<" indicates that they are standard size and in little-endian byte order

```Python
import struct
fields = struct.unpack('<HHHHH', data[0:10])
version,bit_flag,compression_method,int_last_modification_time,int_last_modification_date = fields
```

Decode binary data with specified encoding

```Python
str_filename = filename.decode("utf_8")
```
