#include "pch.h"
#include "DoublyLinkedList.h"
#include <type_traits>

/**
* @brief ID0_0     ���X�g����ł���ꍇ�̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_0_ifListEmpty_return0) {
    DoublyLinkedList list;

    EXPECT_EQ(0, list.size());        
    EXPECT_EQ(std::string(), list.outputData());
}

/**
* @brief ID0_1     ���X�g�����ւ̑}�����s�����ۂ̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_1_insertToTail_return1) {
    DoublyLinkedList list;

    //�����ɕ������}��
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_2     ���X�g�����ւ̑}�������s�����ۂ̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_2_ifInsertToTailFailed_return0) {
    DoublyLinkedList list1, list2;
    list2.insertData(list2.cend(), ScoreData{ 1, "A" });

    //list1��list2�̐擪�C�e���[�^��n��(���s)
    list1.insertData(list2.begin(), ScoreData{ 2, "B" });

    EXPECT_EQ(0, list1.size());
}

/**
* @brief ID0_3     �f�[�^�̑}�����s�����ۂ̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_3_ifInsertList_return1) {
    DoublyLinkedList list;

    //�f�[�^��}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_4     �f�[�^�̑}���Ɏ��s�����ۂ̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_4_ifInsertListFailed_return0) {
    DoublyLinkedList list1, list2;
    list1.insertData(list1.cend(), ScoreData{ 1, "A" });

    //list2��list1�̃C�e���[�^��n��(���s)
    list2.insertData(list1.cend(), ScoreData{ 2, "B" });

    EXPECT_EQ(0, list2.size());
}

/**
* @brief ID0_5     �f�[�^�̍폜���s�����ۂ̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_5_ifDeleteList_return0) {
    DoublyLinkedList list;
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //�f�[�^�폜
    list.deleteData(list.begin());

    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_6     �f�[�^�̍폜�����s�����ۂ̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_6_ifDeleteListFailed_return1) {
    DoublyLinkedList list;
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //���݂��Ȃ��m�[�hend()���w�肵�A�폜
    int result = list.deleteData(list.end());
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_7     ���X�g����ł���ꍇ�ɁA�f�[�^�̍폜���s�����ۂ̖߂�l
*/
TEST(DoublyLinkedListTest, ID0_7_ifListEmptyDeleteData_return0) {
    DoublyLinkedList list;

    //�v�f��ǉ��������̂܂܃m�[�h�폜���w��
    list.deleteData(list.end());
    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_8     const�̃��\�b�h�ł��邩(�r���h���ʂ�̂ŁAconst�ł���)
*/
size_t(DoublyLinkedList::* checkConst)() const = &DoublyLinkedList::size;

/**
* @brief ID0_9     ���X�g����ł���ꍇ�ɁA�}�������ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_9_ifListEmptyInsert_returnTRUE) {
    DoublyLinkedList list;
    
    //�擪�֑}�������݁A��������Ԃ�
    bool check= list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    EXPECT_TRUE(check);

    //���X�g���N���A���čČ���
    list.clear();

    //�����֑}�������݁A��������Ԃ�
    check = list.insertData(list.cend(), ScoreData{ 2, "B" });
    EXPECT_TRUE(check);

    //����ɖ����֑}�������݁A2,B������Ă��邩���m�F
    check = list.insertData(list.cend(), ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�������ʒu��2,B�����邩�`�F�b�N
    DoublyLinkedList::const_iterator it = list.begin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);

    //��O�i���A���e���`�F�b�N
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);


}

/**
* @brief ID0_10    ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�C�e���[�^��n���āA�}�������ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_10_ifListHasSeveralNodesInsertHeadIterator_returnTRUE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //����ɐ擪�֑}��
    bool check = list.insertData(list.cbegin(), ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�������ʒu��2,B�����邩�`�F�b�N
    DoublyLinkedList::const_iterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_11        ���X�g�ɕ����̗v�f������ꍇ�ɁA�����C�e���[�^��n���āA�}�������ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_11_ifListHasSeveralNodesInsertTailIterator_returnTRUE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //�����֑}��
    bool check = list.insertData(list.cend(), ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�������ʒu��3,C�����邩�`�F�b�N
    DoublyLinkedList::const_iterator it = list.cbegin();
    DoublyLinkedList::const_iterator last = it;
    for (; it != list.cend(); ++it) {
        last = it;
    }
    EXPECT_EQ(3, (*last).score);
    EXPECT_EQ(std::string("C"), (*last).userName);
}

/**
* @brief ID0_12        ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�ł������ł��Ȃ��C�e���[�^��n���đ}�������ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_12_ifListHasSeveralNodesInsertMidIterator_returnTRUE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });

    DoublyLinkedList::iterator it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    bool check= list.insertData(it, ScoreData{ 2,"B" });
    EXPECT_TRUE(check);
    EXPECT_EQ(std::string("3\tC\n2\tB\n1\tA\n"), list.outputData());

    //�v�f��̐擪�Ɩ����ɑ}�����s�����ꍇ�̃P�[�X��ID0_10��ID0_11�ɂăe�X�g�ςȂ̂ŏȗ�
}

/**
* @brief ID0_13        ConstIterator���w�肵�đ}�����s�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_13_handConstIteratorAndInsert_returnTRUE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });
    list.insertData(list.cbegin(), ScoreData{ 4, "D" });

    //ConstIterator���w�肵�A���Ԉʒu�܂ňړ�������
    DoublyLinkedList::const_iterator it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    bool check = list.insertData(it, ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�擪�ɑ}��
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //�����ɑ}��
    list.insertData(list.cbegin(), ScoreData{ 5, "E" });
    EXPECT_EQ(std::string("5\tE\n4\tD\n3\tC\n2\tB\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_14        �s���ȃC�e���[�^��n���āA�}�������ꍇ�̋���
*/
TEST(DoublyLinkedListTest, ID0_14_InsertInvalidIterator_returnFALSE) {
    DoublyLinkedList list1, list2;
    list1.insertData(list1.cend(), ScoreData{ 1, "A" });

    //list2��list1�̃C�e���[�^��n��(���s)
    bool check = list2.insertData(list1.begin(), ScoreData{ 2, "B" });

    EXPECT_FALSE(check);

    //���g���`�F�b�N����
    EXPECT_EQ(std::string(), list2.outputData());
}

/**
* @brief ID0_15        ��const�̃��\�b�h�ł��邩(�Ӑ}���ꂽ�r���h�G���[�̂��߁A�R�����g�A�E�g)
*/
//bool (DoublyLinkedList::* checkNotConst)(const DoublyLinkedList::iterator&, const ScoreData&) const= &DoublyLinkedList::insertData;

/**
* @brief ID0_16        ���X�g����ł���ꍇ�ɁA�폜���s�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_16_deleteNodeWhileEmpty_returnFALSE) {
    DoublyLinkedList list;

    //�v�f��ǉ��������̂܂܃m�[�h�폜���w��
      //�������w�肵�A�`�F�b�N
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);

      //�擪���w�肵�A�`�F�b�N
    check = list.deleteData(list.cbegin());
    EXPECT_FALSE(check);

    //���g���`�F�b�N����
    EXPECT_EQ(std::string(), list.outputData());

}

/**
* @brief ID0_17        ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�C�e���[�^��n���āA�폜�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_17_ifListHasSeveralNodesInsertHeadIterator_andDelete_returnTRUE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //����ɐ擪�֑}��
    list.insertData(list.cbegin(), ScoreData{ 3,"C" });

    //�擪�v�f���폜
    bool check = list.deleteData(list.cbegin());
    EXPECT_TRUE(check);

    //���g���`�F�b�N����
    EXPECT_EQ(std::string("2\tB\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_18        ���X�g�ɕ����̗v�f������ꍇ�ɁA�����C�e���[�^��n���āA�폜�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_18_ifListHasSeveralNodesInsertTailIterator_andDelete_returnFALSE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //�����֑}��
    list.insertData(list.cend(), ScoreData{ 3,"C" });

    //�v�f���폜
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);
}

/**
* @brief ID0_19        ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�ł������ł��Ȃ��C�e���[�^��n���č폜�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_19_ifListHasSeveralNodesInsertMidIterator_andDelete_returnTRUE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });

    DoublyLinkedList::iterator it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, ScoreData{ 2,"B" });

    //���Ԃ̃C�e���[�^�ɖ߂�
    --it;

    //���Ԃ̗v�f���폜
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);

    //���g���`�F�b�N����
    EXPECT_EQ(std::string("3\tC\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_20        ConstIterator���w�肵�č폜���s�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_20_handConstIteratorAndInsert_andDelete_returnTRUE) {
    DoublyLinkedList list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });

    //ConstIterator���w�肵�A���Ԉʒu�܂ňړ�������
    DoublyLinkedList::const_iterator it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, ScoreData{ 2,"B" });

    --it;

    //���Ԃ̗v�f���폜
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);
    
    //���g���`�F�b�N����
    EXPECT_EQ(std::string("3\tC\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_21        �s���ȃC�e���[�^��n���āA�폜�����ꍇ�̋���
*/
TEST(DoublyLinkedListTest, ID0_21_deleteInvalidIterator_returnFALSE) {
    DoublyLinkedList list1, list2;
    list1.insertData(list1.cend(), ScoreData{ 1, "A" });

    //list2��list1�̃C�e���[�^��n���A�폜������(���s)
    bool check = list2.deleteData(list1.begin());

    EXPECT_FALSE(check);

    //���g���`�F�b�N����
    EXPECT_EQ(std::string(), list2.outputData());
}

/**
* @brief ID0_22        ��const�̃��\�b�h�ł��邩(�Ӑ}���ꂽ�r���h�G���[�̂��߁A�R�����g�A�E�g)
*/
//bool (DoublyLinkedList::* checkNotConst)(const DoublyLinkedList::iterator&) const= &DoublyLinkedList::deleteData;

/**
* @brief ID0_23        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_24        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_24_ifHaveOneNodeInList_returnBeginIterator) {
    DoublyLinkedList list;

    //�����ɕ������}��
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    
    //�擪�C�e���[�^���m�F
    DoublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);
}

/**
* @brief ID0_25        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_25_ifHaveMoreThanTwoNodeInList_returnBeginIterator) {
    DoublyLinkedList list;

    //�擪�ɕ������}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });

    //�擪�C�e���[�^���m�F
    DoublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_26        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_26_afterInserted_returnBeginIterator) {
    DoublyLinkedList list;

    //�����ɕ������}��
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    //�擪�C�e���[�^���m�F
    DoublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);

    //�擪�ɂɕ������}��
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });
    //�擪�C�e���[�^���m�F
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, ScoreData{ 2,"B" });
    //�ēx�擪�C�e���[�^���m�F
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
    
}

/**
* @brief ID0_27        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_27_afterDeleted_returnBeginIterator) {
    DoublyLinkedList list;

    //�v�f��ǉ�
    list.insertData(list.cbegin(), ScoreData{ 1,"A" });
    list.insertData(list.cbegin(), ScoreData{ 2,"B" });
    list.insertData(list.cbegin(), ScoreData{ 3,"C" });
    
    DoublyLinkedList::iterator it = list.begin();
    ++it;

    //���ԗv�f���폜
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //�����v�f���폜
    ++it;
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //�擪�v�f��ǉ����A�폜
    list.insertData(list.begin(), ScoreData{ 1,"A" });
    
    //3C���w���Ă��邽�߁A��xit��߂�
    it = list.begin();
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_28        const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N(�Ӑ}���ꂽ�r���h�G���[�̂��߁A�R�����g�A�E�g)
*/
//bool (DoublyLinkedList::* checkConst)(const DoublyLinkedList::iterator&) const = &DoublyLinkedList::iterator;

/**
* @brief ID0_29        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_30        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_30_ifHaveOneNodeInList_returnBeginConstIterator) {
    DoublyLinkedList list;

    //�����ɕ������}��
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //�擪�C�e���[�^���m�F
    DoublyLinkedList::const_iterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);
}

/**
* @brief ID0_31        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_31_ifHaveMoreThanTwoNodeInList_returnBeginConstIterator) {
    DoublyLinkedList list;

    //�擪�ɕ������}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });

    //�擪�C�e���[�^���m�F
    DoublyLinkedList::const_iterator it = list.cbegin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_32        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_32_afterInserted_returnBeginConstIterator) {
    DoublyLinkedList list;

    //�����ɕ������}��
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    //�擪�C�e���[�^���m�F
    DoublyLinkedList::const_iterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);

    //�擪�ɂɕ������}��
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });
    //�擪�C�e���[�^���m�F
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, ScoreData{ 2,"B" });
    //�ēx�擪�C�e���[�^���m�F
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

}

/**
* @brief ID0_33        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_23_afterDeleted_returnBeginConstIterator) {
    DoublyLinkedList list;

    //�v�f��ǉ�
    list.insertData(list.cbegin(), ScoreData{ 1,"A" });
    list.insertData(list.cbegin(), ScoreData{ 2,"B" });
    list.insertData(list.cbegin(), ScoreData{ 3,"C" });

    DoublyLinkedList::const_iterator it = list.cbegin();
    ++it;

    //���ԗv�f���폜
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //�����v�f���폜
    ++it;
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //�擪�v�f��ǉ����A�폜
    list.insertData(list.cbegin(), ScoreData{ 1,"A" });

    //3C���w���Ă��邽�߁A��xit��߂�
    it = list.begin();
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_34        const�̃��\�b�h�ł��邩
*/

/**
* @brief ID0_35        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_36        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_36_ifHaveOneNodeInList_returnEndIterator) {
    DoublyLinkedList list;

    //�����ɕ������}��
    list.insertData(list.end(), ScoreData{ 1, "A" });

    //�����C�e���[�^���擾
    DoublyLinkedList::iterator endIt = list.end();

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(endIt, ScoreData{ 2, "B" });

    //�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    DoublyLinkedList::iterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_37        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_37_ifHaveMoreThanTwoNodeInList_returnEndIterator) {
    DoublyLinkedList list;

    //�擪�ɕ������}��
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });

    //�����C�e���[�^���擾
    DoublyLinkedList::iterator endIt = list.end();

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(endIt, ScoreData{ 3, "C" });

    //�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    DoublyLinkedList::iterator it = list.begin();
    ++it;
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_38        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/
TEST(DoublyLinkedListTest, ID0_38_afterInserted_returnEndIterator) {
    //DoublyLinkedList list;

    ////�����C�e���[�^���擾
    //DoublyLinkedList::iterator endIt = list.end();

    ////�����̃C�e���[�^�����Ƀf�[�^��}��
    //list.insertData(endIt, ScoreData{ 2, "B" });

    ////�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    //DoublyLinkedList::iterator it = list.begin();
    //++it;
    //EXPECT_EQ(2, (*it).score);
    //EXPECT_EQ(std::string("B"), (*it).userName);

    ////�擪�ɂɕ������}��
    //list.insertData(list.begin(), ScoreData{ 1, "A" });
    //
    ////����ɖ����ɗv�f��}��
    //list.insertData(endIt, ScoreData{ 4, "D" });

    ////�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    //EXPECT_EQ(std::string("1\tA\n2\tB\n4\tD\n"), list.outputData());


    //////���Ԃ̃C�e���[�^��n���đ}��
    ////it = list.begin();
    ////it++;
    ////list.insertData(it, ScoreData{ 3,"C" });
    ////
    ////EXPECT_EQ(std::string("1\tA\n2\tB\n4\tD\n"), list.outputData());

}

/**
* @brief ID0_39        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_40        const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N
*/

/**
* @brief ID0_41        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_42        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_43        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_44        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_45        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/

/**
* @brief ID0_46        const�̃��\�b�h�ł��邩
*/