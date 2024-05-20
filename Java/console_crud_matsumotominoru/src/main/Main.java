package jp.co.sss.crud.main;

import jp.co.sss.crud.db.Delete;
import jp.co.sss.crud.db.Insert;
import jp.co.sss.crud.db.SelectDepartment;
import jp.co.sss.crud.db.SelectEmployee;
import jp.co.sss.crud.db.Selectall;
import jp.co.sss.crud.db.Update;
import jp.co.sss.crud.input.Input;

public class Main {

	public static void main(String[] args) {
		/**
		 * メニュー番号。初期化の値は0
		 */
		int menu_Num = 0;
		try{
			do{
				//メニュー画面の表示
				Menu.menu();
				//メニュー番号の入力
				menu_Num = Integer.parseInt(Input.input());
				//メニュー番号に応じた処理
				if(menu_Num == 1){
					//社員一覧表示
					Selectall.selectall();
				}
				else if (menu_Num == 2){
					//社員名検索
					SelectEmployee.selectEmployee();
				}
				else if (menu_Num == 3){
					//部署ID検索
					SelectDepartment.selectDepartment();
				}
				else if (menu_Num == 4){
					//社員登録
					Insert.insert();
				}
				else if (menu_Num == 5){
					//社員更新
					Update.update1();
				}
				else if (menu_Num == 6){
					//社員削除
					Delete.delete();
				}
				else if (menu_Num == 7){
					//正常終了
					System.out.println("システムを終了します");

				}
				else {
					//異常終了
					System.out.println("システムエラーが発生しました。\nシステムを終了します。");
				}
			}while(menu_Num <=6 && menu_Num >= 1);//メニュー番号が1～6のときはメニュー画面に戻る
		}
		catch(Exception e){
			e.printStackTrace();
		}

	}

}
