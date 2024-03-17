// CS 317-01: Programming Assignment 1
// Author:    Isaiah R. Harville
// Date:      3/29/2024
//
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

void mergeSort(std::string arr[], int left, int right);
void merge(std::string arr[], int left, int middle, int right);
std::string toLower(const std::string& str);
std::string leftAlign(const std::string& str, size_t width);


int main()
{
    const int MAX_WORD_COUNT = 100000;
    std::string* words = new std::string[MAX_WORD_COUNT];
    std::string* words_c = new std::string[MAX_WORD_COUNT];
    std::string word;                   // Iterator
    std::string in_file_name;
    std::string out_file_name;
    int words_per_line;                 // The amount of words to print per line in o_f
    int count = 0;                      // Count amount of words in the file

    // Copying each element from words
    for (int i = 0; i < MAX_WORD_COUNT; i++) {
        words_c[i] = words[i];
    }

    // Prompt for i/o files
    std::cout << "INPUT FILE: ";
    std::cin >> in_file_name;

    std::cout << std::endl << "OUTPUT FILE: ";
    std::cin >> out_file_name;
    std::cout << std::endl;

    // Open input file
    std::ifstream file(in_file_name);
    if (!file.is_open()) { return 1; } // Failed to open

    while (file >> word && count < MAX_WORD_COUNT) {
        words[count++] = word;
    } file.close();

    // Words per line
    std::cout << "READ " << count << " WORDS FROM: " << in_file_name << std::endl;
    std::cout << std::endl << "WORDS PER LINE: ";
    std::cin >> words_per_line;

    // Outputs
    std::ofstream out_file(out_file_name);
    if (!out_file.is_open()) { return 1; }

    size_t max_length = 0; // longest word in the array
    for (int i = 0; i < count; ++i) {
        max_length = std::max(max_length, words[i].length());
    }

    // Write quick sort
    //quickSort(words)

    out_file << count << " words sorted using Quick Sort:\n";
    for (int i = 0; i < count; ++i) {
        out_file << leftAlign(words[i], max_length) << ",";
        if (!((i + 1) % words_per_line)) { out_file << "\n"; }
    } out_file << "\n";

    std::reverse(words, words + count);

    // Write merge sort
    mergeSort(words_c, 0, count - 1);

    out_file << count <<" words sorted using Merge Sort:\n";
    for (int i = 0; i < count; ++i) {
        out_file << leftAlign(words[i], max_length) << ",";
        if (!((i + 1) % words_per_line)) { out_file << "\n"; }
    } out_file << "\n";

    std::cout << "End of program." << std::endl;
}

void mergeSort(std::string arr[], int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
        std::cout << arr[0] << std::endl;
    }
}


void merge(std::string arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::string* l_a = new std::string[n1];
    std::string* r_a = new std::string[n2];

    for (int i = 0; i < n1; i++)
        l_a[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        r_a[i] = arr[m + 1 + i];


    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if ((toLower(l_a[i]) <= toLower(r_a[j]))) {
            arr[k] = l_a[i];
            i++;
        }
        else {
            arr[k] = r_a[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = l_a[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = r_a[j];
        j++;
        k++;
    }

    delete[] l_a; delete[] r_a;
}


std::string toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

std::string leftAlign(const std::string& s, size_t w) {
    return s + std::string(w - s.length(), '\t');
}
