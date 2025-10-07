#include "pch.h"
#include "../ListReadingTxt/DoublyLinkedList.h"

/**
* @brief ID0_0     リストが空である場合の戻り値
*/
TEST(doublyLinkedListTest, ID0_0_ifListEmpty_return0) {
    doublyLinkedList list;

    EXPECT_EQ(0, list.size());        
}

/**
* @brief ID0_1     リスト末尾への挿入を行った際の戻り値
*/
TEST(doublyLinkedListTest, ID0_1_insertToTail_return1) {
    doublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), scoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_2     リスト末尾への挿入が失敗した際の戻り値
*/
TEST(doublyLinkedListTest, ID0_2_ifInsertToTailFailed_return0) {
    doublyLinkedList list1, list2;
    list2.insertData(list2.cend(), scoreData{ 1, "A" });

    //list1にlist2の先頭イテレータを渡す(失敗)
    list1.insertData(list2.begin(), scoreData{ 2, "B" });

    EXPECT_EQ(0, list1.size());
}

/**
* @brief ID0_3     データの挿入を行った際の戻り値
*/
TEST(doublyLinkedListTest, ID0_3_ifInsertList_return1) {
    doublyLinkedList list;

    //データを挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_4     データの挿入に失敗した際の戻り値
*/
TEST(doublyLinkedListTest, ID0_4_ifInsertListFailed_return0) {
    doublyLinkedList list1, list2;

    //list2にlist1のイテレータを渡す(失敗)
    list2.insertData(list1.cend(), scoreData{ 2, "B" });

    EXPECT_EQ(0, list2.size());
}

/**
* @brief ID0_5     データの削除を行った際の戻り値
*/
TEST(doublyLinkedListTest, ID0_5_ifDeleteList_return0) {
    doublyLinkedList list;
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //データ削除
    list.deleteData(list.begin());

    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_6     データの削除が失敗した際の戻り値
*/
TEST(doublyLinkedListTest, ID0_6_ifDeleteListFailed_return1) {
    doublyLinkedList list;
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //存在しないノードend()を指定し、削除
    int result = list.deleteData(list.end());
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_7     リストが空である場合に、データの削除を行った際の戻り値
*/
TEST(doublyLinkedListTest, ID0_7_ifListEmptyDeleteData_return0) {
    doublyLinkedList list;

    //要素を追加せずそのままノード削除を指定
    list.deleteData(list.end());
    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_8     constのメソッドであるか(ビルドが通るので、constである)
*/
size_t(doublyLinkedList::* checkConst)() const = &doublyLinkedList::size;

/**
* @brief ID0_9     リストが空である場合に、挿入した際の挙動
*/
TEST(doublyLinkedListTest, ID0_9_ifListEmptyInsert_returnTRUE) {
    doublyLinkedList list;
    
    //先頭へ挿入を試み、成功かを返す
    bool check= list.insertData(list.cbegin(), scoreData{ 1, "A" });
    EXPECT_TRUE(check);

    //リストをクリアして再検証
    list.clear();

    //末尾へ挿入を試み、成功かを返す
    check = list.insertData(list.cend(), scoreData{ 2, "B" });
    EXPECT_TRUE(check);

    //さらに末尾へ挿入を試み、2,Bがずれているかを確認
    check = list.insertData(list.cend(), scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //正しい位置に2,Bがあるかチェック
    doublyLinkedList::constIterator it = list.cbegin();
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
TEST(doublyLinkedListTest, ID0_10_ifListHasSeveralNodesInsertHeadIterator_returnTRUE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //さらに先頭へ挿入
    bool check = list.insertData(list.cbegin(), scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //正しい位置に2,Bがあるかチェック
    doublyLinkedList::constIterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_11        リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
*/
TEST(doublyLinkedListTest, ID0_11_ifListHasSeveralNodesInsertTailIterator_returnTRUE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //末尾へ挿入
    bool check = list.insertData(list.cend(), scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //正しい位置に3,Cがあるかチェック
    doublyLinkedList::constIterator it = list.cbegin();
    doublyLinkedList::constIterator last = it;
    for (; it != list.cend(); ++it) {
        last = it;
    }
    EXPECT_EQ(3, (*last).score);
    EXPECT_EQ(std::string("C"), (*last).userName);
}

/**
* @brief ID0_12        リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動
*/
TEST(doublyLinkedListTest, ID0_12_ifListHasSeveralNodesInsertMidIterator_returnTRUE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 3, "C" });

    doublyLinkedList::iterator it = list.begin();
    ++it;

    //中間のイテレータを渡して挿入
    bool check= list.insertData(it, scoreData{ 2,"B" });
    EXPECT_TRUE(check);

    //要素列の先頭と末尾に挿入を行った場合のケースはID0_10とID0_11にてテスト済なので省略
}

/**
* @brief ID0_13        ConstIteratorを指定して挿入を行った際の挙動
*/
TEST(doublyLinkedListTest, ID0_13_handConstIteratorAndInsert_returnTRUE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 2, "B" });
    list.insertData(list.cbegin(), scoreData{ 4, "D" });

    //ConstIteratorを指定し、中間位置まで移動させる
    doublyLinkedList::constIterator it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    bool check = list.insertData(it, scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //先頭に挿入
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //末尾に挿入
    list.insertData(list.cbegin(), scoreData{ 5, "E" });
}

/**
* @brief ID0_14        不正なイテレータを渡して、挿入した場合の挙動
*/
TEST(doublyLinkedListTest, ID0_14_InsertInvalidIterator_returnFALSE) {
    doublyLinkedList list1, list2;

    //list2にlist1のイテレータを渡す(失敗)
    bool check = list2.insertData(list1.begin(), scoreData{ 2, "B" });

    EXPECT_FALSE(check);

    //中身もチェックする
}

/**
* @brief ID0_15        非constのメソッドであるか(意図されたビルドエラーのため、コメントアウト)
*/
//bool (doublyLinkedList::* checkNotConst)(const doublyLinkedList::iterator&, const scoreData&) const= &doublyLinkedList::insertData;

/**
* @brief ID0_16        リストが空である場合に、削除を行った際の挙動
*/
TEST(doublyLinkedListTest, ID0_16_deleteNodeWhileEmpty_returnFALSE) {
    doublyLinkedList list;

    //要素を追加せずそのままノード削除を指定
      //末尾を指定し、チェック
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);

      //先頭を指定し、チェック
    check = list.deleteData(list.cbegin());
    EXPECT_FALSE(check);

}

/**
* @brief ID0_17        リストに複数の要素がある場合に、先頭イテレータを渡して、削除した際の挙動
*/
TEST(doublyLinkedListTest, ID0_17_ifListHasSeveralNodesInsertHeadIterator_andDelete_returnTRUE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //さらに先頭へ挿入
    list.insertData(list.cbegin(), scoreData{ 3,"C" });

    //先頭要素を削除
    bool check = list.deleteData(list.cbegin());
    EXPECT_TRUE(check);
}

/**
* @brief ID0_18        リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
*/
TEST(doublyLinkedListTest, ID0_18_ifListHasSeveralNodesInsertTailIterator_andDelete_returnFALSE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //末尾へ挿入
    list.insertData(list.cend(), scoreData{ 3,"C" });

    //要素を削除
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);
}

/**
* @brief ID0_19        リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
*/
TEST(doublyLinkedListTest, ID0_19_ifListHasSeveralNodesInsertMidIterator_andDelete_returnTRUE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 3, "C" });

    doublyLinkedList::iterator it = list.begin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, scoreData{ 2,"B" });

    //中間のイテレータに戻す
    --it;

    //中間の要素を削除
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);
}

/**
* @brief ID0_20        ConstIteratorを指定して削除を行った際の挙動
*/
TEST(doublyLinkedListTest, ID0_20_handConstIteratorAndInsert_andDelete_returnTRUE) {
    doublyLinkedList list;

    //先頭へ複数挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 3, "C" });

    //ConstIteratorを指定し、中間位置まで移動させる
    doublyLinkedList::constIterator it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, scoreData{ 2,"B" });

    --it;

    //中間の要素を削除
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);
}

/**
* @brief ID0_21        不正なイテレータを渡して、削除した場合の挙動
*/
TEST(doublyLinkedListTest, ID0_21_deleteInvalidIterator_returnFALSE) {
    doublyLinkedList list1, list2;

    //list2にlist1のイテレータを渡し、削除させる(失敗)
    bool check = list2.deleteData(list1.begin());

    EXPECT_FALSE(check);
}

/**
* @brief ID0_22        非constのメソッドであるか(意図されたビルドエラーのため、コメントアウト)
*/
//bool (doublyLinkedList::* checkNotConst)(const doublyLinkedList::iterator&) const= &doublyLinkedList::deleteData;

/**
* @brief ID0_23        リストが空である場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_23_ifHaveNoNodeInList_ReturnDummyBeginIterator) {
    doublyLinkedList list;

    //先頭と末尾イテレータを取得
    doublyLinkedList::iterator beginIt = list.begin();
    doublyLinkedList::iterator endIt = list.end();

    //両方ともダミーであるため、同値であるはず
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_24        リストに要素が一つある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_24_ifHaveOneNodeInList_returnBeginIterator) {
    doublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.end(), scoreData{ 1, "A" });
    
    //先頭イテレータを確認
    doublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);
}

/**
* @brief ID0_25        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_25_ifHaveMoreThanTwoNodeInList_returnBeginIterator) {
    doublyLinkedList list;

    //先頭に文字列を挿入
    list.insertData(list.begin(), scoreData{ 1, "A" });
    list.insertData(list.begin(), scoreData{ 2, "B" });

    //先頭イテレータを確認
    doublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_26        データの挿入を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_26_afterInserted_returnBeginIterator) {
    doublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), scoreData{ 1, "A" });
    //先頭イテレータを確認
    doublyLinkedList::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);

    //先頭にに文字列を挿入
    list.insertData(list.cbegin(), scoreData{ 3, "C" });
    //先頭イテレータを確認
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    it = list.begin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, scoreData{ 2,"B" });
    //再度先頭イテレータを確認
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
    
}

/**
* @brief ID0_27        データの削除を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_27_afterDeleted_returnBeginIterator) {
    doublyLinkedList list;

    //要素を追加
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });
    
    doublyLinkedList::iterator it = list.begin();
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
    list.insertData(list.begin(), scoreData{ 1,"A" });
    
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
/*
TEST(doublyLinkedListTest, ID0_28_checkIfPossibleToGetNonConstIterator) {
    const doublyLinkedList list;
    doublyLinkedList::iterator it = list.begin();
}
*/

/**
* @brief ID0_29        リストが空である場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_29_ifHaveNoNodeInList_ReturnDummyBeginConstIterator) {
    doublyLinkedList list;

    //先頭と末尾イテレータを取得
    doublyLinkedList::constIterator beginIt = list.cbegin();
    doublyLinkedList::constIterator endIt = list.cend();

    //両方ともダミーであるため、同値であるはず
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_30        リストに要素が一つある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_30_ifHaveOneNodeInList_returnBeginConstIterator) {
    doublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //先頭イテレータを確認
    doublyLinkedList::constIterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);
}

/**
* @brief ID0_31        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_31_ifHaveMoreThanTwoNodeInList_returnBeginConstIterator) {
    doublyLinkedList list;

    //先頭に文字列を挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });

    //先頭イテレータを確認
    doublyLinkedList::constIterator it = list.cbegin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_32        データの挿入を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_32_afterInserted_returnBeginConstIterator) {
    doublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), scoreData{ 1, "A" });
    //先頭イテレータを確認
    doublyLinkedList::constIterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).userName);

    //先頭にに文字列を挿入
    list.insertData(list.cbegin(), scoreData{ 3, "C" });
    //先頭イテレータを確認
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    it = list.cbegin();
    ++it;

    //中間のイテレータを渡して挿入
    list.insertData(it, scoreData{ 2,"B" });
    //再度先頭イテレータを確認
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

}

/**
* @brief ID0_33        データの削除を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_23_afterDeleted_returnBeginConstIterator) {
    doublyLinkedList list;

    //要素を追加
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    list.insertData(list.cbegin(), scoreData{ 2,"B" });
    list.insertData(list.cbegin(), scoreData{ 3,"C" });

    doublyLinkedList::constIterator it = list.cbegin();
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
    list.insertData(list.cbegin(), scoreData{ 1,"A" });

    //3Cを指しているため、一度itを戻す
    it = list.cbegin();
    list.deleteData(it);

    //先頭に戻し、要素をチェック
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_34        constのメソッドであるか
*/
TEST(doublyLinkedListTest, ID0_34_checkIfConst) {
    const doublyLinkedList list;
    doublyLinkedList::constIterator it = list.cbegin();  //コンパイルエラーにならない為、constである
}


/**
* @brief ID0_35        リストが空である場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_29_ifHaveNoNodeInList_ReturnDummyEndConstIterator) {
    doublyLinkedList list;

    //先頭と末尾イテレータを取得
    doublyLinkedList::constIterator beginIt = list.begin();
    doublyLinkedList::constIterator endIt = list.end();

    //両方ともダミーであるため、同値であるはず
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_36        リストに要素が一つある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_36_ifHaveOneNodeInList_returnEndIterator) {
    doublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.end(), scoreData{ 1, "A" });

    //末尾イテレータを取得
    doublyLinkedList::iterator endIt = list.end();

    //末尾のイテレータを元にデータを挿入
    list.insertData(endIt, scoreData{ 2, "B" });

    //末尾のイテレータで正しく挿入できているかを確認
    doublyLinkedList::iterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);
}

/**
* @brief ID0_37        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_37_ifHaveMoreThanTwoNodeInList_returnEndIterator) {
    doublyLinkedList list;

    //先頭に文字列を挿入
    list.insertData(list.begin(), scoreData{ 1, "A" });
    list.insertData(list.begin(), scoreData{ 2, "B" });

    //末尾イテレータを取得
    doublyLinkedList::iterator endIt = list.end();

    //末尾のイテレータを元にデータを挿入
    list.insertData(endIt, scoreData{ 3, "C" });

    //末尾のイテレータで正しく挿入できているかを確認
    doublyLinkedList::iterator it = list.begin();
    ++it;
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);
}

/**
* @brief ID0_38        データの挿入を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_38_afterInserted_returnEndIterator) {
    doublyLinkedList list;

    //末尾のイテレータを元にデータを挿入
    list.insertData(list.end(), scoreData{2, "B"});

    //末尾イテレータを取得
    doublyLinkedList::iterator endIt = list.end();

    //末尾を確認
    EXPECT_EQ(endIt,list.end());

    //先頭にに文字列を挿入
    list.insertData(list.begin(), scoreData{ 1, "A" });
    //末尾を確認
    EXPECT_EQ(endIt, list.end());
    
    //中間のイテレータを渡して挿入
    doublyLinkedList::iterator it = list.begin();
    ++it;
    list.insertData(it, scoreData{ 3,"C" });

    //末尾を確認
    EXPECT_EQ(endIt, list.end());

}

/**
* @brief ID0_39        データの削除を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_39_afterDeleted_returnEndIterator) {
    doublyLinkedList list;

    //要素を追加
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });

    doublyLinkedList::iterator it = list.begin();
    ++it;

    //中間要素を削除
    list.deleteData(it);

    //先頭に戻す
    it = list.begin();
    doublyLinkedList::iterator endIt = it;

    //末尾まで移動し、末尾と同値か確認
    ++endIt;
    ++endIt;
    EXPECT_EQ(endIt, list.end());


    //末尾要素を削除
    ++it;
    list.deleteData(it);

    //先頭に戻す
    it = list.begin();
    endIt = it;

    //末尾まで移動し、末尾と同値か確認
    ++endIt;
    EXPECT_EQ(endIt, list.end());

    //先頭要素を追加し、削除
    list.insertData(list.begin(), scoreData{ 1,"A" });
    it = list.begin();
    list.deleteData(it);

    //末尾まで移動し、末尾と同値か確認
    it = list.begin();
    endIt = it;
    ++endIt;
    EXPECT_EQ(endIt, list.end());
}

/**
* @brief ID0_40        constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック(意図されたビルドエラーのため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID0_40_checkIfPossibleToGetNonConstIterator) {
    const doublyLinkedList list;
    doublyLinkedList::iterator it = list.end();
}
*/

/**
* @brief ID0_41        リストが空である場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_41_ifHaveNoNodeInList_ReturnDummyEndConstIterator) {
    doublyLinkedList list;

    //先頭と末尾イテレータを取得
    doublyLinkedList::constIterator beginIt = list.cbegin();
    doublyLinkedList::constIterator endIt = list.cend();

    //両方ともダミーであるため、同値であるはず
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_42        リストに要素が一つある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_42_ifHaveOneNodeInList_returnEndConstIterator) {
    doublyLinkedList list;

    //末尾に文字列を挿入
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //末尾コンストイテレータを取得
    doublyLinkedList::constIterator endIt = list.cend();

    //末尾のイテレータを元にデータを挿入
    list.insertData(endIt, scoreData{ 2, "B" });

    //末尾のイテレータで正しく挿入できているかを確認
    doublyLinkedList::constIterator it = list.cbegin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).userName);

    //末尾を確認
    EXPECT_EQ(endIt, list.cend());
}

/**
* @brief ID0_43        リストに二つ以上の要素がある場合に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_43_ifHaveMoreThanTwoNodeInList_returnEndConstIterator) {
    doublyLinkedList list;

    //先頭に文字列を挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });

    //末尾イテレータを取得
    doublyLinkedList::constIterator endIt = list.cend();

    //末尾のイテレータを元にデータを挿入
    list.insertData(endIt, scoreData{ 3, "C" });

    //末尾のイテレータで正しく挿入できているかを確認
    doublyLinkedList::constIterator it = list.cbegin();
    ++it;
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).userName);

    //末尾を確認
    EXPECT_EQ(endIt, list.cend());
}

/**
* @brief ID0_44        データの挿入を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_44_afterInserted_returnEndConstIterator) {
    doublyLinkedList list;

    //末尾のイテレータを元にデータを挿入
    list.insertData(list.cend(), scoreData{2, "B"});

    //末尾イテレータを取得
    doublyLinkedList::constIterator endIt = list.cend();

    //endItをプラスし、末尾と同値か確認
    EXPECT_EQ(endIt, list.cend());

    //先頭にに文字列を挿入
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    //末尾を確認
    EXPECT_EQ(endIt, list.cend());

    //中間のイテレータを渡して挿入
    doublyLinkedList::constIterator it = list.cbegin();
    ++it;
    list.insertData(it, scoreData{ 3,"C" });

    //末尾を確認
    EXPECT_EQ(endIt, list.cend());

}

/**
* @brief ID0_45        データの削除を行った後に、呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID0_45_afterDeleted_returnEndConstIterator) {
    doublyLinkedList list;

    //要素を追加
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    list.insertData(list.cbegin(), scoreData{ 2,"B" });
    list.insertData(list.cbegin(), scoreData{ 3,"C" });

    doublyLinkedList::constIterator it = list.cbegin();
    ++it;

    //中間要素を削除
    list.deleteData(it);

    //先頭に戻す
    it = list.cbegin();
    doublyLinkedList::constIterator endIt = it;

    //末尾まで移動し、末尾と同値か確認
    ++endIt;
    ++endIt;
    EXPECT_EQ(endIt, list.cend());


    //末尾要素を削除
    ++it;
    list.deleteData(it);

    //先頭に戻す
    it = list.cbegin();
    endIt = it;

    //末尾まで移動し、末尾と同値か確認
    ++endIt;
    EXPECT_EQ(endIt, list.cend());

    //先頭要素を追加し、削除
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    it = list.cbegin();
    list.deleteData(it);

    //末尾まで移動し、末尾と同値か確認
    it = list.cbegin();
    endIt = it;
    ++endIt;
    EXPECT_EQ(endIt, list.cend());
}

/**
* @brief ID0_46        constのメソッドであるか
*/
TEST(doublyLinkedListTest, ID0_46_checkIfConst) {
    const doublyLinkedList list;
    doublyLinkedList::constIterator it = list.cend();  //コンパイルエラーにならない為、constである
}

/**
* @brief ID1_0        リストの参照がない状態で呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_0_whileNoListReference_callAssert) {
    doublyLinkedList list;
 
    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();

        //スコアを代入(リストが空であるため、assert発生)
        (*it).score = 10;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        //スコア読み取り(リストが空であるため、assert発生)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_1        Iteratorから取得した要素に対して、値の代入が行えるかをチェック
*/
TEST(doublyLinkedListTest, ID1_1_ifPossibleToAssignValueFromIterator) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    doublyLinkedList::iterator it = list.begin();

    //スコアを代入
    (*it).score = 10;

    //内容が変更されているかチェック
    EXPECT_EQ(10, (*it).score);
}

/**
* @brief ID1_2        ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック(コンパイルエラーなのでコメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_2_ifPossibleToAssignValueFromConstIterator) {
    doublyLinkedList list;
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    doublyLinkedList::constIterator it = list.cbegin();

    //スコアを代入(代入不可なのでコンパイルエラー)
    (*it).score = 10;

}
*/

/**
* @brief ID1_3        リストが空の際の、先頭イテレータに対して呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_3_ifListEmptyCallBeginIterator_callAssert) {
    doublyLinkedList list;
    
    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.begin();

        //スコアを代入(リストが空なのでassert発生)
        (*it).score = 10;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cbegin();
        //スコア読み取り(リストが空なのでassert発生)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_4        末尾イテレータに対して呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_4_callFromEndIterator_callAssert) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();

        //スコアを代入(末尾は空なのでassert発生)
        (*it).score = 10;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        //スコア読み取り(ダミーノードなのでassert発生)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_5        リストの参照がない状態で呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_5_whileNoListReference_callAssert) {
    doublyLinkedList list;

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();

        //要素を一つ進める(ダミーノードであるため、assert発生)
        ++it;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        //スコア読み取り(ダミーノードであるため、assert発生)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_6        リストが空の際の、先頭イテレータに対して呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_6_ifListEmptyIncrementFromBeginIterator_callAssert) {
    doublyLinkedList list;
    
    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.begin();

        //要素を一つ進める(ダミーノードであるため、assert発生)
        ++it;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cbegin();
        //要素を一つ進める(ダミーノードなのでassert発生)
        ++constIt;
    }
}
*/

/**
* @brief ID1_7        末尾イテレータに対して呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_7_usingIncremetFromEndIterator_callAssert) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();

        //要素を一つ進める(末尾は空なのでassert発生)
        ++it;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        //要素を一つ進める(末尾は空なのでassert発生)
        ++constIt;
    }
}
*/

/**
* @brief ID1_8        リストに二つ以上の要素がある場合に呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID1_8_ifHaveMoreThanTwoElementsUsingIncrement) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.begin();

        //中身を確認
        EXPECT_EQ(3, (*it).score);

        //要素を一つ進め、中身を確認
        ++it;
        EXPECT_EQ(2, (*it).score);

        //要素を一つ進め、中身を確認
        ++it;
        EXPECT_EQ(1, (*it).score);
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cbegin();

        //中身を確認
        EXPECT_EQ(3, (*constIt).score);

        //要素を一つ進め、中身を確認
        ++constIt;
        EXPECT_EQ(2, (*constIt).score);

        //要素を一つ進め、中身を確認
        ++constIt;
        EXPECT_EQ(1, (*constIt).score);
    }
}

/**
* @brief ID1_9        前置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
*/
TEST(doublyLinkedListTest, ID1_9_ifUsingPreIncrement) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.begin();
        doublyLinkedList::iterator headIt = list.begin();
        
        //中身を確認
        EXPECT_EQ(2, (*headIt).score);

        //要素を一つ進め、中身を確認
        ++it;
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ(2, (*headIt).score);
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cbegin();
        doublyLinkedList::constIterator constHeadIt = list.cbegin();

        //中身を確認
        EXPECT_EQ(2, (*constHeadIt).score);

        //要素を一つ進め、中身を確認
        ++constIt;
        EXPECT_EQ(1, (*constIt).score);
        EXPECT_EQ(2, (*constHeadIt).score);
    }
}


/**
* @brief ID1_10        後置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
*/
TEST(doublyLinkedListTest, ID1_9_ifUsingPostIncrement) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.begin();
        doublyLinkedList::iterator headIt = list.begin();

        //中身を確認
        EXPECT_EQ(2, (*headIt).score);

        //要素を一つ進め、中身を確認
        it++;
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ(2, (*headIt).score);
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cbegin();
        doublyLinkedList::constIterator constHeadIt = list.cbegin();

        //中身を確認
        EXPECT_EQ(2, (*constHeadIt).score);

        //要素を一つ進め、中身を確認
        constIt++;
        EXPECT_EQ(1, (*constIt).score);
        EXPECT_EQ(2, (*constHeadIt).score);
    }
}

/**
* @brief ID1_11        リストの参照がない状態で呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_11_whileNoListReference_callAssert) {
    doublyLinkedList list;

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();

        //要素を一つ進める(ダミーノードであるため、assert発生)
        --it;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        //要素を一つ進める(ダミーノードであるため、assert発生)
        --constIt;
    }
}
*/

/**
* @brief ID1_12        リストが空の際の、末尾イテレータに対して呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_12_ifListEmptyDecrementFromEndIterator_callAssert) {
    doublyLinkedList list;

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();

        //要素を一つ進める(ダミーノードであるため、assert発生)
        --it;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        //要素を一つ進める(ダミーノードであるため、assert発生)
        --constIt;
    }
}
*/

/**
* @brief ID1_13        先頭イテレータに対して呼び出した際の挙動(assertが発生するため、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_13_usingDecremetFromBeginIterator_callAssert) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.begin();

        //要素を一つ進める(末尾は空なのでassert発生)
        --it;
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cbegin();
        //要素を一つ進める(末尾は空なのでassert発生)
        --constIt;
    }
}
*/

/**
* @brief ID1_14        リストに二つ以上の要素がある場合に呼び出した際の挙動
*/
TEST(doublyLinkedListTest, ID1_14_ifHaveMoreThanTwoElementsUsingDecrement) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();
        

        //ダミーノードから一つ戻し、中身を確認
        --it;
        EXPECT_EQ(1, (*it).score);

        //要素を一つ戻し、中身を確認
        --it;
        EXPECT_EQ(2, (*it).score);

        //要素を一つ戻し、中身を確認
        --it;
        EXPECT_EQ(3, (*it).score);
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();

        //ダミーノードから一つ戻し、中身を確認
        --constIt;
        EXPECT_EQ(1, (*constIt).score);

        //要素を一つ進め、中身を確認
        --constIt;
        EXPECT_EQ(2, (*constIt).score);

        //要素を一つ進め、中身を確認
        --constIt;
        EXPECT_EQ(3, (*constIt).score);
    }
}
/**
* @brief ID1_15        前置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
*/
TEST(doublyLinkedListTest, ID1_15_ifUsingPreDecrement) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();
        doublyLinkedList::iterator endIt = list.end();

        //中身を確認
        --endIt;
        --it;
        EXPECT_EQ(1, (*endIt).score);

        //要素を一つ進め、中身を確認
        --it;
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ(1, (*endIt).score);
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        doublyLinkedList::constIterator constEndIt = list.cend();

        //中身を確認
        --constIt;
        --constEndIt;
        EXPECT_EQ(1, (*constEndIt).score);

        //要素を一つ進め、中身を確認
        --constIt;
        EXPECT_EQ(2, (*constIt).score);
        EXPECT_EQ(1, (*constEndIt).score);
    }
}

/**
* @brief ID1_16        後置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
*/
TEST(doublyLinkedListTest, ID1_16_ifUsingPostDecrement) {
    doublyLinkedList list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator側でテスト
        doublyLinkedList::iterator it = list.end();
        doublyLinkedList::iterator endIt = list.end();

        //中身を確認
        endIt--;
        it--;
        EXPECT_EQ(1, (*endIt).score);

        //要素を一つ進め、中身を確認
        it--;
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ(1, (*endIt).score);
    }

    {
        //constIterator側でテスト
        doublyLinkedList::constIterator constIt = list.cend();
        doublyLinkedList::constIterator constEndIt = list.cend();

        //中身を確認
        constIt--;
        constEndIt--;
        EXPECT_EQ(1, (*constEndIt).score);

        //要素を一つ進め、中身を確認
        constIt--;
        EXPECT_EQ(2, (*constIt).score);
        EXPECT_EQ(1, (*constEndIt).score);
    }
}

/**
* @brief ID1_17        ConstIteratorから、Iteratorのコピーが作成されないかをチェック(コンパイルエラーの為、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_17_checkNotPossibleToCreateCopyOfIteratorFromConst) {
    doublyLinkedList list;

    //コピーを作成できない為、コンパイルエラー
    doublyLinkedList::iterator it = list.cbegin();
 
}
*/

/**
* @brief ID1_18        コピーコンストラクト後の値がコピー元と等しいことをチェック
*/
TEST(doublyLinkedListTest, ID1_18_checkIfAfterCopyHasSameValue) {
    doublyLinkedList list;

    //コピーを行う
    doublyLinkedList::iterator it = list.begin();

    EXPECT_EQ(it, list.begin());
}

/**
* @brief ID1_19        IteratorにConstIteratorを代入できない事をチェック(コンパイルエラーの為、コメントアウト)
*/
/*
TEST(doublyLinkedListTest, ID1_20_checkNotPossibleAssignConstIntoIterator) {
    doublyLinkedList list;

    doublyLinkedList::iterator      it      = list.begin();
    doublyLinkedList::constIterator constIt = list.cbegin();

    //代入できない為、コンパイルエラー
    it = constIt;
}
*/

/**
* @brief ID1_20        代入後の値がコピー元と等しいことをチェック
*/
TEST(doublyLinkedListTest, ID1_20_checkIfAfterAssignHasSameValue) {
    doublyLinkedList list;

    //コピーを行う
    doublyLinkedList::iterator it = list.begin();
    doublyLinkedList::iterator it2;

    //値を代入
    it2 = it;

    EXPECT_EQ(it, it2);
}

/**
* @brief ID1_21        リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
*/
TEST(doublyLinkedListTest, ID1_21_checkIfCompareBetweenBeginAndEndIterator_returnTRUE) {
    doublyLinkedList list;
    doublyLinkedList::iterator it = list.begin();
    doublyLinkedList::iterator it2;

    EXPECT_TRUE(list.end() == list.begin());
}

/**
* @brief ID1_22        同一のイテレータを比較した際の挙動
*/
TEST(doublyLinkedListTest, ID1_22_checkIfCompareBetweenSameIterator_returnTRUE) {
    doublyLinkedList list;

    doublyLinkedList::iterator it = list.begin();
    doublyLinkedList::iterator it2 = list.begin();
    EXPECT_TRUE(it == it2);
}

/**
* @brief ID1_23        異なるイテレータを比較した際の挙動
*/
TEST(doublyLinkedListTest, ID1_23_checkIfCompareBetweenDifferentIterator_returnFALSE) {
    doublyLinkedList list;



    //データを挿入
    list.insertData(list.begin(), scoreData{ 1,"A" });

    doublyLinkedList::iterator it = list.begin();
    doublyLinkedList::iterator it2 = list.begin();

    //前進し、異なるイテレータにする
    ++it2;


    EXPECT_FALSE(it == it2);
}

/**
* @brief ID1_24        リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
*/
TEST(doublyLinkedListTest, ID1_24_checkIfCompareBetweenBeginAndEndIterator_returnFALSE) {
    doublyLinkedList list;
    doublyLinkedList::iterator it = list.begin();
    doublyLinkedList::iterator it2;

    EXPECT_FALSE(list.end() != list.begin());
}

/**
* @brief ID1_25        同一のイテレータを比較した際の挙動
*/
TEST(doublyLinkedListTest, ID1_25_checkIfCompareBetweenSameIterator_returnFALSE) {
    doublyLinkedList list;

    doublyLinkedList::iterator it = list.begin();
    doublyLinkedList::iterator it2 = list.begin();
    EXPECT_FALSE(it != it2);
}

/**
* @brief ID1_26        異なるイテレータを比較した際の挙動
*/
TEST(doublyLinkedListTest, ID1_26_checkIfCompareBetweenDifferentIterator_returnTRUE) {
    doublyLinkedList list;



    //データを挿入
    list.insertData(list.begin(), scoreData{ 1,"A" });

    doublyLinkedList::iterator it = list.begin();
    doublyLinkedList::iterator it2 = list.begin();

    //前進し、異なるイテレータにする
    ++it2;


    EXPECT_TRUE(it != it2);
}
