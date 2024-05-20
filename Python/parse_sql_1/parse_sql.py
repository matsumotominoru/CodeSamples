from enum import Enum

class ReadState(Enum):
    out_of_create_statement = 0
    in_the_create_statement = 1

if __name__ == "__main__":
    read_state = ReadState.out_of_create_statement.value
    parentheses_depth = 0
    create_sql = ""
    #TODO:指定したディレクトリのファイルでループ処理
    #TODO:拡張子がtableかつファイル名の4番目の文字がCであるファイルが読み込み対象。
    with open("KI_C_DCTCSKH01.table", newline='\n', encoding="cp932") as connection_file:
        for row in connection_file:
            if read_state == ReadState.out_of_create_statement.value:
                if"CREATE TABLE" in row:
                    read_state = ReadState.in_the_create_statement.value
                    create_sql += row
            elif read_state == ReadState.in_the_create_statement.value:
                create_sql += row
                if ')' in row and '(' not in row:
                    read_state = ReadState.out_of_create_statement.value

    print(create_sql[0:-1] + ";")
