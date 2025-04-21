#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "Vector.h"
#include <memory>

namespace TestsForInts {
    void test1() {
        Vector<int> vec;
        vec.push_back(5);
        vec.push_back(-19);
        vec.push_back(23);
        vec.pop_back();
        vec.pop_back();
        vec.pop_back();
        std::cout << vec;

        vec.push_back(1);
        vec.push_back(100);
        std::cout << vec;

        std::cout << std::endl;
    }

    void test2() {
        Vector<int> vec1;
        vec1.push_back(5);
        vec1.push_back(-19);
        vec1.push_back(23);

        Vector<int>vec2 = vec1;

        vec2.pop_back();
        vec1.push_back(999);
    }

    void test3() {
        Vector<int> vec;
        vec.push_back(120);
        vec.push_back(-8);
        vec.push_back(1);
        {
            Vector<int> vec2;
            vec2 = vec;
            vec2.push_back(89);
        }
        vec.pop_back();
    }

    void test4()
    {
        Vector<int> vec(10);

        std::generate(vec.begin(), vec.end(), []() {static int i = 0;  return i++; });
        for (int i : vec) std::cout << i;


        std::cout << std::endl;
        Vector<int> vec1(15);
        Vector<int> vec2 = std::move(vec1);
        for (int i : vec2) std::cout << i;

        Vector<int> vec3(15);
        Vector<int> vec4(15);
        vec4 = std::move(vec3);

        for (int i : vec3) std::cout << i;
        std::cout << std::endl;
    }

    void test5()
    {
        // if we have a ctor that takes std::initializer_list as parameter then if we create obj with {} then it will invoke that ctor
        Vector<int> v2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        for (auto elemnet : v2) std::cout << elemnet << " ";

        std::cout << std::endl << v2;
        std::cout << std::endl;
    }

    void test6()
    {
        Vector<int> v1{ 100, 50, 25, 5, 0 };
        std::cout << v1[1] << std::endl;
        v1[0] = -20; // correctly doesnt allow that if our vec is const type
        std::cout << v1[0];
        std::cout << std::endl;

        const Vector<int> v2{ 0, 520, 215, 15, 5 };
        for (const auto& element : v2) std::cout << element;
        std::cout << std::endl;
    }

    void test7()
    {
        Vector<int> v1{ 100, 50, 25, 5, 0 };
        std::cout << v1.at(2) << std::endl;
        v1.at(2) = 3; // correctly doesnt allow that if our vec is const type
        std::cout << v1.at(2) << std::endl;
        //std::cout << v1.at(-999) << std::endl; //triggers except correctly: Index out of bounds 
        std::cout << std::endl;
    }
}

namespace TestsForStructs {

    struct Simple_struct {

        Simple_struct() { 
            std::cout << "created obj Simple_struct!" << std::endl;
        }
        ~Simple_struct() { 
            std::cout << "destroyed obj Simple_struct!" << std::endl; 
        }
        Simple_struct(const Simple_struct& rhs) = delete;
        Simple_struct(Simple_struct&&) noexcept { 
            std::cout << "moved obj Simple_struct!" << std::endl; a = 0; c = char(0);
        }
        int a = 4;
        char c = 'A';
    };

    struct Advanced_struct {
        Advanced_struct()
        :
            data(new int[100])
        {
            std::cout << "created obj Advanced_struct!" << std::endl;
        }
        Advanced_struct(Advanced_struct&& o) noexcept
            : data(o.data)
        {
            o.data = nullptr;
            std::cout << "moved obj Advanced_struct!" << std::endl;
        }
        Advanced_struct(const Advanced_struct&) = delete; //non copable for now
        Advanced_struct& operator=(const Advanced_struct&) = delete;
        ~Advanced_struct() {
            delete[] data;
            std::cout << "destroyed obj Advanced_struct!" << std::endl;
        }
        int* data;
    };

    void test1() {
        std::cout << std::endl;
        Vector<Simple_struct> vec;
        vec.emplace_back(Simple_struct());
        vec.emplace_back(Simple_struct());
        vec.pop_back();
        vec.emplace_back(Simple_struct());
    }

    void test2() {
       std::cout << std::endl;
       Vector<Advanced_struct> vec;
       vec.emplace_back(Advanced_struct());
       vec.emplace_back(Advanced_struct());
       vec.pop_back();
       vec.emplace_back(Advanced_struct());
    }
}

int main()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

    try {
       TestsForInts::test1(); //ok
       TestsForInts::test2(); //ok
       TestsForInts::test3(); //ok
       TestsForInts::test4(); //ok
       TestsForInts::test5(); //ok
       TestsForInts::test6(); //ok
       TestsForInts::test7(); //ok

       TestsForStructs::test1(); //ok
       TestsForStructs::test2(); //ok


    }
    catch (std::exception& e) {
        std::cout << std::endl << e.what();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}