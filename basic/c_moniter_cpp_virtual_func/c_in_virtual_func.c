#include <stdio.h>

typedef struct {
    int base_data;
} Base;

typedef struct {
    Base base;
    int derived_data;
} Derived;

// 虚函数指针类型
typedef void (*VirtualFunction)(Base *);

// 基类的虚函数实现
void basePrint(Base *self) {
    printf("Base class data:%d\r\n", self->base_data);
}

void derivedPrint(Base *self) {
    // 将基类指针强制转换为派生类指针
    Derived *derivedSelf = (Derived*)self;
    printf("Derived class data:%d\r\n", derivedSelf->derived_data);
}

void initBase(Base *self, int data) {
    self->base_data = data;
}

void initDerived(Derived *self, int baseData, int derivedData) {
    initBase(&(self->base), baseData);
    self->derived_data = derivedData;
}

void callVirtualFunction(Base *self, VirtualFunction virtualFunction) {
    virtualFunction(self);
}

int main() {
    // 创建基类
    Base baseObj;
    int baseData = 10;
    initBase(&baseObj, baseData);

    Derived derivedObj;
    int derivedData = 20;
    initDerived(&derivedObj, baseData, derivedData);

    // 调用基类虚函数
    callVirtualFunction(&baseObj, basePrint);

    // 调用派生类虚函数
    callVirtualFunction((Base*)&derivedObj, derivedPrint);
}

