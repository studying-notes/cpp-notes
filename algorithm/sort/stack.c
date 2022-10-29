#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct node {
    int member;
    struct node *pNext;
} Node, *pNode;

typedef struct stack {
    pNode Top;
    pNode Bottom;
} Stack, *pStack;

void init(pStack);

bool push(pStack, int);

void traverse(pStack);

bool is_empty(pStack);

int pop(pStack);

void clear(pStack);

int main(void) {
    Stack s;
    int i, num, data, re_num;
    init(&s);
    printf("Number: ");
    scanf("%d", &num);
    for (i = 0; i < num; i++) {
        printf("No.%d: ", i + 1);
        scanf("%d", &data);
        if (push(&s, data)) {
            continue;
        } else {
            printf("进栈操作失败！\n");
            exit(-1);
        }
    }
    traverse(&s);
}

void init(pStack ps) {
    ps->Top = (pNode) malloc(sizeof(Node));
    if (NULL == ps->Top) {
        printf("动态分配内存失败\n");
        exit(-1);
    } else {
        ps->Bottom = ps->Top;
        ps->Top->pNext = NULL;
    }
}

bool push(pStack ps, int data) {
    pNode pNew = (pNode) malloc(sizeof(Node));
    if (NULL == pNew) {
        return false;
    }
    pNew->member = data;
    pNew->pNext = ps->Top;
    ps->Top = pNew;
    return true;
}

void traverse(pStack ps) {
    pNode pNew = ps->Top;
    while (pNew != ps->Bottom) {
        printf("%d ", pNew->member);
        pNew = pNew->pNext;
    }
}

bool is_empty(pStack ps) {
    if (ps->Top == ps->Bottom) {
        return true;
    } else {
        return false;
    }
}

int pop(pStack ps) {
    pNode pSwap = NULL;
    int return_val;
    if (is_empty(ps)) {
        exit(-1);
    } else {
        return_val = ps->Top->member;
        pSwap = ps->Top;
        ps->Top = ps->Top->pNext;
        free(pSwap);
        return return_val;
    }
}

void clear(pStack ps) {
    pNode pNew = NULL;
    while (ps->Top != ps->Bottom) {
        pNew = ps->Top;
        ps->Top = ps->Top->pNext;
        free(pNew);
    }
}