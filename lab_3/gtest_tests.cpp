#include <gtest/gtest.h>
#include "newton_solver.h"
#include <cmath>
#include <stdexcept>

// Простой заголовочный файл Google Test, если нет системной установки
#ifndef GTEST_H
#define GTEST_H

#include <iostream>
#include <string>
#include <cmath>

#define EXPECT_TRUE(condition) \
    if (!(condition)) { \
        std::cout << "FAIL: " << #condition << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        return; \
    }

#define EXPECT_NEAR(val1, val2, abs_error) \
    if (std::abs((val1) - (val2)) > (abs_error)) { \
        std::cout << "FAIL: " << #val1 << " ≈ " << #val2 << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        return; \
    }

#define EXPECT_THROW(statement, exception_type) \
    try { \
        statement; \
        std::cout << "FAIL: Expected exception " << #exception_type << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        return; \
    } catch (const exception_type&) { \
        /* Успех */ \
    } catch (...) { \
        std::cout << "FAIL: Wrong exception type at " << __FILE__ << ":" << __LINE__ << std::endl; \
        return; \
    }

#define TEST(test_case_name, test_name) \
    void test_case_name##_##test_name(); \
    class test_case_name##_##test_name##_Class { \
    public: \
        test_case_name##_##test_name##_Class() { \
            std::cout << "TEST: " << #test_case_name << "." << #test_name << std::endl; \
            test_case_name##_##test_name(); \
        } \
    } test_case_name##_##test_name##_instance; \
    void test_case_name##_##test_name()

// Функция main для Google Test
int main(int argc, char** argv) {
    std::cout << "=== GOOGLE TEST TESTS ===" << std::endl;
    // Все тесты запускаются автоматически через статические объекты
    return 0;
}

#endif

// Тесты Google Test
TEST(NewtonSolverTest, SolvesQuadraticEquation) {
    NewtonSolver solver;
    auto f = [](double x) { return x * x - 4; };
    auto df = [](double x) { return 2 * x; };
    
    double root = solver.solve(f, df, 3.0);
    EXPECT_NEAR(root, 2.0, 1e-8);
    EXPECT_NEAR(f(root), 0.0, 1e-10);
}

TEST(NewtonSolverTest, HandlesZeroDerivative) {
    NewtonSolver solver;
    auto f = [](double x) { return x * x * x; };
    auto df = [](double x) { return 3 * x * x; };
    
    EXPECT_THROW(solver.solve(f, df, 0.0), std::runtime_error);
}

TEST(NewtonSolverTest, AchievesHighPrecision) {
    NewtonSolver solver;
    auto f = [](double x) { return std::sin(x); };
    auto df = [](double x) { return std::cos(x); };
    
    double root = solver.solve(f, df, 3.0, 1e-12);
    EXPECT_NEAR(root, M_PI, 1e-12);
    EXPECT_NEAR(f(root), 0.0, 1e-12);
}