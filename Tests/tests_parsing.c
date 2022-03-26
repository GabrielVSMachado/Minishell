#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "parsing.h"
#include "tokenizer.h"

Test(parsing, expected_one_program_with_infile_makefile)
{
	struct s_program	*program = NULL;
	const	char		*line = "< Makefile cat";
	struct s_tokens		*tokens = NULL;
	struct s_io			*tmp;

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	cr_assert_str_eq(program->name, "cat");
	tmp = (struct s_io *)program->infile->content;
	cr_assert_str_eq(tmp->file, "Makefile");
	cr_assert(tmp->type == INFILE);
	destroy_programs(&program);
}

Test(parsing, expected_one_program_with_infile_heredoc) {
	struct s_program	*program = NULL;
	const	char		*line = "<< out tr 'a' 'b'";
	struct s_tokens		*tokens = NULL;
	struct s_io			*tmp;

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	cr_assert_str_eq(program->name, "tr");
	tmp = (struct s_io *)program->infile->content;
	cr_assert_str_eq(tmp->file, "out");
	cr_assert(tmp->type == APPINFILE);
	cr_assert_str_eq((char *)program->params->content, "'a'");
	cr_assert_str_eq((char *)program->params->next->content, "'b'");
	destroy_programs(&program);
}

Test(parsing, expected_one_program_with_name_cat_infile_and_outfile)
{
	struct s_program	*program = NULL;
	char	const		*line = "> outfile cat < infile";
	struct s_tokens		*tokens = NULL;
	struct s_io			*tmp;

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	cr_assert_str_eq(program->name, "cat");
	tmp = (struct s_io *)program->infile->content;
	cr_assert_str_eq(tmp->file, "infile");
	cr_assert(tmp->type == INFILE);
	tmp = (struct s_io *)program->outfile->content;
	cr_assert_str_eq(tmp->file, "outfile");
	cr_assert(tmp->type == OUTFILE);
	destroy_programs(&program);
}

Test(parsing, expected_one_program_with_name_cat_two_outfile) {
	struct s_program	*program = NULL;
	char	const		*line = "> outfile >> oi cat < infile";
	struct s_tokens		*tokens = NULL;
	struct s_io			*tmp;

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	cr_assert_str_eq(program->name, "cat");
	tmp = (struct s_io *)program->infile->content;
	cr_assert_str_eq(tmp->file, "infile");
	cr_assert(tmp->type == INFILE);
	tmp = (struct s_io *)program->outfile->content;
	cr_assert_str_eq(tmp->file, "outfile");
	cr_assert(tmp->type == OUTFILE);
	tmp = (struct s_io *)program->outfile->next->content;
	cr_assert_str_eq(tmp->file, "oi");
	cr_assert(tmp->type == APPOUTFILE);
	destroy_programs(&program);
}

Test(parsing, expected_two_programs_with_one_with_name_null_and_one_with_tr)
{
	const char	*line = "<< out | tr 'a' 'b'";
	struct s_tokens		*tokens = NULL;
	struct s_program	*program = NULL;
	struct s_io			*tmp;

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	cr_assert_null(program->name);
	tmp = (struct s_io *)program->infile->content;
	cr_assert_str_eq(tmp->file, "out");
	cr_assert_eq(tmp->type, APPINFILE);
	cr_assert_str_eq(program->next->name, "tr");
	cr_assert_str_eq((char *)program->next->params->content, "'a'");
	cr_assert_str_eq(program->next->params->next->content, "'b'");
	destroy_programs(&program);
}

Test(parsing, test_valid_command)
{
	const char *line = "cat | tr 'a' 'b' | wc -l < Makefile";
	struct s_program	*program = NULL;
	struct s_tokens		*tokens = NULL;
	struct s_io			*tmp;

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	cr_assert_str_eq(program->name, "cat");
	cr_assert_str_eq(program->next->name, "tr");
	cr_assert_str_eq(program->next->params->content, "'a'");
	cr_assert_str_eq(program->next->params->next->content, "'b'");
	cr_assert_str_eq(program->next->next->name, "wc");
	cr_assert_str_eq(program->next->next->params->content, "-l");
	tmp = (struct s_io *)program->next->next->infile->content;
	cr_assert_str_eq(tmp->file, "Makefile");
	cr_assert_eq(tmp->type, INFILE);
}

Test(parsing, expected_result_right) {
	const char	*line = "cat Makefile";
	struct s_program	*prog = NULL;
	struct s_tokens		*tokens = NULL;

	tokens = tokenizer(line);
	prog = parsing(tokens);
	cr_assert_str_eq(prog->name, "cat");
	cr_assert_str_eq(prog->params->content, "Makefile");
	clear_tokens(&tokens);
	destroy_programs(&prog);
}

Test(parsing, expected_result_right_1)
{
	const char	*line = "cat | cat | ls";
	struct s_tokens	*tokens = NULL;
	struct s_program	*program = NULL;
	struct s_program	*tmp = NULL;
	char	*const expected_result[] = {
		"cat",
		"cat",
		"ls"
	};

	tokens = tokenizer(line);
	program = parsing(tokens);
	tmp = program;
	for (int i = 0; i < 3; i++) {
		cr_assert_str_eq(tmp->name, expected_result[i]);
		tmp = tmp->next;
	}
	destroy_programs(&program);
	clear_tokens(&tokens);
}

Test(parsing, expected_result_right_2) {
	const char	*line = "<< out tr a b | << in tr b a";
	struct s_tokens	*tokens = NULL;
	struct s_program	*program = NULL;
	char	*const	expected_infile[] = {
		"out",
		"in"
	};
	char	*const	expected_params[] = {
		"a",
		"b",
		"a"
	};

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	struct s_io	*tmp_2;
	int i = 0;
	int	j = 0;
	for (struct s_program *tmp = program; tmp; tmp = tmp->next)
	{
		tmp_2 = (struct s_io *)tmp->infile->content;
		cr_assert_str_eq(tmp->name, "tr");
		cr_assert_eq(tmp_2->type, APPINFILE);
		cr_assert_str_eq(tmp_2->file, expected_infile[i++]);
		cr_assert_str_eq(tmp->params->content, expected_params[j]);
		cr_assert_str_eq(tmp->params->next->content, expected_params[++j]);
	}
	destroy_programs(&program);
}

Test(parsing, expected_result_right_3) {
	const	char	*line = "<< out << gabriel tr a b";
	struct s_program	*program = NULL;
	struct s_tokens		*toke = NULL;
	struct s_io			*tmp = NULL;

	toke = tokenizer(line);
	program = parsing(toke);
	clear_tokens(&toke);
	cr_assert_str_eq(program->name, "tr");
	cr_assert_str_eq(program->params->content, "a");
	cr_assert_str_eq(program->params->next->content, "b");
	tmp = program->infile->content;
	cr_assert_str_eq(tmp->file, "out");
	cr_assert_eq(tmp->type, APPINFILE);
	tmp = program->infile->next->content;
	cr_assert_str_eq(tmp->file, "gabriel");
	cr_assert_eq(tmp->type, APPINFILE);
}
