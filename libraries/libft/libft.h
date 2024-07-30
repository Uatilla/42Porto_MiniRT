/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:07:18 by uviana-a          #+#    #+#             */
/*   Updated: 2024/06/03 14:59:04 by lebarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*__________________________________[HEADERS]________________________________*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

//PRINTF
int		ft_putstr(char *str);
int		ft_putchar(const char c);
int		ft_hex_base(unsigned long decimal_address, int flag);
int		ft_ubase(unsigned int number);
int		ft_printf(const char *str, ...);

//GNL

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strchr_mod(char *s, int c);
char	*ft_strjoin_mod(char *s1, char *s2); //libft
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *s); //libft
char	*ft_strtrim_mod(char *s1, char const *set);

//LIBFT
/*_________________________________[FUNCTIONS]_______________________________*/
/*-----------------------------*Mandatory Part I*----------------------------*/

//MEMORY MANIPULATION:****************************************************

//ft_bzero(): Writes zeroes to a byte string.
void	ft_bzero(void *s, size_t n);
//*ft_memcpy(): Copies n bytes of data from a memory area 
//(the data CAN'T overleap).
void	*ft_memcpy(void *dest, const void *src, size_t n);
//*ft_memset(): Writes a byte to a byte string.
void	*ft_memset(void *s, int c, size_t n);
//*ft_memmove(): Copies n bytes of data from 
//a memory area (the data CAN overleap).
void	*ft_memmove(void *dest, const void *src, size_t n);
//*ft_memchr(): Returns the position in the memory that
// the first occurrence of a character happened.
void	*ft_memchr(const void *s, int c, size_t n);
//ft_memcmp(): Compares two memory areas and returns the difference 
//between the first different character.
int		ft_memcmp(const void *s1, const void *s2, size_t n);

//STRING MANIPULATION:****************************************************

//*ft_calloc(): Alocate some memory of size bytes and sets as 0.
void	*ft_calloc(size_t nmemb, size_t size);
//*ft_strdup(): Make some memory with malloc() 
//and duplicates a string to there.
char	*ft_strdup(const char *s);
//ft_strncmp(): Compares two strings and returns the difference between 
//the first different character.
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//ft_strlen(): Measure the size of a string without 
//the NULL character ('\0').
size_t	ft_strlen(const char *s);
//ft_strlcpy(): Copy a string src to a dest and guarantee the null 
//terminator, return the size of src.
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//ft_strlcat(): Concatenate a string src to a dest and guarantee 
//the null terminator, return the size of src + dest.
size_t	ft_strlcat(char *dst, const char *src, size_t size);
//*ft_strchr(): Returns the position in the memory that the first 
//occurrence of a character happened."
char	*ft_strchr(const char *s, int c);
//*ft_strrchr(): Returns the position in the memory that the 
//last occurrence of a character happened."
char	*ft_strrchr(const char *s, int c);
//*ft_strnstr(): Returns the position of the first occurrence of a 
//string, if it didn't find it returns NULL, if the little 
//string isn't find it returns the big string. 
char	*ft_strnstr(const char *big, const char *little, size_t len);

//CHARACTER CLASSIFICATION:***********************************************

//ft_isalnum(): Alphanumeric character test.
int		ft_isalnum(int c);
//ft_isalpha(): Alphabetic character test.
int		ft_isalpha(int c);
//ft_isascii(): Ascii character test.
int		ft_isascii(int c);
//ft_isdigit(): Decimal digit character test.
int		ft_isdigit(int c);
//ft_isprint(): Printing character test (space character inclusive).
int		ft_isprint(int c);
//ft_toupper(): Changes one character to uppercase if it's 
//lowercase else returns the character without changes.
int		ft_toupper(int c);
//ft_tolower(): Changes one character to lowercase if it's 
//uppercase else returns the character without changes.
int		ft_tolower(int c);
//ft_isspace(): Space character test
int		ft_isspace(int c);

//STRING TO INTEGER CONVERSION:*******************************************

//ft_atoi(): Converts the initial portion of the string in int.
int		ft_atoi(const char *nptr);
//ft_atoi_hex(): Converts the initial portion of hex string 
//representation in int.
int		ft_atoi_hex(char *str);

/*-----------------------------*Mandatory Part II*---------------------------*/

// STRING MANIPULATION: 

//*ft_substr(): Returns a pointer to a substring that has size len. 
char	*ft_substr(char const *s, unsigned int start, size_t len);
//*ft_strjoin(): Concatenate two strings and returns a pointer to 
//the new bigger string.
char	*ft_strjoin(char const *s1, char const *s2);
//*ft_strtrim(): Returns a pointer to a new string that has the 
//characters of the set removed from the beginning and the 
//end of the string.
char	*ft_strtrim(char const *s1, char const *set);
//**ft_split(): Returns a pointer to an array of strings that 
//are obtained by splitting the string s using the character c as a delimiter.
char	**ft_split(char const *s, char c);
//*ft_strmapi(): Applies the function f to each character of 
//the string s to create a new string resulting from 
//successive applications of f.
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
//*ft_striteri(): Applies the function f to each character 
//of the string passed as argument, and passing its index 
//as first argument. Each character is passed by address to f 
//to be modified if necessary.
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
//ft_putchar_fd(): Outputs the character c to the given file descriptor.

// FILE DESCRIPTOR OUTPUT:************************************************* 

void	ft_putchar_fd(char c, int fd);
//ft_putstr_fd(): Outputs the string s to the given file descriptor.
void	ft_putstr_fd(char *s, int fd);
//ft_putendl_fd(): Outputs the string s to the given file descriptor, 
//followed by a newline.
void	ft_putendl_fd(char *s, int fd);
//ft_putnbr_fd(): Outputs the integer n to the given file descriptor.
void	ft_putnbr_fd(int n, int fd);

//INTEGER TO STRING CONVERSION:*******************************************

//*ft_itoa(): Returns a pointer to a new string that 
//represents the integer received as an argument.
char	*ft_itoa(int n);

int		ft_iswhitespace(char c);

int		ft_strcmp(char *s1, char *s2);

int		ft_isnumber(char c);

/*___________________________________[BONUS]_________________________________*/

//LINKED LIST:************************************************************

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//LIST CREATION AND MODIFICATION:*****************************************

//*ft_lstnew(): Allocates (with malloc(3)) and returns a new element.
t_list	*ft_lstnew(void *content);
//*ft_lstadd_front(): Adds the element ’new’ at the beginning of the list.
void	ft_lstadd_front(t_list **lst, t_list *new);
//*ft_lstlast(): Returns the last element of the list.
t_list	*ft_lstlast(t_list *lst);
//*ft_lstadd_back(): Adds the element ’new’ at the end of the list.
void	ft_lstadd_back(t_list **lst, t_list *new);

//LIST DELETION AND MEMORY MANAGEMENT:************************************

//*ft_lstdelone(): Takes as a parameter an element and frees the memory
void	ft_lstdelone(t_list *lst, void (*del)(void *));
//*ft_lstclear(): Deletes and frees the given element and every successor
void	ft_lstclear(t_list **lst, void (*del)(void	*));

//LIST ITERATION AND MAPPING:*********************************************

//ft_lstiter(): Iterates the list ’lst’ and applies the function
void	ft_lstiter(t_list *lst, void (*f)(void *));
//*ft_lstsize(): Counts the number of elements in a list.
int		ft_lstsize(t_list *lst);
//*ft_lstmap(): Iterates the list ’lst’ and applies the function returning 
//a new list
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*_______________________________[NEW FUNCTIONS]_____________________________*/
/**ft_count_words(): Count the qty of words looking at a specific sep.*/
int		ft_count_words(char *str, char sep);

#endif
