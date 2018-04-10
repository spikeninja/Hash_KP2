#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEY int
#define HASH(x,y) (x)%(y)
#define HASH_DA(key) (key)
#define EQUAL(x,y) (x)==(y)
#define MAX 10

typedef struct {
    KEY * key;
} item;

typedef struct{
    int n, m;
    item ** array;
} hash_tbl;


void hash_tbl_init(hash_tbl * ht,int max);
int hash_tbl_count(hash_tbl * ht);
int hash_tbl_insert(hash_tbl * ht, item * it);
int hash_tbl_search(hash_tbl * ht, KEY k);
int hash_tbl_free(hash_tbl * ht);
int hash_tbl_delete(hash_tbl * ht, item * it);

void item_free(item ** v);

int main(){
    item * it = NULL;
    hash_tbl * h = (hash_tbl *)malloc(sizeof(hash_tbl));
    if (!h) {
        printf("\nBad allocation!");
        exit(1);
    }
    printf("\n-------- INIT HASH-TABLE --------\n");
    hash_tbl_init(h, MAX);
    srand(time(NULL));
    printf("\n-------- INSERT --------\n");
    for(int i = 0; i < MAX; i++){
        it = (item*)malloc(sizeof(item));
        it->key = (KEY*)malloc(sizeof(KEY));
        if (!it) {
            printf("\nBad allocation!");
            exit(1);
        }
        *(it->key) = rand() % 10000;
        printf("Item %5d was inserted in \t%d index\n", *(it->key), hash_tbl_insert(h, it));
    }
    printf("\n-------- SEARCH --------\n");
    for(int i = 0; i < MAX; i++){
        int key = 0;
        it = (h->array)[rand()%h->m];
        if (it)    key = *(it->key);
        else key = rand()% 10000;
        printf("Item with key = %5d in \t%d index\n", key, hash_tbl_search(h, key));

    }
    printf("\n-------- DELETE --------\n");
    for(int i = 0; i < 2*MAX; i++){
        it = (h->array)[rand()%h->m];
        if (it)    {
            printf("Item with key = %5d was deleted ",*(it->key));
            printf(" \t%d index\n", hash_tbl_delete(h, it));
        }
    }
    printf("\n-------- FREE HASH-TABLE --------\n");
    printf("\n%d items were deleted\n", hash_tbl_free(h));
    free(h);
    return 0;
}
void hash_tbl_init(hash_tbl * ht,int max){
    ht->n = 0;
    ht->m = MAX * 2;
    ht->array = (item **)malloc((ht->m) * sizeof(item *));
    if (!ht->array) {
        printf("\nBad allocation!");
        exit(1);
    }
    for (int i = 0; i < ht->m; i++) {
        (ht->array)[i] = NULL;
    }
}
int hash_tbl_count(hash_tbl * ht){
    // ...
     return 0;
}
int hash_tbl_insert(hash_tbl * ht, item * it){
    KEY k = *(it->key);
    int i = HASH(k, ht->m);
    while(ht->array[i]){
        i = (i + 1) % ht-> m;
    }
    ht->array[i] = it;
    (ht->n)++;
    return i;

}
int hash_tbl_search(hash_tbl * ht, KEY k){
    int count = 0;
    int i = HASH(k, ht -> m);
    while(ht->array[i]){
        count++;
        if(EQUAL(k, *((ht->array)[i] -> key))){
        printf("%d",count);
            return i;
        }else{
            i= (i + 1) % ht->m;
    }
    }
    printf("%d",count);
    return -1;
}

int hash_tbl_delete(hash_tbl * ht, item * it){
    int i = HASH(*(it->key), ht->m);
    item * v = NULL;
    int cnt = 0;
    int tr = 1;
    while(((ht->array)[i]) && tr){
        cnt++;
        if(EQUAL(*(it->key), *((ht->array)[i] -> key))){
            tr = 0;
        }else{
             i= (i + 1) % ht->m;
        }
    }
    if(!(ht->array)[i]){
        printf("%d",cnt);
        return -1;
    }
    printf("%d",cnt);
    item_free(&((ht->array)[i]));
    (ht->n)--;
    cnt = 0;
    int j = (i + 1) % ht->m;
    while ((ht->array)[j]) {
        v = (ht->array)[j];
        (ht->array)[j] = NULL;
        cnt++;
        (ht->n)--;
        hash_tbl_insert(ht, v);
        j = (j+1) % ht->m;
    }
    printf("%d",cnt);
    return i;
}
void item_free(item ** v){
    if (*v){
        if ((*v)->key) free((*v)->key);
        (*v)->key = NULL;
        free((*v));
    }
    (*v) = NULL;
}
int hash_tbl_free(hash_tbl * ht){
    int cnt = 0;
    if (ht) {
        if (ht->array) {
            for (int i = 0; i < ht->m ; i++){
                if ((ht->array)[i]) cnt++;
                item_free(&((ht->array)[i]));
            }
        }
        free(ht->array);
        ht->array = NULL;
    }
    return cnt;
}
