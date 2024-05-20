import sys
import pathlib
import csv
# 現在のディレクトリのCSVの行数を数え、出力する。ヘッダー行も数える。
# CSVの値の中の改行コードは数えない。
def count_csv_records(csv_file_name,encoding,has_header = True):
    number_of_records = 0
    with open(csv_file_name, newline='', encoding = encoding) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',', quotechar='"')
        if(has_header):
            next(csv_reader)
        for csv_row in csv_reader:
            number_of_records += 1
    return number_of_records

if __name__ == "__main__":
    if len(sys.argv) > 1:
        #csvの文字コードがUTF-8の場合は、第一引数で「utf-8」と指定する。
        encoding_ = sys.argv[1]
    else:
        encoding_ = "cp932"
    csv_files = [f for f in pathlib.Path().glob("*.csv")]
    for csv_file_name in csv_files:
        number_of_records = count_csv_records(csv_file_name,encoding_)
        print(f'{csv_file_name}の行数は{number_of_records}')
