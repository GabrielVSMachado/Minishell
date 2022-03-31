#include <criterion/criterion.h>
#include "libft.h"
#include "error.h"
#include <stdio.h>

static int	is_special(char	const c)
{
	return (ft_strchr("|&()><", c) != NULL);
}

static int	is_space(char const c)
{
	return (c == ' ');
}

static void	which_other_tokens(struct s_tokens **head, char const *line,
		unsigned int *cursor)
{
	add_back_token(head, new_token(
			NULL,
			T_PIPE * (line[*cursor] == '|' && line[*cursor + 1] != '|')
			+ T_OR * (line[*cursor] == '|' && line[*cursor + 1] == '|')
			+ T_CPARENTHESIS * (line[*cursor] == ')')
			+ T_OPARENTHESIS * (line[*cursor] == '(')
			+ T_AND * (line[*cursor] == '&' && line[*cursor + 1] == '&')
			+ T_RAOUTPUT * (line[*cursor] == '>' && line[*cursor + 1] == '>')
			+ T_RINPUT * (line[*cursor] == '<' && line[*cursor + 1] != '<')
			+ T_ROUTPUT * (line[*cursor] == '>' && line[*cursor + 1] != '>')
			+ T_HEREDOC * (line[*cursor] == '<' && line[*cursor + 1] == '<')
			));
	(*cursor) += (1 + (line[*cursor] == line[*cursor + 1]
				AND (line[*cursor] != '(' AND line[*cursor] != ')')));
}

static int	treat_words(struct s_tokens **head, char const *line,
		unsigned int *cursor)
{
	unsigned int	counter;
	unsigned char	c;
	char			*next_quotes;

	counter = *cursor;
	while (line[counter] != '\0'
		&& NOT is_space(line[counter])
		&& NOT is_special(line[counter]))
	{
		c = ('\'' * (line[counter] == '\''))
			+ ('\"' * (line[counter] == '\"'));
		if (c != 0)
		{	
			next_quotes = ft_strchr(line + counter + 1, c);
			if (next_quotes == NULL)
				return (raise_tokenizer_err(
						"bad format string: unclosed quotes", head));
			counter += (next_quotes - (line + counter));
		}
		counter += 1;
	}
	add_back_token(head,
		new_token(ft_substr(line, *cursor, counter - *cursor), T_WORD));
	(*cursor) += (counter - *cursor);
	return (0);
}

struct s_tokens	*_tokenizer(char const *line)
{
	struct s_tokens	*head;
	unsigned int	cursor;

	head = NULL;
	cursor = 0;
	while (line[cursor] != '\0')
	{
		if (is_special(line[cursor]))
		{
			which_other_tokens(&head, line, &cursor);
			continue ;
		}
		else if (NOT is_space(line[cursor]))
		{
			if (treat_words(&head, line, &cursor) == -1)
				return (clear_tokens(&head), NULL);
			continue ;
		}
		cursor += 1;
	}
	return (head);
}


Test(tokenizer, expected_llist_with_two_words) {
	char const	*line;
	struct s_tokens	*head = NULL;

	line = strdup("cat Makefile");
	head = _tokenizer(line);
	cr_assert_str_eq(
			head->value, "cat",
			"head->value on first test: %s\n", head->value);
	cr_assert(
		head->token == T_WORD,
		"head->token on first test: %i\n", head->token
		);
	cr_assert_str_eq(head->next->value, "Makefile",
			"head->next->value on first test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on first test: %i\n", head->next->token);
	clear_tokens(&head);
	free((void *)line);
}

Test(tokenizer, expected_llist_with_fours_words_and_one_rinput) {
	char const	line[] = "tr '\n' ' ' < command.txt";
	struct s_tokens	*head = NULL;

	head = _tokenizer(line);
	cr_assert_str_eq(head->value, "tr",
			"head->value on second test: %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on second test: %d\n", head->token);


	cr_assert_str_eq(head->next->value, "'\n'",
			"head->next->value on second test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on second test: %d\n", head->next->token);


	cr_assert_str_eq(head->next->next->value, "' '",
		"head->next->next->value on second test: %s\n", head->next->next->value);
	cr_assert(head->next->next->token == T_WORD,
		"head->next->next->token on second test: %d\n", head->next->next->token);


	cr_assert_null(head->next->next->next->value,
		"head->next->next->next->next->value is not null on second test");
	cr_assert(
		head->next->next->next->token == T_RINPUT,
		"head->next->next->next->next->token on second test: %d\n",
		head->next->next->next->token
		);


	cr_assert_str_eq(
			head->next->next->next->next->value,
			"command.txt",
		"head->next->next->next->next->next->next->next->next->value on second test: %s\n",
		head->next->next->next->next->value);
	cr_assert(
		head->next->next->next->next->token == T_WORD,
		"head->next->next->next->next->next->next->next->next->token on second test: %d\n",
		head->next->next->next->next->token);

	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_three_words_and_one_routput) {
	char const	*line = "cat Makefile > makefile.txt";
	struct s_tokens	*head = NULL;

	head = _tokenizer(line);

	cr_assert_str_eq(head->value, "cat",
			"head->value on third test: %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on third test: %d\n", head->token);

	cr_assert_str_eq(head->next->value, "Makefile",
			"head->next->value on third test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on third test: %d\n", head->next->token);

	cr_assert_null(head->next->next->value,
			"head->next->next->value is not null");
	cr_assert(head->next->next->token == T_ROUTPUT,
			"head->next->next->token on third test: %d\n",
			head->next->next->token);

	cr_assert_str_eq(
			head->next->next->next->value, "makefile.txt",
			"head->next->next->next->next->next->value on third test: %s\n",
			head->next->next->next->value);
	cr_assert(head->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on third test: %d\n",
			head->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_fours_words_and_one_rinput_complex) {
	char const	*line = "tr 'banana pera' 'manga abacaxi' < frutas.csv";
	struct s_tokens	*head = NULL;

	head = _tokenizer(line);

	cr_assert_str_eq(head->value, "tr",
			"head->value on fourth test: %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on fourth test: %d\n", head->token);

	cr_assert_str_eq(head->next->value, "'banana pera'",
			"head->next->value on fourth test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on fourth test: %d\n", head->next->token);

	cr_assert_str_eq(head->next->next->value, "'manga abacaxi'",
			"head->next->value on fourth test: %s\n", head->next->next->value);
	cr_assert(head->next->next->token == T_WORD,
			"head->next->token on fourth test: %d\n", head->next->next->token);

	cr_assert_null(head->next->next->next->value,
			"head->next->next->next->value on fourth test");
	cr_assert(head->next->next->next->token == T_RINPUT,
			"head->next->next->token on fourth test: %d\n",
			head->next->next->next->token);

	cr_assert_str_eq(
			head->next->next->next->next->value, "frutas.csv",
			"head->next->next->next->next->value on fourth test: %s\n",
			head->next->next->next->next->value);
	cr_assert(head->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on fourth test: %d\n",
			head->next->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_four_words_and_one_pipe_with_one_token_invalid) {
	char const	*line = "valgrind ./test |& cat -e";
	struct s_tokens	*head = NULL;

	head = _tokenizer(line);

	cr_assert_str_eq(head->value, "valgrind",
			"head->value on fifth %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on fifth %d\n", head->token);

	cr_assert_str_eq(head->next->value, "./test",
			"head->next->value on fifth %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on fifth %d\n", head->next->token);

	cr_assert_null(head->next->next->value,
			"head->next->next->value is not NULL");
	cr_assert(head->next->next->token == T_PIPE,
			"head->next->next->token on fifth %d\n", T_PIPE);

	cr_assert_null(head->next->next->next->value,
			"head->next->next->next->value is not null"); //invalid token
	cr_assert(head->next->next->next->token == T_WORD,
			"head->next->next->next->token on fifth %d\n",
			head->next->next->next->token);

	cr_assert_str_eq(head->next->next->next->next->value, "cat",
			"head->next->next->next->next->value on fifth %s\n",
			head->next->next->next->next->value);
	cr_assert(head->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on fifth %d\n",
			head->next->next->next->next->token);

	cr_assert_str_eq(head->next->next->next->next->next->value, "-e",
			"head->next->next->next->next->next->value on fifth %s\n",
			head->next->next->next->next->next->value);
	cr_assert(head->next->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->next->token on fifth %d\n",
			head->next->next->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_heredoc_and_four_words) {
	char const	*line = "<< out tr 'a' 'b'";
	struct s_tokens	*head = NULL;

	head = _tokenizer(line);

	cr_assert_null(head->value, "head->value on sixth is not NULL");
	cr_assert(head->token == T_HEREDOC, "head->token on sixth %d\n", head->token);

	cr_assert_str_eq(head->next->value, "out",
			"head->next->value on sixth %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on sixth %d\n", head->next->token);

	cr_assert_str_eq(head->next->next->value, "tr",
			"head->next->next->value on sixth %s\n", head->next->next->value);
	cr_assert(head->next->next->token == T_WORD,
			"head->next->next->token on sixth %d\n", head->next->next->token);

	cr_assert_str_eq(head->next->next->next->value, "'a'",
			"head->next->next->next->value on sixth %s\n",
			head->next->next->next->value);
	cr_assert(head->next->next->next->token == T_WORD,
			"head->next->next->next->token on sixth %d\n",
			head->next->next->next->token);

	cr_assert_str_eq(head->next->next->next->next->value, "'b'",
			"head->next->next->next->next->value on sixth %s\n",
			head->next->next->next->next->value);
	cr_assert(head->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on sixth %d\n",
			head->next->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_six_words_and_AND_and_OR) {
	char const *line = "true && echo $? && false || echo $?";
	struct s_tokens	*head = NULL;
	unsigned int	tokens[] = {
		T_WORD,
		T_AND,
		T_WORD,
		T_WORD,
		T_AND,
		T_WORD,
		T_OR,
		T_WORD,
		T_WORD
	};
	char *values[] = {
		"true",
		NULL,
		"echo",
		"$?",
		NULL,
		"false",
		NULL,
		"echo",
		"$?"
	};
	head = _tokenizer(line);
	int i = 0;
	for (struct s_tokens *tmp = head; tmp != NULL; tmp = tmp->next) {
		if (values[i] == NULL) {
			cr_assert_null(tmp->value);
		} else {
			cr_assert_str_eq(tmp->value, values[i]);
		}
		cr_assert(tmp->token == tokens[i++]);
	}
}

Test(tokenizer, expected_llist_with_rinput_routput_and_three_words) {
	char const	*line = "echo < Makefile > out.txt";
	struct s_tokens	*head = NULL;
	const char *expected_values[] = {
		"echo",
		NULL,
		"Makefile",
		NULL,
		"out.txt"
	};
	const unsigned int expected_tokens[] = {
		T_WORD,
		T_RINPUT,
		T_WORD,
		T_ROUTPUT,
		T_WORD
	};

	head = _tokenizer(line);
	int	i = 0;
	for (struct s_tokens *tmp = head; tmp; tmp = tmp->next) {
		if (!expected_values[i]) {
			cr_assert_null(tmp->value);
		} else {
			cr_assert_str_eq(tmp->value, expected_values[i]);
		}
		cr_assert(tmp->token == expected_tokens[i++]);
	}
	clear_tokens(&head);
}

Test(tokenizer, expected_four_words_and_one_pipe) {
	char const *line = "cat Makefile |tr 'a' 'b'";
	struct s_tokens *head = NULL;
	char const *expected_values[] = {
		"cat",
		"Makefile",
		NULL,
		"tr",
		"'a'",
		"'b'"
	};
	unsigned const int expected_tokens[] = {
		T_WORD,
		T_WORD,
		T_PIPE,
		T_WORD,
		T_WORD,
		T_WORD
	};
	head = _tokenizer(line);
	int i = 0;
	for (struct s_tokens *tmp = head; tmp; tmp = tmp->next) {
		if (!expected_values[i]) {
			cr_assert_null(tmp->value);
		} else {
			cr_assert_str_eq(tmp->value, expected_values[i]);
		}
		cr_assert(tmp->token == expected_tokens[i++]);
	}
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_three_words) {
	char const *line = "ping -c1 8.8.8.8";
	struct s_tokens *head = NULL;
	char const *expected_values[] = {
		"ping",
		"-c1",
		"8.8.8.8"
	};
	unsigned const int expected_tokens[] = {
		T_WORD,
		T_WORD,
		T_WORD
	};
	head = _tokenizer(line);
	int i = 0;
	for (struct s_tokens *tmp = head; tmp; tmp = tmp->next) {
		cr_assert_str_eq(tmp->value, expected_values[i]);
		cr_assert(tmp->token == expected_tokens[i++]);
	}
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_five_words_one_pipe_and_one_rout) {
	char const *line = "cd .. > abc.txt | echo oi";
	struct s_tokens *head = NULL;
	char const *expected_values[] = {
		"cd",
		"..",
		NULL,
		"abc.txt",
		NULL,
		"echo",
		"oi"
	};
	unsigned const int expected_tokens[] = {
		T_WORD,
		T_WORD,
		T_ROUTPUT,
		T_WORD,
		T_PIPE,
		T_WORD,
		T_WORD
	};
	head = _tokenizer(line);
	int i = 0;
	for (struct s_tokens *tmp = head; tmp; tmp = tmp->next) {
		if (!expected_values[i]) {
			cr_assert_null(tmp->value);
		} else {
			cr_assert_str_eq(tmp->value, expected_values[i]);
		}
		cr_assert(tmp->token == expected_tokens[i++]);
	}
	clear_tokens(&head);
}

Test(tokenizer, expected_RAOUTPUT) {
	char const *line = "echo 'a' >> abc.txt";
	struct s_tokens *head = NULL;
	char const *expected_values[] = {
		"echo",
		"'a'",
		NULL,
		"abc.txt"
	};
	unsigned const int expected_tokens[] = {
		T_WORD,
		T_WORD,
		T_RAOUTPUT,
		T_WORD
	};
	head = _tokenizer(line);
	int i = 0;
	for (struct s_tokens *tmp = head; tmp; tmp = tmp->next) {
		if (!expected_values[i]) {
			cr_assert_null(tmp->value);
		} else {
			cr_assert_str_eq(tmp->value, expected_values[i]);
		}
		cr_assert(tmp->token == expected_tokens[i++]);
	}
	clear_tokens(&head);
}

Test(tokenizer, check_two_parenthesis_sequence) {
	const char *line = "echo oi | ((cat -e)";
	struct s_tokens *head = _tokenizer(line);
	const char *expected_values[] = {
		"echo",
		"oi",
		NULL,
		NULL,
		NULL,
		"cat",
		"-e",
		NULL
	};
	const unsigned int expected_tokens[] = {
		T_WORD,
		T_WORD,
		T_PIPE,
		T_OPARENTHESIS,
		T_OPARENTHESIS,
		T_WORD,
		T_WORD,
		T_CPARENTHESIS
	};
	int i = 0;
	for (struct s_tokens *tmp = head; tmp; tmp=tmp->next) {
		if (!expected_values[i]) {
			cr_assert_null(tmp->value);
		}else {
			cr_assert_str_eq(tmp->value, expected_values[i]);
		}
		cr_assert(tmp->token == expected_tokens[i++]);
	}
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_four_words_four_parenthesis_and_one_pipe) {
	const char *line = "(echo oi | (cat -e))";
	struct s_tokens *head = NULL;
	const char *expected_values[] = {
		NULL,
		"echo",
		"oi",
		NULL,
		NULL,
		"cat",
		"-e",
		NULL,
		NULL
	};
	const unsigned int expected_tokens[] = {
		T_OPARENTHESIS,
		T_WORD,
		T_WORD,
		T_PIPE,
		T_OPARENTHESIS,
		T_WORD,
		T_WORD,
		T_CPARENTHESIS,
		T_CPARENTHESIS
	};
	head = _tokenizer(line);
	int i = 0;
	for (struct s_tokens *tmp = head; tmp; tmp=tmp->next) {
		if (!expected_values[i]) {
			cr_assert_null(tmp->value);
		}else {
			cr_assert_str_eq(tmp->value, expected_values[i]);
		}
		cr_assert(tmp->token == expected_tokens[i++]);
	}
	clear_tokens(&head);
}
