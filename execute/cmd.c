
#include "../minishell.h"

int is_redirect(char *input)
{
    if (zi_strcmp(input, "<<") == 0 || zi_strcmp(input, "<") == 0 || zi_strcmp(input, ">>") == 0 || zi_strcmp(input, ">") == 0)
        return 0;

    else if (input[0] != '<' && input[0] != '>' && (ft_strchr(input, '<') || ft_strchr(input, '>')))
    {
        return 1;
    }


    return (3);
}

int cmd_counter(t_program *program, int *i)
{
    int j = 0;
    int count = 0;
    while (program->parser_input[*i] != NULL && program->parser_input[*i][j] && program->parser_input[*i][j]->cmd)
    {
        if (program->parser_input[*i][j]->key == 8 || program->parser_input[*i][j]->key == 7)
        {

            if (program->parser_input[*i][j]->key == 8 && program->parser_input[*i][j - 1]->key != 7)
            {
                count++;
                if (program->parser_input[*i][j]->cmd)
                    j++;
            }
            else if (is_redirect(program->parser_input[*i][j]->cmd) == 1)
            {
                count++;
                if (program->parser_input[*i][j]->cmd)
                    j++;
            }
            else if (program->parser_input[*i][j] && is_redirect(program->parser_input[*i][j]->cmd) == 0)
            {

                if (program->parser_input[*i][j] && program->parser_input[*i][j + 1])
                {
                    j++;
                    j++;
                }
            }
            else if (is_redirect(program->parser_input[*i][j]->cmd) == 3)
            {
                if (program->parser_input[*i][j]->cmd)
                    j++;
            }
        }
        else
        {
            count++;
            j++;
        }
    }
    return count;
}

void fill_cmd(t_program *program, int *i)
{
    int cmd_len;
    cmd_len = cmd_counter(program, i);
    printf("cmd_len:%d\n", cmd_len);
    // program->cmd = malloc(sizeof(char **) * (cmd_len + 1));
    // if (!program->cmd)
    // {
    //     perror("memory failure allocation");
    //     exit(1);
    // }
}