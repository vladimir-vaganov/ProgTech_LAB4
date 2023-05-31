#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

using namespace std;

/**
 *  @brief Класс генератора псевдослучайных чисел
 *  @details Имеет два режима работы: в первом использует метод генерации псевдослучайных чисел XOR-shift, во втором - линейный конгруэнтный метод.
 */

class Generator{
public:
    unsigned long current, randMax = 4294967295;
    int minValue, maxValue, type;


    /**
 *  @brief Конструктор класса
 *  @details Задаёт зерно генерации, границы генерируемых значений, а также режим работы
 *  @param Зерно генератора seed, границы значений minv и maxv, режим работы t. Если t = 1, используется XOR-shift, если t = 2, то используется линейный конгруэнтный метод
 *  @return Возвращаемое значение отсутствует
 */


    Generator(unsigned long seed, int minv, int maxv, int t){
        current = seed;
        minValue = minv;
        maxValue = maxv;
        type = t;
    }

        /**
 *  @brief Метод генерации случайных чисел
 *  @details Меняет текущее значение генератора и возвращает его в качестве результата генерации
 *  @param Параметры отсутствуют
 *  @return Целое число - результат работы ГПСЧ
 */

    int next(){
        if (type == 1){
            current ^= current << 17;
            current ^= current >> 19;
            current ^= current << 7;
            current %= randMax;
        }
        if (type == 2){
            current = (unsigned int)(current) * 20999917 + 20995031;
        }

        return minValue + current % (maxValue - minValue);
    }
};

/**
 *  @brief Функция анализа выборки случайных чисел
 *  @details Находит и выводит на экран среднее значение, стандартное отклонение, коэффициент вариации, частоты и значение критерия при использовании критерия Хи-квадрат
 *  @param Вектор целых чисел - выборка
 *  @return Возвращаемые параметры отсутствуют
 */

void analysis(vector <int> data){
    cout << "_______________________________________\n\n\n";
    cout << "Volume of data is " << data.size() << "\n\n";

    double mean = 0.0;
    for (auto v : data)
        mean += v;
    mean /= data.size();

    cout << "Mean is " << mean << "\n\n";

    double deviation = 0.0;

    for (auto v : data)
        deviation += (v - mean) * (v - mean);
    deviation /= data.size();
    deviation = pow(deviation, 0.5);

    cout << "Standard deviation is " << deviation << "\n\n";

    cout << "Coefficient of variation is " << deviation / mean << "\n\n";

    vector <long long> n = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (long long i = 0; i < data.size(); i++)
        n[data[i] / 1000]++;

    cout << "Array n looks like:\n\n";

    for (long long i = 0; i < 10; i++)
        cout << "[" << i * 1000 << "..." << (i + 1) * 1000 << ")\t:\t" << n[i] << endl;

    long long sum = 0;
    for (long long i = 0; i < 10; i++)
        sum += n[i];
    cout << "\nTotal of array n is " << sum << endl;

    double xisum = 0.0;

    for (long long i = 0; i < 10; i++)
        xisum += (n[i] * n[i] * 10);

    xisum /= data.size();

    xisum -= data.size();

    cout << "\nValue of criterion is " << xisum;
    cout << "\n\n\n_______________________________________\n\n";
}

/**
 *  @brief Главная функция программы
 *  @details Создаёт объекты генератора, выборки разного объема, замеряет время генерации, а также вызывает функцию analysis
 *  @param Параметры отсутствуют
 *  @return Целое число - код завершения программы
 */

int main(){
    int choice;
    cout << "Choose a generator:\n\n1. XOR-shift\n2. Ne pridumal\n\n";
    cin >> choice;
    cout << endl;

    if (choice == 1){
        Generator aboba(3359, 0, 10000, 1);
        ofstream out("output.txt");
        vector <int> data100 = {},
                     data500 = {},
                     data1000 = {},
                     data5000 = {},
                     data10000 = {},
                     data50000 = {},
                     data100000 = {},
                     data500000 = {},
                     data1000000 = {},
                     data5000000 = {};


        auto start_t = chrono::steady_clock::now();
        for (long i = 0; i < 100; i++)
            data100.push_back(aboba.next());
        cout << "Generation time for volume of\t100\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 500; i++)
            data500.push_back(aboba.next());
        cout << "Generation time for volume of\t500\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 1000; i++)
            data1000.push_back(aboba.next());
        cout << "Generation time for volume of\t1000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 5000; i++)
            data5000.push_back(aboba.next());
        cout << "Generation time for volume of\t5000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 10000; i++)
            data10000.push_back(aboba.next());
        cout << "Generation time for volume of\t10000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 50000; i++)
            data50000.push_back(aboba.next());
        cout << "Generation time for volume of\t50000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 100000; i++)
            data100000.push_back(aboba.next());
        cout << "Generation time for volume of\t100000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 500000; i++)
            data500000.push_back(aboba.next());
        cout << "Generation time for volume of\t500000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 1000000; i++)
            data1000000.push_back(aboba.next());
        cout << "Generation time for volume of\t1000000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 5000000; i++)
            data5000000.push_back(aboba.next());
        cout << "Generation time for volume of\t5000000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        analysis(data100);
        analysis(data500);
        analysis(data1000);
        analysis(data5000);
        analysis(data10000);
        analysis(data50000);
        analysis(data100000);
        analysis(data500000);
        analysis(data1000000);
        analysis(data5000000);
    }

    if (choice == 2){
        Generator aboba(3359, 0, 10000, 2);
        ofstream out("output.txt");
        vector <int> data100 = {},
                     data500 = {},
                     data1000 = {},
                     data5000 = {},
                     data10000 = {},
                     data50000 = {},
                     data100000 = {},
                     data500000 = {},
                     data1000000 = {},
                     data5000000 = {};


        auto start_t = chrono::steady_clock::now();
        for (long i = 0; i < 100; i++)
            data100.push_back(aboba.next());
        cout << "Generation time for volume of\t100\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 500; i++)
            data500.push_back(aboba.next());
        cout << "Generation time for volume of\t500\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 1000; i++)
            data1000.push_back(aboba.next());
        cout << "Generation time for volume of\t1000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 5000; i++)
            data5000.push_back(aboba.next());
        cout << "Generation time for volume of\t5000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 10000; i++)
            data10000.push_back(aboba.next());
        cout << "Generation time for volume of\t10000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 50000; i++)
            data50000.push_back(aboba.next());
        cout << "Generation time for volume of\t50000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 100000; i++)
            data100000.push_back(aboba.next());
        cout << "Generation time for volume of\t100000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 500000; i++)
            data500000.push_back(aboba.next());
        cout << "Generation time for volume of\t500000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 1000000; i++)
            data1000000.push_back(aboba.next());
        cout << "Generation time for volume of\t1000000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        start_t = chrono::steady_clock::now();
        for (long i = 0; i < 5000000; i++)
            data5000000.push_back(aboba.next());
        cout << "Generation time for volume of\t5000000\t"
             << chrono::duration_cast<std::chrono::nanoseconds>(chrono::steady_clock::now() - start_t).count()
             << " ns\n";

        analysis(data100);
        analysis(data500);
        analysis(data1000);
        analysis(data5000);
        analysis(data10000);
        analysis(data50000);
        analysis(data100000);
        analysis(data500000);
        analysis(data1000000);
        analysis(data5000000);
    }
}
