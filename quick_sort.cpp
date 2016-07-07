/* クイックソートの使用例（整数編） */
#include <stdio.h>
#include <stdlib.h>

int numcmp(const void *a, const void *b)
{
	return - *((int *)a) + *((int *)b);
}

int main()
{
	int i, a[20];

	/* 適当に数を代入する */
	for( i = 0; i < 20; i++ )
		a[i] = rand() % 100;

	for( i = 0; i < 20; i++ )
		printf("%d,",a[i]);
	putchar('\n');

	/* クイックソート */
	qsort(a, 20, sizeof(int), numcmp);//(*fcmp)(&base[i], &base[j])

	for( i = 0; i < 20; i++ )
		printf("%d,",a[i]);
	putchar('\n');
	return 0;
}
