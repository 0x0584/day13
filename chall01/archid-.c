/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archid-.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-tudent.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:49:26 by archid-           #+#    #+#             */
/*   Updated: 2024/11/23 20:58:01 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int ft_itos_base_encode(int val, int base, char *buff, size_t *size) {
  static const char digits[17] = "0123456789abcdef";
  bool negative = val < 0;
  if (negative)
    val *= -1;
  do {
    buff[*size] = digits[val % base];
    val /= base;
    if (!*size)
      return !val && !negative;
    --*size;
  } while (val);
  if (negative) {
    buff[*size] = '-';
    if (!*size)
      return true;
    --*size;
  }
  return -1;
}

static bool ft_itos_base_setup_buffer(char *buff, size_t *size) {
  if (!*size)
    return false;
  buff[--*size] = '\0';
  if (!*size)
    return false;
  --*size;
  return true;
}

bool ft_itos_base(int val, int base, char ws, char *buff, size_t size) {
  assert(base == 2 || base == 8 || base == 10 || base == 16);
  ft_itos_base_setup_buffer(buff, &size);
  const int finished = ft_itos_base_encode(val, base, buff, &size);
  if (finished != -1)
    return finished;
  do {
    buff[size] = ws;
    if (size)
      --size;
  } while (size);
  return true;
}

void ft_strncpy(char *s, const char *t, size_t n) {
  assert(s);
  assert(t);
  assert(n);
  while (n && *t) {
    *s++ = *t++;
    --n;
  }
  if (n) {
    *s++ = '\0';
    --n;
  }
}

bool ft_strncmp(const char *s, const char *t, size_t n) {
  assert(s);
  assert(t);
  while (n && *s && *t && *t == *s)
    --n, ++s, ++t;
  return n == 0;
}

char *ft_rgb2hex(int r, int g, int b) {
  assert(r >= 0 && r <= 255);
  assert(g >= 0 && g <= 255);
  assert(b >= 0 && b <= 255);

  char *hex = malloc(8);
  if (!hex)
    return NULL;

  hex[0] = '#';
  hex[6] = '\0';

  ft_itos_base(r, 16, '0', hex + 1, 3 /* no neeed for NUL */);
  ft_itos_base(g, 16, '0', hex + 3, 3);
  ft_itos_base(b, 16, '0', hex + 5, 3);

  return hex;
}

int main(void) {
  assert(ft_strncmp(ft_rgb2hex(255, 255, 255), "#ffffff", 7));
  assert(ft_strncmp(ft_rgb2hex(0, 0, 0), "#000000", 7));
  assert(ft_strncmp(ft_rgb2hex(255, 0, 0), "#ff0000", 7));
  assert(ft_strncmp(ft_rgb2hex(0, 255, 0), "#00ff00", 7));
  assert(ft_strncmp(ft_rgb2hex(0, 0, 255), "#0000ff", 7));
  assert(ft_strncmp(ft_rgb2hex(255, 255, 0), "#ffff00", 7));
  assert(ft_strncmp(ft_rgb2hex(0, 255, 255), "#00ffff", 7));
  assert(ft_strncmp(ft_rgb2hex(255, 0, 255), "#ff00ff", 7));
  assert(ft_strncmp(ft_rgb2hex(192, 192, 192), "#c0c0c0", 7));
  assert(ft_strncmp(ft_rgb2hex(128, 128, 128), "#808080", 7));
  assert(ft_strncmp(ft_rgb2hex(128, 0, 0), "#800000", 7));
  assert(ft_strncmp(ft_rgb2hex(128, 128, 0), "#808000", 7));
  assert(ft_strncmp(ft_rgb2hex(0, 128, 0), "#008000", 7));
  assert(ft_strncmp(ft_rgb2hex(128, 0, 128), "#800080", 7));
  assert(ft_strncmp(ft_rgb2hex(0, 128, 128), "#008080", 7));
  assert(ft_strncmp(ft_rgb2hex(0, 0, 128), "#000080", 7));
  puts("OK");
  return EXIT_SUCCESS;
}
