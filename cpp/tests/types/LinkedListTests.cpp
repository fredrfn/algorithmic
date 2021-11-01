#include "catch.hpp"
#include "types/LinkedList.hpp"

TEST_CASE("LinkedList elements getter and setters") {
    LinkedList<int> list;
    list.push(0);
    list.push(0);
    list.push(0);

    REQUIRE(list.size() == 3);
    REQUIRE(list[0] == 0);
    REQUIRE(list[1] == 0);
    REQUIRE(list[2] == 0);

    for (int i = 0; i < 3; i++) {
        list[i] = i;
    }

    REQUIRE(list[0] == 0);
    REQUIRE(list[1] == 1);
    REQUIRE(list[2] == 2);
    REQUIRE_THROWS_AS(list[3], IllegalIndexException);
}

TEST_CASE("LinkedList instantiation") {
    SECTION("LinkedList::LinkedList()") {
        LinkedList<int> list;
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty());
    }

    SECTION("LinkedList copy/move constructors") {
        LinkedList<int> list;
        list.push(0);
        list.push(1);
        list.push(2);

        SECTION("LinkedList::LinkedList(LinkedList&)") {
            LinkedList<int> copy(list);
            REQUIRE(list == copy);
        }

        SECTION("LinkedList::LinkedList(const LinkedList&)") {
            LinkedList<int> copy((const LinkedList<int>&)list);
            REQUIRE(list == copy);
        }

        SECTION("LinkedList::LinkedList(const LinkedList&&)") {
            LinkedList<int> copy(list);  
            
            LinkedList<int> moved(std::move(copy));
            
            REQUIRE(moved == list);
            REQUIRE(copy.size() == 0);
            REQUIRE_THROWS_AS(copy[0], IllegalIndexException);
        }
    }

    SECTION("Assignment operators") {
        LinkedList<int> list;
        list.push(1);
        list.push(2);

        SECTION("LinkedList& operator=(LinkedList<T>& other)") {
            LinkedList<int> copy;
            copy = list;
            list.clear();

            REQUIRE(copy[0] == 1);
            REQUIRE(copy[1] == 2);
            REQUIRE(copy.size() == 2);
            REQUIRE(list.empty());
        }
        
    
        SECTION("LinkedList& operator=(const LinkedList<T>& other)") {
            const LinkedList<int> clist = list;

            LinkedList<int> copy = clist;
            list.clear();

            REQUIRE(copy[0] == 1);
            REQUIRE(copy[1] == 2);
            REQUIRE(copy.size() == 2);
            REQUIRE(list.empty());
        }
        
        SECTION("LinkedList& operator=(LinkedList<T>&& other)") {
            LinkedList<int> moved = std::move(list);

            REQUIRE(moved[0] == 1);
            REQUIRE(moved[1] == 2);
            REQUIRE(moved.size() == 2);
            REQUIRE(list.empty());
            REQUIRE_THROWS_AS(list[0], IllegalIndexException);          
        }
    }
}

TEST_CASE("LinkedList push/pop/size/clear functions") {
    LinkedList<int> list;
    list.push(3);
    list.push(2);

    SECTION("LinkedList::push(const T&)") {
        list.push(1);

        REQUIRE(list.size() == 3);
        REQUIRE(list[2] == 1);
    }

    SECTION("LinkedList::pop()") {
        list.pop();

        REQUIRE(list.size() == 1);
        REQUIRE(!list.empty());
        REQUIRE(list[0] == 3);
        REQUIRE_THROWS_AS(list[1], IllegalIndexException);

        list.pop();
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty());
        REQUIRE_THROWS_AS(list[0], IllegalIndexException);
    }

    SECTION("LinkedList::clear()") {
        list.clear();
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty());

        list.push(1);
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == 1);
    }
}


TEST_CASE("LinkedList Comparison operators") {
    LinkedList<int> list1;
    list1.push(1);
    list1.push(1);

    LinkedList<int> list2;
    list2.push(2);
    list2.push(2);

    LinkedList<int> list1cp = list1;

    REQUIRE(list1 == list1cp);
    REQUIRE(list1 != list2);

    const LinkedList<int> clist1 = list1;
    const LinkedList<int> clist1cp = clist1;
    const LinkedList<int> clist2 = list2;

    REQUIRE(clist1 == clist1cp);
    REQUIRE(clist1 != clist2);
}

TEST_CASE("LinkedList insert/erase functions") {
    SECTION("void insertBefore(size_t at, const T& value)") {
        SECTION("empty list case") {
            LinkedList<int> list;
            SECTION("at 0") {
                list.insertBefore(0, 50);
                REQUIRE(list.size() == 1);
                REQUIRE(list[0] == 50);
            } 

            SECTION("otherwise") {
                REQUIRE_THROWS_AS(list.insertBefore(1, 50), IllegalIndexException);
            }
        }

        SECTION("invalid index") {
            LinkedList<int> list;
            REQUIRE_THROWS_AS(list.insertBefore(1, 50), IllegalIndexException);
        }

        SECTION("at = size() case") {
            LinkedList<int> list;
            list.push(1);
            list.insertBefore(1, 50);
            REQUIRE(list.size() == 2);
            REQUIRE(list[0] == 1);
            REQUIRE(list[1] == 50);
        }

        SECTION("Valid standard case") {
            LinkedList<int> list;
            list.push(1);
            list.push(3);
            list.insertBefore(1, 2);
            REQUIRE(list.size() == 3);
            REQUIRE(list[0] == 1);
            REQUIRE(list[1] == 2);
            REQUIRE(list[2] == 3);
        }
    }

    SECTION("void insertAfter(size_t at, const T& value)") {
        SECTION("throws for an empty list") {
            LinkedList<int> list;
            REQUIRE_THROWS_AS(list.insertAfter(0, 50), IllegalIndexException);
        }

        SECTION("works in standard case (at < size())") {
            LinkedList<int> list;
            list.insertBefore(0, 0);
            list.insertAfter(0, 1);
            list.insertAfter(1, 2);

            REQUIRE(list.size() == 3);
            REQUIRE(list[0] == 0);
            REQUIRE(list[1] == 1);
            REQUIRE(list[2] == 2);
        }

        SECTION("throws for at >= list size()") {
            LinkedList<int> list;
            list.push(0);
            REQUIRE_THROWS_AS(list.insertAfter(1, 50), IllegalIndexException);
        }
    }

    SECTION("void erase(size_t at)") {
        SECTION("throws for empty list") {
            LinkedList<int> list;
            REQUIRE_THROWS_AS(list.erase(0), IllegalIndexException);
        }

        SECTION("work in standard case") {
            LinkedList<int> list;
            list.push(0);
            list.push(1);
            list.push(2);

            list.erase(1);

            REQUIRE(list.size() == 2);
            REQUIRE(list[0] == 0);
            REQUIRE(list[1] == 2);

            list.erase(0);
            list.erase(0);

            REQUIRE(list.empty());
        }

        SECTION("throws for at >= list size()") {
            LinkedList<int> list;
            list.push(0);
            REQUIRE_THROWS_AS(list.erase(1), IllegalIndexException);
        }
    }
}

TEST_CASE("LinkedList Iterators") {
    LinkedList<int> list;
    list.push(1);
    list.push(2);

    int result = 0;
    for(int& value: list) {
        result += value;
    }

    REQUIRE(result == 3);
}