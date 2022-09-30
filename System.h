//
// Created by Frederico on 29/09/2022.
//

#ifndef METODODEGAUSS_SYSTEM_H
#define METODODEGAUSS_SYSTEM_H
#include "AnswerVector.h"
#include "CoeffMatrix.h"

template<unsigned int _size>
class System {
    AnswerVector<_size> results;
    CoeffMatrix<_size> coeffs;
public:

    System(){}
    System(std::array<std::array<double, _size>, _size> _coeffs) : coeffs(_coeffs){}
    System(std::array<double, _size> _results) : results(_results){
    }
    System(std::array<std::array<double, _size>, _size> _coeffs, std::array<double, _size> _results) : coeffs(_coeffs), results(
            _results){}

    void swap_results(size_t row1, size_t row2){
        results.swap(row1, row2);
    }
    void swap_coeffs(size_t row1, size_t row2){
        coeffs.swap(row1, row2);
    }

    double& result(size_t row){
        return results[row];
    }
    double& coeff(size_t row, size_t col){
        return coeffs[row][col];
    }

    double calculate_beta(){
        std::array<double, 3> betas;betas.fill(-INFINITY);

        for(int i = 0; i < size(); i++){
            double sum = 0;
            for(int j = 0; j < i; j++){
                sum += coeff(i, j)*betas[j];
            }
            for(int j = i+1; j < size(); j++){
                sum += coeff(i,j);
            }
            sum /= coeff(i,i);
            betas[i] = sum;
        }

        return *std::max_element(betas.begin(), betas.end());
    }

    double phi(unsigned int x, std::array<double, _size>& guess){
        double res = 0;
        for(int i = 0; i < _size; i++){
            if (i != x) res -= coeff(x, i)*guess[i];
        }
        res += result(x);
        res /= coeff(x,x);
        return res;
    }

    AnswerVector<_size> solve(std::array<double, _size> initial_guess = {0,0,0}, int limit_iterations = -1, double error = 1e-4) {

        if(calculate_beta() >= 1){
            increase_beta();
        }
        if(calculate_beta() >= 1){
            throw std::exception("System is not granted to converge\n");
        }

        std::array<double, _size> calculated(initial_guess);
        bool lesser_than_error = false;
        while (limit_iterations != 0 && !lesser_than_error){
            for(int i = 0; i < _size; i++){
                calculated[i] = phi(i, initial_guess);
            }

            for(int i = 0; i < _size; i++){
                lesser_than_error = std::abs(calculated[i] - initial_guess[i]) < error;
                if(!lesser_than_error) break;
            }
            if(limit_iterations > 0) limit_iterations--;
            for(int i = 0; i < _size; i++) initial_guess[i] = calculated[i];
        }

        return calculated;
    }

    void increase_beta(){
        double max = -INFINITY;
        for(int i = 0; i < _size; i++){
            for(int j = i; j < _size; j++) {
                if(coeffs[j][i] > max) max = j;
            }
            if(max != i){
                swap_coeffs(max, i);
                swap_results(max, i);
            }
        }
    }

    AnswerVector<_size> test(std::array<double, _size> x){
        std::array<double, _size> res; res.fill(0);
        for(int i = 0; i < size(); i++){
            for(int j = 0; j < size(); j++) res[i] += coeff(i, j)*x[j];
        }
        return res;
    }

    unsigned int size() const {
        return _size;
    }
};
#endif //METODODEGAUSS_SYSTEM_H
