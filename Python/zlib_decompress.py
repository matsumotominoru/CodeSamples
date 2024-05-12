import zlib
import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("CLI args required.")
        quit()
    zlib_file_name = sys.argv[1]
    with open(zlib_file_name, 'rb') as zlib_file:
        compress_data = zlib_file.read()
        decompress_data  = zlib.decompress(compress_data)
        decompress_file_name =  zlib_file_name + ".txt"
        with open(decompress_file_name, 'wb') as plain_file:
            plain_file.write(decompress_data)
