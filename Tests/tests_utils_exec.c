#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdlib.h>
#include "../src/executor/utils_exec.h"
#include "parsing.h"
#include "tokenizer.h"

Test(gen_argv, expected_char_pp_with_rights_params)
{
	char	*const *result;
	char	const	*expected_result[] = {
		"cat",
		"-e",
		"-p",
		"-t",
		NULL
	};
	struct s_tokens	*tokens = NULL;
	struct s_program	*program = NULL;
	char	*const line = "cat -e -p -t";

	tokens = tokenizer(line);
	program = parsing(tokens);
	clear_tokens(&tokens);
	result = gen_argv(program->params, program->name);
	for (int i = 0; i < 4; i++)
		cr_assert_str_eq(result[i], expected_result[i]);
	cr_assert_null(result[4]);
	free((void *)result);
	destroy_programs(&program);
}
