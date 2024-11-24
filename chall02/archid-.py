# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    archid-.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>            +#+  +:+       +#+       #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 21:01:18 by archid-           #+#    #+#              #
#    Updated: 2024/11/24 15:25:39 by archid-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from sys import argv

encoding = (
    ".-", "-...", "-.-.", "-..", ".", "..-.",
    "--.", "....", "..", ".---", "-.-", ".-..",
    "--", "-.", "---", ".--.", "--.-", ".-.",
    "...", "-", "..-", "...-", ".--", "-..-",
    "-.--", "--..",
)

mapping = { chr(c) : encoding[c - 97] for c in range(97, 123) }

if __name__ == '__main__':
    if len(argv) != 2 or argv[1] == "usage" or not argv[1].isalpha():
        print(f"./{argv[0]} <a-zA-Z string>")
        exit(-1)
    s = argv[1].lower()
    print(" ".join([mapping[s[idx]] for idx in range(len(s))]))
