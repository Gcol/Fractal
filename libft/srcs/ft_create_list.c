char  **ft_create_list_str(int cnt, ...)
{
	va_list lst;
	char **result;
	char *tmp;
	int i;

	va_start(lst, cnt);
	i = 0;
	result = ft_memalloc_exit(sizeof(char **) * (cnt + 1));
	while(i < cnt)
	{
		tmp = va_arg(lst, char *);
		result[i] = ft_strdup(tmp);
		i++;
	}
	return(result);
}
