from csvsort import csvsort
import csv
import sys
import os
import tempfile

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("supply file name")
        quit()
    else:
        csv_file_name = sys.argv[1]
        
    if len(sys.argv) > 2:
        encoding  = sys.argv[2]
    else:
        encoding = "cp932"

    #tempフォルダのパスがDドライブか確認する
    #マージソート時の作業領域はWindowsではユーザー環境変数のtempかtmpのディレクトリの中で行う。巨大なCSVの場合はこれをDドライブのパスに変更する必要がある。
    file = tempfile.NamedTemporaryFile(delete=True, mode='w')
    if os.path.splitdrive(file.name)[0] != "D:":
        print("temp folder is not in D drive.")
        quit()
    
    # max_size: the maximum size (in MB) of CSV file to load in memory at once.
    # 5GBを指定、メモリ上でソートする場合はこの5倍程度のメモリの空きが必要になる。
    max_size = 5000

    table_id = os.path.basename(csv_file_name).split("_")[0]
    PK_list_str = ""
    with open("table_PK_list.txt", newline='') as PK_csv_file:
        PK_csv_reader = csv.reader(PK_csv_file, delimiter='\t', quotechar='"')
        for PK_row in PK_csv_reader:
            if(table_id == PK_row[0]):
                PK_list_str = PK_row[1]
                break

    if(len(PK_list_str) == 0):
        print("Key info of specified table does not exist.")
        quit()
    #TODO oracleとpostgresqlで場合分け
    #TODO ヘッダー行の有無で場合分け
    #Oracleの場合はすべての大文字
    PK_list = PK_list_str.split(",")

    # sort this CSV on the 5th and 3rd columns (columns are 0 indexed or header keys)
    #csvsort(csv_file_name, [0,1], output_filename='test.csv', has_header=True, quoting=csv.QUOTE_ALL,encoding = encoding,max_size = max_size)
    #csvsort(csv_file_name, ["KEIYK_CD","KANYU_KOZA_NO"], output_filename='test.csv', has_header=True, quoting=csv.QUOTE_ALL,encoding = encoding,max_size = max_size, show_progress = True)
    csvsort(csv_file_name, PK_list, has_header=True, quoting=csv.QUOTE_ALL,encoding = encoding,max_size = max_size, show_progress = True,parallel = False)
