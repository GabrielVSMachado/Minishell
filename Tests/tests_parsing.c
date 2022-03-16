#include <criterion/criterion.h>
#include "parsing.h"

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
