#define SIZE 100

typedef int List[SIZE];

//初始化表。构造一个空的线性表。
void InitList(List &L);

//求表长。返回线性表L的长度，即L中数据元素的个数。
int Length(List L);

// 按值查找操作。在表L中查找具有给定关键字值的元素。
int LocateElem(List L, int e);

//按位查找操作。获取表L中第1个位置的元素的值。
int GetElem(List L, int i);

//插入操作。在表中的第1个位置上插入指定元素e。
void ListInsert(List &L, int i, int e);

// 删除操作。删除表L中第1个位置的元素，并用e返回删除元素的值。
void ListDelete(List &L, int i, int &e);

// 输出操作。按前后顺序输出线性表L的所有元素值。
void PrintList(List L);

// 判空操作。若L为空表，则返回true，否则返回false。
int EmptyList(List L);

// 销毁操作。销毁线性表，并释放线性表L所占用的内存空间。
void DestroyList(List &L);

int main() {
  return 0;
}
