#include "main.h"
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

    unsigned int size() const {
        return _size;
    }
};


int main() {
    System<3> sistema(
            std::array<std::array<double, 3>,3>({
                std::array<double, 3>{2, 3, 10},
                std::array<double, 3>{10, 2, 1},
                std::array<double, 3>{1, 5, 1}}),
            {6,7,-8}
    );

    for(int i=0; i< sistema.size(); i++) {
        for(int j = 0; j < sistema.size(); j++){
            std::cout << sistema.coeff(i,j) << "x" << j+1 << " ";
        }
        std::cout << "= " << sistema.result(i) << '\n';
    }
    std::cout << "\nBETA = " << sistema.calculate_beta();
    sistema.increase_beta();
    std::cout << "\n\n";
    std::cout << "\nBETA = " << sistema.calculate_beta();
    std::cout << "\n\n";

    for(int i=0; i< sistema.size(); i++) {
        for(int j = 0; j < sistema.size(); j++){
            std::cout << sistema.coeff(i,j) << "x" << j+1 << " ";
        }
        std::cout << "= " << sistema.result(i) << '\n';
    }
    return 0;
}
