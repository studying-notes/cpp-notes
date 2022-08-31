#include <iostream>

using namespace std;

class Base {
public:
  virtual void a() { cout << "Base a()" << endl; }
  virtual void b() { cout << "Base b()" << endl; }
  virtual void c() { cout << "Base c()" << endl; }
};

class Derive : public Base {
public:
  virtual void b() { cout << "Derive b()" << endl; }
};

typedef void (*Func)();

int main() {
  cout << "-----------Base------------" << endl;
  auto *base = new Base;
  auto *tmp1 = (long long *) base;
  auto *vptr1 = (long long *) (*tmp1);
  for (int i = 0; i < 3; i++) {
    cout << "vptr[" << i << "] : " << vptr1[i] << endl;
  }

  Func a = (Func) vptr1[0];
  Func b = (Func) vptr1[1];
  Func c = (Func) vptr1[2];

  a();
  b();
  c();

  cout << "-----------Derive------------" << endl;
  auto *derive = new Derive;
  auto *tmp2 = (long long *) derive;
  auto *vptr2 = (long long *) (*tmp2);
  for (int i = 0; i < 3; i++) {
    cout << "vptr[" << i << "] : " << vptr2[i] << endl;
  }

  Func d = (Func) vptr2[0];
  Func e = (Func) vptr2[1];
  Func f = (Func) vptr2[2];
  d();
  e();
  f();

  return 0;
}
