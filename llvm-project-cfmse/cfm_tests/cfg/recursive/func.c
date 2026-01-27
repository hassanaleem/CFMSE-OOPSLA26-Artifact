void func1(int a);
void func2(int b);
void func3(int c);
void func4(int d);

void func1(int a) {
    if (a > 10) return;
    func1(a+1);
    func1(a+2);
}

void func2(int b) {
    if (b > 10) return;
    if (b < 5)
        func3(b+1);
}

void func3(int c) {
    if (c > 10) return;
    int i = 0;
    while (i < 5) {
        func2(c+1);
        i++;
    }
}

void func4(int d) {
    int i = 10;
    while (i > 0) i--;
    return;
}
