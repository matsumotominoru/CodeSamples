package jp.co.sss.crud.input;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Input {
	/**
	 * 標準入力を1回行い、入力値をString型で返す。
	 * @return String 入力値
	 */
	public static String input(){
		try{
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			String read_line = br.readLine();
			return read_line;
		}
		catch(IOException e){
			e.printStackTrace();
		}
		return null;
	}

}
