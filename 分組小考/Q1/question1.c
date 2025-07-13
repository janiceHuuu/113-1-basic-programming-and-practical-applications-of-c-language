#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val){
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
};

struct TreeNode* buildTree (char* input){
    input += 5;
    input[strlen(input) - 1] = '\0';

    char* token = strtok(input, ",");
    if (!token || strcmp(token, "null") == 0) {
        return NULL;
    }

    struct TreeNode* root = createNode(atoi(token));
    struct TreeNode* queue[100000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while ((token = strtok(NULL, ",")) != NULL) {
        struct TreeNode* node = queue[front++];

        if (strcmp(token, "null") != 0) {
            node->left = createNode(atoi(token));
            queue[rear++] = node->left;
        }

        if ((token = strtok(NULL, ",")) != NULL && strcmp(token, "null") != 0) {
            node->right = createNode(atoi(token));
            queue[rear++] = node->right;
        }
    }

    return root;
}

int compare(const void* a, const void* b) {
    return ((int*)a)[0] - ((int*)b)[0];
}

int calculateMinSwaps(int* arr, int size) {
    int swaps = 0;
    int pairs[size][2];
    for (int i = 0; i < size; i++) {
        pairs[i][0] = arr[i];
        pairs[i][1] = i;
    }

    qsort(pairs, size, sizeof(pairs[0]), compare);

    int visited[size];
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < size; i++) {
        if (visited[i] || pairs[i][1] == i) continue;

        int cycle_size = 0, j = i;
        while (!visited[j]) {
            visited[j] = 1;
            j = pairs[j][1];
            cycle_size++;
        }

        swaps += cycle_size - 1;
    }

    return swaps;
}

int minimumOperations(struct TreeNode* root) {
    if (!root) return 0;

    struct TreeNode* queue[100000];
    int front = 0, back = 0;

    queue[back++] = root;
    int total_swaps = 0;

    while (front < back) {
        int level_size = back - front;
        int* level_values = (int*)malloc(level_size * sizeof(int));

        for (int i = 0; i < level_size; i++) {
            struct TreeNode* node = queue[front++];
            level_values[i] = node->val;

            if (node->left) queue[back++] = node->left;
            if (node->right) queue[back++] = node->right;
        }

        total_swaps += calculateMinSwaps(level_values, level_size);
        free(level_values);
    }

    return total_swaps;
}

int main() {
    char input[100000];
    printf("Input tree as root=[...]: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // ¥h±¼´«¦æ²Å

    struct TreeNode* root = buildTree(input);

    int result = minimumOperations(root);
    printf("Minimum operations needed: %d\n", result);

    return 0;
}
