package jp.co.sss.crud.db;

import java.sql.Connection;
import java.sql.PreparedStatement;

import jp.co.sss.crud.input.Input;

public class Delete {
	/**
	 * 入力した社員IDの社員データを削除する。
	 */
	public static void delete(){
		Connection conn = null;
		PreparedStatement ps = null;

		try{
			conn = DBManager.getConnection();

			String sql = "delete from employee where emp_id = ?";

			ps = conn.prepareStatement(sql);

			System.out.print("削除する社員の社員IDを入力してください。");

			int emp_Id = Integer.parseInt(Input.input());

			ps.setInt(1, emp_Id);

			int cnt = ps.executeUpdate();
			//1件以上実行されたとき削除完了メッセージを出力、実行されなかったらなしと出力
			if(cnt >= 1){
				System.out.println("社員情報を削除しました。");
			}
			else{
				System.out.println("なし");
			}
		}
		catch (Exception e){
			e.printStackTrace();
		}
		finally{
			DBManager.close(conn);
			DBManager.close(ps);
		}
	}

}
