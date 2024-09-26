This project was done by:

Jhonas Leal - https://github.com/Jburlama

Uatilla  Almeida - https://github.com/Uatilla

# Credits

We decided to put the credits at the beginning of the readme because this project would not be possible without the book:

**The Ray Tracer Challenger - by Jamis Buck**

 [Jamis Buck - The Ray Tracer Challenge](https://github.com/user-attachments/files/16740679/Jamis.Buck.-.The.Ray.Tracer.Challenge-Pragmatic.Bookshelf.2019.pdf) | `PDF`

# Technical overview
# Tuples

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
# Operations

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

- ==Calculating the inverse of a matrix is very computationally intense, is more efficient to do it before the render.

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
