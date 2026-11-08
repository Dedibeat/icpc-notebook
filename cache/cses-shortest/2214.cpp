#import <ios>
long K, i = 1, j;

main() {
    for (scanf("%d%ld", &j, &K); j--; printf("%d ", j <= K ? K -= j, i + j : i++));
}