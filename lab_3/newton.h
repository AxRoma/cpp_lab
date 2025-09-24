#ifndef NEWTON_SOLVER_H
#define NEWTON_SOLVER_H

#include <functional>

class NewtonSolver {
public:
    // Решение уравнения f(x) = 0 методом Ньютона
    // f - функция, корень которой ищем
    // df - производная функции f
    // initial_guess - начальное приближение
    // tolerance - точность решения
    // max_iterations - максимальное количество итераций
    double solve(std::function<double(double)> f,
                std::function<double(double)> df,
                double initial_guess,
                double tolerance = 1e-10,
                int max_iterations = 100);

private:
    // Вспомогательная функция для проверки сходимости
    bool is_converged(double x_old, double x_new, double tolerance);
};

#endif