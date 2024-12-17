#include <iostream>
using namespace std;

class SuffixArray {
private:
    const char* text;
    int n;
    int* sa;
    int* rank;
    int* temp_rank;

public:
    SuffixArray(const char* input_text) {
        text = input_text;

        n = 0;
        while (text[n] != '\0') {
            n++;
        }

        sa = new int[n];
        rank = new int[n];
        temp_rank = new int[n];
    }

    ~SuffixArray() {
        delete[] sa;
        delete[] rank;
        delete[] temp_rank;
    }

    bool Compare(int i, int j, int length) {
        if (rank[i] != rank[j]) return rank[i] < rank[j];
        int ri = (i + length < n) ? rank[i + length] : -1;
        int rj = (j + length < n) ? rank[j + length] : -1;
        return ri < rj;
    }

    void QuickSort(int low, int high, int length) {
        if (low < high) {
            int pi = Partition(low, high, length);
            QuickSort(low, pi - 1, length);
            QuickSort(pi + 1, high, length);
        }
    }

    int Partition(int low, int high, int length) {
        int pivot = sa[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (Compare(sa[j], pivot, length)) {
                i++;
                Swap(sa[i], sa[j]);
            }
        }
        Swap(sa[i + 1], sa[high]);
        return (i + 1);
    }

    void Swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void ConstructUsingPrefixDoubling() {
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = text[i];
        }

        for (int length = 1; length < n; length *=2) {
            QuickSort(0, n - 1, length);

            temp_rank[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                temp_rank[sa[i]] = temp_rank[sa[i - 1]];
                if (Compare(sa[i - 1], sa[i], length)) {
                    temp_rank[sa[i]]++;
                }
            }
            for (int i = 0; i < n; i++) {
                rank[i] = temp_rank[i];
            }
        }
    }

    void Print() {
        for (int i = 0; i < n; i++) {
            cout << sa[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    SuffixArray t("ACGACTACGATAAC$");
    t.ConstructUsingPrefixDoubling();
    t.Print();  // Expected: 14 11 12 0 6 3 9 13 1 7 4 2 8 10 5
    return 0;
}
