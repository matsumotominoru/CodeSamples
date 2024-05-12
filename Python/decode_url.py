import urllib.parse
import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("supply url")
        quit()
    url_string = sys.argv[1]
    print(urllib.parse.unquote(url_string))
