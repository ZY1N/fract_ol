/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:00:03 by yinzhang          #+#    #+#             */
/*   Updated: 2020/01/27 12:01:01 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main()
{
	int rgb;

	rgb = (1 << 16 | 1 << 8 | 1);
	printf("%d\n", rgb);
}