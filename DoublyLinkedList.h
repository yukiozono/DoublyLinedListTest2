#pragma once
#include <string>
#include <fstream>

struct scoreData {
	int            score = 0;
	std::string    userName = {};
};

/**
 * @class doublyLinkedList
 * @brief 指定したファイルを取り込める双方向リスト
 *
 * @note 入力と出力はstd::stringのみ
 * txtファイルを指定し、読み込むことで、
 * 再度同順に出力できます
 */
class doublyLinkedList {
private:
	struct Node {
		Node* prevNode = nullptr;    //一つ前のノードのポインタ
		Node* nextNode = nullptr;    //一つ後のノードのポインタ
		scoreData data = {};
	};

	//ノードへのポインタ
	Node* head = nullptr;  //先頭アドレス
	size_t listSize = 0;   //現在のリストのサイズ

	Node* dummy = nullptr;

	/**
     * @brief  引数のノードが存在するかを探索する
     * @param  node 対象のポインタ
	 * @return 存在する場合はtrue、無い場合はfalseを返す
     */
	bool containsNode(const Node* node) const {
		if (node == dummy) return true;  //指定ノードがダミーノードである場合、一応存在しているので、trueを返す

		for (Node* current = head; current != nullptr; current = current->nextNode) {
			if (current == node) {
				return true;
			}
		}
		return false;
	}
	

public:

	class constIterator {
		//doublyLinkedListからアクセスするための宣言
		friend class doublyLinkedList;

	protected:
		Node* node = nullptr;

		//生成元
		const doublyLinkedList* host = nullptr;

		//コンストラクタ(initの値で初期化)
		explicit constIterator(Node* init, const doublyLinkedList* hostInit) : node(init), host(hostInit) {}

	public:
	    /**
	     * @brief  デフォルトコンストラクタ(iterator()呼出時、nodeをnullptrに)
	     */
		constIterator() = default;

		/** 
		 * @brief  前置デクリメント用(--it)(リストの先頭に向かって一つ進める[operator--]())
		 * @return *this
		 */
		constIterator& operator--() { if (this->node) this->node = this->node->prevNode; return *this; }

		/**
		 * @brief  後置デクリメント用(it--)(リストの先頭に向かって一つ進める[operator--]())
		 * @return 前に戻る以前のconstIterator
		 */
		constIterator  operator--(int) { constIterator it = *this; --(*this); return it; }

		/**
		 * @brief  前置インクリメント用(++it)(リストの末尾に向かって一つ進める[operator++]())
		 * @return *this
		 */
		constIterator& operator++() { if (this->node) this->node = this->node->nextNode; return *this; }

		/**
		 * @brief  後置インクリメント用(it++)(リストの末尾に向かって一つ進める[operator++]())
		 * @return 次に進む以前のconstIterator
		 */
		constIterator  operator++(int) { constIterator it = *this; ++(*this); return it; }

		/**
		 * @brief  間接参照(戻り値 const scoreData&)（イテレータの指す要素を取得する[operator* const版]())
		 * @return const scoreData&
		 */
		const scoreData& operator*() const { return this->node->data; }

		/**
		 * @brief   コピーコンストラクタ自動生成(iteratorの位置ポインタを上書き)(代入を行う[operator=]())
		 * @param   source 代入元
		 * @return  *this
		 */
		constIterator& operator=(const constIterator& source) = default;
		
		/**
		 * @brief   等値比較(==であればtrueを返す)(値と所有者が同一か比較する[operator==]())
		 * @param   comp 比較相手
		 * @return  等しい場合、true
		 */
		bool operator==(const constIterator& comp) const {
			return this->host == comp.host && this->node == comp.node;
		}

		/**
		 * @brief   非等値比較(!=であればtrueを返す)(異なるかか比較する[operator!=]()
		 * @param   comp 比較相手
		 * @return  等しくない場合、true
		 */
		bool operator!=(const constIterator& comp) const {
			return !(*this == comp);
		}
	};

	class iterator : public constIterator {
		//doublyLinkedListからアクセスするための宣言
		friend class doublyLinkedList;

		//コンストラクタ(initの値で初期化)
		explicit iterator(Node* init, const doublyLinkedList* hostInit) : constIterator(init, hostInit) {}

	public:
		//初期値はdefaultのnullptrにお任せ
		iterator() = default;

		//scoreDataにアクセスするための間接参照
		scoreData& operator*() { return node->data; }

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
		iterator  operator--(int) { iterator it = *this; --(*this); return it; }

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
		iterator  operator++(int) { iterator it = *this; ++(*this); return it; }

		/**
		 * @brief   等値比較(==であればtrueを返す)(同一か比較する[operator==]())
		 * @param   comp 比較相手
		 * @return  等しい場合、true
		 */
		bool operator==(const iterator& comp) const {
			return this->host == comp.host && this->node == comp.node;
		}

		/**
		 * @brief   非等値比較(!=であればtrueを返す)(異なるかか比較する[operator!=]()
		 * @param   comp 比較相手
		 * @return  等しくない場合、true
		 */
		bool operator!=(const iterator& comp) const {
			return !(*this == comp);
		}
	};


public:
	//データ数の取得
	size_t size() const { return listSize; }

	//先頭/末尾イテレータの取得
	/**
	* @brief   先頭イテレータの取得
	* @return  listSizeが0の場合はdummyを返し、そうでない場合は先頭イテレータを返す
	*/
	iterator begin() {
		if (listSize == 0) {
			return iterator(dummy, this);
		}
		return iterator(head, this);
	}

	/**
	* @brief   先頭コンストイテレータの取得
	* @return  listSizeが0の場合はdummyを返し、そうでない場合は先頭コンストイテレータを返す
	*/
	constIterator cbegin() const {
		if (listSize == 0) {
			return constIterator(dummy, this);
		}
		return constIterator(head, this);
	}

	/**
	* @brief   末尾イテレータの取得
	* @return  listSizeが0の場合はdummyを返し、そうでない場合は末尾イテレータ(nullptr)を返す
	*/
	iterator end() {
		if (listSize == 0) {
			return iterator(dummy, this);
		}
		return iterator(nullptr, this);
	}

	/**
	* @brief   末尾コンストイテレータの取得
	* @return  listSizeが0の場合はdummyを返し、そうでない場合は末尾コンストイテレータ(nullptr)を返す
	*/
	constIterator cend() const {
		if (listSize == 0) {
			return constIterator(dummy, this);
		}
		return constIterator(nullptr, this);
	}

	/**
	 * @brief          ノード追加
	 * @param nodePos  挿入先のノードの位置
	 * @param datas    追加するデータstring
	 * @return         追加したノードの位置
	 */
	iterator addNode(const constIterator& nodePos, const scoreData& datas) {
		//新規ノードにデータを代入
		Node* current = new Node{ nullptr, nullptr, datas };

		//もしリストが空であった場合
		if (listSize == 0) {
			//先頭と末尾アドレスにcurrentを代入
			head = current;
		}
		//もしpreviousが末尾のノードだった場合		
		else if (nodePos.node == nullptr) {
			//currentを追加し、末尾アドレスにcurrentを代入
			Node* tail = head;

			//末尾の要素を保持するアドレスまで辿り、
			while (tail->nextNode) {
				tail = tail->nextNode;
			}

			//nextNodeとprevNodeを繋ぎなおす
			tail->nextNode = current;
			current->prevNode = tail;
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
			scoreData data{};
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
	doublyLinkedList() {
		//ダミーノード作成
		dummy = new Node();
	}

	/**
	 * @brief デストラクタでリストの内容物全消去
	 */
	~doublyLinkedList() {
		clear(); 
		delete dummy;
		dummy = nullptr;
	}

	/**
	 * @brief コピーコンストラクタを削除。
	 */
	doublyLinkedList(const doublyLinkedList&) = delete;

	/**
	 * @brief コピー代入演算子を削除。
	 */
	doublyLinkedList& operator=(const doublyLinkedList&) = delete;

	/**
	 * @brief  位置nodePosの直前に挿入(iterator)
	 * @param  nodePos ノード位置
	 * @param  data    入力データ
	 * @return 成功であればtrue、不正イテレータ等の場合はfalseを返す
	 */
	bool insertData(const iterator& nodePos, const scoreData& data) {
		//イテレータの所有者が自分でない場合、falseを返す
		if (nodePos.host != this) {
			return false;
		}

		if (nodePos.node != nullptr && !containsNode(nodePos.node)) {
			return false;
		}
		addNode(constIterator(nodePos.node,this), data);
		return true;
	}

	/**
	 * @brief  位置nodePosの直前に挿入(constIterator)
	 * @param  nodePos ノード位置
	 * @param   data   入力データ
	 * @return 成功であればtrue、不正イテレータ等の場合はfalseを返す
	 */
	bool insertData(const constIterator& nodePos, const scoreData& data) {
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
		if (nodePos.node == dummy)       return false;
		if (!containsNode(nodePos.node)) return false;
		deleteNode(nodePos);
		return true;
	}

	/**
	 * @brief  位置nodePosにある要素を削除(constIterator)
	 * @param  nodePos ノード位置
	 * @return 成功であればtrue、失敗の場合はfalseを返す
	 */
	bool deleteData(const constIterator& nodePos) {
		if (listSize == 0)               return false;
		if (nodePos.host != this)           return false;
		if (nodePos.node == nullptr)         return false;
		if (nodePos.node == dummy)       return false;
		if (!containsNode(nodePos.node))     return false;

		return deleteData(iterator(nodePos.node, this));
	}
};