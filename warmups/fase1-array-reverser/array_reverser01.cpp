#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Ingresa el tamaño del arreglo: ";
    cin >> size;
    int *arr = new int[size];
    cout << "Ingresa los elementos:\n";
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    cout << "Arreglo original: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    int *left = arr;
    int *right = arr + size - 1;

    while (left < right)
    {
        int temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
    cout << "Arreglo invertido: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}
