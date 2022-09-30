#include "main.h"
#include "AnswerVector.h"
#include "CoeffMatrix.h"
#include "System.h"




int main() {
    System<3> sistema(
            std::array<std::array<double, 3>,3>({
                std::array<double, 3>{2, 3, 10},
                std::array<double, 3>{10, 2, 1},
                std::array<double, 3>{1, 5, 1}}),
            {6,7,-8}
    );
    auto answer = sistema.solve();

    for(int i = 0; i < answer.size(); i++){
        std::cout << "x" << i << " = " << answer[i] << '\n';
    }

    std::cout << '\n';
    auto teste = sistema.test(answer.to_array());

    for(int i = 0; i < teste.size(); i++){
        std::cout << i << " -> " << teste[i] << '\n';
    }

    return 0;
}
