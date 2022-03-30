#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <criterion/redirect.h>
#include "../src/expand/envs.h"
#include "hashtable.h"
#include "linked_list.h"
#include "minishell.h"
#include "parsing.h"
#include "tokenizer.h"
#include <string.h>
#include <unistd.h>
#include <limits.h>

Test(cd, expected_STDERR_msg, .init=cr_redirect_stderr) {
	struct s_tokens *tok;
	struct s_program *prog;

	tok = tokenizer("cd ../ ./");
	prog = parsing(tok);
	clear_tokens(&tok);
	cd(prog->params);
	cr_assert_stderr_eq_str("minishell: cd: too many arguments\n");
}

Test(cd, expected_STDERR_msg_no_home, .init=cr_redirect_stderr) {
	struct s_tokens *tok;
	struct s_program *prog;
	struct s_list *params = NULL;

	ft_lstadd_back(&params, ft_lstnew(strdup("HOME")));
	init_hashtbl();
	init_envs();
	unset(params);
	tok = tokenizer("cd");
	prog = parsing(tok);
	clear_tokens(&tok);
	int result = cd(prog->params);
	cr_assert_eq(result, 1);
	cr_assert_stderr_eq_str("minishell: cd: HOME not set\n");
	destroy_programs(&prog);
	destroy_hashtbl();
	ft_lstclear(&params, free);
}

Test(cd, expected_pwd_eq_cwd) {
	struct s_tokens *tok = tokenizer("cd ../");
	struct s_program *prog = parsing(tok);

	clear_tokens(&tok);
	init_hashtbl();
	init_envs();
	cr_assert_str_eq(hashtbl_lookup("PWD")->val, getcwd(NULL, PATH_MAX));
	int result = cd(prog->params);
	cr_assert_eq(result, 0);
	cr_assert_str_eq(hashtbl_lookup("PWD")->val, getcwd(NULL, PATH_MAX));
	destroy_programs(&prog);
	destroy_hashtbl();
}
