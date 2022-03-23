#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "../src/executor/utils_exec.h"
#include "../src/expand/envs.h"
#include "ft_string.h"
#include "hashtable.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"
#include <stdlib.h>
#include <time.h>

extern struct s_hashtbl	g_envs;

Test(gen_envp, expected_envp_eq_environ)
{
	char 		**envp;
	char		**tmp;

	init_hashtbl();
	init_envs();
	envp = gen_envp();
	tmp = envp;
	while (*tmp)
	{
		tmp++;
	}
	cr_assert_null(*tmp);
	delete_envp((char **)envp);
	destroy_hashtbl();
}
