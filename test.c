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