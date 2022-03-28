#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <criterion/redirect.h>
#include <criterion/alloc.h>
#include <stdio.h>
#include "minishell.h"
#include "parsing.h"
#include "tokenizer.h"

Test(echo, expected_stdout_eq_parans_splited_by_spacem, .init=cr_redirect_stdout) {
	struct s_tokens *tok = tokenizer("echo 42sp > tr a b");
	struct s_program	*prog = parsing(tok);

	clear_tokens(&tok);
	cr_assert_str_eq(prog->name, "echo");
	echo(prog->params);
	cr_assert_stdout_eq_str("42sp a b\n");
	destroy_programs(&prog);
}

Test(echo, expected_new_line, .init=cr_redirect_stdout)
{
	echo(NULL);
	cr_assert_stdout_eq_str("\n");
}

Test(echo, expected_no_new_line, .init=cr_redirect_stdout) {
	struct s_tokens *tok = tokenizer("echo -n");
	struct s_program *prog = parsing(tok);

	clear_tokens(&tok);
	echo(prog->params);
	cr_assert_stdout_eq_str("");
	destroy_programs(&prog);

}

Test(echo, expected_no_new_line_with_word, .init=cr_redirect_stdout) {
	struct s_tokens *tok = tokenizer("echo -n 42sp");
	struct s_program *prog = parsing(tok);

	clear_tokens(&tok);
	echo(prog->params);
	cr_assert_stdout_eq_str("42sp");
	destroy_programs(&prog);
}

Test(echo, expected_no_new_line_with_two_word, .init=cr_redirect_stdout) {
	struct s_tokens *tok = tokenizer("echo -n 42 sp");
	struct s_program *prog = parsing(tok);

	clear_tokens(&tok);
	echo(prog->params);
	cr_assert_stdout_eq_str("42 sp");
	destroy_programs(&prog);
}

Test(echo, expected_new_line_with_word, .init=cr_redirect_stdout) {
	struct s_tokens *tok = tokenizer("echo 42sp");
	struct s_program *prog = parsing(tok);

	clear_tokens(&tok);
	echo(prog->params);
	cr_assert_stdout_eq_str("42sp\n");
	destroy_programs(&prog);
}

Test(echo, expected_new_line_with_two_word, .init=cr_redirect_stdout)
{
	struct s_tokens *tok = tokenizer("echo 42 sp");
	struct s_program *prog = parsing(tok);

	clear_tokens(&tok);
	echo(prog->params);
	cr_assert_stdout_eq_str("42 sp\n");
	destroy_programs(&prog);
}
