#include <minishell.h>
#include <unistd.h>
#include <sys/wait.h>
#include <criterion/criterion.h>

Test(pwd, expected_cwd_eq_path){
	char	*path = "/home/gvitor-s/Documents/42Projects/Minishell\n";
	pid_t	pid;
	int		fd[2];
	char	*cwd = malloc(strlen(path));

	if (pipe(fd) == -1) {
		exit(EXIT_FAILURE);
	}
	pid = fork();

	if (pid == 0) {
		free(cwd);
		close(fd[0]);
		close(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (pwd() == -1) {
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else {
		close(fd[1]);
		int	status;
		wait(&status);
		if (WEXITSTATUS(status) != 0) {
			exit(EXIT_FAILURE);
		}
		if (read(fd[0], cwd, strlen(path)) == -1) {
			exit(EXIT_SUCCESS);
		}
		close(fd[0]);
	}
	cr_assert_str_eq(cwd, path, "Wrong cwd: %s\n, in first test.\n", cwd);
}
