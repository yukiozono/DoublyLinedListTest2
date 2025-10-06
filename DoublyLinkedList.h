#pragma once
#include <string>
#include <fstream>

struct ScoreData {
	int            score = 0;
	std::string    userName = {};
};

/**
 * @class DoublyLinkedList
 * @brief 指定したファイルを取り込める双方向リスト
 *
 * @note 入力と出力はstd::stringのみ
 * txtファイルを指定し、読み込むことで、
 * 再度同順に出力できます
 */
class DoublyLinkedList {
private:
	struct Node {
		Node* prevNode = nullptr;    //一つ前のノードのポインタ
		Node* nextNode = nullptr;    //一つ後のノードのポインタ
		ScoreData data = {};
	};

	//ノードへのポインタ
	Node* head = nullptr;  //先頭アドレス
	Node* tail = nullptr;  //末尾アドレス
	size_t listSize = 0;   //現在のリストのサイズ

	/**
     * @brief  引数のノードが存在するかを探索する
     * @param  node 対象のポインタ
	 * @return 存在する場合はtrue、無い場合はfalseを返す
     */
	bool containsNode(const Node* node) const {
		for (Node* current = head; current != nullptr; current = current->nextNode) {
			if (current == node) {
				return true;
			}
		}
		return false;
	}
	

public:

	class iterator {
		//DoublyLinkedListからアクセスするための宣言
		friend class DoublyLinkedList;

	protected:
		Node* node = nullptr;

		//生成元
		const DoublyLinkedList* host = nullptr;

		//コンストラクタ(initの値で初期化)
		explicit iterator(Node* init,const DoublyLinkedList* hostInit) : node(init), host(hostInit) {}

	public:
		//初期値はdefaultのnullptrにお任せ
		iterator() = default;

		//ScoreDataにアクセスするための間接参照
		ScoreData& operator*() { return node->data; }

		//先頭でも末尾でもないイテレータ直接指定用
		/**
		 * @brief  前置デクリメント用(--it)(リストの先頭に向かって一つ進める[operator--]())
		 * @return *this
		 */
		iterator& operator--() { if (this->node) this->node = this->node->prevNode; return *this; }

		/**
		 * @brief  後置デクリメント用(it--)(リストの先頭に向かって一つ進める[operator--]())
		 * @param  dummy(int)
		 * @return 前に戻る以前のiterator
		 */
		iterator  operator--(int dummy) { (void)dummy; const_iterator it = *this; --(*this); return it; }

		/**
		 * @brief  前置インクリメント用(++it)(リストの末尾に向かって一つ進める[operator++]())
		 * @return *this
		 */
		iterator& operator++() { if (this->node) this->node = this->node->nextNode; return *this; }

		/**
		 * @brief  後置インクリメント用(it++)(リストの末尾に向かって一つ進める[operator++]())
		 * @param  dummy(int)
		 * @return 次に進む以前のiterator
		 */
		iterator  operator++(int dummy) { (void)dummy; const_iterator it = *this; ++(*this); return it; }

	};

	class const_iterator : public iterator {
		//DoublyLinkedListからアクセスするための宣言
		friend class DoublyLinkedList;

		//コンストラクタ(initの値で初期化)
		explicit const_iterator(Node* init, const DoublyLinkedList* hostInit) : iterator(init, hostInit) {}

	public:
	    /**
	     * @brief  デフォルトコンストラクタ(iterator()呼出時、nodeをnullptrに)
	     */
		const_iterator() : iterator() {}

		/** 
		 * @brief  前置デクリメント用(--it)(リストの先頭に向かって一つ進める[operator--]())
		 * @return *this
		 */
		const_iterator& operator--() { if (this->node) this->node = this->node->prevNode; return *this; }

		/**
		 * @brief  後置デクリメント用(it--)(リストの先頭に向かって一つ進める[operator--]())
		 * @param  dummy(int)
		 * @return 前に戻る以前のconst_iterator
		 */
		const_iterator  operator--(int dummy) { (void)dummy; const_iterator it = *this; --(*this); return it; }

		/**
		 * @brief  前置インクリメント用(++it)(リストの末尾に向かって一つ進める[operator++]())
		 * @return *this
		 */
		const_iterator& operator++() { if (this->node) this->node = this->node->nextNode; return *this; }

		/**
		 * @brief  後置インクリメント用(it++)(リストの末尾に向かって一つ進める[operator++]())
		 * @param  dummy(int)
		 * @return 次に進む以前のconst_iterator
		 */
		const_iterator  operator++(int dummy) { (void)dummy; const_iterator it = *this; ++(*this); return it; }

		/**
		 * @brief  間接参照(戻り値 const ScoreData&)（イテレータの指す要素を取得する[operator* const版]())
		 * @return const ScoreData&
		 */
		const ScoreData& operator*() const { return this->node->data; }

		/**
		 * @brief   コピーコンストラクタ自動生成(iteratorの位置ポインタをコピー)(コピーを行う[コピーコンストラクタ]())
		 * @param   source 複製元
		 */
		const_iterator(const const_iterator& source) = default;

		/**
		 * @brief   コピーコンストラクタ自動生成(iteratorの位置ポインタを上書き)(代入を行う[operator=]())
		 * @param   source 代入元
		 * @return  *this
		 */
		const_iterator& operator=(const const_iterator& source) = default;
		
		/**
		 * @brief   等値比較(==であればtrueを返す)(同一か比較する[operator==]())
		 * @param   comp 比較相手
		 * @return  等しい場合、true
		 */
		bool operator==(const const_iterator& comp) const { return this->node == comp.node; }

		/**
		 * @brief   非等値比較(!=であればtrueを返す)(異なるかか比較する[operator!=]()
		 * @param   comp 比較相手
		 * @return  等しくない場合、true
		 */
		bool operator!=(const const_iterator& comp) const { return this->node != comp.node; }

		/**
		 * @brief   iteratorからconst_iteratorへ変換
		 * @param   it 変換元
		 */
		const_iterator(const iterator& it) : iterator(it.node,it.host) {}
	};

public:
	//データ数の取得
	size_t size() const { return listSize; }

	//先頭/末尾イテレータの取得
	iterator       begin() { return iterator(head,this); }
	const_iterator cbegin() const { return const_iterator(head, this); }
	iterator       end() { return iterator(nullptr, this); }
	const_iterator cend()   const { return const_iterator(nullptr, this); }

	/**
	 * @brief          ノード追加
	 * @param nodePos  挿入先のノードの位置
	 * @param datas    追加するデータstring
	 * @return         追加したノードの位置
	 */
	iterator addNode(const const_iterator& nodePos, const ScoreData& datas) {
		//新規ノードにデータを代入
		Node* current = new Node{ nullptr, nullptr, datas };

		//もしリストが空であった場合
		if (listSize == 0) {
			//先頭と末尾アドレスにcurrentを代入
			head = tail = current;
		}
		//もしpreviousが末尾のノードだった場合		
		else if (nodePos.node == nullptr) {
			//currentを追加し、末尾アドレスにcurrentを代入
			current->prevNode = tail;
			tail->nextNode = current;
			tail = current;
		}
		
		//もし挿入先が先頭であった場合
		else if (nodePos.node == head) {
			//currentを先頭にし、headの位置を交代
			current->nextNode = head;
			head->prevNode = current;
			head = current;
		}
		//もしどちらでもない途中からの挿入だった場合
		else {
			//previousのノードとcurrentの前後のアドレスを再編成
			Node* prev = nodePos.node->prevNode;
			current->prevNode = prev;
			current->nextNode = nodePos.node;
			prev->nextNode = current;

			//次のノードの前要素アドレスにcurrentを代入
			nodePos.node->prevNode = current;
		}

		//リストサイズを管理する変数を+1
		++listSize;

		return iterator(current, this);
	}


	/**
	 * @brief          ノード削除
	 * @param nodePos  削除するノードの位置
	 * @return         次のノードの位置
	 */
	iterator deleteNode(const iterator& nodePos) {
		Node* current = nodePos.node;

		//見つからなかった場合は、nullptrをreturn
		if (!current) return iterator(nullptr,this);

		Node* next = current->nextNode;

		//ノードの前後のポインタを再編成
		if (current->prevNode) {
			current->prevNode->nextNode = current->nextNode;
		}
		else {
			head = current->nextNode;
		}

		if (current->nextNode) {
			current->nextNode->prevNode = current->prevNode;
		}
		else {
			tail = current->prevNode;
		}

		//currentを削除し、リストサイズも減らす
		delete current;
		--listSize;
		return iterator(next, this);
	}

	/**
	 * @brief リスト内の要素先頭から全消去
	 */
	void clear() {
		Node* current = head;
		//currentがnullptrになるまでループし、ノードを削除
		while (current != nullptr) {
			Node* next = current->nextNode;
			delete current;
			current = next;
		}
		head = nullptr;
		tail = nullptr;
		listSize = 0;
	}

	/**
	 * @brief ファイル読み込み
	 * @param ファイルパス
	 */
	void inputData(const std::string& filePath) {
		//まずはリストの内容物クリア
		clear();

		//ファイルパスからファイルを開く
		std::ifstream file(filePath.c_str());

		//もし正しくファイルを開けなかった場合、return
		if (!file.is_open()) {
			return;
		}

		std::string line = {};

		//一行ずつListに追加
		while (std::getline(file, line)) {
			if (line.empty()) continue;  //もし空だった場合、続行

			//最初のタブキー入力の位置を検索
			std::size_t tab = line.find('\t');

			// tabがない場合、スキップ
			if (tab == std::string::npos) continue;

			std::string inputScore = line.substr(0, tab);
			std::string name = line.substr(tab + 1);
			ScoreData data{};
			//数字だった場合、inputScoreを数字に変換
			try { 
				data.score = std::stoi(inputScore);
			}
			// 数字ではない場合、スキップ
			catch (...) { 
				continue; 
			}              
			data.userName = name;

			// 末尾にノードを追加
			insertData(cend(), data);
		}

		//ファイルを閉じる
		file.close();
	}

	/**
	 * @brief 読み込んだ内容の出力
	 * @return 文字列(string)
	 */
	std::string outputData() const{
		std::string outputLine = {};
		Node* current = head;

		//currentがnullptrになるまでループ
		while (current != nullptr) {
			//文字列を追加し、改行
			outputLine += std::to_string(current->data.score);  //スコアを文字列に変換し、
			outputLine += '\t';   //タブを追加
			outputLine += current->data.userName;  //名前を追加し
			outputLine += '\n';   //改行

			//次のノードへ
			current = current->nextNode;
		}

		//文字列を返す
		return outputLine;
	}

	/**
	 * @brief デフォルトコンストラクタ。
	 */
	DoublyLinkedList() = default;

	/**
	 * @brief デストラクタでリストの内容物全消去
	 */
	~DoublyLinkedList() {
		clear(); 
	}

	/**
	 * @brief コピーコンストラクタを削除。
	 */
	DoublyLinkedList(const DoublyLinkedList&) = delete;

	/**
	 * @brief コピー代入演算子を削除。
	 */
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

	/**
	 * @brief  位置nodePosの直前に挿入(iterator)
	 * @param  nodePos ノード位置
	 * @param  data    入力データ
	 * @return 成功であればtrue、不正イテレータ等の場合はfalseを返す
	 */
	bool insertData(const iterator& nodePos, const ScoreData& data) {
		//イテレータの所有者が自分でない場合、falseを返す
		if (nodePos.host != this) {
			return false;
		}

		if (nodePos.node != nullptr && !containsNode(nodePos.node)) {
			return false;
		}
		addNode(const_iterator(nodePos.node,this), data);
		return true;
	}

	/**
	 * @brief  位置nodePosの直前に挿入(const_iterator)
	 * @param  nodePos ノード位置
	 * @param   data   入力データ
	 * @return 成功であればtrue、不正イテレータ等の場合はfalseを返す
	 */
	bool insertData(const const_iterator& nodePos, const ScoreData& data) {
		//イテレータの所有者が自分でない場合、falseを返す
		if (nodePos.host != this) {
			return false;
		}

		if (nodePos.node != nullptr && !containsNode(nodePos.node)) {
			return false;
		}
		addNode(nodePos, data);
		return true;
	}

	/**
	 * @brief  位置nodePosにある要素を削除(iterator)
	 * @param  nodePos ノード位置
	 * @return 成功であればtrue、そして空、host不一致、nodePos==endもしくは不正であればfalseを返す
	 */
	bool deleteData(const iterator& nodePos) {
		if (listSize == 0)           return false;
		if (nodePos.node == nullptr)     return false;
		if (nodePos.host != this)           return false;
		if (!containsNode(nodePos.node)) return false;
		deleteNode(nodePos);
		return true;
	}

	/**
	 * @brief  位置nodePosにある要素を削除(const_iterator)
	 * @param  nodePos ノード位置
	 * @return 成功であればtrue、失敗の場合はfalseを返す
	 */
	bool deleteData(const const_iterator& nodePos) {
		if (listSize == 0)               return false;
		if (nodePos.host != this)           return false;
		if (nodePos.node == nullptr)         return false;
		if (!containsNode(nodePos.node))     return false;

		return deleteData(iterator(nodePos.node, this));
	}
};