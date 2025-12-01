# 📋 Evaluation Tests - Minishell

Tests organizados según los criterios de la **evaluation sheet** oficial de 42.

## 🎯 Estructura de Evaluación

La evaluación de minishell se divide en 8 secciones obligatorias (40 puntos) y bonus opcional (10 puntos).

### Secciones Obligatorias (40 puntos)

#### 1. Simple Commands (5 pts)
- ✅ Ejecutar comandos simples con y sin path
- ✅ Búsqueda en PATH
- ✅ Comandos con argumentos
- ✅ Manejo de errores (command not found)

#### 2. Builtin Commands (5 pts)
- ✅ `echo` con y sin `-n`
- ✅ `cd` (con path relativo, absoluto, sin argumentos)
- ✅ `pwd` sin opciones
- ✅ `export` (crear/modificar variables)
- ✅ `unset` (eliminar variables)
- ✅ `env` (mostrar environment)
- ✅ `exit` con y sin argumentos numéricos

#### 3. Redirections (5 pts)
- ✅ `>` (output redirection)
- ✅ `>>` (append)
- ✅ `<` (input redirection)
- ✅ `<<` (heredoc)
- ✅ Múltiples redirecciones

#### 4. Pipes (5 pts)
- ✅ Pipes simples `|`
- ✅ Múltiples pipes
- ✅ Pipes con builtins
- ✅ Pipes con errores

#### 5. Environment Variables (5 pts)
- ✅ Expansión `$VAR`
- ✅ Variables inexistentes
- ✅ `$?` (exit status)
- ✅ Variables después de `export`

#### 6. Exit Status $? (5 pts)
- ✅ `$?` = 0 (éxito)
- ✅ `$?` = 1 (error)
- ✅ `$?` = 2 (syntax error)
- ✅ `$?` = 127 (command not found)
- ✅ Actualización correcta

#### 7. Signals (5 pts)
- ⚠️ `ctrl-C` - Nueva línea
- ⚠️ `ctrl-D` - Exit
- ⚠️ `ctrl-\` - No hace nada
- **Nota**: Tests manuales requeridos

#### 8. Quotes (5 pts)
- ✅ Comillas simples `'` (sin expansión)
- ✅ Comillas dobles `"` (con expansión)
- ✅ Preservación de espacios
- ✅ Comillas vacías
- ✅ Comillas anidadas

### Sección Bonus (10 puntos) ⭐ OPCIONAL

#### 9. Logical Operators (bonus)
- `&&` (AND)
- `||` (OR)
- Paréntesis para prioridad

#### 10. Wildcards (bonus)
- `*` (cualquier secuencia)
- `?` (un carácter)
- `[...]` (conjunto de caracteres)

## 🚀 Ejecución

### Ejecutar todos los tests de evaluación

```bash
cd evaluation_tests
./test_evaluation.sh
```

### Salida esperada

```
╔════════════════════════════════════════════════════════════╗
║  EVALUATION TESTS - MINISHELL                              ║
╚════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════
1. SIMPLE COMMANDS (Mandatory - 5 pts)
═══════════════════════════════════════════════════════════

Test 1: Comando simple: ls
...
✅ TEST PASADO

[... más tests ...]

╔════════════════════════════════════════════════════════════╗
║                  RESUMEN DE EVALUACIÓN                     ║
╠════════════════════════════════════════════════════════════╣
║  Total de tests ejecutados: 45                             ║
║  Tests pasados: 45                                         ║
║  Tests fallados: 0                                         ║
╚════════════════════════════════════════════════════════════╝

Tasa de éxito: 100%
Puntos estimados (parte obligatoria): 40/40

🎉 TODOS LOS TESTS DE EVALUACIÓN PASARON 🎉
```

## 📊 Interpretación de Resultados

### Puntuación

- **40/40 puntos**: Todas las funcionalidades obligatorias implementadas
- **35-39 puntos**: Casi completo, algunos edge cases fallan
- **30-34 puntos**: Funcional pero con problemas en varias áreas
- **< 30 puntos**: Funcionalidades críticas faltantes

### Nota Final

```
Puntos Obligatorios: 40 pts (máximo)
Puntos Bonus:        10 pts (opcional)
─────────────────────────────────
Total Posible:       50 pts

Nota = (Puntos / 40) * 100  (sin bonus)
Nota = (Puntos / 50) * 125  (con bonus, máximo 125)
```

## 🔍 Comparación con Tests Existentes

### Tests de Parsing vs Tests de Evaluación

| Tests de Parsing | Tests de Evaluación |
|------------------|---------------------|
| Enfoque técnico | Enfoque evaluación |
| Edge cases | Casos básicos requeridos |
| Falsos positivos detectados | Criterios oficiales |
| 50 tests | 45+ tests |
| Debugging | Aprobación |

**Recomendación**: Usa ambos
- **Evaluation tests**: Para saber si aprobarás
- **Parsing tests**: Para encontrar y corregir bugs

## ⚠️ Tests Manuales Requeridos

Los siguientes aspectos deben probarse manualmente durante la evaluación:

### 1. Signals (ctrl-C, ctrl-D, ctrl-\)
```bash
./bin/minishell
# Presionar ctrl-C -> debe mostrar nueva línea
# Presionar ctrl-D -> debe salir
# Presionar ctrl-\ -> no debe hacer nada
```

### 2. Prompt Display
```bash
# El prompt debe mostrarse correctamente
# Ejemplo: minishell>
```

### 3. History
```bash
# Flechas arriba/abajo deben navegar el historial
```

### 4. Interactive Behavior
- Readline funciona correctamente
- Autocompletado (si implementado)
- Edición de línea

## 🎓 Consejos para la Evaluación

1. **Ejecuta los tests antes**: `./test_evaluation.sh`
2. **Revisa los fallos**: Cada test muestra qué esperaba
3. **Prueba manualmente**: Signals y comportamiento interactivo
4. **Prepara explicaciones**: Entiende cómo funciona tu código
5. **Ten ejemplos listos**: Muestra casos especiales que manejas bien

## 🐛 Casos Comunes que Fallan

### Exit Codes Incorrectos
```bash
# Debe retornar 2, no 258 o 1
ls >
echo $?  # Debe ser 2
```

### Variables en Quotes
```bash
echo '$HOME'     # Debe imprimir: $HOME
echo "$HOME"     # Debe expandir
```

### Redirecciones Múltiples
```bash
< in > out cat   # Debe funcionar
```

### Pipes con Errores
```bash
ls /noexiste | grep x   # Debe manejar el error correctamente
```

## 📖 Referencias

- [42 Subject - Minishell](https://cdn.intra.42.fr/pdf/pdf/XXX/minishell.en.pdf)
- Bash man page: `man bash`
- POSIX Shell: [Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)

## ✅ Checklist Pre-Evaluación

- [ ] Compilación sin errores ni warnings
- [ ] No hay leaks de memoria (valgrind)
- [ ] Tests de evaluación al 100%
- [ ] Tests de parsing al 90%+ (opcional, para robustez)
- [ ] Ctrl-C, Ctrl-D, Ctrl-\\ funcionan
- [ ] Readline y history funcionan
- [ ] Norminette pasa (si aplica)
- [ ] Makefile correcto (all, clean, fclean, re)
- [ ] README.md actualizado
