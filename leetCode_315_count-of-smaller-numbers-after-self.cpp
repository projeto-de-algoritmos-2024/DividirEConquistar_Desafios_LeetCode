#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> result(n, 0);        // Armazena a resposta: quantos menores à direita de cada índice
        vector<int> indices(n), temp(n); // 'indices' é para manipular as posições; 'temp' p/ merge auxiliar
        
        // Inicializamos o array de índices
        iota(indices.begin(), indices.end(), 0);

        // Chamamos o mergesort
        mergeSort(nums, indices, result, 0, n - 1, temp);

        return result;
    }

private:
    void mergeSort(const vector<int> &nums, vector<int> &indices,
                   vector<int> &result, int left, int right, vector<int> &temp) {
        if (left >= right) return;
        int mid = (left + right) / 2;
        
        // Ordena/subdivide o lado esquerdo
        mergeSort(nums, indices, result, left, mid, temp);
        // Ordena/subdivide o lado direito
        mergeSort(nums, indices, result, mid + 1, right, temp);
        // Faz o merge e conta quantos menores estão à direita
        merge(nums, indices, result, left, mid, right, temp);
    }

    // merge contabiliza o número de "smaller elements" à direita
    void merge(const vector<int> &nums, vector<int> &indices, 
               vector<int> &result, int left, int mid, int right, vector<int> &temp) {
        int i = left;        
        int j = mid + 1;     
        int pos = left;     
        int countRightUsed = 0;

        while (i <= mid && j <= right) {
            if (nums[indices[i]] <= nums[indices[j]]) {
                result[indices[i]] += countRightUsed;
                temp[pos++] = indices[i++];
            } else {
                temp[pos++] = indices[j++];
                countRightUsed++;
            }
        }

        while (i <= mid) {
            result[indices[i]] += countRightUsed;
            temp[pos++] = indices[i++];
        }

        while (j <= right) {
            temp[pos++] = indices[j++];
        }

        for (int k = left; k <= right; k++) {
            indices[k] = temp[k];
        }
    }
};
