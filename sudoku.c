/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:56:45 by rnugroho          #+#    #+#             */
/*   Updated: 2017/08/13 17:56:47 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_putstr(char *str)
{
	char *c;

	c = str;
	while (*c != '\0')
	{
		ft_putchar(*c);
		c++;
	}
}

int		ft_check_number(int board[9][9], int row, int col, int number)
{
	int i;
	int j;
	int base_row;
	int base_col;
	int exist;

	exist = 0;
	base_row = (row / 3) * 3;
	base_col = (col / 3) * 3;
	i = base_row;
	while (i < base_row + 3)
	{
		j = base_col;
		while (j < base_col + 3)
		{
			if (board[i][j] == number)
			{
				exist = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (exist);
}

int		ft_is_available(int board[9][9], int row, int col, int number)
{
	int i;

	if (ft_check_number(board, row, col, number))
		return (0);
	i = 0;
	while (i < 9)
	{
		if (board[i][col] == number)
			return (0);
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (board[row][i] == number)
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_board(int board[9][9])
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if (j > 0)
				ft_putchar(' ');
			ft_putchar(board[i][j] + '0');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int		ft_mcv_heuristic(int board[9][9], int *row, int *col)
{
	int	heu[3];
	int counter[4];

	heu[0] = 0;
	heu[1] = 0;
	heu[2] = 10;
	counter[0] = 0;
	while (counter[0] < 9)
	{
		counter[1] = 0;
		while (counter[1] < 9)
		{
			counter[2] = 1;
			counter[3] = 0;
			while (counter[2] <= 9)
			{
				if (board[counter[0]][counter[1]] != 0)
					counter[3] = 10;
				else if (ft_is_available(board, counter[0], counter[1], counter[2]))
					counter[3]++;
				counter[2]++;
			}
			if (heu[2] > counter[3])
			{
				heu[2] = counter[3];
				heu[0] = counter[0];
				heu[1] = counter[1];
			}
			counter[1]++;
		}
		counter[0]++;
	}
	*row = heu[0];
	*col = heu[1];
	return (heu[2]);
}

int		ft_put_number(int board[9][9], int row, int col, int *solution)
{
	int number;

	if (ft_mcv_heuristic(board, &row, &col) == 10)
		return (1);
	number = 1;
	while (number <= 9)
	{
		if (ft_is_available(board, row, col, number))
		{
			board[row][col] = number;
			if (ft_put_number(board, row, col + 1, solution))
			{
				*solution = *solution + 1;
			}
			if (*solution < 2)
				board[row][col] = 0;
		}
		number++;
	}
	return (0);
}

int		ft_print_number(int board[9][9], int row, int col, int *solution)
{
	int number;

	if (ft_mcv_heuristic(board, &row, &col) == 10)
		return (1);
	number = 1;
	while (number <= 9)
	{
		if (ft_is_available(board, row, col, number))
		{
			board[row][col] = number;
			if (ft_print_number(board, row, col + 1, solution))
			{
				*solution = *solution + 1;
				ft_print_board(board);
			}
			if (*solution < 2)
				board[row][col] = 0;
		}
		number++;
	}
	return (0);
}
