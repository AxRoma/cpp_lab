#include "newton_solver.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

double NewtonSolver::solve(std::function<double(double)> f,
                          std::function<double(double)> df,
                          double initial_guess,
                          double tolerance,
                          int max_iterations) {
    
    if (tolerance <= 0) {
        throw std::invalid_argument("Точность должна быть положительным числом");
    }
    
    if (max_iterations <= 0) {
        throw std::invalid_argument("Максимальное число итераций должно быть положительным");
    }
    
    double x = initial_guess;
    
    for (int iteration = 0; iteration < max_iterations; ++iteration) {
        double fx = f(x);
        double dfx = df(x);
        
        // Проверяем, что производная не слишком мала
        if (std::abs(dfx) < 1e-15) {
            throw std::runtime_error("Производная слишком мала, возможно деление на ноль");
        }
        
        // Формула метода Ньютона: x_new = x - f(x)/f'(x)
        double x_new = x - fx / dfx;
        
        // Проверяем сходимость
        if (is_converged(x, x_new, tolerance)) {
            std::cout << "Сходимость достигнута за " << (iteration + 1) << " итераций" << std::endl;
            return x_new;
        }
        
        x = x_new;
    }
    
    throw std::runtime_error("Превышено максимальное число итераций: " + std::to_string(max_iterations));
}

bool NewtonSolver::is_converged(double x_old, double x_new, double tolerance) {
    return std::abs(x_new - x_old) < tolerance;
}