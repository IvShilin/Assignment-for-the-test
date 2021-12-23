#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

const char* FNAME = "input.txt";

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleOutputCP(CP_UTF8);

    ifstream FIN(FNAME);

    int i, j, temp,
    k = 0,
    minI, minV, minK = 0,
    maxI, maxV, maxK = 0,
    leftBorderIndex,
    rightBorderIndex;

    //файл не найден
    if (!FIN)
    {
        cout << "ОШИБКА! Файл " << FNAME << " не найден\n";
        FIN.close(); //закрыть файл
        system("pause");
        return 1; //выход по ошибке
    } // end if

    //проверки состояния файла
    if (FIN.peek() == EOF) 	//файл пуст
    {
        cout << "Файл " << FNAME << " пустой\n";
        FIN.close();    //закрыть файл
        system("pause");
        return 2;   //выход по ошибке
    } // end if

    while(!FIN.eof()){ // цикл считывания файла до конца
        FIN >> temp; // запись в переменную
        k++; // инкриментируем счётчик

        if (FIN.fail()) { ///в файле не число
            cout << "Сбой при чтении файла " << FNAME << endl;
            FIN.close();//закрыть файл
            system("pause");
            return 3;//выход по ошибке
        }
    }

    int const N = k; // размерность исходного массива
    int AVec[N]; // декларирование исходного массива

    FIN.seekg(0); // перемещение указателя в начало считываемой строки

    cout << "Полученный из файла " << FNAME << " массив (исходный): " << endl;
    for (i = 0; i < N; i++){ // цикл инициализации исходного массива
        FIN >> AVec[i];
        cout << AVec[i] << " "; // вывод каждого элемента считанного массива
    }

    minV = maxV = AVec[0]; // инициализация минимума и максимума по первому элменту считанного массива
    maxK = 1;
    minK = 1;

    for (i = 0; i < N; i++){ // поиск минимума и максимума и их индексов
        if (AVec[i] > maxV){
            maxV = AVec[i];
            maxI = i;
            maxK = 1;
        } else if (AVec[i] == maxV){
            maxK++;
        }
        if (AVec[i] < minV){
            minV = AVec[i];
            minI = i;
            minK = 1;
        } else if (AVec[i] == minV){
            minK++;
        }
    }

    if (maxK != 1 and minK == 1){
        cout << endl << "У нас несколько максимумов!" << endl;
        system("pause");
        return 4;
    }

    if (maxK == 1 and minK != 1){
        cout << endl << "У нас несколько минимумов!" << endl;
        system("pause");
        return 5;
    }

    if (maxK != 1 and minK != 1 ){
        cout << endl << "У нас несколько максимумов и минимумов!" << endl;
        system("pause");
        return 6;
    }

    if (minV ==  maxV and N != 2 and N != 1){
        cout << endl << "Все числа одинаковы" << endl;
        system("pause");
        return 7;
    }

    if (N == 1){
        cout << endl << "Массив состоит всего из 1 значения!" << endl;
        system("pause");
        return 8;
    }

    if (N == 2 and minV == maxV){
        cout << endl << "Массив состоит из двух одинаковых элементов!";
        system("pause");
        return 9;
    }

    if (N == 2 and minV != maxV){
        cout << endl << "Массив состоит из двух элементов!";
        system("pause");
        return 10;
    }

    cout << endl << endl;

    cout << "Максимум: " << maxV << endl
         << "Индекс максимума: " << maxI
         << endl << endl;

    cout << "Минимум: " << minV << endl
         << "Индекс минимума: " << minI
         << endl << endl;

    if (maxI > minI){ // определение левой и правой границы
        leftBorderIndex = minI;
        rightBorderIndex = maxI;
    } else {
        leftBorderIndex = maxI;
        rightBorderIndex = minI;
    }

    k = 0; // обнуление счётчика
    for (i = leftBorderIndex + 1; i < rightBorderIndex - k; i++){ // цикл удаления
        if (AVec[i] >= 0){
            for (j = 0; j < ( (N - k) - i - 1); j++){
                temp = AVec[i+j];
                AVec[i+j] = AVec[i+j+1];
                AVec[i+j+1] = temp;
            }
            i--;
            k++;
        }
    }

    cout << "Измененный массив с переставленными значениями: " << endl;
    for (i = 0; i < N; i++){
        cout << AVec[i] << " ";
    }

    cout << endl << endl << "Итоговый массив: " << endl;
    for (i = 0; i < N - k; i++){
        cout << AVec[i] << " ";
    }
    return 0;
}