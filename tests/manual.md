# Testes Manuais
- Testar com programas que mostrem uma tela inteira

# Test de EOF
Se o End Of File for "EOF" o programa não deve interpretar "EOFA"="EOF"
Exemplo
```bash
# "exit" sai do programa

# comando que deve sair
exit
# comando que não deve sair
exita
```

# Test here_doc
valgrind --leak-check=full ./minishell
here_doc
EOF