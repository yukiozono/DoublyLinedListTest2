#include "pch.h"
#include "DoublyLinkedList.h"
#include <type_traits>

/**
* @brief ID0_0     リストが空である場合の戻り値
*/
TEST(DoublyLinkedListTest, ID0_0_ifListEmpty_return0) {
    DoublyLinkedList list;

    EXPECT_EQ(0, list.size());        
    EXPECT_EQ(std::string(), list.outputData());
}

/**
* @brief ID0_1     リスト末尾への挿入を行った際の戻り値
*/
TEST(DoublyLinkedListTest, ID0_1_insertToTail_return1) {
    DoublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_2     リスト末尾への挿入が失敗した際の戻り値
*/
TEST(DoublyLinkedListTest, ID0_2_ifInsertToTailFailed_return0) {
    DoublyLinkedList list1, list2;
    list2.insertData(list2.cend(), ScoreData{ 1, "A" });

    //list1にlist2の先頭イテレータを渡す(失敗)
    list1.insertData(list2.begin(), ScoreData{ 2, "B" });

    EXPECT_EQ(0, list1.size());
}

/**
* @brief ID0_3     データの挿入を行った際の戻り値
*/
TEST(DoublyLinkedListTest, ID0_3_ifInsertList_return1) {
    DoublyLinkedList list;

    //データを挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_4     データの挿入に失敗した際の戻り値
*/
TEST(DoublyLinkedListTest, ID0_4_ifInsertListFailed_return0) {
    DoublyLinkedList list1, list2;
    list1.insertData(list1.cend(), ScoreData{ 1, "A" });

    //list2にlist1のイテレータを渡す(失敗)
    list2.insertData(list1.cend(), ScoreData{ 2, "B" });

    EXPECT_EQ(0, list2.size());
}

/**
* @brief ID0_5     データの削除を行った際の戻り値
*/
TEST(DoublyLinkedListTest, ID0_5_ifDeleteList_return0) {
    DoublyLinkedList list;
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //データ削除
    list.deleteData(list.begin());

    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_6     データの削除が失敗した際の戻り値
*/
TEST(DoublyLinkedListTest, ID0_6_ifDeleteListFailed_return1) {
    DoublyLinkedList list;
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //存在しないノードend()を指定し、削除
    int result = list.deleteData(list.end());
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_7     リストが空である場合に、データの削除を行った際の戻り値
*/
TEST(DoublyLinkedListTest, ID0_7_ifListEmptyDeleteData_return0) {
    DoublyLinkedList list;

    //要素を追加せずそのままノード削除を指定
    list.deleteData(list.end());
    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_8     constのメソッドであるか(ビルドが通るので、constである)
*/
size_t(DoublyLinkedList::* checkConst)() const = &DoublyLinkedList::size;

/**
* @brief ID0_9     リストが空である場合に、挿入した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_9_ifListEmptyInsert_returnTRUE) {
    DoublyLinkedList list;
    
    //先頭へ挿入を試み、成功かを返す
    bool check= list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    EXPECT_TRUE(check);

    //リストをクリアして再検証
    list.clear();

    //末尾へ挿入を試み、成功かを返す
    check = list.insertData(list.cend(), ScoreData{ 2, "B" });
    EXPECT_TRUE(check);

    //さらに末尾へ挿入を試み、2,Bがずれているかを確認
    check = list.insertData(list.cend(), ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //正しい位置に2,Bがあるかチェック
    DoublyLinkedList::const_iterator it = list.begin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);

    //一つ前進し、内容をチェック
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);


}

/**
* @brief ID0_10    リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_10_ifListHasSeveralNodesInsertHeadIterator_returnTRUE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //さらに先頭へ挿入
    bool check = list.insertData(list.cbegin(), ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //正しい位置に2,Bがあるかチェック
    DoublyLinkedList::const_iterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_11        リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_11_ifListHasSeveralNodesInsertTailIterator_returnTRUE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //末尾へ挿入
    bool check = list.insertData(list.cend(), ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //正しい位置に3,Cがあるかチェック
    DoublyLinkedList::const_iterator it = list.cbegin();
    DoublyLinkedList::const_iterator last = it;
    for (; it != list.cend(); ++it) {
        last = it;
    }
    EXPECT_EQ(3, (*last).score);
    EXPECT_EQ(std::string("C"), (*last).userName);
}

/**
* @brief ID0_12        リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_12_ifListHasSeveralNodesInsertMidIterator_returnTRUE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });

    DoublyLinkedList::iterator it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    bool check= list.insertData(it, ScoreData{ 2,"B" });
    EXPECT_TRUE(check);
    EXPECT_EQ(std::string("3\tC\n2\tB\n1\tA\n"), list.outputData());

    //要素列の先頭と末尾に挿入を行った場合のケースはID0_10とID0_11にてテスト済なので省略
}

/**
* @brief ID0_13        ConstIteratorを指定して挿入を行った際の挙動
*/
TEST(DoublyLinkedListTest, ID0_13_handConstIteratorAndInsert_returnTRUE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });
    list.insertData(list.cbegin(), ScoreData{ 4, "D" });

    //ConstIteratorを指定し、中間位置まで移動させる
    DoublyLinkedList::const_iterator it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    bool check = list.insertData(it, ScoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //先頭に挿入
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //末尾に挿入
    list.insertData(list.cbegin(), ScoreData{ 5, "E" });
    EXPECT_EQ(std::string("5\tE\n4\tD\n3\tC\n2\tB\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_14        不正なイテレータを渡して、挿入した場合の挙動
*/
TEST(DoublyLinkedListTest, ID0_14_InsertInvalidIterator_returnFALSE) {
    DoublyLinkedList list1, list2;
    list1.insertData(list1.cend(), ScoreData{ 1, "A" });

    //list2にlist1のイテレータを渡す(失敗)
    bool check = list2.insertData(list1.begin(), ScoreData{ 2, "B" });

    EXPECT_FALSE(check);

    //中身もチェックする
    EXPECT_EQ(std::string(), list2.outputData());
}

/**
* @brief ID0_15        非constのメソッドであるか(意図されたビルドエラーのため、コメントアウト)
*/
//bool (DoublyLinkedList::* checkNotConst)(const DoublyLinkedList::iterator&, const ScoreData&) const= &DoublyLinkedList::insertData;

/**
* @brief ID0_16        リストが空である場合に、削除を行った際の挙動
*/
TEST(DoublyLinkedListTest, ID0_16_deleteNodeWhileEmpty_returnFALSE) {
    DoublyLinkedList list;

    //要素を追加せずそのままノード削除を指定
      //末尾を指定し、チェック
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);

      //先頭を指定し、チェック
    check = list.deleteData(list.cbegin());
    EXPECT_FALSE(check);

    //中身もチェックする
    EXPECT_EQ(std::string(), list.outputData());

}

/**
* @brief ID0_17        リストに複数の要素がある場合に、先頭イテレータを渡して、削除した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_17_ifListHasSeveralNodesInsertHeadIterator_andDelete_returnTRUE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //さらに先頭へ挿入
    list.insertData(list.cbegin(), ScoreData{ 3,"C" });

    //先頭要素を削除
    bool check = list.deleteData(list.cbegin());
    EXPECT_TRUE(check);

    //中身もチェックする
    EXPECT_EQ(std::string("2\tB\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_18        リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_18_ifListHasSeveralNodesInsertTailIterator_andDelete_returnFALSE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });


    //末尾へ挿入
    list.insertData(list.cend(), ScoreData{ 3,"C" });

    //要素を削除
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);
}

/**
* @brief ID0_19        リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_19_ifListHasSeveralNodesInsertMidIterator_andDelete_returnTRUE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });

    DoublyLinkedList::iterator it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, ScoreData{ 2,"B" });

    //中間のイテレータに戻す
    --it;

    //中間の要素を削除
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);

    //中身もチェックする
    EXPECT_EQ(std::string("3\tC\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_20        ConstIteratorを指定して削除を行った際の挙動
*/
TEST(DoublyLinkedListTest, ID0_20_handConstIteratorAndInsert_andDelete_returnTRUE) {
    DoublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });

    //ConstIteratorを指定し、中間位置まで移動させる
    DoublyLinkedList::const_iterator it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, ScoreData{ 2,"B" });

    --it;

    //中間の要素を削除
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);
    
    //中身もチェックする
    EXPECT_EQ(std::string("3\tC\n1\tA\n"), list.outputData());
}

/**
* @brief ID0_21        不正なイテレータを渡して、削除した場合の挙動
*/
TEST(DoublyLinkedListTest, ID0_21_deleteInvalidIterator_returnFALSE) {
    DoublyLinkedList list1, list2;
    list1.insertData(list1.cend(), ScoreData{ 1, "A" });

    //list2にlist1のイテレータを渡し、削除させる(失敗)
    bool check = list2.deleteData(list1.begin());

    EXPECT_FALSE(check);

    //中身もチェックする
    EXPECT_EQ(std::string(), list2.outputData());
}

/**
* @brief ID0_22        非constのメソッドであるか(意図されたビルドエラーのため、コメントアウト)
*/
//bool (DoublyLinkedList::* checkNotConst)(const DoublyLinkedList::iterator&) const= &DoublyLinkedList::deleteData;

/**
* @brief ID0_23        リストが空である場合に、呼び出した際の挙動
*/

/**
* @brief ID0_24        リストに要素が一つある場合に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_24_ifHaveOneNodeInList_returnBeginIterator) {
    DoublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    
    //先頭イテレータを確認
    DoublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);
}

/**
* @brief ID0_25        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_25_ifHaveMoreThanTwoNodeInList_returnBeginIterator) {
    DoublyLinkedList list;

    //先頭に文字列を挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });

    //先頭イテレータを確認
    DoublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_26        データの挿入を行った後に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_26_afterInserted_returnBeginIterator) {
    DoublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    //先頭イテレータを確認
    DoublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);

    //先頭にに文字列を挿入
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });
    //先頭イテレータを確認
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, ScoreData{ 2,"B" });
    //再度先頭イテレータを確認
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
    
}

/**
* @brief ID0_27        データの削除を行った後に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_27_afterDeleted_returnBeginIterator) {
    DoublyLinkedList list;

    //要素を追加
    list.insertData(list.cbegin(), ScoreData{ 1,"A" });
    list.insertData(list.cbegin(), ScoreData{ 2,"B" });
    list.insertData(list.cbegin(), ScoreData{ 3,"C" });
    
    DoublyLinkedList::iterator it = list.begin();
    ++it;

    //中間要素を削除
    list.deleteData(it);

    //先頭に戻し、要素をチェック
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //末尾要素を削除
    ++it;
    list.deleteData(it);

    //先頭に戻し、要素をチェック
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //先頭要素を追加し、削除
    list.insertData(list.begin(), ScoreData{ 1,"A" });
    
    //3Cを指しているため、一度itを戻す
    it = list.begin();
    list.deleteData(it);

    //先頭に戻し、要素をチェック
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_28        constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック(意図されたビルドエラーのため、コメントアウト)
*/
//bool (DoublyLinkedList::* checkConst)(const DoublyLinkedList::iterator&) const = &DoublyLinkedList::iterator;

/**
* @brief ID0_29        リストが空である場合に、呼び出した際の挙動
*/

/**
* @brief ID0_30        リストに要素が一つある場合に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_30_ifHaveOneNodeInList_returnBeginConstIterator) {
    DoublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), ScoreData{ 1, "A" });

    //先頭イテレータを確認
    DoublyLinkedList::const_iterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);
}

/**
* @brief ID0_31        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_31_ifHaveMoreThanTwoNodeInList_returnBeginConstIterator) {
    DoublyLinkedList list;

    //先頭に文字列を挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });

    //先頭イテレータを確認
    DoublyLinkedList::const_iterator it = list.cbegin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_32        データの挿入を行った後に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_32_afterInserted_returnBeginConstIterator) {
    DoublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), ScoreData{ 1, "A" });
    //先頭イテレータを確認
    DoublyLinkedList::const_iterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);

    //先頭にに文字列を挿入
    list.insertData(list.cbegin(), ScoreData{ 3, "C" });
    //先頭イテレータを確認
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, ScoreData{ 2,"B" });
    //再度先頭イテレータを確認
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

}

/**
* @brief ID0_33        データの削除を行った後に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_23_afterDeleted_returnBeginConstIterator) {
    DoublyLinkedList list;

    //要素を追加
    list.insertData(list.cbegin(), ScoreData{ 1,"A" });
    list.insertData(list.cbegin(), ScoreData{ 2,"B" });
    list.insertData(list.cbegin(), ScoreData{ 3,"C" });

    DoublyLinkedList::const_iterator it = list.cbegin();
    ++it;

    //中間要素を削除
    list.deleteData(it);

    //先頭に戻し、要素をチェック
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //末尾要素を削除
    ++it;
    list.deleteData(it);

    //先頭に戻し、要素をチェック
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //先頭要素を追加し、削除
    list.insertData(list.cbegin(), ScoreData{ 1,"A" });

    //3Cを指しているため、一度itを戻す
    it = list.begin();
    list.deleteData(it);

    //先頭に戻し、要素をチェック
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_34        constのメソッドであるか
*/

/**
* @brief ID0_35        リストが空である場合に、呼び出した際の挙動
*/

/**
* @brief ID0_36        リストに要素が一つある場合に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_36_ifHaveOneNodeInList_returnEndIterator) {
    DoublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.end(), ScoreData{ 1, "A" });

    //末尾イテレータを取得
    DoublyLinkedList::iterator endIt = list.end();

    //末尾のイテレータを元にデータを挿入
    list.insertData(endIt, ScoreData{ 2, "B" });

    //末尾のイテレータで正しく挿入できているかを確認
    DoublyLinkedList::iterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_37        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_37_ifHaveMoreThanTwoNodeInList_returnEndIterator) {
    DoublyLinkedList list;

    //先頭に文字列を挿入
    list.insertData(list.cbegin(), ScoreData{ 1, "A" });
    list.insertData(list.cbegin(), ScoreData{ 2, "B" });

    //末尾イテレータを取得
    DoublyLinkedList::iterator endIt = list.end();

    //末尾のイテレータを元にデータを挿入
    list.insertData(endIt, ScoreData{ 3, "C" });

    //末尾のイテレータで正しく挿入できているかを確認
    DoublyLinkedList::iterator it = list.begin();
    ++it;
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_38        データの挿入を行った後に、呼び出した際の挙動
*/
TEST(DoublyLinkedListTest, ID0_38_afterInserted_returnEndIterator) {
    //DoublyLinkedList list;

    ////末尾イテレータを取得
    //DoublyLinkedList::iterator endIt = list.end();

    ////末尾のイテレータを元にデータを挿入
    //list.insertData(endIt, ScoreData{ 2, "B" });

    ////末尾のイテレータで正しく挿入できているかを確認
    //DoublyLinkedList::iterator it = list.begin();
    //++it;
    //EXPECT_EQ(2, (*it).score);
    //EXPECT_EQ(std::string("B"), (*it).userName);

    ////先頭にに文字列を挿入
    //list.insertData(list.begin(), ScoreData{ 1, "A" });
    //
    ////さらに末尾に要素を挿入
    //list.insertData(endIt, ScoreData{ 4, "D" });

    ////末尾のイテレータで正しく挿入できているかを確認
    //EXPECT_EQ(std::string("1\tA\n2\tB\n4\tD\n"), list.outputData());


    //////中間のイテレータを渡して挿入
    ////it = list.begin();
    ////it++;
    ////list.insertData(it, ScoreData{ 3,"C" });
    ////
    ////EXPECT_EQ(std::string("1\tA\n2\tB\n4\tD\n"), list.outputData());

}

/**
* @brief ID0_39        データの削除を行った後に、呼び出した際の挙動
*/

/**
* @brief ID0_40        constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
*/

/**
* @brief ID0_41        リストが空である場合に、呼び出した際の挙動
*/

/**
* @brief ID0_42        リストに要素が一つある場合に、呼び出した際の挙動
*/

/**
* @brief ID0_43        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/

/**
* @brief ID0_44        データの挿入を行った後に、呼び出した際の挙動
*/

/**
* @brief ID0_45        データの削除を行った後に、呼び出した際の挙動
*/

/**
* @brief ID0_46        constのメソッドであるか
*/