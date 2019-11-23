#include <stdio.h>
#include <stdlib.h>

typedef struct {int x; int y;} point;

void assign_val(int *i, int val);
void assign_point(point *p, int x, int y);
void create_point(point **p, int x, int y);

int main()
{
	int x = 123;
	printf("x = %d\n", x);
	assign_val(&x, 456);
	printf("x = %d\n", x);

	point p;
	assign_point(&p, 42, 33);
	printf("p = { %d, %d }\n", p.x, p.y);

	point *p2;
	create_point(&p2, 12, 34);
	printf("p2 = { %d, %d }\n", p2->x, p2->y);

	free(p2);
}

void assign_val(int *i, int val)
{
	*i = val;
}

void assign_point(point *p, int x, int y)
{
	p->x = x;
	p->y = y;
}

void create_point(point **p, int x, int y)
{
	*p = malloc(sizeof(point));
	(*p)->x = x;
	(*p)->y = y;
}

