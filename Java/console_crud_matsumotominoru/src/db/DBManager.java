package jp.co.sss.crud.db;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DBManager {
	/**
	 * DBと接続する
	 * @return  DBコネクション
	 * @throws ClassNotFoundException
	 *ドライバクラスが見つからなかった場合
	 * @throws SQLException
	 * DB接続に失敗した場合
	 */
	public static Connection getConnection() throws ClassNotFoundException, SQLException {
		//JDBCドライバクラスをJVMに登録
		Class.forName(ConstantDB.JDBC_DRIVER);

		//DBに接続
		Connection conn = DriverManager.getConnection(ConstantDB.DB_URL, ConstantDB.USER_NAME, ConstantDB.PASSWORD);
		System.out.println("ローカルDB接続しました。");

		return conn;
	}
	/**
	 * DBとの接続を切断する
	 * @param conn
	 * DBとの接続情報
	 */
	public static void close(Connection conn) {
		if (conn != null) {
			try {
				conn.close();
				System.out.println("DB切断しました。");

			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
	/**
	 * PreparedStatementを閉じる
	 * @param ps
	 * ステートメント情報
	 */
	public static void close(PreparedStatement ps) {
		if (ps != null) {
			try {
				ps.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
	/**
	 * ResultSetを閉じる
	 * @param rs
	 * SQL検索結果
	 */
	public static void close(ResultSet rs) {
		if (rs != null) {
			try {
				rs.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}

}