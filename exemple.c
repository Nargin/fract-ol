#include <mlx.h>
#include <math.h>

#define WIDTH 700
#define HEIGHT 540

typedef struct s_complex {
    double r;
    double i;
} t_complex;

typedef struct s_fractal {
    void *mlx_ptr;
    void *win_ptr;
    int img_width;
    int img_height;
    void *img_ptr;
    int bpp;
    int size_line;
    int endian;
    t_complex c;
    t_complex pos;
    double zoom;
    double moveX;
    double moveY;
} t_fractal;

int fractal_escape_time(t_complex z, t_complex c, int max_iter)
{
    int i;
    double tmp;

    i = 0;
    while (i < max_iter && (z.r * z.r + z.i * z.i) < 4)
    {
        tmp = z.r;
        z.r = z.r * z.r - z.i * z.i + c.r;
        z.i = 2 * tmp * z.i + c.i;
        i++;
    }
    return (i);
}

void draw_fractal(t_fractal *fractal)
{
    int x;
    int y;
    int max_iter;
    int color;
    t_complex z;

    max_iter = 100;
    x = 0;
    while (x < fractal->img_width)
    {
        y = 0;
        while (y < fractal->img_height)
        {
            z.r = (x - fractal->img_width / 2.0) / (0.5 * fractal->zoom * fractal->img_width) + fractal->pos.r + fractal->moveX;
            z.i = (y - fractal->img_height / 2.0) / (0.5 * fractal->zoom * fractal->img_height) + fractal->pos.i + fractal->moveY;
            color = fractal_escape_time(z, fractal->c, max_iter);
            mlx_pixel_put(fractal->mlx_ptr, fractal->win_ptr, x, y, color * 0xFFFFFF / max_iter);
            y++;
        }
        x++;
    }
}

void zoom(t_fractal *fractal, int mouseX, int mouseY, double zoomFactor)
{
    double newPosX = fractal->pos.r + (mouseX - fractal->img_width / 2.0) / (0.5 * fractal->zoom * fractal->img_width) + fractal->moveX;
    double newPosY = fractal->pos.i + (mouseY - fractal->img_height / 2.0) / (0.5 * fractal->zoom * fractal->img_height) + fractal->moveY;

    fractal->zoom *= zoomFactor;
    fractal->moveX += fractal->pos.r - newPosX;
    fractal->moveY += fractal->pos.i - newPosY;
    fractal->pos.r = newPosX;
    fractal->pos.i = newPosY;
}

int mouse_hook(int button, int x, int y, t_fractal *fractal)
{
    if (button == 4 || button == 5)
    {
        zoom(fractal, x, y, button == 4 ? 1.1 : 0.9);
        mlx_clear_window(fractal->mlx_ptr, fractal->win_ptr);
        draw_fractal(fractal);
    }
    return (0);
}

int main(void)
{
    t_fractal fractal;

    fractal.mlx_ptr = mlx_init();
    fractal.win_ptr = mlx_new_window(fractal.mlx_ptr, WIDTH, HEIGHT, "Julia Set");
    fractal.img_ptr = mlx_new_image(fractal.mlx_ptr, WIDTH, HEIGHT);
    fractal.pos.r = -0.5;
    fractal.pos.i = 0;
    fractal.zoom = 1.0;
    fractal.moveX = 0.0;
    fractal.moveY = 0.0;

    mlx_hook(fractal.win_ptr, 4, 0, mouse_hook, &fractal);
    mlx_hook(fractal.win_ptr, 5, 0, mouse_hook, &fractal);

    mlx_put_image_to_window(fractal.mlx_ptr, fractal.win_ptr, fractal.img_ptr, 0, 0);
    draw_fractal(&fractal);

    mlx_loop(fractal.mlx_ptr);
    return (0);
}