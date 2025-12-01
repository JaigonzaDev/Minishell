# Tests de Parsing y Expansión

Este directorio contiene tests completos para verificar el parsing, errores de sintaxis y expansión de variables del minishell.

## Archivos

### Scripts de Tests
- **test_syntax_manual.sh**: Verifica mensajes de error de sintaxis (10/10 ✅)
- **test_syntax_exit_code.sh**: Verifica que `$?` = 2 después de errores de sintaxis (0/15 ❌)
- **test_expander.sh**: Verifica expansión de variables (`$VAR`, `$?`, `$0`, etc.) (2/10 ❌)
- **run_all_tests.sh**: 🎯 **Master script** que ejecuta todos los tests y muestra resumen global

### Documentación
- **README.md**: Este archivo
- **RESULTS.md**: Resultados detallados de la última ejecución

## Uso Rápido

```bash
cd tester/parsing_tests

# Ejecutar TODOS los tests con resumen bonito
./run_all_tests.sh

# O ejecutar tests individuales
./test_syntax_manual.sh
./test_syntax_exit_code.sh
./test_expander.sh
```

## 🐛 Bugs Identificados

Ver informe completo en: **`tester/INFORME_BUGS.md`**

### 🔴 BUG #1: Exit Status Incorrecto (CRÍTICO)
- **Afecta**: 10 tests en `test_syntax_exit_code.sh`
- **Problema**: `$?` retorna 0 en lugar de 2 tras errores de sintaxis
- **Ejemplo**: `ls >` → minishell: `$? = 0` ❌ | bash: `exit 2` ✅

### 🔴 BUG #5: Variables Inexistentes Eliminan Palabras (CRÍTICO)
- **Afecta**: ~4 tests en `test_expander.sh`
- **Problema**: Palabras después de variables inexistentes desaparecen
- **Ejemplo**: `echo hello $non_exist world` → minishell: `hello` ❌ | bash: `hello world` ✅

### 🟡 BUG #4: Variables Con Espacios No Se Colapsan (MEDIA)
- **Afecta**: ~3 tests en `test_expander.sh`
- **Problema**: Espacios múltiples no se colapsan como en bash
- **Ejemplo**: `test="  hello  "` → minishell: `  hello  ` ❌ | bash: `hello` ✅

## Estado Actual

### ✅ Mensajes de Error (10/10 tests pasando - 100%)
El minishell detecta correctamente todos los errores de sintaxis y muestra los mensajes apropiados:
- `ls >` → `syntax error near unexpected token 'newline'` ✓
- `>>>` → `syntax error near unexpected token '>'` ✓
- `<<<` → `syntax error near unexpected token '<'` ✓
- `|` → `syntax error near unexpected token '|'` ✓
- Y más...

### ❌ Exit Code ($? = 2) (0/15 tests fallando)
**PROBLEMA:** El minishell NO está actualizando `$?` a 2 después de errores de sintaxis.
- Actualmente: `$?` = 0 después de error de sintaxis
- Esperado: `$?` = 2 (estándar de bash)

## Casos de Prueba

### Errores de Sintaxis Requeridos

| Comando | Mensaje Esperado | Exit Code | Estado |
|---------|------------------|-----------|--------|
| `ls >` | `syntax error near unexpected token 'newline'` | 2 | ✓ |
| `>>>` | `syntax error near unexpected token '>'` | 2 | ✓ |
| `<<<` | `syntax error near unexpected token '<'` | 2 | ✓ |
| `\|` | `syntax error near unexpected token 'newline'` | 2 | ✓ |
| `\| \|` | `syntax error near unexpected token '\|'` o `newline` | 2 | ✓ |
| `<<` | `syntax error near unexpected token 'newline'` | 2 | ✓ Bonus |
| `>>` | `syntax error near unexpected token 'newline'` | 2 | ✓ Bonus |
| `<` | `syntax error near unexpected token 'newline'` | 2 | ✓ |
| `echo \| \| cat` | `syntax error near unexpected token '\|'` | 2 | ✓ |
| `ls > > file` | `syntax error near unexpected token '>'` | 2 | ✓ |

## Uso

```bash
cd tester/syntax_tests
./test_syntax_manual.sh
```

## Comportamiento Esperado

El minishell debe:
1. Detectar errores de sintaxis en los operadores (`>`, `<`, `|`, etc.)
2. Mostrar un mensaje de error descriptivo en stderr
3. **Retornar exit code 2** (estándar de bash para errores de sintaxis)
4. No ejecutar el comando si hay error de sintaxis
5. Continuar esperando el siguiente comando

## Nota Importante

El exit code del minishell después de un error de sintaxis puede ser 0 (normal) si el shell continúa ejecutándose correctamente. El exit code 2 debe ser almacenado en `$?` para el siguiente comando dentro del shell.

## Ejemplo de Comportamiento

```bash
$ ./minishell
minishell> ls >
minishell: syntax error near unexpected token `newline'
minishell> echo $?
2
minishell> ls
# Ejecuta normalmente
minishell> echo $?
0
```
