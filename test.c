#include <stdio.h>
#include <math.h>

// void	DrawLine(t_data *data, float x_start, float y_start)
// {
// 	float x_end = x_start + (cos(ANGLE * M_PI / 180) * LINE_LENGHT);
// 	float y_end = y_start + (sin(ANGLE * M_PI / 180) * LINE_LENGHT);
// 	float m;
// 	float b;

// 	// fprintf(stderr, "x_end == %f, y_end %f\n", x_end, y_end);
// 	m = ((y_end - y_start) / (x_start - x_end));
// 	b = y_start - (m * x_start);
// 	fprintf(stderr, "m == %f, b == %f\n", m, b);
// 	for (float y = y_start; y <= y_end; y += 0.1)
// 	{
// 		for(float x = x_start; x <= x_end; x += 0.1)
// 		{
// 			if (roundf((y - (m * x) - b)) == 0)
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
	float a = 2.554;
	float b = 2.123456;


	float r = remainderf(a, b);
	printf("remainder == %f\n", r);
}