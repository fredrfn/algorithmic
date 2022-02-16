#include "catch.hpp"
#include "types/Vector.hpp"

TEST_CASE("Vector constructors and copy/move semantics") {
    SECTION("Vector::Vector()") {
        Vector<int> vect;
        REQUIRE(vect.size() == 0);
        REQUIRE(vect.empty());
    }

    SECTION("Vector::Vector(size_t, const T&)") {
        Vector<int> vect(3, 1);
        REQUIRE(vect.size() == 3);
        REQUIRE(vect[0] == 1);
        REQUIRE(vect[1] == 1);
        REQUIRE(vect[2] == 1);    
    }

    SECTION("Vector::Vector(Vector&)") {
        Vector<int> vect(3, 3);
        Vector<int> copy(vect);

        REQUIRE(vect.size() == 3);
        REQUIRE(vect[0] == 3);
        REQUIRE(vect[1] == 3);
        REQUIRE(vect[2] == 3);      
        
        REQUIRE(copy.size() == 3);
        REQUIRE(copy[0] == 3);
        REQUIRE(copy[1] == 3);
        REQUIRE(copy[2] == 3); 
    }

    SECTION("Vector::Vector(const Vector&)") {
        const Vector<int> vect(3, 3);
        const Vector<int> copy(vect);

        REQUIRE(vect.size() == 3);
        REQUIRE(vect[0] == 3);
        REQUIRE(vect[1] == 3);
        REQUIRE(vect[2] == 3);      
        
        REQUIRE(copy.size() == 3);
        REQUIRE(copy[0] == 3);
        REQUIRE(copy[1] == 3);
        REQUIRE(copy[2] == 3);
    }

    SECTION("Vector::Vector(Vector&&)") {
        Vector<int> vect(3, 3);
        Vector<int> copy = vect;
        Vector<int> moved(std::move(copy));  
                
        REQUIRE(moved == vect);
        REQUIRE(copy.size() == 0);
        REQUIRE_THROWS_AS(copy[0], IllegalIndexException);
    }

    SECTION("Vector::Vector(std::initializer_list)") {
        Vector<int> vect = {0, 1, 2};

        REQUIRE(vect.size() == 3);
        REQUIRE(vect[0] == 0);
        REQUIRE(vect[1] == 1);
        REQUIRE(vect[2] == 2);
    }
}

TEST_CASE("Vector elements getter and setters") {
    Vector<int> vect(3, 0);

    for (int i = 0; i < 3; i++) {
        vect[i] = i;
    }

    const Vector<int> cvect(vect);

    REQUIRE(vect[0] == 0);
    REQUIRE(vect[1] == 1);
    REQUIRE(vect[2] == 2);
    REQUIRE_THROWS_AS(vect[3], IllegalIndexException);

    REQUIRE(cvect[0] == 0);
    REQUIRE(cvect[1] == 1);
    REQUIRE(cvect[2] == 2);   
    REQUIRE_THROWS_AS(cvect[3], IllegalIndexException);
}

TEST_CASE("Vector Comparison operators") {
    Vector<int> vect1(3, 1);
    Vector<int> vect1cp = vect1;
    Vector<int> vect2(3, 2);

    REQUIRE(vect1 == vect1cp);
    REQUIRE(vect1 != vect2);

    Vector<int> cvect1(3, 1);
    Vector<int> cvect1cp = cvect1;
    Vector<int> cvect2(3, 2);

    REQUIRE(cvect1 == cvect1cp);
    REQUIRE(cvect1 != cvect2);
}

TEST_CASE("Vector size-modifying functions") {
    SECTION("push") {
        Vector<int> vect;
        REQUIRE(vect.capacity() == 0);
        vect.push(0);
        REQUIRE(vect.capacity() == 1);
        vect.push(1);
        REQUIRE(vect.capacity() == 2);
        vect.push(2); 
        REQUIRE(vect.capacity() == 4);
        REQUIRE(vect.size() == 3);
        REQUIRE(vect == Vector<int>({0, 1, 2}));
    }

    SECTION("pop") {
        Vector<int> vect({0, 1, 2});
        vect.pop();
        REQUIRE(vect == Vector<int>{0, 1});
        vect.pop();
        REQUIRE(vect == Vector<int>{0});
        vect.pop();
        REQUIRE(vect == Vector<int>());
        REQUIRE_THROWS_AS(vect.pop(), IllegalIndexException);
    }

    SECTION("erase") {
        SECTION("Throws for empty vector") {
            Vector<int> vect;
            REQUIRE_THROWS_AS(vect.erase(0), IllegalIndexException);
        }

        SECTION("Throws outside of vector range") {
            Vector<int> vect = {0, 1, 2};
            REQUIRE_THROWS_AS(vect.erase(3), IllegalIndexException);
        }

        SECTION("Works as intended for element removal") {
            Vector<int> vect = {0, 1, 2, 3};
            vect.erase(1);
            REQUIRE(vect == Vector<int>({0, 2, 3}));
            vect.erase(0);
            REQUIRE(vect == Vector<int>({2, 3}));
            vect.erase(1);
            REQUIRE(vect == Vector<int>({2}));
        }
    }

    SECTION("insert") {
        SECTION("Throws for index out of range") {
            Vector<int> vect = {0, 1, 2};
            REQUIRE_THROWS_AS(vect.insert(3, 3), IllegalIndexException);
        }

        SECTION("Works at index 0") {
            Vector<int> vect = {0, 1, 2};
            vect.insert(0, 3);
            REQUIRE(vect == Vector<int>({3, 0, 1, 2}));
        }

        SECTION("Works for last element of the array") {
            Vector<int> vect = {0, 1, 2};
            vect.insert(2, 3);
            REQUIRE(vect == Vector<int>({0, 1, 3, 2}));
        }

        SECTION("Works correctly for standard case (at < size() - 1)") {
            Vector<int> vect = {0, 1, 2};
            vect.insert(1, 3);
            REQUIRE(vect == Vector<int>({0, 3, 1, 2}));
        }
    }
}

TEST_CASE("Vector Helper functions") {
    Vector<int> vect;
    vect.push(0);
    vect.push(1);
    Vector<int> cvect = vect;

    SECTION("fill") {
        vect.fill(2);
        REQUIRE(vect[0] == 2);
        REQUIRE(vect[1] == 2);
    }

    SECTION("swap") {
        vect.swap(0, 1);
        REQUIRE(vect[0] == 1);
        REQUIRE(vect[1] == 0);
    }

    SECTION("first") {
        REQUIRE(vect.first() == 0);
        REQUIRE(cvect.first() == 0);
    }

    SECTION("last") {
        REQUIRE(vect.last() == 1);
        REQUIRE(cvect.last() == 1);
    }
}

TEST_CASE("Vector Iterators") {
    Vector<int> vect(2, 0);

    int result = 0;
    for(int& value: vect) {
        value = result;
        result++;
    }

    result = 0;
    for(const int& value: vect) {
        result += value + 1;
    }

    REQUIRE(result == 3);
}