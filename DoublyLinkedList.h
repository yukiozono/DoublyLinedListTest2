#pragma once
#include <string>
#include <fstream>

struct ScoreData {
	int            score = 0;
	std::string    userName = {};
};

/**
 * @class DoublyLinkedList
 * @brief �w�肵���t�@�C������荞�߂�o�������X�g
 *
 * @note ���͂Əo�͂�std::string�̂�
 * txt�t�@�C�����w�肵�A�ǂݍ��ނ��ƂŁA
 * �ēx�����ɏo�͂ł��܂�
 */
class DoublyLinkedList {
private:
	struct Node {
		Node* prevNode = nullptr;    //��O�̃m�[�h�̃|�C���^
		Node* nextNode = nullptr;    //���̃m�[�h�̃|�C���^
		ScoreData data = {};
	};

	//�m�[�h�ւ̃|�C���^
	Node* head = nullptr;  //�擪�A�h���X
	Node* tail = nullptr;  //�����A�h���X
	size_t listSize = 0;   //���݂̃��X�g�̃T�C�Y

	/**
     * @brief  �����̃m�[�h�����݂��邩��T������
     * @param  node �Ώۂ̃|�C���^
	 * @return ���݂���ꍇ��true�A�����ꍇ��false��Ԃ�
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
		//DoublyLinkedList����A�N�Z�X���邽�߂̐錾
		friend class DoublyLinkedList;

	protected:
		Node* node = nullptr;

		//������
		const DoublyLinkedList* host = nullptr;

		//�R���X�g���N�^(init�̒l�ŏ�����)
		explicit iterator(Node* init,const DoublyLinkedList* hostInit) : node(init), host(hostInit) {}

	public:
		//�����l��default��nullptr�ɂ��C��
		iterator() = default;

		//ScoreData�ɃA�N�Z�X���邽�߂̊ԐڎQ��
		ScoreData& operator*() { return node->data; }

		//�擪�ł������ł��Ȃ��C�e���[�^���ڎw��p
		/**
		 * @brief  �O�u�f�N�������g�p(--it)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @return *this
		 */
		iterator& operator--() { if (this->node) this->node = this->node->prevNode; return *this; }

		/**
		 * @brief  ��u�f�N�������g�p(it--)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @param  dummy(int)
		 * @return �O�ɖ߂�ȑO��iterator
		 */
		iterator  operator--(int dummy) { (void)dummy; const_iterator it = *this; --(*this); return it; }

		/**
		 * @brief  �O�u�C���N�������g�p(++it)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @return *this
		 */
		iterator& operator++() { if (this->node) this->node = this->node->nextNode; return *this; }

		/**
		 * @brief  ��u�C���N�������g�p(it++)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @param  dummy(int)
		 * @return ���ɐi�ވȑO��iterator
		 */
		iterator  operator++(int dummy) { (void)dummy; const_iterator it = *this; ++(*this); return it; }

	};

	class const_iterator : public iterator {
		//DoublyLinkedList����A�N�Z�X���邽�߂̐錾
		friend class DoublyLinkedList;

		//�R���X�g���N�^(init�̒l�ŏ�����)
		explicit const_iterator(Node* init, const DoublyLinkedList* hostInit) : iterator(init, hostInit) {}

	public:
	    /**
	     * @brief  �f�t�H���g�R���X�g���N�^(iterator()�ďo���Anode��nullptr��)
	     */
		const_iterator() : iterator() {}

		/** 
		 * @brief  �O�u�f�N�������g�p(--it)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @return *this
		 */
		const_iterator& operator--() { if (this->node) this->node = this->node->prevNode; return *this; }

		/**
		 * @brief  ��u�f�N�������g�p(it--)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @param  dummy(int)
		 * @return �O�ɖ߂�ȑO��const_iterator
		 */
		const_iterator  operator--(int dummy) { (void)dummy; const_iterator it = *this; --(*this); return it; }

		/**
		 * @brief  �O�u�C���N�������g�p(++it)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @return *this
		 */
		const_iterator& operator++() { if (this->node) this->node = this->node->nextNode; return *this; }

		/**
		 * @brief  ��u�C���N�������g�p(it++)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @param  dummy(int)
		 * @return ���ɐi�ވȑO��const_iterator
		 */
		const_iterator  operator++(int dummy) { (void)dummy; const_iterator it = *this; ++(*this); return it; }

		/**
		 * @brief  �ԐڎQ��(�߂�l const ScoreData&)�i�C�e���[�^�̎w���v�f���擾����[operator* const��]())
		 * @return const ScoreData&
		 */
		const ScoreData& operator*() const { return this->node->data; }

		/**
		 * @brief   �R�s�[�R���X�g���N�^��������(iterator�̈ʒu�|�C���^���R�s�[)(�R�s�[���s��[�R�s�[�R���X�g���N�^]())
		 * @param   source ������
		 */
		const_iterator(const const_iterator& source) = default;

		/**
		 * @brief   �R�s�[�R���X�g���N�^��������(iterator�̈ʒu�|�C���^���㏑��)(������s��[operator=]())
		 * @param   source �����
		 * @return  *this
		 */
		const_iterator& operator=(const const_iterator& source) = default;
		
		/**
		 * @brief   ���l��r(==�ł����true��Ԃ�)(���ꂩ��r����[operator==]())
		 * @param   comp ��r����
		 * @return  �������ꍇ�Atrue
		 */
		bool operator==(const const_iterator& comp) const { return this->node == comp.node; }

		/**
		 * @brief   �񓙒l��r(!=�ł����true��Ԃ�)(�قȂ邩����r����[operator!=]()
		 * @param   comp ��r����
		 * @return  �������Ȃ��ꍇ�Atrue
		 */
		bool operator!=(const const_iterator& comp) const { return this->node != comp.node; }

		/**
		 * @brief   iterator����const_iterator�֕ϊ�
		 * @param   it �ϊ���
		 */
		const_iterator(const iterator& it) : iterator(it.node,it.host) {}
	};

public:
	//�f�[�^���̎擾
	size_t size() const { return listSize; }

	//�擪/�����C�e���[�^�̎擾
	iterator       begin() { return iterator(head,this); }
	const_iterator cbegin() const { return const_iterator(head, this); }
	iterator       end() { return iterator(nullptr, this); }
	const_iterator cend()   const { return const_iterator(nullptr, this); }

	/**
	 * @brief          �m�[�h�ǉ�
	 * @param nodePos  �}����̃m�[�h�̈ʒu
	 * @param datas    �ǉ�����f�[�^string
	 * @return         �ǉ������m�[�h�̈ʒu
	 */
	iterator addNode(const const_iterator& nodePos, const ScoreData& datas) {
		//�V�K�m�[�h�Ƀf�[�^����
		Node* current = new Node{ nullptr, nullptr, datas };

		//�������X�g����ł������ꍇ
		if (listSize == 0) {
			//�擪�Ɩ����A�h���X��current����
			head = tail = current;
		}
		//����previous�������̃m�[�h�������ꍇ		
		else if (nodePos.node == nullptr) {
			//current��ǉ����A�����A�h���X��current����
			current->prevNode = tail;
			tail->nextNode = current;
			tail = current;
		}
		
		//�����}���悪�擪�ł������ꍇ
		else if (nodePos.node == head) {
			//current��擪�ɂ��Ahead�̈ʒu�����
			current->nextNode = head;
			head->prevNode = current;
			head = current;
		}
		//�����ǂ���ł��Ȃ��r������̑}���������ꍇ
		else {
			//previous�̃m�[�h��current�̑O��̃A�h���X���ĕҐ�
			Node* prev = nodePos.node->prevNode;
			current->prevNode = prev;
			current->nextNode = nodePos.node;
			prev->nextNode = current;

			//���̃m�[�h�̑O�v�f�A�h���X��current����
			nodePos.node->prevNode = current;
		}

		//���X�g�T�C�Y���Ǘ�����ϐ���+1
		++listSize;

		return iterator(current, this);
	}


	/**
	 * @brief          �m�[�h�폜
	 * @param nodePos  �폜����m�[�h�̈ʒu
	 * @return         ���̃m�[�h�̈ʒu
	 */
	iterator deleteNode(const iterator& nodePos) {
		Node* current = nodePos.node;

		//������Ȃ������ꍇ�́Anullptr��return
		if (!current) return iterator(nullptr,this);

		Node* next = current->nextNode;

		//�m�[�h�̑O��̃|�C���^���ĕҐ�
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

		//current���폜���A���X�g�T�C�Y�����炷
		delete current;
		--listSize;
		return iterator(next, this);
	}

	/**
	 * @brief ���X�g���̗v�f�擪����S����
	 */
	void clear() {
		Node* current = head;
		//current��nullptr�ɂȂ�܂Ń��[�v���A�m�[�h���폜
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
	 * @brief �t�@�C���ǂݍ���
	 * @param �t�@�C���p�X
	 */
	void inputData(const std::string& filePath) {
		//�܂��̓��X�g�̓��e���N���A
		clear();

		//�t�@�C���p�X����t�@�C�����J��
		std::ifstream file(filePath.c_str());

		//�����������t�@�C�����J���Ȃ������ꍇ�Areturn
		if (!file.is_open()) {
			return;
		}

		std::string line = {};

		//��s����List�ɒǉ�
		while (std::getline(file, line)) {
			if (line.empty()) continue;  //�����󂾂����ꍇ�A���s

			//�ŏ��̃^�u�L�[���͂̈ʒu������
			std::size_t tab = line.find('\t');

			// tab���Ȃ��ꍇ�A�X�L�b�v
			if (tab == std::string::npos) continue;

			std::string inputScore = line.substr(0, tab);
			std::string name = line.substr(tab + 1);
			ScoreData data{};
			//�����������ꍇ�AinputScore�𐔎��ɕϊ�
			try { 
				data.score = std::stoi(inputScore);
			}
			// �����ł͂Ȃ��ꍇ�A�X�L�b�v
			catch (...) { 
				continue; 
			}              
			data.userName = name;

			// �����Ƀm�[�h��ǉ�
			insertData(cend(), data);
		}

		//�t�@�C�������
		file.close();
	}

	/**
	 * @brief �ǂݍ��񂾓��e�̏o��
	 * @return ������(string)
	 */
	std::string outputData() const{
		std::string outputLine = {};
		Node* current = head;

		//current��nullptr�ɂȂ�܂Ń��[�v
		while (current != nullptr) {
			//�������ǉ����A���s
			outputLine += std::to_string(current->data.score);  //�X�R�A�𕶎���ɕϊ����A
			outputLine += '\t';   //�^�u��ǉ�
			outputLine += current->data.userName;  //���O��ǉ���
			outputLine += '\n';   //���s

			//���̃m�[�h��
			current = current->nextNode;
		}

		//�������Ԃ�
		return outputLine;
	}

	/**
	 * @brief �f�t�H���g�R���X�g���N�^�B
	 */
	DoublyLinkedList() = default;

	/**
	 * @brief �f�X�g���N�^�Ń��X�g�̓��e���S����
	 */
	~DoublyLinkedList() {
		clear(); 
	}

	/**
	 * @brief �R�s�[�R���X�g���N�^���폜�B
	 */
	DoublyLinkedList(const DoublyLinkedList&) = delete;

	/**
	 * @brief �R�s�[������Z�q���폜�B
	 */
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

	/**
	 * @brief  �ʒunodePos�̒��O�ɑ}��(iterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @param  data    ���̓f�[�^
	 * @return �����ł����true�A�s���C�e���[�^���̏ꍇ��false��Ԃ�
	 */
	bool insertData(const iterator& nodePos, const ScoreData& data) {
		//�C�e���[�^�̏��L�҂������łȂ��ꍇ�Afalse��Ԃ�
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
	 * @brief  �ʒunodePos�̒��O�ɑ}��(const_iterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @param   data   ���̓f�[�^
	 * @return �����ł����true�A�s���C�e���[�^���̏ꍇ��false��Ԃ�
	 */
	bool insertData(const const_iterator& nodePos, const ScoreData& data) {
		//�C�e���[�^�̏��L�҂������łȂ��ꍇ�Afalse��Ԃ�
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
	 * @brief  �ʒunodePos�ɂ���v�f���폜(iterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @return �����ł����true�A�����ċ�Ahost�s��v�AnodePos==end�������͕s���ł����false��Ԃ�
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
	 * @brief  �ʒunodePos�ɂ���v�f���폜(const_iterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @return �����ł����true�A���s�̏ꍇ��false��Ԃ�
	 */
	bool deleteData(const const_iterator& nodePos) {
		if (listSize == 0)               return false;
		if (nodePos.host != this)           return false;
		if (nodePos.node == nullptr)         return false;
		if (!containsNode(nodePos.node))     return false;

		return deleteData(iterator(nodePos.node, this));
	}
};