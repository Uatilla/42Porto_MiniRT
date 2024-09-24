# 42Porto_Libft
This project is about coding a C library. It will contain a lot of general-purpose functions your programs will rely upon.
Libft is a custom library created as a part of the 42 curriculum. It contains a set of useful functions that can be used in various C projects. The purpose of this library is to provide an implementation of standard library functions, as well as additional functions that can be handy in everyday programming tasks.
For more detailed information, look at the [**subject of this project**](https://github.com/Uatilla/42Porto_Libft/blob/main/Libft_en.subject.pdf).

[![MasterHead](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExODI4MTEwMzllZjE2ODE4OGI1NDM3YTg5MTgxYzYyNzRiOWQyNDI2NCZlcD12MV9pbnRlcm5hbF9naWZzX2dpZklkJmN0PWc/fsXOS3oBboiYf6fSsY/giphy.gif)](https://www.linkedin.com/in/uatilla/)

## Getting Started

You need to download or clone this git repository.
`git clone git@github.com:Uatilla/42Porto_Libft.git`

The repository contains all functions source code, and the Makefile that can be used to compile.
In the repository's root directory runs on the terminal the following codes:

To build the library and link the **Mandatory** files: `make`
To build the library and link the **Bonus** files: `make bonus`

## How to use it

To compile your code you can do: `cc yourmaincode.c libft.a`

To clean the .o files: `make clean`
To clean all .o files and the libft.a: `make fclean`

To clean all .o files, the libft.a and build the library libft.a the Mandatory files .o: `make re`

## Functions

The library provides a wide range of functions that cover various everyday programming operations, such as:

## Mandatory part

### Memory manipulation

**ft_bzero()**: Writes zeroes to a byte string.

***ft_memcpy()**: Copies n bytes of data from a memory area (the data CAN'T overleap).

***ft_memset()**: Writes a byte to a byte string.

***ft_memmove()**: Copies n bytes of data from a memory area (the data CAN overleap).

***ft_memchr()**: Returns the position in the memory where the first occurrence of a character happened.

**ft_memcmp()**: Compares two memory areas and returns the difference between the first different character.

### String manipulation

***ft_calloc()**: Allocate some memory of size bytes and set it as 0.

***ft_strdup()**: Make some memory with malloc() and duplicates a string to there.

**ft_strncmp()**: Compares two strings and returns the difference between the first different character.

**ft_strlen()**: Measure the size of a string without the NULL character ('\0').

**ft_strlcpy()**: Copy a string src to a dest and guarantee the null terminator, return the size of src.

**ft_strlcat()**: Concatenate a string src to a dest and guarantee the null terminator, return the size of src + dest.

***ft_strchr()**: Returns the position in the memory that the first occurrence of a character happened."

***ft_strrchr()**: Returns the position in the memory that the last occurrence of a character happened."

***ft_strnstr()**: Returns the position of the first occurrence of a string, if it didn't find it returns NULL, if the little string isn't find it returns the big string. 

***ft_substr()**: Returns a pointer to a substring that has size len. 

***ft_strjoin()**: Concatenate two strings and returns a pointer to the new bigger string.

***ft_strtrim()**: Returns a pointer to a new string that has the characters of the set removed from the beginning and the end of the string.

** **ft_split()**: Returns a pointer to an array of strings that are obtained by splitting the string s using the character c as a delimiter.

***ft_strmapi()**: Applies the function f to each character of the string s to create a new string resulting from successive applications of f.

***ft_striteri()**: Applies the function f to each character of the string passed as argument, and passing its index as first argument. Each character is passed by address to f to be modified if necessary.

**ft_putchar_fd()**: Outputs the character c to the given file descriptor.

### Character classification

**ft_isalnum()**: Alphanumeric character test.

**ft_isalpha()**: Alphabetic character test.

**ft_isascii()**: Ascii character test.

**ft_isdigit()**: Decimal digit character test.

**ft_isprint()**: Printing character test (space character inclusive).

**ft_toupper()**: Changes one character to uppercase if it's lowercase else returns the character without changes.

**ft_tolower()**: Changes one character to lowercase if it's uppercase else returns the character without changes.


### String to integer conversion

**ft_atoi()**: Converts the initial portion of the string in int.

### File descriptor output

**ft_putchar_fd()**: Outputs a char to the given file descriptor.

**ft_putstr_fd()**: Outputs the string s to the given file descriptor.

**ft_putendl_fd()**: Outputs the string s to the given file descriptor, followed by a newline.

**ft_putnbr_fd()**: Outputs the integer n to the given file descriptor.

### Integer to string conversion
***ft_itoa()**: Returns a pointer to a new string that represents the integer received as an argument.

## Bonus part

### List creation and modification

***ft_lstnew()**: Allocates (with malloc(3)) and returns a new element.

***ft_lstadd_front()**: Adds the element ’new’ at the beginning of the list.

***ft_lstlast()**: Returns the last element of the list.

***ft_lstadd_back()**: Adds the element ’new’ at the end of the list.

### List deletion and memory management

***ft_lstdelone()**: Takes as a parameter an element and frees the memory

***ft_lstclear()**: Deletes and frees the given element and every successor

### List iteration and mapping

**ft_lstiter()**: Iterates the list ’lst’ and applies the function

***ft_lstsize()**: Counts the number of elements in a list.

***ft_lstmap()**: Iterates the list ’lst’ and applies the function returning a new list

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
- 👀 I'm interested in `Bitcoin`, `Games` and `Sports` of all kinds.
- 🚀 Additionally, I have an interest in `AI`, `Python`, `Data Analysis` and `Project Management`.
- 📫 You can reach me on [**LinkedIn**](https://www.linkedin.com/in/uatilla/).
- 🤔 Feeling amazing about how AI can help our society.

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
