#include <stdlib.h>
#include <stdio.h>
#include "minilibx_linux/mlx.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int key_hook(int keycode, t_data *data)
{
    printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)  // ESC key
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    return (0);
}

int draw(t_data *data)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            my_mlx_pixel_put(data, 100 + i, 100 + j, 0x00FF0000);
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

int main(void)
{
    t_data data;

    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);

    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "MLX Test");
    if (!data.win)
        return (1);

    data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    mlx_key_hook(data.win, key_hook, &data);
    mlx_loop_hook(data.mlx, draw, &data);

    mlx_loop(data.mlx);

    return (0);
}

// cc mlx_test.c -I./minilibx_linux -L./minilibx_linux -lmlx -lX11 -lXext -lm -o mlx_test