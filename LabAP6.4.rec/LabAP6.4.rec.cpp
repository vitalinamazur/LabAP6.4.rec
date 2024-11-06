#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

void create(double* arr, int SIZE, double MIN, double MAX, int i = 0) {
    if (i < SIZE) {
        arr[i] = MIN + (double)rand() / RAND_MAX * (MAX - MIN);
        create(arr, SIZE, MIN, MAX, i + 1);
    }
}

void print(double* arr, int SIZE, int i = 0) {
    if (i < SIZE) {
        cout << setw(10) << arr[i];
        print(arr, SIZE, i + 1);
    }
    else {
        cout << endl;
    }
}

double productOfNegatives(double* arr, int SIZE, int i = 0, double product = 1.0) {
    if (i >= SIZE) return (product == 1.0) ? 0 : product;
    if (arr[i] < 0) product *= arr[i];
    return productOfNegatives(arr, SIZE, i + 1, product);
}

int findMaxIndex(double* arr, int SIZE, int i = 0, int maxIndex = 0) {
    if (i >= SIZE) return maxIndex;
    if (arr[i] > arr[maxIndex]) maxIndex = i;
    return findMaxIndex(arr, SIZE, i + 1, maxIndex);
}

double sumBeforeMax(double* arr, int SIZE) {
    int maxIndex = findMaxIndex(arr, SIZE);
    double sum = 0.0;
    for (int i = 0; i < maxIndex; i++) {
        if (arr[i] > 0) sum += arr[i];
    }
    return sum;
}

void collectEvenElements(double* arr, double* evens, int SIZE, int i = 0, int j = 0) {
    if (i >= SIZE) return;
    if (static_cast<int>(arr[i]) % 2 == 0) evens[j++] = arr[i];
    collectEvenElements(arr, evens, SIZE, i + 1, j);
}

void placeReversedEvens(double* arr, double* evens, int SIZE, int i = 0, int j = 0) {
    if (i >= SIZE) return;
    if (static_cast<int>(arr[i]) % 2 == 0) arr[i] = evens[j--];
    placeReversedEvens(arr, evens, SIZE, i + 1, j);
}

void reverseEvenElements(double* arr, int SIZE) {
    int evenCount = 0;
    for (int i = 0; i < SIZE; i++)
        if (static_cast<int>(arr[i]) % 2 == 0) evenCount++;

    double* evens = new double[evenCount];
    collectEvenElements(arr, evens, SIZE, 0, 0);
    placeReversedEvens(arr, evens, SIZE, 0, evenCount - 1);
    delete[] evens;
}

int main() {
    srand((unsigned)time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int SIZE;
    cout << "(SIZE): "; cin >> SIZE;

    double MIN = -20.0, MAX = 20.0;
    double* arr = new double[SIZE];
    create(arr, SIZE, MIN, MAX);

    print(arr, SIZE);

    cout << "Добуток від'ємних елементів масиву: " << productOfNegatives(arr, SIZE) << endl;
    cout << "Сума додатних елементів перед максимальним: " << sumBeforeMax(arr, SIZE) << endl;

    reverseEvenElements(arr, SIZE);

    print(arr, SIZE);

    delete[] arr;
    return 0;
}