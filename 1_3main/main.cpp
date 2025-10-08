#include "DoublyLinkedList.h"
#include <fstream>
#include <iostream>
#include <string>

int main(void) {
	//ファイルパスからファイルを開く
	std::string filePath = "Scores.txt";
	std::ifstream file(filePath.c_str());

	//もし正しくファイルを開けなかった場合、return
	if (!file.is_open()) {
		return 0;
	}

	doublyLinkedList list;
	std::string line = {};

	//一行ずつListに追加
	while (std::getline(file, line)) {
		if (line.empty()) continue;  //もし空だった場合、続行

		//最初のタブキー入力の位置を検索
		std::size_t tab = line.find('\t');

		// tabがない場合、スキップ
		if (tab == std::string::npos) continue;

		scoreData data = {};
		
		//数字だった場合、inputScoreを数字に変換
		try {
			data.score = std::stoi(line.substr(0,tab));
		}
		// 数字ではない場合、スキップ
		catch (...) {
			continue;
		}
		data.userName = line.substr(tab + 1);

		// 末尾にノードを追加
		list.insertData(list.cend(), data);
	}

	//ファイルを閉じる
	file.close();

	
	//リストの内容を出力
	for (doublyLinkedList::iterator it = list.begin(); it != list.end(); ++it) {
		std::cout << (*it).score << '\t' << (*it).userName << std::endl;
	}

	return 0;
}