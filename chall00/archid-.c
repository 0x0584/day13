/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archid-.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:54:17 by archid-           #+#    #+#             */
/*   Updated: 2024/11/23 16:50:20 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

size_t ft_strlen(const char *s) {
  assert(s);
  size_t size = 0;
  while (*s++)
    ++size;
  return size;
}

bool ft_strncmp(const char *s, const char *t, size_t n) {
  assert(s);
  assert(t);
  while (n && *s && *t && *t == *s)
    --n, ++s, ++t;
  return n == 0;
}

bool ft_necklace(const char *s, const char *t) {
  const size_t len = ft_strlen(s);
  if (len != ft_strlen(t))
    return false;
  else if (!len)
    return true;

  size_t it = 0;
  while (it < len) {
    while (*(s + it) && *(s + it) != *t)
      ++it;
    if (!*(s + it))
      return false;
    else if (ft_strncmp(s + it, t, (len - it)) &&
             (!it || ft_strncmp(t + (len - it), s, it)))
      return true;
    else
      ++it;
  }

  return false;
}

int main(void) {
  assert(ft_necklace("", ""));
  assert(ft_necklace("x", "x"));
  assert(ft_necklace("nicole", "icolen"));
  assert(ft_necklace("nicole", "lenico"));
  assert(ft_necklace("aabaaaaabaab", "aabaabaabaaa"));

  assert(!ft_necklace("x", "xx"));
  assert(!ft_necklace("x", ""));
  assert(!ft_necklace("nicole", "coneli"));
  assert(!ft_necklace("abc", "cba"));
  assert(!ft_necklace("xxyyy", "xxxyy"));
  assert(!ft_necklace("xyxxz", "xxyxz"));

  puts("OK");

  return EXIT_SUCCESS;
}
