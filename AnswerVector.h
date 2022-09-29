//
// Created by Frederico on 29/09/2022.
//

#ifndef METODODEGAUSS_ANSWERVECTOR_H
#define METODODEGAUSS_ANSWERVECTOR_H
#include "main.h"

template <unsigned int _size>
class AnswerVector {
    std::array<double, _size> values;
public:
    AnswerVector(){
        values.fill(0);
    }
    AnswerVector(std::initializer_list<double> vals){
        int index = 0;
        for(auto& val : vals){
            values[index++] = val;
        }
    }
    AnswerVector(std::array<double, _size> vals){
        for(int i = 0; i < vals.size(); i++){
            values[i] = vals[i];
        }
    }
    double& operator[](size_t index){
        return values[index];
    }
    unsigned int size() const {
        return _size;
    }
    void swap(double row1, double row2) {
        std::swap(values[row1], values[row2]);
    }
};

#endif //METODODEGAUSS_ANSWERVECTOR_H
