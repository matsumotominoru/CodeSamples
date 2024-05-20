package jp.co.sss.crud.db;

/**
 * 設定値をまとめたクラス
 *
 * @author System Shared
 *
 */
public class ConstantDB {

    /** インスタンス化を禁止 */
    private ConstantDB() {
    }

    // ***** DB接続のための設定値 *****

    /** DBドライバー */
    public static final String JDBC_DRIVER = "oracle.jdbc.driver.OracleDriver";

    /** DB接続用文字列 */
    public static final String DB_URL = "jdbc:oracle:thin:@localhost:1521:XE";

    /** DB接続用ユーザー */
    public static final String USER_NAME = "console_crud_user";

    /** DB接続用パスワード */
    public static final String PASSWORD = "systemsss";

}
