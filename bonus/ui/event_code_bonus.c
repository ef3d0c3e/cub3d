/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_code_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

t_event_code
	encode_event_code(enum e_event_type type, uint32_t code)
{
	return ((uint8_t)type | (code << 8));
}

enum e_event_type
	decode_event_code(t_event_code event, uint32_t *code)
{
	*code = (uint32_t)(event >> 8);
	return (event & 0xFF);
}
