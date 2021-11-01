#include "catch.hpp"
#include "types/Array.hpp"

TEST_CASE("Array constructors and copy semantics") {
    SECTION("Array::Array()") {
        Array<int, 3> arr;
        REQUIRE(arr.size() == 3);
        REQUIRE(arr[0] == 0);
        REQUIRE(arr[1] == 0);
        REQUIRE(arr[2] == 0);
    }

    SECTION("Array::Array(T)") {
        Array<int, 3> arr(3);
        REQUIRE(arr.size() == 3);
        REQUIRE(arr[0] == 3);
        REQUIRE(arr[1] == 3);
        REQUIRE(arr[2] == 3);    
    }

    SECTION("Array::Array(Array&)") {
        Array<int, 3> arr(3);
        Array<int, 3> copy(arr);

        REQUIRE(arr.size() == 3);
        REQUIRE(arr[0] == 3);
        REQUIRE(arr[1] == 3);
        REQUIRE(arr[2] == 3);      
        
        REQUIRE(copy.size() == 3);
        REQUIRE(copy[0] == 3);
        REQUIRE(copy[1] == 3);
        REQUIRE(copy[2] == 3); 
    }

    SECTION("Array::Array(const Array&)") {
        const Array<int, 3> arr(3);
        const Array<int, 3> copy(arr);

        REQUIRE(arr.size() == 3);
        REQUIRE(arr[0] == 3);
        REQUIRE(arr[1] == 3);
        REQUIRE(arr[2] == 3);      
        
        REQUIRE(copy.size() == 3);
        REQUIRE(copy[0] == 3);
        REQUIRE(copy[1] == 3);
        REQUIRE(copy[2] == 3);
    }

    SECTION("operator=(Array&)") {
        Array<int, 3> arr(3);
        Array<int, 3> copy = arr;

        REQUIRE(arr.size() == 3);
        REQUIRE(arr[0] == 3);
        REQUIRE(arr[1] == 3);
        REQUIRE(arr[2] == 3);      
        
        REQUIRE(copy.size() == 3);
        REQUIRE(copy[0] == 3);
        REQUIRE(copy[1] == 3);
        REQUIRE(copy[2] == 3);
    }

    SECTION("operator=(const Array&)") {
        const Array<int, 3> arr(3);
        const Array<int, 3> copy = arr;

        REQUIRE(arr.size() == 3);
        REQUIRE(arr[0] == 3);
        REQUIRE(arr[1] == 3);
        REQUIRE(arr[2] == 3);      
        
        REQUIRE(copy.size() == 3);
        REQUIRE(copy[0] == 3);
        REQUIRE(copy[1] == 3);
        REQUIRE(copy[2] == 3);
    }
}

TEST_CASE("Array elements getter and setters") {
    Array<int, 3> arr;

    for (int i = 0; i < 3; i++) {
        arr[i] = i;
    }

    const Array<int, 3> carr(arr);

    REQUIRE(arr[0] == 0);
    REQUIRE(arr[1] == 1);
    REQUIRE(arr[2] == 2);
    REQUIRE_THROWS_AS(arr[3], IllegalIndexException);

    REQUIRE(carr[0] == 0);
    REQUIRE(carr[1] == 1);
    REQUIRE(carr[2] == 2);   
    REQUIRE_THROWS_AS(carr[3], IllegalIndexException);
}

TEST_CASE("Array Comparison operators") {
    Array<int, 2> arr1(1);
    Array<int, 2> arr1cp = arr1;
    Array<int, 2> arr2(2);

    REQUIRE(arr1 == arr1cp);
    REQUIRE(arr1 != arr2);

    Array<int, 2> carr1(1);
    Array<int, 2> carr1cp = carr1;
    Array<int, 2> carr2(2);

    REQUIRE(carr1 == carr1cp);
    REQUIRE(carr1 != carr2);
}

TEST_CASE("Array Helper functions") {
    Array<int, 2> arr(0);
    arr[1] = 1;
    Array<int, 2> carr = arr;

    SECTION("fill") {
        arr.fill(2);
        REQUIRE(arr[0] == 2);
        REQUIRE(arr[1] == 2);
    }

    SECTION("swap") {
        arr.swap(0, 1);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 0);
    }

    SECTION("first") {
        REQUIRE(arr.first() == 0);
        REQUIRE(carr.first() == 0);
    }

    SECTION("last") {
        REQUIRE(arr.last() == 1);
        REQUIRE(carr.last() == 1);
    }
}

TEST_CASE("Array Iterators") {
    Array<int, 2> arr(0);

    int result = 0;
    for(int& value: arr) {
        value = result;
        result++;
    }

    result = 0;
    for(const int& value: arr) {
        result += value + 1;
    }

    REQUIRE(result == 3);
}