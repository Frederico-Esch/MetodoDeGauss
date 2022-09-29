//
// Created by Frederico on 29/09/2022.
//

#ifndef METODODEGAUSS_COEFFMATRIX_H
#define METODODEGAUSS_COEFFMATRIX_H

template<unsigned int _size>
class CoeffMatrix {
    std::array<std::array<double, _size>, _size> values;
public:

    CoeffMatrix(){
        for(auto& val : values){
            val.fill(0);
        }
    }

    CoeffMatrix(std::initializer_list<std::initializer_list<double>> matrix){
        int i = 0, j = 0;
        for(auto list : matrix){
            for(auto val : list){
                values[i][j++] = val;
            }
            i++; j = 0;
        }
    }

    CoeffMatrix(std::array<std::array<double, _size>, _size> matrix){
        int i = 0, j = 0;
        for(auto list : matrix){
            for(auto val : list){
                values[i][j++] = val;
            }
            i++; j = 0;
        }
    }

    unsigned int size() const {
        return _size;
    }

    std::array<double, _size>& operator[](size_t row){
        return values[row];
    }

    void swap(size_t row1, size_t row2){
        std::swap(values[row1], values[row2]);
    }
};
#endif //METODODEGAUSS_COEFFMATRIX_H
