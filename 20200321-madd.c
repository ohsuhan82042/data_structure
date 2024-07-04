#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
//교재와 같음
typedef enum { head, entry } tagfield;

typedef struct matrix_node* matrix_pointer;
typedef struct entry_node {
   int row;
   int col;
   int value;
} entry_node;

typedef struct matrix_node {
   matrix_pointer down;
   matrix_pointer right;
   tagfield tag;
   union {
      matrix_pointer next;
      struct entry_node entry;
   } u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];
matrix_pointer mread(FILE*); 
void mwrite(matrix_pointer); 
void merase(matrix_pointer*); 
matrix_pointer madd(matrix_pointer, matrix_pointer);

int main() {

   matrix_pointer a, b, d;
   FILE* fp_A, * fp_B;

   fp_A = fopen("A.txt", "r");
   fp_B = fopen("B.txt", "r");
   
   a = mread(fp_A);
   b = mread(fp_B);
   mwrite(a);
   mwrite(b);
   d = madd(a,b);
   mwrite(a);
   mwrite(d);
   merase(&a);
   merase(&b);
   merase(&d);
   mwrite(a);
   mwrite(b);
   mwrite(d);
   fclose(fp_A);
   fclose(fp_B);

   return 0;
}

matrix_pointer new_node() {
   matrix_pointer node = (matrix_node*)malloc(sizeof(matrix_node));
   if (!node) {
      fprintf(stderr, " no available memory");
      exit(0);
   }
   return node;
}

matrix_pointer mread(FILE* fp) {
   int numRows, numCols, numValue, numHeads, i, j,value,row,col,current_row = 0;

   matrix_pointer temp, last, node;
//파일 읽기
   fscanf(fp, "%d %d", &numRows, &numCols);

   numHeads = (numCols > numRows) ? numCols : numRows;

   node = new_node();
   node->u.entry.row = numRows;
   node->u.entry.col = numCols;
//헤더 초기화
   if (!numHeads) node->right = node;
   else {
      for (i = 0; i < numHeads; i++) {
         temp = new_node();
         hdnode[i] = temp; 
            hdnode[i]->tag = head;
         hdnode[i]->right = temp; 
            hdnode[i]->u.next = temp;
      }
   }
//txt 파일의 원소를 하나씩 탐색함
   last = hdnode[0];
   for (i = 0; i < numRows; i++) {
      for (j = 0; j < numCols; j++) {
         fscanf(fp, "%d", &value);
//value를 읽고 0이 아닌 숫자만 가지고 옴
         if (!value) 
         {
            continue;
         }
//다음 열로 넘어가면 current_row를 변경해서 해결함
         if (current_row != i) 
            {
            last->right = hdnode[current_row];
            current_row = i;
            last = hdnode[i];
         }
         temp = new_node();
         temp->tag = entry;
         temp->u.entry.row = i;
         temp->u.entry.col = j;
         temp->u.entry.value = value;
         last->right = temp;
         last = temp;
         hdnode[j]->u.next->down = temp;
         hdnode[j]->u.next = temp;
         numValue++;
      }
   }
//다 읽고 난 뒤 마무리
   last->right = hdnode[numRows - 1];
   for (int i = 0; i < numHeads; i++) {
      hdnode[i]->u.next->down = hdnode[i];
   }
   for (int i = 0; i + 1 < numHeads; i++) {
      hdnode[i]->u.next = hdnode[i + 1];
   }
   hdnode[numHeads - 1]->u.next = node;
   node->right = hdnode[0];
   node->u.entry.value=numValue;
   return node;
}

void mwrite(matrix_pointer node) {
   int i, j;
   if (node == NULL) {
      printf("no element!!!\n");
      return;
   }
   matrix_pointer temp, head = node->right;
   for (i = 0; i < node->u.entry.row; i++) {
      head = head->right;
      for (j = 0; j < node->u.entry.col; j++) 
      {
         if (j == head->u.entry.col) {
            printf("%d ", head->u.entry.value);
            head = head->right;
         }
      
         else 
         {
            printf("%d ", 0);
         }
      }
      head = head->u.next;
      printf("\n");
   }
   printf("\n");
}

void merase(matrix_pointer* node) {
   matrix_pointer x, y, head = (*node)->right;
   int i;
   for (i = 0; i < (*node)->u.entry.row; i++) {
      y = head->right;
      while (y != head) {
         x = y; y = y->right; free(x);
      }
      x = head; head = head->u.next; free(x);
   }
   y = head;
   while (y != *node) {
      x = y; y = y->u.next; free(x);
   }
   free(*node); *node = NULL;
}

matrix_pointer madd(matrix_pointer a, matrix_pointer b) {
    if (!a || !b || a->u.entry.row != b->u.entry.row || a->u.entry.col != b->u.entry.col) {
        fprintf(stderr, "not same size\n");
        return NULL;
    }

    int numRows = a->u.entry.row;
    int numCols = a->u.entry.col;
    int numHeads = (numCols > numRows) ? numCols : numRows;
    int numValue = 0;

    // 결과 행렬을 생성
    matrix_pointer result = new_node();
    result->u.entry.row = numRows;
    result->u.entry.col = numCols;

    // 헤더 초기화
    for (int i = 0; i < numHeads; i++) {
        matrix_pointer temp = new_node();
        hdnode[i] = temp; 
        hdnode[i]->tag = head;
        hdnode[i]->right = temp; 
        hdnode[i]->u.next = temp;
    }

    // 각 위치를 더하여 결과 행렬에 저장
   matrix_pointer a_row = a->right;
   matrix_pointer b_row = b->right;
   matrix_pointer last = hdnode[0];
   int current_row = 0;
    for (int i = 0; i < numRows; i++) {
      a_row = a_row->right;
      b_row = b_row->right;
        for (int j = 0; j < numCols; j++) {
         if(current_row != i){
            last->right = hdnode[current_row];
            current_row = i;
            last = hdnode[i];
         }
         //같은 열일때만 저장할 수 있도록
            int sum = ((a_row->tag != head && a_row->u.entry.col == j) ? a_row->u.entry.value : 0) +
                      ((b_row->tag != head && b_row->u.entry.col == j) ? b_row->u.entry.value : 0);

            if (sum != 0) {
                matrix_pointer temp = new_node();
                temp->tag = entry;
                temp->u.entry.row = i;
                temp->u.entry.col = j;
                temp->u.entry.value = sum;
            last->right = temp;
            last = temp;
            hdnode[j]->u.next->down = temp;
            hdnode[j]->u.next = temp;
                numValue++;
            }

            if (a_row->tag != head && a_row->u.entry.col == j) a_row = a_row->right;
            if (b_row->tag != head && b_row->u.entry.col == j) b_row = b_row->right;
        }
      a_row = a_row->u.next;
      b_row = b_row->u.next;
    }
   last->right = hdnode[numRows - 1];
   for(int i=0;i<numHeads;i++){
      hdnode[i]->u.next->down = hdnode[i];
   }
   for(int i=0;i+1<numHeads;i++){
      hdnode[i]->u.next = hdnode[i+1];
   }
   hdnode[numHeads-1]->u.next = result;
   result->right = hdnode[0];

    // 
    result->u.entry.value = numValue;
    return result;
}