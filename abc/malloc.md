# C 内存管理

- [C 内存管理](#c-内存管理)
  - [常见错误](#常见错误)
    - [值传递错误](#值传递错误)
      - [双重指针](#双重指针)
    - [局部变量错误](#局部变量错误)
    - [操作已释放内存指针错误](#操作已释放内存指针错误)
    - [通过指针相关字符常量错误](#通过指针相关字符常量错误)

```c
int* p = (int *) malloc(sizeof(int)*128);
```

分配 128 个整型存储单元，并将这 128 个连续的整型存储单元的首地址存储到指针变量 p 中。


```c
if (NULL == (p = (type *) malloc(sizeof (type)))) 
```

判断是否正确分配内存。

## 常见错误

### 值传递错误

```c
void getMemory(char *p) {
    p = (char *) malloc(100);
}

int main() {
    char *str = NULL;
    getMemory(str);
    strcpy(str, "error");
    printf("%s", str);
    return 0;
}
```

#### 双重指针

```c
void getMemory(char **p) {
    *p = (char *) malloc(100);
}

int main() {
    char *str = NULL;
    getMemory(&str);
    strcpy(str, "error");
    printf("%s", str);
    free(str);
    return 0;
}
```

### 局部变量错误

```c
char *getMemory() {
    char p[] = "error";
    return p;
}

int main() {
    char *str = NULL;
    str = getMemory();
    printf("%s", str);
    return 0;
}
```

### 操作已释放内存指针错误

```c
int main() {
    char *str = (char *) malloc(100);
    strcpy(str, "hello");
    free(str);
    if (str != NULL) {
        strcpy(str, "world");
        printf("%s", str);
    }

    return 0;
}
```

### 通过指针相关字符常量错误

```c
void copy(char *s1, char *s2) {
    *s1 = *s2;
}

int main() {
    char *s1 = "ABC\n";
    char *s2 = "abc\n";
    copy(s1, s2);
    printf("%s", s1);
    return 0;
}
```


```c

```


```c

```


```c

```
