#pragma once
#include <string>
#include <fstream>
#include <cassert>

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
		bool isDummy = false;        //ダミーノードであるか
	};

	//ノードへのポインタ
	size_t listSize = 0;   //現在のリストのサイズ

	Node* dummy = nullptr;

	/**
     * @brief  引数のノードが存在するかを探索する
     * @param  node 対象のポインタ
	 * @return 存在する場合はtrue、無い場合はfalseを返す
     */
	bool containsNode(const Node* node) const {
		if (node == dummy) return true;  //指定ノードがダミーノードである場合、一応存在しているので、trueを返す

		for (Node* current = dummy->nextNode; current != dummy; current = current->nextNode) {
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
		constIterator& operator--() { 
			//もしend()などから末尾(ダミーノード)を指定してデクリメントした場合、
			if (node->isDummy) {
				//もしダミーのprevNodeが自身を指していた場合、リストは空なので、assert発生
				assert(node->prevNode != node);
			}
			//実際に中身があるノードだった場合
			else {
				//prevNodeがダミーだった場合、先頭を通り越しているので、assert発生
				assert(!node->prevNode->isDummy);
			}
			node = node->prevNode;
			return *this;;
		}

		/**
		 * @brief  後置デクリメント用(it--)(リストの先頭に向かって一つ進める[operator--]())
		 * @return 前に戻る以前のconstIterator
		 */
		constIterator  operator--(int) { constIterator it = *this; --(*this); return it; }

		/**
		 * @brief  前置インクリメント用(++it)(リストの末尾に向かって一つ進める[operator++]())
		 * @return *this
		 */
		constIterator& operator++() {
			//nullptrではない場合と、ダミーノードではない場合のみ通す
			assert(node != nullptr && !node->isDummy);
			node = node->nextNode; 
			return *this; 
		}

		/**
		 * @brief  後置インクリメント用(it++)(リストの末尾に向かって一つ進める[operator++]())
		 * @return 次に進む以前のconstIterator
		 */
		constIterator  operator++(int) { constIterator it = *this; ++(*this); return it; }

		/**
		 * @brief  間接参照(戻り値 const scoreData&)（イテレータの指す要素を取得する[operator* const版]())
		 * @return const scoreData&
		 */
		const scoreData& operator*() const { 
			//nullptrではない場合と、ダミーノードではない場合のみ通す
			assert(node != nullptr && !node->isDummy);
			return node->data; 
		}

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
			return host == comp.host && node == comp.node;
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
		scoreData& operator*() {

			//nullptrではない場合と、ダミーノードではない場合のみ通す
			assert(node != nullptr && !node->isDummy);
			return node->data; 
		}

		//先頭でも末尾でもないイテレータ直接指定用
		/**
		 * @brief  前置デクリメント用(--it)(リストの先頭に向かって一つ進める[operator--]())
		 * @return *this
		 */
		iterator& operator--() {
			//もしend()などから末尾(ダミーノード)を指定してデクリメントした場合、
			if (node->isDummy) {
				//もしダミーのprevNodeが自身を指していた場合、リストは空なので、assert発生
				assert(node->prevNode != node);
			}
			//実際に中身があるノードだった場合
			else {
				//prevNodeがダミーだった場合、先頭を通り越しているので、assert発生
				assert(!node->prevNode->isDummy);
			}
			node = node->prevNode; 
			return *this; 
		}

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
		iterator& operator++() {
			//nullptrではない場合と、ダミーノードではない場合のみ通す
			assert(node != nullptr && !node->isDummy);
			node = node->nextNode; 
			return *this; 
		}

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
			return host == comp.host && node == comp.node;
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
	* @return  循環リストの為、常にダミーの次を渡す
	*/
	iterator begin() {
		return iterator(dummy->nextNode, this);
	}

	/**
	* @brief   先頭コンストイテレータの取得
	* @return  循環リストの為、常にダミーの次を渡す
	*/
	constIterator cbegin() const {
		return constIterator(dummy->nextNode, this);
	}

	/**
	* @brief   末尾イテレータの取得
	* @return  循環リストの為、常にダミーを渡す
	*/
	iterator end() {
		return iterator(dummy, this);
	}

	/**
	* @brief   末尾コンストイテレータの取得
	* @return  循環リストの為、常にダミーを渡す
	*/
	constIterator cend() const {
		return constIterator(dummy, this);
	}

	/**
	 * @brief          ノード追加
	 * @param nodePos  挿入先のノードの位置
	 * @param datas    追加するデータstring
	 * @return         追加したノードの位置
	 */
	iterator addNode(const constIterator& nodePos, const scoreData& datas) {
		Node* next = {};

		//nodePosが空でない場合
		if (nodePos.node != nullptr) {
			//挿入先を代入
			next = nodePos.node;
		}
		//それ以外の場合はダミーを代入
		else {
			next = dummy;
		}

		//新規ノードを生成し、接続を再編成
		Node* current = new Node();
		current->prevNode = next->prevNode;
		current->nextNode = next;
		next->prevNode->nextNode = current;
		next->prevNode = current;

		//データを代入し、ダミーではないと判別する
		current->data = datas;
		current->isDummy = false;


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

		//見つからなかった場合もしくはダミーだった場合は、削除不可なのでダミーをreturn
		if (current == nullptr || current == dummy) return iterator(dummy,this);

		Node* next = current->nextNode;
		Node* prev = current->prevNode;
		//ノードの前後のポインタを再編成
		prev->nextNode = next;
		next->prevNode = prev;

		//currentを削除し、リストサイズも減らす
		delete current;
		--listSize;
		return iterator(next, this);
	}

	/**
	 * @brief リスト内の要素先頭から全消去
	 */
	void clear() {
		Node* current = dummy->nextNode;
		//currentがdummyになるまでループし、ノードを削除
		while (current != dummy) {
			Node* next = current->nextNode;
			delete current;
			current = next;
		}
		dummy->nextNode = dummy;
		dummy->prevNode = dummy;
		listSize = 0;
	}

	/**
	 * @brief コンストラクタでダミーノードの初期設定
	 */
	doublyLinkedList() {
		//ダミーノード作成
		dummy = new Node();
		dummy->isDummy = true; //ダミーノードであると判別

		//循環リストにする
		dummy->nextNode = dummy;
		dummy->prevNode = dummy;
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
		if (listSize == 0)               return false;
		if (nodePos.node == nullptr)     return false;
		if (nodePos.host != this)        return false;
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
		if (nodePos.host != this)        return false;
		if (nodePos.node == nullptr)     return false;
		if (nodePos.node == dummy)       return false;
		if (!containsNode(nodePos.node)) return false;

		return deleteData(iterator(nodePos.node, this));
	}
};
