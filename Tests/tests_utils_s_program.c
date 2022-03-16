#include <criterion/criterion.h>
#include <parsing.h>

Test(new_program, expected_one_node_of_s_Program) {
	struct s_program	*head = NULL;

	head = new_program(strdup("cat"));
	cr_assert_str_eq(head->name, "cat");
	cr_assert_null(head->infile);
	cr_assert_null(head->outfile);
	cr_assert_null(head->next);
	free(head->name);
}

Test(destroy_programs, expected_llist_null)
{
	struct s_program	*head = NULL;
	struct s_program	*tmp;

	for (int i = 0; i < 3; i++) {
		if (!tmp) {
			head = new_program(strdup("cat"));
			tmp = head->next;
		} else {
			tmp = new_program(strdup("cat"));
			tmp = tmp->next;
		}
	}
	cr_assert_not_null(head);
	destroy_programs(&head);
	cr_assert_null(head);
}

Test(add_program, expected_thre_nodes) {
	struct	s_program	*head = NULL;

	for (int i = 0; i < 3; i++) {
		add_program(&head, new_program(strdup("cat")));
	}
	for (struct s_program *tmp = head; tmp; tmp = tmp->next) {
		cr_assert_str_eq(tmp->name, "cat");
		cr_assert_null(tmp->outfile);
		cr_assert_null(tmp->infile);
		cr_assert_null(tmp->params);
	}
	destroy_programs(&head);
}

Test(destroy_programs, expected_llist_null_1)
{
	struct s_program	*head = NULL;
	struct s_program	*last;
	struct s_io			*infile;
	struct s_io			*outfile;

	for (int i = 0; i < 3; i++)
	{
		add_program(&head, new_program(ft_strdup("cat")));
		last = last_program(head);
		ft_lstadd_back(&last->infile, ft_lstnew(malloc(sizeof(struct s_io))));
		infile = (struct s_io *)last->infile->content;
		infile->type = 1;
		infile->file = ft_strdup("outfile");
		ft_lstadd_back(&last->outfile, ft_lstnew(malloc(sizeof(struct s_io))));
		outfile = (struct s_io *)last->outfile->content;
		outfile->type = 1;
		outfile->file = ft_strdup("outfile");
	}
	cr_assert_not_null(head);
	destroy_programs(&head);
	cr_assert_null(head);
}
