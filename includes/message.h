/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:04:13 by ykawakit          #+#    #+#             */
/*   Updated: 2024/03/12 16:37:40 by ykawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

# define ERR_INITIALIZE_MINISHELL "\
Error\nSomething happened during initializing minishell."

# define ERR_PIPE "\
Error\nPipe error.\n"
# define ERR_FORK "\
Error\nFork error."
# define ERR_MALLOC "\
Error\nMalloc fails."

# define ERR_COMMAND_NOT_FOUND "\
minishell: Command not found: "

# define ERR_HOME_NOT_FOUND "\
minishell: cd: HOME not set."
# define ERR_OLD_PATH_NOT_FOUND "\
minishell: cd: OLDPWD not set"
# define ERR_STRING_NOT_IN_PWD "\
minishell: cd: string not in pwd: "
# define ERR_NO_SUCH_FILE_OR_DIRECTORY "\
minishell: cd: no such file or directory: "
# define ERR_NO_PWD "\
minishell: pwd: PWD not set"
# define ERR_OPTION_NOT_SUPPORTED "\
minishell: option not supported"
# define ERR_TOO_MANY_ARGUMENT "\
minishell: too many arguments"
# define ERR_ARGUMENT_NOT_SUPPORTED "\
minishell: argument not supported"

#endif
