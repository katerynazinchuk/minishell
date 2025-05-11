#include <stdio.h>
#include <unistd.h>

int main() {
	int a = 10;
    if (a > 0) {
        return -3; // Повертаємо -1 у випадку помилки write
    }
	else
    	return 0; // Повертаємо 0 при успішному виконанні
}
