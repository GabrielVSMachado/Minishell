#include <criterion/criterion.h>
#include "libft.h"

static int	is_interpreted_symbol(int c)
{
	return (ft_isdigit(c) || c == '?' || c == '!' || c == '-');
}

static int	check_valid_key(const char *word)
{
	int	counter;

	if (is_interpreted_symbol(*word))
		return (*word);
	counter = 0;
	while (word[counter] && word[counter] != '='
		&& (ft_isalnum(word[counter]) || word[counter] == '_'))
		counter += 1;
	return ((word[counter] != 0 && word[counter] != '=') * (word[counter]));
}

Test(check_valid_key, expected_result_eq_0)
{
	char	result;

	result = check_valid_key("g");
	cr_assert_eq(result, 0);
}

Test(check_valid_key, expected_result_eq_interrogation)
{
	char	result;

	result = check_valid_key("ga?=");
	cr_assert_eq(result, '?');
}

Test(check_valid_key, expected_result_eq_1)
{
	char	result;

	result = check_valid_key("1ga?=");
	cr_assert_eq(result, '1');
}

Test(check_valid_key, expected_result_eq_0_when_valid_key_without_equal_char)
{
	char	result;

	result = check_valid_key("ga_1");
	cr_assert_eq(result, 0);
}

Test(check_valid_key, expected_result_eq_difference_char)
{
	char	result;

	result = check_valid_key("ga-1");
	cr_assert_eq(result, '-');
}
