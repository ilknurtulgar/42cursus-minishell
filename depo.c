// void	go_redirect(t_program *program, void run_redirect(char *), char *key,
// 		int *i, int *j)
// {
// 	int		k;
// 	char	*doc;
// 	char	*redi;
// 	int		a;
// 	int		len;
// 	int		z;

// 	doc = NULL;
// 	redi = program->parser_input[*i][*j]->cmd;
// 	len = 0;
// 	z = 0;
// 	while (program->parser_input[*i][*j]->cmd[z])
// 	{
// 		if (zi_strcmp(program->parser_input[*i][*j]->cmd + z, key) != 0)
// 		{
// 			// a << a a<<a<<c
// 			k = 0;
// 			a = 0;
// 			redi_loc(program, &a, &k, redi, key, &len, i, j);
// 			doc = ft_substr(redi, k, len);
// 			printf("redi1:%s\n", doc);
// 			run_redirect(doc);
// 			free(doc);
// 			printf("%s\n", program->parser_input[*i][*j]->cmd + z);
// 		}
// 		else
// 		{
// 			// << a
// 			(*j)++;
// 			a = 0;
// 			len = 0;
// 			redi = program->parser_input[*i][*j]->cmd;
// 			while (redi[a] && redi[a] != '>' && redi[a] != '<')
// 			{
// 				len++;
// 				a++;
// 			}
// 			if (redi[a] == '\0' || (redi[a] == '<' || redi[a] == '>'))
// 			{
// 				doc = ft_substr(redi, 0, len);
// 				printf("redi2:%s\n", doc);
// 				run_redirect(doc);
// 				free(doc);
// 			}
// 		}
// 		z = a;
// 	}
	
// }
// void	redi_loc(t_program *program, int *a, int *k, char *redi, char *key,
// 		int *len, int *i, int *j)
// {
// 	while (redi[*a])
// 	{
// 		if (redi[*a] == key[0])
// 		{
// 			(*a)++;
// 			if (redi[*a] != key[0])
// 				*k = *a;
// 			if (redi[*a] == key[0])
// 			{
// 				(*a)++;
// 				*k = *a;
// 				if (redi[*a] == '\0' && program->parser_input[*i][*j + 1])
// 				{
// 					(*j)++;
// 					*k = 0;
// 					redi = program->parser_input[*i][*j]->cmd;
// 					*a = 0;
// 					*len = 0;
// 					while (redi[*a] && redi[*a] != '>' && redi[*a] != '<')
// 					{
// 						(*len)++;
// 						(*a)++;
// 					}
// 				}
// 				else if (redi[*a] != '\0')
// 				{
// 					while (redi[*a] && redi[*a] != '>' && redi[*a] != '<')
// 					{
// 						(*len)++;
// 						(*a)++;
// 					}
// 				}
// 				if (redi[*a] == '\0' || redi[*a] == '>' || redi[*a] == '<')
// 				{
			
// 					printf("k:%d\n", *k);
// 					printf("len:%d\n", *len);
// 					printf("a:%d\n", *a);
// 					break ;
// 				}
// 			}
// 		}
// 		else
// 			(*a)++;
// 	}
// }