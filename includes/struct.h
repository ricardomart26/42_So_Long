#ifndef STRUCT_H
# define STRUCT_H


typedef struct s_img {
	void	*img_var;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

#endif