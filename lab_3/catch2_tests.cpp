#include "catch.hpp"
#include "newton.h"
#include <cmath>
#include <iostream>

TEST_CASE("Базовые тесты метода Ньютона", "[newton][basic]") {
    NewtonSolver solver;
    
    SECTION("Решение квадратного уравнения x² - 4 = 0") {
        auto f = [](double x) { return x * x - 4; };
        auto df = [](double x) { return 2 * x; };
        
        double root = solver.solve(f, df, 3.0);  // Начальное приближение 3.0
        REQUIRE(root == Approx(2.0).margin(1e-8));
        
        // Проверяем, что найденный корень действительно является решением
        REQUIRE(std::abs(f(root)) < 1e-10);
    }
    
    SECTION("Решение уравнения cos(x) = 0 (ожидаем x ≈ π/2)") {
        auto f = [](double x) { return std::cos(x); };
        auto df = [](double x) { return -std::sin(x); };
        
        double root = solver.solve(f, df, 1.0);
        double expected = M_PI / 2;  // π/2 ≈ 1.5708
        
        REQUIRE(root == Approx(expected).margin(1e-8));
        REQUIRE(std::abs(f(root)) < 1e-10);
    }
}

TEST_CASE("Тесты на обработку ошибок", "[newton][errors]") {
    NewtonSolver solver;
    
    SECTION("Обработка нулевой производной") {
        auto f = [](double x) { return x * x * x; };      // f(x) = x³
        auto df = [](double x) { return 3 * x * x; };     // f'(x) = 3x²
        
        // При x=0 производная равна 0
        REQUIRE_THROWS_AS(solver.solve(f, df, 0.0), std::runtime_error);
    }
    
    SECTION("Превышение максимального числа итераций") {
        auto f = [](double x) { return std::exp(x) + 1; };  // eˣ + 1 = 0 не имеет решений
        auto df = [](double x) { return std::exp(x); };
        
        // Функция никогда не достигнет 0, должен быть исключение
        REQUIRE_THROWS_AS(solver.solve(f, df, 1.0, 1e-10, 5), std::runtime_error);
    }
    
    SECTION("Некорректные параметры") {
        auto f = [](double x) { return x - 1; };
        auto df = [](double x) { return 1.0; };
        
        REQUIRE_THROWS_AS(solver.solve(f, df, 1.0, -0.1), std::invalid_argument);  // Отрицательная точность
        REQUIRE_THROWS_AS(solver.solve(f, df, 1.0, 0.1, -10), std::invalid_argument);  // Отрицательные итерации
    }
}

TEST_CASE("Тесты на точность и различные начальные приближения", "[newton][precision]") {
    NewtonSolver solver;
    
    SECTION("Разные начальные приближения для x² - 4 = 0") {
        auto f = [](double x) { return x * x - 4; };
        auto df = [](double x) { return 2 * x; };
        
        // Должны найти корень x=2 из разных начальных точек
        double root1 = solver.solve(f, df, 3.0);
        double root2 = solver.solve(f, df, 10.0);
        double root3 = solver.solve(f, df, 1.5);
        
        REQUIRE(root1 == Approx(2.0).margin(1e-8));
        REQUIRE(root2 == Approx(2.0).margin(1e-8));
        REQUIRE(root3 == Approx(2.0).margin(1e-8));
    }
    
    SECTION("Высокая точность для уравнения x³ - 8 = 0") {
        auto f = [](double x) { return x * x * x - 8; };
        auto df = [](double x) { return 3 * x * x; };
        
        double root = solver.solve(f, df, 2.5, 1e-12);  // Очень высокая точность
        REQUIRE(root == Approx(2.0).margin(1e-12));
        REQUIRE(std::abs(f(root)) < 1e-12);
    }
}