﻿#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "Vector.h"


void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();


int main()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

    try {
        test1(); //ok
        test2(); //ok
        test3(); //ok
        test4(); //ok
        test5(); //ok
        test6(); //ok
        test7(); 
    }
    catch (std::exception& e) {
        std::cout << std::endl << e.what();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}


void test1() {
    Vector<int> vec;
    vec.push_back(5);
    vec.push_back(-19);
    vec.push_back(23);
    vec.push_back(1);
    vec.push_back(100);
}

void test2() {
    Vector<int> vec1;
    vec1.push_back(5);
    vec1.push_back(-19);
    vec1.push_back(23);

    Vector<int>vec2 = vec1;

    vec2.pop();
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
    vec.pop();
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
