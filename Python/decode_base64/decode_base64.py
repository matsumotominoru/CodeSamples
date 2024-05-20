import base64
print(base64.b64decode(b'44GT44KT44Gr44Gh44Gv').decode("utf_8"))

with open(file = "C:\\Users\\MatsumotoMinoru\\OneDrive\\ドキュメント\\Python\\decode_base64\\base64_sample2.txt" , encoding="utf_8") as file_stream:
    for line in file_stream:
        print(base64.b64decode(line).decode("utf_8"))