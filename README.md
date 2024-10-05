This project was done by:

Jhonas Leal - https://github.com/Jburlama

Uatilla  Almeida - https://github.com/Uatilla

![screencast-from-10-02-2024-075450-pm-qmgathoj_bob4h5d7-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/b106da57-a23c-400b-924d-7da3dbd8bf8c)




# miniRT
**My first RayTracer with miniLibX** the last C project from 42 Common Core Program. The main goal of this project is about implementing a [**raytracing algorithm**](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)). We must implement scene aspects as ambient lightining, camera, light, and objects (sphere, plane, cylinder, and cone (bonus only)).
Besides these elements, we must apply moviments and rotations into the each element of the scene.
For more detailed information, look at the [**subject of this project**](https://cdn.intra.42.fr/pdf/pdf/113053/en.subject.pdf).

One of our learnings after building this project is that **everyone can apply mathematics or physics without being a mathematician or physician.**

## How to use it

### Getting Started
**Program start process:**
![Untitled(1)](https://github.com/user-attachments/assets/6ba44dce-98b3-41d8-92f4-3262e822bb91)

**Event handler:**
![Untitled(2)](https://github.com/user-attachments/assets/25738721-7ddf-4647-812f-f013c1d59bd0)


## Usage

If you want to run the project yourself:

	- First clone this git repository to your machine.
 
	- Enter the repo and run ``` make ```
 
	- The first time will download and set up the minilibx
 
	- Run ./minirt <scene>.rt

![Screencastfrom2024-10-0213-06-34-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/de0515b2-773e-4dc4-b93e-9673e2670730)
## Movements and Rotation
- As will be explained on **Matrices Transformations**, every element on the screen has two structures one called **transformation** and another called **inverse** these two matrices has the function to deal with  modifications on how the scene element is displayed on the screen. Every time the program catches a movement or rotation event, it updates these elements to express the behavior desired by the user:
- Here you can see the possible movements/rotation for each element:
  
  ![Untitled(3)](https://github.com/user-attachments/assets/1b0c933a-844b-4fc7-8247-3718f7d99b51)
  
- Element type selection:
  
  ![image](https://github.com/user-attachments/assets/e1e5813c-ec26-4b62-aaf4-c956c01a7e6d)

  
- Remember once you hit 'o' all objects were selected, then you can use tab to change between the objects on the screen or click on home to remove the element type selection:
  
  ![image](https://github.com/user-attachments/assets/0601d63c-c66e-486d-8726-930873bb3612)

**The effects of modidifications on scene elements are:**

Center of the image:

![image](https://github.com/user-attachments/assets/835310bb-cd54-4e1d-86d5-f59ef64d71ba)

Move to the right (using 'c' to select the camera, using right key to move the camera):

![image](https://github.com/user-attachments/assets/506e7685-9c4e-4f0a-9bdc-35400197ac89)

Rotating the camera to the left on its own position (not necessary to hit 'c' again, once the camera was already selected, using 'q' key to rotate counter clockwork).

![image](https://github.com/user-attachments/assets/dc884e02-27c6-48dd-9719-09988b0d54ce)

Bringing only the yellow sphere to the camera (using 'o' to select the objects (all objects were selected), hitting 'tab' to select only the sphere and '+' to zoom the sphere).

![image](https://github.com/user-attachments/assets/d26e8f88-92aa-48bb-8784-bfc00fe85f33)

Moving the light to the left side (using 'l' to select the light and then left arrow to move it to the left).

![image](https://github.com/user-attachments/assets/600545d5-23f7-4ddb-87c1-9f00677d0485)

### Try it by yourself!

![image](https://github.com/user-attachments/assets/f567a756-da1c-4cb7-b399-d963b8ec70e0)


## Rules

**Norminette:**

The Norminette is a tool provided by 42 Network to check whether the source code complies with the school's norm. The rules include the prohibition of ‘for’ loops, a limit of 25 lines, and no more than 4 parameters in each function, among other specifications.

Here is a [link](https://github.com/gdamion/Norminette/blob/master/norme.en.pdf) to more details about what is evaluated by the Norminette tool.


**MiniLibX:**
 - This project uses the minilibx-linux, a API written in c by 42 students, to interact with the X11 window system.

	https://github.com/42Paris/minilibx-linux

# Technical overview
## Tuples

- A tuple is just an ordered list of things, like numbers.
- For this project, we used two types of tuples:
	- points and vector

- the way we can tell if a tuple (x, y, z) is a point or a vector, we introduce a new component w;
	- (x, y, z, w);
	- if w == 0, the tuple is a vector;
	- if w == 1, the tuple is a point;

```c
typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
} t_tuple;
```

```c
t_tuple	creating_tuple(float x, float y, float z, float w)
{
	t_tuple	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
	return (ret);
}
```
## Operations

Now that we have tuples, we need to be able to make operations with them.

## Adding

- Let's say you start from a point (3, -2, 5, 1) and you want to know where you will be if you follow a vector (-2, 3, 1, 0) from that point, you can add those tuples together, and the result will be a new point.

``` c
t_tuple	sum_tuples(t_tuple *a, t_tuple *b)
{
	t_tuple	res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	res.w = a->w + b->w;
	return (res);
}
```

## Subtracting

- You can find the vector that goes from one point to another by subtracting them.
- for example:
- *point(3, 2, 1, 1) - point(5, 6, 7, 1) = vector(-2, -4, -6, 0).*
- notice that the w components cancel each other out, resulting in a vector;

- Similarly, you can subtract a vector (w of 0) from a point (w of 1) and get another tuple with a w of 1, a point. Conceptually, this is just moving backward by the given vector.
- *point(3, 2, 1, 1) - vector(5, 6, 7, 0) = vector(-2, -4, -6, 0)*

- Lastly, subtracting two vectors gives us another vector, representing the change in direction between the two.
- *vector(3, 2, 1, 0) - vector(5, 6, 7, 0) = vector(-2, -4, -6, 0).*

```c
t_tuple	subtrac_tuples(t_tuple *a, t_tuple *b)
{
	t_tuple	res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	res.w = a->z - b->w;
	return (res);
}
```
## Negating
	
- Sometimes you’ll want to know what the opposite of some vector is.
- Mathematically, you can get it by subtracting the vector from the tuple (0, 0, 0, 0).
- *(0, 0, 0, 0) - (1, -2, 3, 0) = (-1, 2, -3, 0).*

```c
t_tuple	negating_tuple(t_tuple *a)
{
	return (subtrac_tuples(&(t_tuple){0, 0, 0, 0}, a));
}
```
## Scalar multiplication and Division

- Now let’s say you have some vector and you want to know what point lies 3.5 times farther in that direction.
- Multiplying the vector by 3.5 does just what you need. The 3.5 here is a scalar value because multiplying by it scales the vector (changes its length uniformly).
- To do it, you multiply each tuple component by the scalar.
- *tuple(1, -2, 3, -4) * 3.5 = (3.5, -7, 10.5, -14).*

- The same works for division
- *tuple(1, -2, 3, -4) / 2 = (0.5, -1, 1.5, -2).*

- Another way of doing division is to divide by a fraction
- *tuple(1, -2, 3, -4) * 0.5 = (0.5, -1, 1.5, -2).*

``` c
t_tuple	mult_tuple_scalar(t_tuple *a, float sc)
{
	t_tuple	res;

	res.x = a->x * sc;
	res.y = a->y * sc;
	res.z = a->z * sc;
	res.w = a->w * sc;
	return (res);
}
```

```c
t_tuple	div_tuple_scalar(t_tuple *a, float sc)
{
	t_tuple	res;

	res.x = a->x / sc;
	res.y = a->y / sc;
	res.z = a->z / sc;
	res.w = a->w / sc;
	return (res);
}
```
## Magnitude

- The distance represented by a vector is called its magnitude, or length.
- We can use the Pythagorean Theorem  to find the magnitude.

![Screenshot from 2024-09-18 18-09-38](https://github.com/user-attachments/assets/0f99335f-3d1c-4ba5-811f-f42972102097)


```c
float	magnitude(t_tuple *a)
{
	t_tuple	res;

	res.x = a->x * a->x;
	res.y = a->y * a->y;
	res.z = a->z * a->z;
	res.w = a->w * a->w;
	return (sqrtf(res.x + res.y + res.z + res.w));
}
```

## Normalization

- Vectors with magnitudes of 1 are called a unit vectors, and these will be super handy.
- Normalization is the process of taking an arbitrary vector and converting it into a unit vector.
- It will keep the calculations anchored relative to a common scale (the unit vector), which is pretty important. If we were to skip normalizing the ray vectors or the surface normals, the calculations would be scaled differently for every ray we cast, and the scenes would look terrible (if they rendered at all).
- You normalize a tuple by dividing each of its components by its magnitude.

```c
t_tuple	normalize(t_tuple *a)
{
	return (creating_tuple(a->x / magnitude(a), a->y / magnitude(a),
			a->z / magnitude(a), a->w / magnitude(a)));
}
```

## Dot product

- The dot product takes two vectors and returns a scalar value.
- Given those two vectors, the dot product is computed as the sum of the products of the corresponding components of each vector.

``` c
float	dot_product(t_tuple *a, t_tuple *b)
{
	t_tuple	res;

	res.x = a->x * b->x;
	res.y = a->y * b->y;
	res.z = a->z * b->z;
	res.w = a->w * b->w;
	return (res.x + res.y + res.z + res.w);
}
```

- the smaller the dot product, the larger the angle between the vectors. For example, given two unit vectors, a dot product of 1 means the vectors are identical, and a dot product of -1 means they point in opposite directions.

## Cross Product

- The cross product is another vector operation, but unlike the dot product, it returns another vector instead of a scalar
- For the cross product the order of operands matters because if you change the order you change the direction of the vector

```c
t_tuple	cross_product(t_tuple *a, t_tuple *b)
{
	return (creating_tuple((a->y * b->z) - (a->z * b->y), \
			(a->z * b->x) - (a->x * b->z), \
			(a->x * b->y) - (a->y * b->x), 0));
}
```

- This returns a new vector that is perpendicular to both of the original vectors. 

![Screenshot from 2024-09-18 20-53-25](https://github.com/user-attachments/assets/85f29c11-ebf4-46b2-84e6-bb373d9b2c5f)

# Matrices
- A matrix is a grid of numbers that you can manipulate as a single unit.
- For this project, we used 4×4 matrices.

![Screenshot from 2024-09-19 17-28-43](https://github.com/user-attachments/assets/b4e44a11-2abe-4a33-a3c9-3934a20c5fa6)


```c
t_matrix	*mtx_create(t_minirt *data, int rows, int cols)
{
	t_matrix	*mtx_struct;
	int			curr_row;

	curr_row = 0;
	mtx_struct = (t_matrix *)ft_calloc(sizeof(t_matrix), 1);
	if (!mtx_struct)
		clean_matrix(data, mtx_struct, errno);
	mtx_struct->rows = rows;
	mtx_struct->cols = cols;
	mtx_struct->mtx = (float **)ft_calloc(sizeof(float *), rows);
	if (!mtx_struct->mtx)
		clean_matrix(data, mtx_struct, errno);
	while (curr_row < rows)
	{
		mtx_struct->mtx[curr_row] = (float *)ft_calloc(sizeof(float), cols);
		if (!mtx_struct->mtx[curr_row])
			clean_matrix(data, mtx_struct, errno);
		curr_row++;
	}
	return (mtx_struct);
}
```

## Transformations

- Is with matrices that we'll be able to do transformations in our objects.
- The transformations we'll use are:
	- *Translation.
	- *Scaling.
	- *Rotation.

### Is by multiplying matrices that we'll be able to apply transformations

- The way we multiply matrices is:
	- for each element of the resultant matrix, we add the products of the multiplication of each pair from the first matrix row, and the second matrix collum.
 
![Screenshot from 2024-09-19 17-45-20](https://github.com/user-attachments/assets/02a00ea6-d19a-4bf5-a516-f41e691cd0d8)



```c
t_matrix	*mtx_multiply(t_minirt *mrt, t_matrix *mtx_a, t_matrix *mtx_b)
{
	t_matrix	*mtx_res;
	int			row;
	int			col;

	if (!mtx_size_compare(mtx_a, mtx_b))
		return (NULL);
	mtx_res = mtx_create(mrt, mtx_a->rows, mtx_a->cols);
	row = -1;
	while (++row < mtx_res->rows)
	{
		col = -1;
		while (++col < mtx_res->cols)
			mtx_res->mtx[row][col] = mult_mtx_row_col(mtx_a, mtx_b, row, col);
	}
	clean_matrix(mrt, mtx_b, 0);
	clean_matrix(mrt, mtx_a, 0);
	return (mtx_res);
}
```


- We are also able to multiply matrices with tuples to produce another tuple.
- We treat the tuple as a 1 column and 4 row matrix.

![Screenshot from 2024-09-19 17-50-37](https://github.com/user-attachments/assets/f0687a75-df3b-4c1f-ac66-86f0e42266a9)

	
	
```c
t_tuple	mtx_mult_tuple(t_matrix *mtx_a, t_tuple *tup)
{
	t_tuple	tup_res;
	float	*ptr_res;
	int		i;

	ptr_res = (float *)&tup_res;
	i = -1;
	while (++i < mtx_a->rows)
		ptr_res[i] = mult_mtx_row_tuple(mtx_a, tup, i);
	return (tup_res);
}
```

## Identity Matrix

- Every shape will have a transformation matrix, and the default without any transformation is the identity matrix.
- If you multiply any matrix by the identity matrix, you'll get the matrix itself.

![Screenshot from 2024-09-19 17-57-06](https://github.com/user-attachments/assets/e346a73d-df63-486e-9256-1701f4f37a58)


```c
void	fill_idnty_mtx(t_matrix *mtx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		while (++j < mtx->cols)
		{
			if (i == j)
				mtx->mtx[i][j] = 1;
		}
	}
}
```

## Transposing Matrices

- The matrix transpose will be used when normal vectors, between object space and world space.

	![Screenshot from 2024-09-19 18-04-38](https://github.com/user-attachments/assets/a0aa70b5-b4d4-4adb-ae1a-ccc216e124e0)


- The transpose of the identity matrix always gives you the identity matrix.

```c
t_matrix	*mtx_transpose(t_minirt *mrt, t_matrix *mtx)
{
	t_matrix	*mtx_res;
	int			i;
	int			j;
	int			k;

	mtx_res = mtx_create(mrt, mtx->rows, mtx->cols);
	if (!mtx_res)
		clean_matrix(mrt, mtx_res, errno);
	i = -1;
	while (++i < mtx->rows)
	{
		j = -1;
		while (++j < mtx->cols)
			mtx_res->mtx[i][j] = mtx->mtx[j][i];
	}
	return (mtx_res);
}
```

## Inverting matrix

- If you multiply some matrix A by another matrix B, producing C, you can multiply C by the inverse of B to get A again.
- Well employ a method known as cofactor expansion.

### Determinants
- The determinant is a number that is derived from the elements of a matrix.
- If the determinant is zero, then the corresponding system of equations has no solution.

![Screenshot from 2024-09-19 18-30-03](https://github.com/user-attachments/assets/7aebb03b-4afd-4f57-9d3b-338530a111ce)

![Screenshot from 2024-09-19 18-30-39](https://github.com/user-attachments/assets/eb89835d-af01-4da6-a513-ae49b908b3ef)


### Submatrices
- A submatrix is what is left when you delete a single row and column from a matrix.
- The submatrix of a 4x4 matrix is 3x3, and the submatrix of a 3x3 matrix is 2x2, and we know how to find the determinant of 2x2 matrices. 

![Screenshot from 2024-09-19 18-36-44](https://github.com/user-attachments/assets/4ea19806-4e92-47b2-9a9b-0adf362d8d7d)


```c
t_matrix	*submatrix(t_minirt *mrt, t_matrix *mtx, int excl_row, int excl_col)
{
	t_matrix	*sub_mtx_res;

	if (excl_row >= mtx->rows || excl_col >= mtx->cols)
		return (NULL);
	sub_mtx_res = mtx_create(mrt, mtx->rows - 1, mtx->cols - 1);
	if (!sub_mtx_res)
		clean_matrix(mrt, sub_mtx_res, errno);
	copy_val_to_submtx(mtx, sub_mtx_res, excl_row, excl_col);
	return (sub_mtx_res);
}
```

### Minors

- The minor is the determinant of the submatrix at (i, j).

![Screenshot from 2024-09-19 18-44-34](https://github.com/user-attachments/assets/af8fc461-1621-4c70-94a5-51b1c73667f3)

```c
float	minor(t_minirt *mrt, t_matrix *mtx, int row, int col)
{
	t_matrix	*submtx;
	float		determ;

	submtx = submatrix(mrt, mtx, row, col);
	determ = determinant(mrt, submtx);
	if (submtx)
		clean_matrix(mrt, submtx, 0);
	return (determ);
}
```

### Cofactors

- Cofactors minors that have (possibly) had their sign changed.
- first well compute the minor at the given row and column. Then well consider that row and column to determine whether or not to negate the result.

![Screenshot from 2024-09-19 18-48-17](https://github.com/user-attachments/assets/75c611fc-850f-4d9f-b5b6-0cfd029fe5a3)

- If the row and column identify a spot with a +, then the minor’s sign doesn’t change. If the row and column identify a spot with a -, then you negate the minor.

```c
float	cofactor(t_minirt *mrt, t_matrix *mtx, int row, int col)
{
	if ((row + col) % 2 == 0)
		return (minor(mrt, mtx, row, col));
	else
		return (minor(mrt, mtx, row, col) * -1);
}
```

### Determinants of Larger Matrices

- Finding the determinant of matrices larger than 2x2 works recursively.

![Screenshot from 2024-09-19 18-55-56](https://github.com/user-attachments/assets/0975132d-1c0b-4d92-912f-2f5c68526aeb)

	
- To find the determinant, look at any one of the rows or columns. It doesn’t matter which, so let’s just choose the first row.

![Screenshot from 2024-09-19 18-56-18](https://github.com/user-attachments/assets/518373f3-fcdd-4b01-827d-a48bff4b9f30)

	
- Then, for each of those elements, you’ll multiply the element by its cofactor, and add the products together.

![Screenshot from 2024-09-19 18-56-42](https://github.com/user-attachments/assets/636d7763-4e42-43fd-bede-e3492365c17c)


```c
float	determinant(t_minirt *mrt, t_matrix *mtx)
{
	float	determ;
	int		i;
	int		col;

	(void)mrt;
	determ = 0;
	i = -1;
	if (mtx->rows == 2 && mtx->cols == 2)
		return ((mtx->mtx[0][0] * mtx->mtx[1][1]) -
				(mtx->mtx[0][1] * mtx->mtx[1][0]));
	else
	{
		col = -1;
		while (++col < mtx->cols)
			determ += mtx->mtx[0][col] * cofactor(mrt, mtx, 0, col);
	}
	return (determ);
}
```

### Implementing Inversion
- Not every matrix is invertible. If the determinant is ever 0, the matrix is not invertible. Anything else is okay.

	- We start the algorithm with the construction of a matrix of cofactors.
	- Then we transpose the cofactor matrix.
	- Finally, divide each of the resulting elements by the determinant of the original matrix.
	
![Screenshot from 2024-09-19 19-07-14](https://github.com/user-attachments/assets/9808121e-47b8-447d-b4b0-e667a8b67904)
![Screenshot from 2024-09-19 19-07-46](https://github.com/user-attachments/assets/576dd030-5376-4f64-bc9a-548fde0d3048)
![Screenshot from 2024-09-19 19-08-02](https://github.com/user-attachments/assets/74ffb57e-241f-4af1-a7f7-a5f44961cc59)


```c
t_matrix	*mtx_inverse(t_minirt *mrt, t_matrix *mtx)
{
	t_matrix	*mtx_res;
	t_matrix	*mtx_trans;
	float		determ;
	int			row;
	int			col;

	determ = determinant(mrt, mtx);
	if (compare_float(determ, 0))
		return (NULL);
	mtx_res = mtx_create(mrt, mtx->rows, mtx->cols);
	if (!mtx_res)
		clean_matrix(mrt, mtx_res, errno);
	row = -1;
	while (++row < mtx->rows)
	{
		col = -1;
		while (++col < mtx->cols)
			mtx_res->mtx[row][col] = cofactor(mrt, mtx, row, col) / determ;
	}
	mtx_trans = mtx_transpose(mrt, mtx_res);
	clean_matrix(mrt, mtx_res, 0);
	return (mtx_trans);
}
```

- Calculating the inverse of a matrix is very computationally intense, is more efficient to do it before the render.

# Matrices Transformations

- With transformation matrices will be able to move and deform objects.
- The below functions take the identity matrix as a parameter.

## Translation

- Translation is a transformation that moves a point by adding to it.
 
![Screenshot from 2024-09-20 16-53-51](https://github.com/user-attachments/assets/1bb0b7ba-47a5-4a26-86f7-e46bf321ed92)


```c
void	mtx_translation(t_matrix *mtx, t_tuple *tup_transl)
{
	int			row;
	float		*tup_arr;

	tup_arr = (float *)tup_transl;
	row = -1;
	while (++row < 3)
		mtx->mtx[row][3] = tup_arr[row];
}
```
## Scaling
- scaling is a transformation that moves a point by multiplication.
 
	![Screenshot from 2024-09-20 16-57-55](https://github.com/user-attachments/assets/4c8d299c-732e-4431-bee8-dce308621e8d)


```c
void	mtx_scaling(t_matrix *mtx, t_tuple *tup_scale)
{
	int			row;
	int			col;
	float		*tup_arr;

	tup_arr = (float *)tup_scale;
	row = -1;
	while (++row < 3)
	{
		col = -1;
		while (++col < 3)
		{
			if (row == col)
				mtx->mtx[row][col] = tup_arr[row];
		}
	}
}
```

## Rotation
- Multiplying a tuple by a rotation matrix will rotate that tuple around an axis.
- The rotation function will take as a parameter the angle in radians.

### Rotating around the x axis

![Screenshot from 2024-09-20 17-02-28](https://github.com/user-attachments/assets/ab1cd28b-6edf-4cac-8e2d-5dd70fbed3ed)


```c
void	mtx_rotation_x(t_matrix *mtx, float rot_deg)
{
	mtx->mtx[1][1] = cosf(rot_deg);
	mtx->mtx[1][2] = sinf(rot_deg) * -1;
	mtx->mtx[2][1] = sinf(rot_deg);
	mtx->mtx[2][2] = cosf(rot_deg);
}
```

### Rotating around the y axis

![Screenshot from 2024-09-20 17-05-26](https://github.com/user-attachments/assets/f71dea4e-961f-4c1e-9b9b-015e3eeed218)


```c
void	mtx_rotation_y(t_matrix *mtx, float rot_deg)
{
	mtx->mtx[0][0] = cosf(rot_deg);
	mtx->mtx[0][2] = sinf(rot_deg);
	mtx->mtx[2][0] = sinf(rot_deg) * -1;
	mtx->mtx[2][2] = cosf(rot_deg);
}
```

### Rotating around the z axis

![Screenshot from 2024-09-20 17-06-45](https://github.com/user-attachments/assets/3ad203eb-53a3-410a-b9a6-8e7e4663abdb)

	
```c
void	mtx_rotation_z(t_matrix *mtx, float rot_deg)
{
	mtx->mtx[0][0] = cosf(rot_deg);
	mtx->mtx[0][1] = sinf(rot_deg) * -1;
	mtx->mtx[1][0] = sinf(rot_deg);
	mtx->mtx[1][1] = cosf(rot_deg);
}
```

# Chaining Transformations

- We can perform multiple transformations by multiplying the above matrices.
- Note that the order of the multiplications is important! Matrix multiplication is associative, but not commutative.
- if you want a single matrix that rotates, and then scales, and then translates, you can multiply the translation matrix by the scaling matrix, and then by the rotation matrix. That is to say, you must concatenate the transformations in reverse order to have them applied in the order you want!

```c
t_matrix	*mtx_multiply(t_minirt *mrt, t_matrix *mtx_a, t_matrix *mtx_b)
{
	t_matrix	*mtx_res;
	int			row;
	int			col;

	if (!mtx_size_compare(mtx_a, mtx_b))
		return (NULL);
	mtx_res = mtx_create(mrt, mtx_a->rows, mtx_a->cols);
	row = -1;
	while (++row < mtx_res->rows)
	{
		col = -1;
		while (++col < mtx_res->cols)
			mtx_res->mtx[row][col] = mult_mtx_row_col(mtx_a, mtx_b, row, col);
	}
	clean_matrix(mrt, mtx_b, 0);
	clean_matrix(mrt, mtx_a, 0);
	return (mtx_res);
}
```


# Ray Casting

- Ray casting is the process of creating a ray, or line, and finding the intersections of that ray with the objects in a scene
- Each ray will have a starting point called the origin, and a vector called the direction which says where it points.

```c
typedef struct s_ray
{
	t_point			origin;
	t_vector		direction;
}	t_ray;
```

- With the origin (O) and direction (D), we can find any point (P) that lies long the ray, t units.
	- *P = O + Dt*

```c
t_point	position(t_ray *ray, float t)
{
	t_point	point;

	point = mult_tuple_scalar(&ray->direction, t);
	point = sum_tuples(&point, &ray->origin);
	return (point);
}
```

# Ray-Sphere Intersections

- when casting a ray, there are three possible different scenarios:
	- the ray misses the sphere and has 0 intersections.
	- the ray hits a tangent and only has one intersection.
	- the hits two different points in the sphere.

- Assuming the sphere is centered at the world origin (0, 0, 0) with radii of 1.
- For any point (P), if the point minus the sphere center (C) is equal to the radius of the sphere (1), then the point belongs to the sphere.
	- $P - C = 1$

- To find if a ray intersects the sphere, we check if the ray has any possible t, being P a point in the ray:
	- $(O + Dt) - C = 1$

- $(O + Dt)^2 - C^2 = 1^2 =>$
- $O^2 + 2ODt + (Dt)^2 - C^2 = 1 =>$
- $O^2 + 2ODt + D^2 * t^2 - C^2 - 1 = 0 =>$
- $2ODt + D^2 * t^2 + O^2 - C^2 - 1 = 0$

- $O - C$ is a vector from the ray origin and the sphere center, let's call W.

- $2ODt + D^2 * t^2 + W^2 - 1 = 0$ =>
- $D^2 * t^2 + 2ODt + W^2 - 1 = 0$

- What we have left is a quadratic equation, and we can solve it in function of t:

	![Screenshot from 2024-09-20 18-08-06](https://github.com/user-attachments/assets/8a2e90e5-723e-4281-a921-a3d617e13ffb)


- $a = D^2$
- $b = 2OD$
- $c = W^2 - 1$

- a = the dot product of the ray direction with the ray direction
- b = 2 * the dot product of the ray direction with the ray origin
- c = the dot product of w with w minus 1.

- First, we need to solve what's inside the square root, to see if the equation has a solution.
	- if we get a negative value, the ray misses the sphere.
	- if we get zero than we will only have one solution, and the ray hits a tangent.
	- if we get a value bigger than zero, the ray intercepts the sphere in two points.

```c
int8_t	ray_sphere_intersect(t_ray *ray, float *t)
{
	float	a;
	float	b;
	float	c;
	t_tuple	sphere_to_ray;
	float	discriminant;

	if (!ray || !t)
		return (0);
	sphere_to_ray = subtrac_tuples(&ray->origin, &(t_point){0, 0, 0, 1});
	a = dot_product(&ray->direction, &ray->direction);
	b = 2 * dot_product(&ray->direction, &ray->origin);
	c = dot_product(&sphere_to_ray, &sphere_to_ray) - 1;
 	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t[0] = (-b - sqrtf(discriminant)) / (2 * a);
	t[1] = (-b + sqrtf(discriminant)) / (2 * a);
	if (t[0] == t[1])
		return (1);
	return (2);
}
```
# Plane

- A plane is a perfectly flat surface that extends infinitely in two dimensions, in our case, the plane will extend in both x and z dimensions, passing through the origin. Using the transformation matrix will be able to rotate and translate the plane in any orientation we like.

- The normal vector is the same in every point of the plane, (0,1,0).

- If the ray is parallel to the plane there will be no intersections.
- Also no intersection if the ray is coplanar with the plane, which is to say that the ray’s origin is on the plane, and the ray’s direction is parallel to the plane.

```c
int8_t	ray_plane_intersect(t_ray *ray, float *t)
{
	if (fabs(ray->direction.y) < EPSILON)
		return (0);
	t[0] = -ray->origin.y / ray->direction.y;
	t[1] = -ray->origin.y / ray->direction.y;
	return (1);
}
```

# Cylinder

- At first, we assume the cylinder goes extends infinitely in the y direction, and have a radius of 1.

- We can check if the ray intersects the cylinder by joining the Ray formula $(O + Dt)$ with the circle formula $(x^2 + z^2 = 1)$;

- $(Ox + Dxt)^2 + (Oz + Dzt)^2 = 1$
- $Ox^2 + 2OxDxt + Dxt^2 + Oz^2 + 2OzDzt + Dzt^2 = 1$
- $Dxt^2 + Dzt^2 + 2OxDxt + 2OzDzt + Ox^2 + Oz^2 = 1$
- $t^2(Dx^2 + Dz^2) + t(OxDxt + OzDzt) + Ox^2 + Oz^2 - 1 = 0$

- Again just like the circle we can use the quadratic equation to solve in function of t:
	- $a = Dx^2 + Dz^2$
	- $b = 2OxDxt + 2OzDzt$
	- $c = Ox^2 + Oz^2 - 1$

```c
int8_t	ray_cylinder_intersect(t_ray *ray, float *t, t_shape *obj)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	bool	count[2];

	a = (ray->direction.x * ray->direction.x) + (ray->direction.z
			* ray->direction.z);
	if (fabs(a) < EPSILON)
		return (0);
	b = (2 * ray->origin.x * ray->direction.x) + (2 * ray->origin.z
			* ray->direction.z);
	c = (ray->origin.x * ray->origin.x) + (ray->origin.z
			* ray->origin.z) - 1;
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	if (t[0] > t[1])
		swap(t);
	count[0] = check_cy_range(ray, t[0], obj);
	count[1] = check_cy_range(ray, t[1], obj);
	return (intercections_count(count, t));
}
```

- before checking the intersections we cap the cylinder in a range, set in the object materials
- Then in the check_cy_range we check if the intersection point is between that range

```c
bool	check_cy_range(t_ray *ray, float t, t_shape *obj)
{
	float	y;
	float	cap_t;

	y = ray->origin.y + (ray->direction.y * t);
	if (obj->material.min < y && y < obj->material.max)
		return (true);
	return (false);
}
```

- The intersections_count, will return how many points the ray hits.

```c
int8_t	intercections_count(bool *count, float *t)
{
	if (count[0] && count[1])
	{
		if (t[0] == t[1])
			return (1);
		else
			return (2);
	}
	else if (!count[0] && !count[1])
		return (0);
	else if (count[0])
	{
		t[1] = t[0];
		return (1);
	}
	else if (count[1])
	{
		t[0] = t[1];
		return (1);
	}
	return (0);
}
```

## Caped cylinders

- For the top and bottom of the cylinder we treated them like another object, planes. All we need to check is if it's within the y set in the t_material, and if it's within the radius of the circle.

```c
int8_t	ray_cap_inter(t_ray *ray, float *t, t_shape *obj)
{
	bool	count[2];

	if (obj->material.closed == false || fabs(ray->direction.y) < EPSILON)
		return (0);
	t[0] = (obj->material.min - ray->origin.y) / ray->direction.y;
	t[1] = (obj->material.max - ray->origin.y) / ray->direction.y;
	count[0] = check_cap(ray, t[0], obj, 1);
	count[1] = check_cap(ray, t[1], obj, 2);
	return (intercections_count(count, t));
}

bool	check_cap(t_ray *ray, float t, t_shape *obj, int8_t	order)
{
	float	x;
	float	z;

	x = ray->origin.x + (t * ray->direction.x);
	z = ray->origin.z + (t * ray->direction.z);
	return (((x * x) + (z * z)) <= 1);
}
```

# Cone
- The cone works just like the cylinder but the a, b, and c  are computed differently:
	- $a = d2x − d2y + d2z$
	- $b = 2ox dx − 2oy dy + 2oz dz$
	- $c = o2x − o2y + o2z$

```c
int8_t	ray_cone_intersect(t_ray *ray, float *t, t_shape *obj)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	bool	count[2];

	set_cone_intersect(&a, &b, &c, ray);
	if (a == 0 && b == 0)
		return (0);
	if (a == 0)
	{
		t[0] = -c / 2 * b;
		t[1] = -c / 2 * b;
		return (1);
	}
	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	if (t[0] > t[1])
		swap(t);
	count[0] = check_cy_range(ray, t[0], obj);
	count[1] = check_cy_range(ray, t[1], obj);
	return (intercections_count(count, t));
}

void	set_cone_intersect(float *a, float *b, float *c, t_ray *ray)
{
	*a = (ray->direction.x * ray->direction.x) - (ray->direction.y
			* ray->direction.y) + (ray->direction.z * ray->direction.z);
	*b = (2 * ray->origin.x * ray->direction.x) - (2 * ray->origin.y
			* ray->direction.y) + (2 * ray->origin.z * ray->direction.z);
	*c = (ray->origin.x * ray->origin.x) - (ray->origin.y
			* ray->origin.y) + (ray->origin.z * ray->origin.z);
}
```

- This algorithm will check for intersections on a double-napped cone.
- If both a and b are 0, then the ray misses the cone.
- When a is 0 and b isn't the ray is parallel to one of the cone halves.


![Screenshot from 2024-09-26 21-15-37](https://github.com/user-attachments/assets/c7ebc88e-980f-4abc-8c51-49a0774c2a75)

 
- This still means that the ray will intersect the other half, so we use the following formula to find the single point of intersection:
	- $t = -c / 2 * b$

- To check the cap for the cone we use the same logic as the cylinder, but the radius of the circle is not the same everywhere, and will change along the y coordinates.
```c
bool	check_cap(t_ray *ray, float t, t_shape *obj, int8_t	order)
{
	float	x;
	float	z;

	x = ray->origin.x + (t * ray->direction.x);
	z = ray->origin.z + (t * ray->direction.z);
	if (obj->type == CY)
		return (((x * x) + (z * z)) <= 1);
	else if (obj->type == CONE)
	{
		if (order == 1)
			return (((x * x) + (z * z)) <= fabs(obj->material.min \
				* obj->material.min));
		else if (order == 2)
			return (((x * x) + (z * z)) <= fabs(obj->material.max \
				* obj->material.max));
	}
	return (false);
}
```

# Shapes

- All shapes will be represented by the t_shape struct, which will be put into a linked list.

```c
typedef struct s_shape
{
	t_material			material;
	t_ray				trans_ray;
	t_matrix			*mtx_trans;
	t_matrix			*mtx_inver;
	t_point				center;
	t_angle				angle;
	enum e_id			type;
	float				amb_ratio;
	int					id;
	void				*next;
}	t_shape;

typedef t_shape	t_sphere;
typedef t_shape	t_plane;
typedef t_shape	t_cyl;
typedef	t_shape	t_cone;
```

- They will all have in common:
	- a material:
 ```c
typedef struct s_material
{
	t_pattern	pattern;
	t_color		color;
	t_color		color_sec;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
	float		reflective;
	float		min;
	float		max;
	bool		closed;
	bool		is_bump;
}	t_material;
```
	- The min, max, and closed values will be only used by the cone and cylinder.

- a transformation matrix, which will be set as the identity matrix, if the object doesn't have a transformation, and the inverse of that matrix.
- The transformed ray. The ray that multiplied by the inverse of the object transformation matrix.

# Tracking Intersections

- Every time a ray hits an object will add then to a list of intersections

```c
typedef struct s_intersections
{
	t_point					point;
	float					t[2];
	float					hit;
	t_shape					*obj;
	struct s_intersections	*next;
}	t_intersections;
```

- after check if the ray intersects with all the objects, we keep a reference to the intersection with the smallest positive hit value, being that the first point the ray hits in a object.

- The intersection's node keeps track of:
	- the t values the ray hits, if the ray only hits one point, t[0] will be equal to t[1];
	- the t value the ray hit first in hit;
	- the point of intersection;
	- a pointer to the object the ray intersects;


# Transforming Rays

- You can notice that the calculations for the ray intersections will always assume that the object is in the center of the world, point(0,0,0), and with radii of 1 in the case of the sphere.
- The way we move objects is not by moving the object itself but the ray.
- before we check the intersections, we first transform the ray by multiplying it by the object's inverse matrix.
- This will give us the correct location of the points of the objects.

```c
t_ray	ray_trasform(t_ray *ray, t_matrix *mtx)
{
	t_ray		new_ray;

	new_ray.origin = mtx_mult_tuple(mtx, &ray->origin);
	new_ray.direction = mtx_mult_tuple(mtx, &ray->direction);
	return (new_ray);
}
```

```c
void	intersections(t_minirt *data, t_ray *ray)
{
	t_shape	*obj;

	obj = data->world.objs;
	while (obj)
	{
		obj->trans_ray = ray_trasform(ray, obj->mtx_inver);
		ray_intersections(data, obj, &obj->trans_ray, ray);
		obj = obj->next;
	}
	first_hit(data);
}
```

# Representing Colors

We use the rgb representation to determine the color of the pixel.

- Each value will range from [0-1] being 0, completely absent of that color, and 1 the full value of that color.
- We will represent color as a tuple, and we will also need to be able to do tuple operations with them.

```c
typedef struct s_tuple
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
			float	w;
		};
		struct
		{
			float	r;
			float	g;
			float	b;
		};
	};
}	t_tuple;

typedef t_tuple	t_point;
typedef t_tuple	t_vector;
typedef t_tuple	t_color;
```

- We used union to make the code more readable, and more distinguishable when we are working with r,g,b colors or x,y,z coordinates.

# Point light

- Every call to point light will add a new light source to the world and will put it on a list of lights.

```c
void	point_light(t_point *pos, t_color *intensity, t_world *world)
{
	t_light	*light;

	if (world->light == NULL)
	{
		world->light = ft_calloc(sizeof(*world->light), 1);
		if (world->light == NULL)
			exit (errno);
		world->light->position = *pos;
		world->light->intensity = *intensity;
		world->light->next = NULL;
		return ;
	}
	light = ft_calloc(sizeof(*light), 1);
	if (light == NULL)
		exit(errno);
	light->position = *pos;
	light->intensity = *intensity;
	light->next = world->light;
	world->light = light;
}
```

# Light and Shading

- To simulate the reflection of light on a surface, we'll implement the Phong algorithm.

- For the algorithm, we need 4 vectors.

	- The eye vector. P (Points from the point of intersection), to the origin of the ray.
		- To find E, we negate the ray’s direction vector, turning it around to point back at its origin.
		
	- The light vector. Pointing from P to the origin of the light source.
		 - To find L, we subtract P from the position of the light source, giving us the vector pointing toward the light.

	- The surface normal, a vector that is perpendicular to the surface at P.

	- The reflection vector, pointing in the direction that incoming light would bounce, or reflect.

# Normal

- First, we need to undo the transformations of the point, making it easier to calculate the normal.
- We achieve that by multiplying the point by the object inverse matrix.


![normal_at1](https://github.com/user-attachments/assets/7edb98d6-245a-4866-802c-acb912e95182)


- The reason we use the inverse matrix, instead of the object transformation matrix, is because the transformation matrix wont preserve the correct y component, changing the size of the vector.
- So we multiply the normal by the inverse transpose matrix instead.

```c
t_vector	normal_at(t_shape *obj, t_point *point, t_minirt *data)
{
	t_point		local_point;
	t_vector	local_normal;
	t_vector	world_normal;
	t_matrix	*transpose;

	local_point = mtx_mult_tuple(obj->mtx_inver, point);
	local_normal = local_normal_at(obj, &local_point);
	transpose = mtx_transpose(data, obj->mtx_inver);
	world_normal = mtx_mult_tuple(transpose, &local_normal);
	world_normal.w = 0;
	clean_matrix(data, transpose, 0);
	return (normalize(&world_normal));
```

## Normal_local_at

- after undoing the transformations of the point, we will calculate the normal for each object.

### Sphere
- We subtract the point by the center, giving us the normalized normal of the tangent plane of that point.


	![Screenshot from 2024-08-07 13-02-26](https://github.com/user-attachments/assets/c22932ba-d184-471b-b88e-66f377094c87)

	
```c
	if (obj->type == SP)
		local_normal = subtrac_tuples(local_point, &(t_point){0, 0, 0, 1});

```
### Plane
- the local normal at a plane is always perpendicular to the y axis.
```c
	else if (obj->type == PL)
		local_normal = (t_vector){0, 1, 0, 0};
```

### Cone
- The cone is similar to the cylinder but we need to find the y component of the vector.

 	![Screenshot from 2024-09-25 17-03-30](https://github.com/user-attachments/assets/d75ca7bb-8236-458d-afc8-ed8702922a12)

	
```c
t_vector	normal_at_cone(t_point *point, t_shape *obj)
{
	float		dist;
	float		y;
	t_vector	normal;

	dist = (point->x * point->x) + (point->z * point->z);
	if (dist < obj->material.max * obj->material.max \
		&& point->y >= obj->material.max - EPSILON)
		return ((t_vector){0, 1, 0, 0});
	else if (dist < obj->material.min * obj->material.min \
		&& point->y <= obj->material.min + EPSILON)
		return ((t_vector){0, -1, 0, 0});
	y = sqrtf(dist);
	if (y > EPSILON)
		y = -y;
	normal = (t_vector){point->x, y, point->z, 0};
	return (normal);
}
```

## reflection vector

- This is the reflected vector around the normal.
- the vector coming in will have the same angle as the vector going out.

```c
t_vector	reflect(t_vector *in, t_vector *normal)
{
	t_tuple		vect;

	vect = mult_tuple_scalar(normal, 2);
	vect = mult_tuple_scalar(&vect, dot_product(in, normal));
	vect = subtrac_tuples(in, &vect);
	return (vect);
}
```


# The Phong Reflection Model

- To simulate the reflection of light we implement the Phong reflection model.
- This algorithm simulates the interaction between 3 types of lights.
	- **Ambient:** Is the background lightning, this value will be a constant.
	- **Diffuse:** Is the light reflected from the material surface, this only depends on the angle between the light source and the surface normal.
	- **Specular:** Is the reflection of the light source itself, the bright spot on a curved surface, It depends only on the angle between the reflection vector and the eye vector and is controlled by a parameter that we call shininess. The higher the shininess, the smaller and tighter the specular highlight.
	
	![Screenshot from 2024-09-25 17-46-31](https://github.com/user-attachments/assets/a7afbe86-88c5-4aca-9feb-4a9f4092f3a7)


```c
typedef struct s_phong
{
	t_color			ambient;
	t_color			diffuse;
	t_color			spec;
}	t_phong;
```

```c
t_color	lighting(t_comps *comps, t_light *light, t_world *world)
{
	t_color			color;
	t_phong			phong;
	float			light_normal_dot;

	color = color_multiply(&comps->obj->material.color, &world->ambient_light);
	comps->lightv = subtrac_tuples(&light->position, &comps->point);
	comps->lightv = normalize(&comps->lightv);
	phong.ambient = mult_tuple_scalar(&color, comps->obj->material.ambient);
	light_normal_dot = dot_product(&comps->lightv, &comps->normalv);
	if (light_normal_dot < 0 || comps->is_shadown)
		light_is_behind_obj(&phong.diffuse, &phong.spec);
	else
	{
		color = color_multiply(&color, &light->intensity);
		phong.diffuse = mult_tuple_scalar(&color,
				comps->obj->material.diffuse * light_normal_dot);
		bump(&phong, comps->obj);
		comps->reflectv = negating_tuple(&comps->lightv);
		comps->reflectv = reflect(&comps->reflectv, &comps->normalv);
		get_specular(comps, light, &phong);
	}
	return (add_color3(&phong.ambient, &phong.diffuse, &phong.spec));
}

void	light_is_behind_obj(t_color *diffuse, t_color *specular)
{
	*diffuse = (t_color){0, 0, 0, 999999};
	*specular = (t_color){0, 0, 0, 999999};
}

void	get_specular(t_comps *comps, t_light *light, t_phong *phong)
{
	float			ref_dot_eye;

	ref_dot_eye = dot_product(&comps->reflectv, &comps->eyev);
	if (ref_dot_eye <= 0)
		phong->spec = (t_color){0, 0, 0, 999999};
	else
		phong->spec = specular(&comps->obj->material, light, ref_dot_eye);
}
```


# Shadows

- If the point is in shadow, in the lightning function, we will ignore the specular and diffuse values and use only the ambient to color the point.
- We will cast a shadow ray, going through the point of intersection to the light source, and if that ray intersects an object, then that point is on shadow.

```c
bool	is_shadowed(t_world *w, t_light *light, t_point *p)
{
	t_minirt	data;
	t_vector	v;
	float		distance;
	t_ray		ray;

	ft_memset(&data, 0, sizeof(data));
	data.world = *w;
	v = subtrac_tuples(&light->position, p);
	distance = magnitude(&v);
	ray.direction = normalize(&v);
	ray.origin = *p;
	intersections(&data, &ray);
	if (data.first_hit && distance > data.first_hit->hit)
	{
		clear_ray_inter(&data);
		return (true);
	}
	clear_ray_inter(&data);
	return (false);
}
```

1. We Measure the distance from point to the light source by subtracting point from the light position and taking the magnitude of the resulting vector. Call this distance.

2. We Create a ray from point toward the light source by normalizing the vector from step 1.

3. We intersect the world with that ray.

4. We check to see if there was a hit, and if so, whether t is less than distance. If so, the hit lies between the point and the light source, and the point is in shadow.




# Camera

- The camera will represent our eye.
- The camera will have a transformation matrix, that will pretty much orientate the world relative to our eye.

# View transformation

- The view_transformation function will return the camera transformation matrix and take 3 parameters.
	- **From:** The point of origin of the camera.
	- **To:** To were the camera is pointing to.
	- **Up:** The vector indicating which direction is up.

```c
typedef struct s_view
{
	t_vector	forward;
	t_vector	upn;
	t_vector	left;
	t_vector	true_uper;
}	t_view;
```

```c
t_matrix	*view_transformation(t_point *from, t_point *to, t_vector *up)
{
	t_view		view;
	t_matrix	*orientation;
	t_matrix	*trans;
	t_matrix	*ret;

	view.forward = subtrac_tuples(to, from);
	view.forward = normalize(&view.forward);
	view.upn = normalize(up);
	view.left = cross_product(&view.forward, &view.upn);
	view.true_uper = cross_product(&view.left, &view.forward);
	orientation = view_orientation(&view.left, &view.true_uper, &view.forward);
	trans = mtx_create(NULL, 4, 4);
	fill_idnty_mtx(trans);
	mtx_translation(trans, &(t_point){-from->x, -from->y, -from->z, 1});
	ret = mtx_multiply(NULL, orientation, trans);
	return (ret);
}
```

```c
t_matrix	*view_orientation(t_vector *left, t_vector *up, t_vector *forward)
{
	t_matrix	*orientation;

	orientation = mtx_create(NULL, 4, 4);
	orientation->mtx[0][0] = left->x;
	orientation->mtx[0][1] = left->y;
	orientation->mtx[0][2] = left->z;
	orientation->mtx[1][0] = up->x;
	orientation->mtx[1][1] = up->y;
	orientation->mtx[1][2] = up->z;
	orientation->mtx[2][0] = -forward->x;
	orientation->mtx[2][1] = -forward->y;
	orientation->mtx[2][2] = -forward->z;
	orientation->mtx[3][3] = 1;
	return (orientation);
}
```

1. We compute the forward vector by subtracting from, from to, and normalizing the result.

2. We compute the left vector by taking the cross product of forward and the normalized up vector.

3. We compute the true_up vector by taking the cross product of left and forward. This allows the original up vector to be only approximately up, which makes framing scenes a lot easier.

4. With these left, true_up, and forward vectors, we can now construct a matrix that represents the orientation transformation:

	![[Pasted image 20240926174653.png]]

5. The last step is to append a translation to that transformation to move the scene into place before orienting it. Multiplying orientation by translation(-from.x, -from.y, -from.z).


# Constructing the camera

```c
typedef struct s_camera
{
	t_matrix	*trans;
	t_matrix	*inver;
	t_point		center;
	t_point		direct_center;
	t_vector	up;
	int			hsize;
	int			vsize;
	float		half_width;
	float		half_height;
	float		pixel_size;
	float		fov;
}	t_camera;
```

- The camera is defined by the following four attributes:
	- **hsize:** is the horizontal size (in pixels) of the canvas that the picture will be rendered to.
	- **vsize:** is the canvas’s vertical size (in pixels). 
	- **field_of_view (fov):** is an angle that describes how much the camera can see.
	- **transform (trans):** is a matrix describing how the world should be oriented relative to the camera. We achieve this with view transformation.

```c
t_camera	camera_construct(size_t hsize, size_t vsize, float fov)
{
	t_camera	camera;
	float		half_view;
	float		aspect;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.fov = fov;
	half_view = tan(fov / 2);
	aspect = (float)hsize / (float)vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / hsize;
	return (camera);
```

# Ray for pixel

- The ray_for_pixel() function computes the world coordinates at the center of the given pixel, and then constructs a ray that passes through that point.
- It takes as a parameter the camera, px (the x position of the pixel), and py (the y position of the pixel).

```c
t_ray	ray_for_pixel(t_camera *camera, size_t px, size_t py)
{
	t_ray	ray;
	t_point	pixel;
	t_rfp	rpf;

	rpf.xoffset = (px + 0.5) * camera->pixel_size;
	rpf.yoffset = (py + 0.5) * camera->pixel_size;
	rpf.w_x = camera->half_width - rpf.xoffset;
	rpf.w_y = camera->half_height - rpf.yoffset;
	pixel = mtx_mult_tuple(camera->inver, &(t_point){rpf.w_x, rpf.w_y, -1, 1});
	ray.origin = mtx_mult_tuple(camera->inver, &(t_point){0, 0, 0, 1});
	ray.direction = subtrac_tuples(&pixel, &ray.origin);
	ray.direction = normalize(&ray.direction);
	return (ray);
}
```

# Render

- The render function will iterate, through the pixels of the scream.
- With the help of the functions ray_for_pixel(), and color_at(), will create the ray, and then compute the color of that pixel.
- Then write the pixel in the window using the minilibx API.

```c
void	render(t_minirt *data)
{
	t_color		color;
	t_ray		ray;
	int			x;
	int			y;

	y = -1;
	while (++y < data->camera.vsize - 1)
	{
		x = -1;
		while (++x < data->camera.hsize - 1)
		{
			ray = ray_for_pixel(&data->camera, x, y);
			color = color_at(data, &ray, 5);
			write_pixel(&data->canvas, x, y, &color);
		}
	}
	printf("RENDER\t\t[OK]\n");
	manage_interface(data);
}
```

# Reflection

- The reflection works by spawning an additional ray at the point of intersection and recursively following it to determine the color at that point.

```c
t_color	reflected_color(t_comps *comps, t_minirt *data, int8_t remaining)
{
	t_color	color;
	t_ray	reflected_ray;

	if (comps->obj->material.reflective == 0 || remaining == 0)
		return ((t_color){0, 0, 0, 999999});
	reflected_ray.origin = comps->over_point;
	reflected_ray.direction = comps->reflectv;
	color = color_at(data, &reflected_ray, remaining - 1);
	color = mult_tuple_scalar(&color, comps->obj->material.reflective);
	return (color);
}
```

- The remaining parameter, is do that we don't have an infinity recursion if we have two reflective objects pointing at each other.
- the reflective attribute in the object material, will determine how reflective is the object, being 0 non-reflective and 1 a perfect mirror.
- We'll add the color returning from this function to the color of the object intersected, to have the final color.


# Patterns

- If the object has a pattern, will change the default color of the object according to the point, and the pattern the object has.

- The possible patterns the objects can have are:
	- STR, stripe pattern;
	- PC, point color;
	- GR, gradient;
	- RNG, ring;
	- CHK, checkers.

```c
enum e_p
{
	STR = 0,
	PC = 1,
	GR = 2,
	RNG = 3,
	CHK = 4,
};
```

```c
void	set_pattern(t_intersections *inter, t_point *point)
{
	if (inter->obj->material.pattern.has)
	{
		inter->obj->material.color = pattern_at(&inter->obj->material.pattern, \
			point, inter->obj, inter->obj->material.pattern.type);
	}
}
```

## Stripe pattern

- As the x coordinate changes, the pattern alternates between the two colors.
```c
t_color	stripe_at(t_pattern *patterns, t_point *point)
{
	t_color	c;

	if ((int)point->x % 2 == 0)
		c = patterns->a;
	else
		c = patterns->b;
	return (c);
}
```

## Gradient pattern

- A gradient pattern is like stripes, but instead of discrete steps from one color to the next, the function returns a blend of the two colors, linearly interpolating from one to the other as the x coordinate changes.

```c
t_color	gradient(t_pattern *pattern, t_point *point)
{
	t_color	distance;
	float	fraction;
	t_color	ret;

	distance = subtrac_tuples(&pattern->a, &pattern->b);
	fraction = point->x - floor(point->x);
	ret = mult_tuple_scalar(&distance, fraction);
	return (sum_tuples(&pattern->a, &ret));
}
```

## Ring pattern

- A ring pattern depends on two dimensions, x, and z, to decide which color to return. It works similarly to stripes, but instead of testing the distance of the point in just x, it tests the distance of the point in both x and z.

```c
t_color	ring_patt(t_pattern *pattern, t_point *point)
{
	t_color	c;

	if ((int)sqrtf((point->x * point->x) + (point->z * point->z)) % 2 == 0)
		c = pattern->a;
	else
		c = pattern->b;
	return (c);
}
```

## Checkers pattern

- The function of this pattern is very much like that of stripes, but instead of relying on a single dimension, it relies on the sum of all three dimensions, x, y, and z.
```c
t_color	checker_patt(t_pattern *pattern, t_point *point)
{
	t_color	c;

	if ((int)(floor(point->x) + floor(point->y) + floor(point->z)) % 2 == 0)
		c = pattern->a;
	else
		c = pattern->b;
	return (c);
}
```

# Credits

This project would not be possible without the guidelines of the book:

**The Ray Tracer Challenger - by Jamis Buck**

 [Jamis Buck - The Ray Tracer Challenge](https://github.com/user-attachments/files/16740679/Jamis.Buck.-.The.Ray.Tracer.Challenge-Pragmatic.Bookshelf.2019.pdf) | `PDF`
 
 We strongly recommend to anyone who wants to build this project from scratch, that deep dive on the reading of this book to understand the concepts, there is a lot of valuable information there.

## Contributing

Contributions to the project are welcome! If you have any ideas, improvements, or bug fixes, please submit them as issues or pull requests to this repository.

<div align="center">
  <h1><b>Welcome to my new brave world!</b></h1> 
  <h2><b>00100010 01000010 01100101 00100000 01110111 01100001 01110100 01100101 01110010 00100000 01101101 01111001 00100000 01100110 01110010 01101001 01100101 01101110 01100100 00100010 00100000 01000010 01110010 01110101 01100011 01100101 00100000 01001100 01100101 01100101</b></h2>
</div>

<!---
SMALL ICONS
--->
<div style="text-align: center;">
  <a href='https://www.linkedin.com/in/uatilla' target="_blank" style="display: inline-block; margin: 0 10px;">
    <img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat&logo=Linkedin&logoColor=white&labelColor=0A66C2&color=0A66C2'/>
  </a>
  <a href='https://profile.intra.42.fr/users/uviana-a' target="_blank" style="display: inline-block; margin: 0 10px;">
    <img alt='42' src='https://img.shields.io/badge/Porto-100000?style=flat&logo=42&logoColor=white&labelColor=000000&color=000000'/>
  </a>
  <img src="https://komarev.com/ghpvc/?username=uatilla&label=Profile%20views&color=0e75b6&style=flat" alt="uatilla" style="display: inline-block; margin: 0 10px;" />
</div>


## About me

- 👋 I'm `Uatilla Viana Almeida`.
- 🌱 I'm currently studying Common Core at [**42 Porto**](https://www.42porto.com) after successfully completing the Piscine.
- 👀 I'm interested in `Bitcoin`, `Macroeconomy`, `Adventure` and `Sports` of all kinds.
- 🚀 Additionally, I have an interest in `Blockchain`, `Python`, `Data Analysis` and `Machine Learning`.
- 📫 You can reach me on [**LinkedIn**](https://www.linkedin.com/in/uatilla/).
- 🤔 Feeling amazing about how the blockchain technology will change our lives.
<div align="center">

## Skills
<p align="left">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=c,python,git,github,bash,linux,vim,vscode,sketchup,sql" />
  </a>
</p>

<p><img align="left" src="https://github-readme-stats.vercel.app/api/top-langs?username=uatilla&show_icons=true&locale=en&layout=compact" alt="uatilla" /></p>

<p>&nbsp;<img align="left" src="https://github-readme-stats.vercel.app/api?username=uatilla&show_icons=true&locale=en" alt="uatilla" /></p>

<p><img align="left" src="https://github-readme-streak-stats.herokuapp.com/?user=uatilla&" alt="uatilla" /></p>



