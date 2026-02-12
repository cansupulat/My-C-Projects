#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- 1. VERI YAPILARI (STRUCTS) ---
struct Node {
    char data;
    unsigned freq;
    struct Node *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct Node** array;
};

// --- 2. YARDIMCI FONKSIYONLAR (Önce bunlarý tanýmlýyoruz) ---

struct Node* newNode(char data, unsigned freq) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Node**)malloc(minHeap->capacity * sizeof(struct Node*));
    return minHeap;
}

void swapNode(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct Node* extractMin(struct MinHeap* minHeap) {
    struct Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct Node* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// --- 3. ANA HUFFMAN FONKSIYONLARI (Yardýmcýlarý kullanýyorlar) ---

struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    struct Node *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);
    int i=0;
    for (i = 0; i < size; ++i)
        insertMinHeap(minHeap, newNode(data[i], freq[i]));

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        int i=0;
        for (i = 0; i < top; ++i) printf("%d", arr[i]);
        printf("\n");
    }
}

// --- 4. MAIN ---
int main() {
    char metin[500];
    int freq[256] = {0};
    
    printf("Huffman koduna cevirmek istediginiz metni girin: ");
    fgets(metin, sizeof(metin), stdin);

    metin[strcspn(metin, "\n")] = 0;

    // Metindeki karakterlerin frekansýný say
    int i;
    for (i = 0; metin[i] != '\0'; i++) {
        freq[(unsigned char)metin[i]]++;
    }

    // Sadece geçen karakterleri dizilere aktar
    char arr[256];
    int f[256];
    int j = 0;
    for (i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            arr[j] = (char)i;
            f[j] = freq[i];
            j++;
        }
    }

    // Aðacý kur ve kodlarý yazdýr
    struct Node* root = buildHuffmanTree(arr, f, j);

    int codes[100], top = 0;
    printf("\n--- Huffman Kodlari ---\n");
    printCodes(root, codes, top);

    return 0;
}
