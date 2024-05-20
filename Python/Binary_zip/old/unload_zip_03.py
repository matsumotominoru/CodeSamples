import struct
import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("CLI args required.")
        quit()
    zip_file_name = sys.argv[1]
    with open(zip_file_name, 'rb') as zip_file:
        while(True):
            data = zip_file.read(14)
            # Pack codes "H" and "I" represent two and four byte unsigned numbers respectively. 
            # The "<" indicates that they are standard size and in little-endian byte order
            fields = struct.unpack('<IHHHHH', data[0:14])
            header_signature,version,bit_flag,compression_method,last_modification_time,last_modification_date = fields
            if(hex(header_signature) != "0x4034b50"):
                print("This file is not a zip file.")
                print(f'header_signature is {hex(header_signature)}')
                quit()
            print(f'version = {version}, bit flag = {bit_flag}, compression method is {compression_method}, last modification time is {hex(last_modification_time)}, last_modification_date is {hex(last_modification_date)}')

            data = zip_file.read(16)
            fields = struct.unpack('<IIIHH', data[0:16])
            crc32, comp_size, uncomp_size, filenamesize, extra_size = fields
            data = zip_file.read(filenamesize)
            filename = data[0:filenamesize]
            data = zip_file.read(extra_size)
            str_filename = filename.decode("shift_jis")
            print(f'filename={str_filename},crc32={hex(crc32)},comp_size={comp_size}, uncomp_size={uncomp_size}')

            # skip to the next header
            data = zip_file.read(comp_size)