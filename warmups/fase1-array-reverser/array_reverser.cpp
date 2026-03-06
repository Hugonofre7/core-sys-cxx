#include <iostream>

// Función que invierte el array usando punteros
void reverse(int *arr, int size)
{
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
}

int main()
{
    int size;

    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    int *arr = new int[size];

    std::cout << "Enter " << size << " numbers: ";
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }

    std::cout << "Original array: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    reverse(arr, size);

    std::cout << "Reversed array: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;

    return 0;
}