/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <bmoulin@42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:39:48 by bmoulin           #+#    #+#             */
/*   Updated: 2021/02/26 11:51:16 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
#include <fcntl.h>
#define KEY_D 2
#define KEY_S 1 
#define KEY_A 0
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define PI 3.14159265359
#define NORTH 4.71239
#define SOUTH 1.5708
#define EAST 3.14159
#define WEST 0
//#define MINIMAP_HEIGHT (int)512
// #define MINIMAP_WIDTH (int)512
#define MAP_HEIGHT (int)512
#define MAP_WIDTH (int)1024
#define FOV 1.0472

typedef struct		s_list
{
      void			*content;
      struct s_list	*next;
}					t_list;

typedef struct	s_struct
{
	int				lenmax; // width de la map
	int				Rx; // Width
	int				Ry; // Height
	int				i;
	int				F_R; //couleur sol
	int				F_G;
	int				F_B;
	int				C_R; //couleur ciel
	int				C_G;
	int				C_B;
	int				northside;
	char			position; //orientation WNES
	int				xplayer; //px
	int				yplayer; //py
	char			*pathtoNO;
	char			*pathtoSO;
	char			*pathtoWE;
	char			*pathtoEA;
	char			*pathtoS;
	char			*map;

}				t_struct;

typedef struct  s_cub {
        void    *mlx;
        void    *win;
		int		x;
		int		y;
		void    *img;
		char    *addr;
		int     bits_per_pixel;
		int     line_length;
		int     endian;
}               t_cub;

typedef struct  s_data {
		int		cx;
		int		cy;
		double	px;
		double	py;
		double	pa;
		double	pdx;
		double	pdy;
		double	rdx;
		double	rdy;
		double	angle_min;
		int		imgx;
		int		imgy;
		int		minimap_height;
		int		minimap_width;
		int		map_height;
		int		map_width;
		int		mapX;
		int		mapY;
		int		mapS;
		int		x;
		int		y;
}               t_data;

typedef struct  	s_img {
		int    	bits_per_pixel;
		int    	line_length;
		int     endian;
		char    *addr;
		void    *img;
    	char    *relative_path;
    	int     img_width;
		int     img_height;
}               	t_img;

typedef struct  	s_vars {
        void    	*mlx;
        void    	*win;
		int			x;
		int			y;
		void    	*img;
		char    	*addr;
		int     	bits_per_pixel;
		int     	line_length;
		int     	endian;
		t_cub		*cub;
		t_struct	*pars;
		t_data		*data;
		t_img		*txt;
}               	t_vars;

int             close_exit(int keycode, t_vars *vars);
void            my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int             loop_hook(t_vars *vars);
void			playerposition(t_vars *vars);
int             key_hook(int keycode, t_vars *vars);
void			putsquareWall(t_vars *vars, int x, int y);
void			putsquareVoid(t_vars *vars, int x, int y);
void			putWallInImage(t_vars *vars);
void			ft_putbackground(t_vars *vars);
void			drawline(int x0, int y0, int x1, int y1, t_vars *vars);
double			drawray(int x0, int y0, int x1, int y1, t_vars *vars);
int				ft_retindex(int px, int py, int mapX);
void			ft_putbackground2(t_vars *vars);
void			*wrmalloc(unsigned long size);
int				wrfree(void *ptr);
void			wrdestroy(void);
t_list			*ft_lstlast(t_list *lst);

//----------------------------------------------------------------------------------------------

t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
int				ft_lstsize(t_list *lst);
t_list			*makelst(int fd, t_struct *mstruct);
int				getlenmax(t_list **alst);
char			**fromlsttotab(t_list **alst, t_struct *mstruct);
char			**fillthetabwithspaces(char **tab, t_struct *mstruct);
void			structinit(t_struct *mstruct);
int				checkthenorth(char **tab, t_struct *mstruct);
int				checkalltab(char **tab, t_struct *mstruct);
int				checkspaces(char **tab, t_struct *mstruct, int i, int j);
int				checkthemap(char **tab, t_struct *mstruct);
t_struct		*ismapvalid(char **arv);
int				ft_atoi(const char *nptr);
size_t			ft_cmpt(char const *s, char c);
char			*ft_free(char **tab, size_t i);
char			**ft_mem(char const *s, char c);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			checkelemR(char *line, t_struct *mstruct);
char			*checktheid(char *line, char a, char b);
void			checkelemF(char *line, t_struct *mstruct);
void			checkelemC(char *line, t_struct *mstruct);
int				checktheorder(char **tab, t_struct *mstruct);
char			*ft_strcpy(char *dst, const char *src, size_t dstsize);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *s);
static size_t	ft_check(char c, char const *set);
static char		*ft_putzero(char *str, size_t i);
char			*ft_strtrim(char const *s1, char const *set);
int				shouldiskip(char *line, t_struct *mstruct, int a);
char			*ft_strdup(const char *s);
int				checkplayerposition(char **tab, t_struct *mstruct);
t_struct		*fromdoubletosimple(char **tab, t_struct *mstruct);

#endif