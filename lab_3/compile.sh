#!/bin/bash

echo "=== Компиляция проекта метода Ньютона ==="

# Компилируем основную библиотеку
echo "1. Компилируем newton_solver.cpp..."
g++ -c newton_solver.cpp -o newton_solver.o -std=c++17

# Компилируем и запускаем Catch2 тесты
echo "2. Компилируем и запускаем Catch2 тесты..."
g++ catch2_tests.cpp newton_solver.o -o catch2_tests -std=c++17
echo "--- Результаты Catch2 тестов ---"
./catch2_tests

echo ""

# Компилируем и запускаем Google Test тесты
echo "3. Компилируем и запускаем Google Test тесты..."
g++ gtest_tests.cpp newton_solver.cpp -lgtest -lgtest_main -pthread -o gtest_tests
echo "--- Результаты Google Test тестов ---"
./gtest_tests

echo ""
echo "=== Все тесты завершены ==="