#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdlib.h>
#include "../src/executor/utils_exec.h"
#include "hashtable.h"
#include "parsing.h"
#include "tokenizer.h"
#include "../src/expand/envs.h"

Test(check_path, expected_path_of_command_cat)
{
	const char	*line = "cat Makefile";
	struct s_program	*program = NULL;
	struct s_tokens		*tokens = NULL;
	char				*path = NULL;

	init_hashtbl();
	init_envs();
	tokens = tokenizer(line);
	program = parsing(tokens);
	path = check_path(program->name);
	cr_assert_str_eq(path, "/usr/bin/cat");
	free(path);
	clear_tokens(&tokens);
	destroy_programs(&program);
	destroy_hashtbl();
}

Test(check_path, exepected_path_null) {
	const char	*line = "asdfsafsa";
	struct s_program	*prog = NULL;
	struct s_tokens		*tokens = NULL;
	char				*path = NULL;

	init_hashtbl();
	init_envs();
	tokens = tokenizer(line);
	prog = parsing(tokens);
	path = check_path(prog->name);
	cr_assert_null(path);
	destroy_programs(&prog);
	clear_tokens(&tokens);
	destroy_hashtbl();
}
