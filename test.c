#include <stdio.h>
#include <math.h>

// void	DrawLine(t_data *data, double x_start, double y_start)
// {
// 	double x_end = x_start + (cos(ANGLE * M_PI / 180) * LINE_LENGHT);
// 	double y_end = y_start + (sin(ANGLE * M_PI / 180) * LINE_LENGHT);
// 	double m;
// 	double b;

// 	// fprintf(stderr, "x_end == %f, y_end %f\n", x_end, y_end);
// 	m = ((y_end - y_start) / (x_start - x_end));
// 	b = y_start - (m * x_start);
// 	fprintf(stderr, "m == %f, b == %f\n", m, b);
// 	for (double y = y_start; y <= y_end; y += 0.1)
// 	{
// 		for(double x = x_start; x <= x_end; x += 0.1)
// 		{
// 			if (round((y - (m * x) - b)) == 0)
// 			{
// 				write(2, "HERE\n", 5);
// 				fprintf(stderr, "x == %f, y == %f\n", x, y);
// 				my_mlx_pixel_put(data, x, y, 0xE24666);
// 			}
// 			// fprintf(stderr, "x == %f, y %f", x, y);
// 		}
// 	}
// 	my_mlx_pixel_put(data, x_end, y_end, 0xE24666);
// }






int main()
{
	double a = 2.554;
	double b = 2.123456;


	double r = remainderf(a, b);
	printf("remainder == %f\n", r);
}


1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
#include<stdio.h>
// #include<graphics.h>
 
void drawline(int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
 
	dx=x1-x0;
	dy=y1-y0;
	
	x=x0;
	y=y0;
	
	p=2*dy-dx;
	
	while(x<x1)
	{
		if(p>=0)
		{
			putpixel(x,y,7);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			my_mlx_pixel_put(data, x,y,7);
			p=p+2 * dy;
		}
		x++;
	}
}
