#include <stdio.h>

void main() {
    char *s = "121314211";
    int v[4] = {0, 0, 0, 0}, k, i;
    for (k = 0; s[k]; k++) {
//        printf("%c ", s[k]);
        switch (s[k]) {
            case '1':
                i = 0;
//                break;
            case '2':
                i = 1;
//                break;
            case '3':
                i = 2;
//                break;
            case '4':
                i = 3;
//                break;
        }
        v[i]++;
//        printf("%d", i);
//        printf("\n");
    }
    for (k = 0; k < 4; k++) {
        printf("%d", v[k]);
    }
}