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

