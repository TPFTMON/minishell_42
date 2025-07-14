/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:28:57 by sguan             #+#    #+#             */
/*   Updated: 2025/06/27 18:25:29 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cd_args(char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc > 2)
	{
		ft_dprintf(2, "cd: too many arguments\n");
		return (1);
	}
	if (argc > 1 && args[1][0] == '-'
		&& args[1][1] != '\0' && !ft_strcmp(args[1], "--"))
	{
		ft_dprintf(2, "cd: invalid path: %s\n", args[1]);
		return (2);
	}
	return (0);
}

static char	*get_cd_dest(char **args, char **envp, int *status)
{
	char	*dest;

	if (!args[1] || args[1][0] == '\0'
		|| (args[1][0] == '~' && args[1][1] == '\0')
		|| (args[1][0] == '-' && args[1][1] == '-' && args[1][2] == '\0'))
	{
		dest = get_env_value(envp, "HOME");
		if (!dest)
			return (*status = 1, ft_dprintf(2, "cd: HOME not set\n"), NULL);
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		dest = get_env_value(envp, "OLDPWD");
		if (!dest)
			return (*status = 1, ft_dprintf(2, "cd: OLDPWD not set\n"), NULL);
		printf("%s\n", dest);
	}
	else
		dest = args[1];
	return (dest);
}

int	cd_update_env(char ***envp)
{
	char	cwd[4096];
	int		set_old;
	char	**new_env;

	if (!getcwd(cwd, sizeof(cwd)))
		cwd[0] = '\0';
	set_old = set_env_value(envp, "OLDPWD", cwd);
	if (set_old != 0)
	{
		new_env = add_env_value(envp, "OLDPWD", cwd);
		if (new_env)
			*envp = new_env;
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (set_env_value(envp, "PWD", cwd) != 0)
		{
			new_env = add_env_value(envp, "OLDPWD", cwd);
			if (new_env)
				*envp = new_env;
		}
	}
	return (0);
}

int	builtin_cd(char **args, char ***envp)
{
	int		status;
	char	*dest;

	status = check_cd_args(args);
	if (status)
		return (status);
	dest = get_cd_dest(args, *envp, &status);
	if (!dest)
		return (status);
	if (chdir(dest) != 0)
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", dest, strerror(errno));
		return (1);
	}
	status = cd_update_env(envp);
	return (status);
}

/////////////TEST CD/////////////////////////////////////

/*
char **init_test_envp(void) {
    char **envp = malloc(sizeof(char *) * 4);
    envp[0] = strdup("HOME=/home/sguan");
    envp[1] = strdup("PWD=/home/sguan/Minishell");
    envp[2] = strdup("OLDPWD=/home/sguan/Minishell/libft");
    envp[3] = NULL;
    return envp;
}

void free_envp(char **envp) {
    for (int i = 0; envp[i]; i++) {
        free(envp[i]);
    }
    free(envp);
}

t_command *init_test_command(char **argv) {
    t_command *cmd = malloc(sizeof(t_command));
    cmd->argv = argv;
    cmd->cmd_path = NULL;
    cmd->redirections = NULL;
    cmd->next_in_pipe = NULL;
    cmd->pid = 0;
    cmd->is_builtin = 1;
    return cmd;
}

void print_env_vars(char **envp) {
    printf("PWD: %s\n", get_env_value(envp, "PWD"));
    printf("OLDPWD: %s\n", get_env_value(envp, "OLDPWD"));
}

void run_cd_tests(void) {
    int status;

    // Test 1: cd with no arguments
    {
        printf("\nTest 1: cd (no arguments, should go to HOME)\n");
        char **envp = init_test_envp();
        char *argv[] = {"cd", NULL};
        t_command *cmd = init_test_command(argv);

        status = builtin_cd(cmd->argv, &envp);
        printf("Status: %d\n", status);
        print_env_vars(envp);

        free(cmd);
        free_envp(envp);
    }

    // Test 2: cd to a valid directory
    {
        printf("\nTest 2: cd /tmp\n");
        char **envp = init_test_envp();
        char *argv[] = {"cd", "/tmp", NULL};
        t_command *cmd = init_test_command(argv);

        status = builtin_cd(cmd->argv, &envp);
        printf("Status: %d\n", status);
        print_env_vars(envp);

        free(cmd);
        free_envp(envp);
    }

    // Test 3: cd with too many arguments
    {
        printf("\nTest 3: cd /tmp /home (too many arguments)\n");
        char **envp = init_test_envp();
        char *argv[] = {"cd", "/tmp", "/home", NULL};
        t_command *cmd = init_test_command(argv);

        status = builtin_cd(cmd->argv, &envp);
        printf("Status: %d\n", status);

        free(cmd);
        free_envp(envp);
    }

    // Test 4: cd to invalid directory
    {
        printf("\nTest 4: cd /nonexistent (invalid directory)\n");
        char **envp = init_test_envp();
        char *argv[] = {"cd", "/nonexistent", NULL};
        t_command *cmd = init_test_command(argv);

        status = builtin_cd(cmd->argv, &envp);
        printf("Status: %d\n", status);

        free(cmd);
        free_envp(envp);
    }

    // Test 5: cd - (go to OLDPWD)
    {
        printf("\nTest 5: cd - (go to OLDPWD)\n");
        char **envp = init_test_envp();
        char *argv[] = {"cd", "-", NULL};
        t_command *cmd = init_test_command(argv);

        status = builtin_cd(cmd->argv, &envp);
        printf("Status: %d\n", status);
        print_env_vars(envp);

        free(cmd);
        free_envp(envp);
    }

    // Test 6: cd with invalid option
    {
        printf("\nTest 6: cd -x (invalid option)\n");
        char **envp = init_test_envp();
        char *argv[] = {"cd", "-x", NULL};
        t_command *cmd = init_test_command(argv);

        status = builtin_cd(cmd->argv, &envp);
        printf("Status: %d\n", status);

        free(cmd);
        free_envp(envp);
    }
}

// === Entry point ===

int main(void) {
    run_cd_tests();
    return 0;
}
*/
