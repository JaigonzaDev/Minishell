# 🧪 Minishell Test Suite

Suite completa de tests para validar el comportamiento del minishell comparado con bash.

## 📊 Resultados Actuales

**Tests Obligatorios: 45/45 (100%)** ✅
- Exit codes de sintaxis: 14/14 ✅
- Mensajes de sintaxis: 9/9 ✅
- Expansión de variables: 10/10 ✅
- Redirecciones y pipes: 10/10 ✅

**Tests Bonus (Opcional): 2/7 (28%)**
- Wildcards (*, ?, [...]): 2/7 ⚠️ NO OBLIGATORIO

## 🚀 Ejecución Rápida

```bash
# Ejecutar TODOS los tests (obligatorios + bonus)
cd tester/tests && ./run_all.sh

# Ejecutar tests individuales
cd tester/tests
./test_syntax_exit_code.sh    # Exit codes (2 para syntax errors)
./test_syntax_manual.sh        # Mensajes de error de sintaxis
./test_expander.sh             # Expansión de variables ($var, $?, etc)
./test_redirections.sh         # Redirecciones y pipes
./test_wildcards.sh            # BONUS: Wildcards (opcional)
```

## 📁 Estructura

```
tester/
├── README.md              # Este archivo
└── tests/                 # Todos los tests
    ├── run_all.sh                 # 🎯 Script principal
    ├── test_syntax_exit_code.sh   # Exit codes de sintaxis
    ├── test_syntax_manual.sh      # Mensajes de error
    ├── test_expander.sh           # Expansión de variables
    ├── test_redirections.sh       # Redirecciones y pipes
    └── test_wildcards.sh          # BONUS: Wildcards (opcional)
```

## 📝 Descripción de Tests

### Tests Obligatorios

#### 1. Exit Codes de Sintaxis (14 tests)
Verifica que el minishell retorne el código de salida correcto para errores de sintaxis.
- Debe retornar `2` para errores de sintaxis (como bash)
- Ejemplos: pipes sin comando, redirecciones inválidas, quotes sin cerrar

#### 2. Mensajes de Sintaxis (9 tests)
Valida los mensajes de error para sintaxis inválida.
- Tokens inesperados
- Operadores mal formados
- Quotes sin cerrar

#### 3. Expansión de Variables (10 tests)
Prueba la expansión de variables y casos especiales.
- Variables de entorno: `$HOME`, `$USER`, `$PATH`
- Exit status: `$?`
- Variables posicionales: `$0`, `$1`, etc.
- Variables consecutivas: `$a$b`
- Variables inexistentes
- Word splitting (solo en variables sin comillas)

#### 4. Redirecciones y Pipes (10 tests)
Valida redirecciones, heredocs y pipes.
- Redirecciones de entrada/salida: `<`, `>`, `>>`
- Heredocs: `<<`
- Pipes: `|`
- Combinaciones de redirecciones
- Errores de archivos (deben ir a stderr)

### Tests Bonus (Opcional)

#### 5. Wildcards (7 tests) ⭐ BONUS - NO OBLIGATORIO
Expansión de patrones con wildcards.
- `*` (cualquier secuencia de caracteres)
- `?` (un solo carácter)
- `[...]` (conjunto de caracteres)

> ⚠️ **Nota**: Los wildcards son una característica **OPCIONAL** según el subject de minishell.
> No es necesario implementarlos para aprobar el proyecto.

## ✅ Criterios de Éxito

Para considerar el minishell completo y funcional:
- ✅ **100% en tests obligatorios** (45/45)
- ⚠️ Tests bonus opcionales (wildcards)

## 🐛 Bugs Corregidos

1. **Exit status para syntax errors**: Ahora retorna `2` (antes retornaba `258`)
2. **Word splitting**: Implementado para variables sin comillas
3. **Variables consecutivas**: `$a$b` ahora funciona correctamente
4. **Variables posicionales**: `$0`, `$1`, etc. implementados
5. **Operadores en variables**: Respeta comillas al separar operadores
6. **Errores a stderr**: Los mensajes de error van a stderr (fd 2)
7. **Variables vacías**: No eliminan palabras siguientes

## 📖 Comparación con Bash

Todos los tests comparan el output y exit code del minishell con bash real:
```bash
# El test ejecuta el mismo comando en ambos y compara
bash -c "comando" > output_bash.txt 2>&1
./minishell < input.txt > output_mini.txt 2>&1
diff output_bash.txt output_mini.txt
```

## 🎯 Próximos Pasos

Si quieres alcanzar el 100% completo (incluyendo bonus):
1. Implementar wildcards usando `glob.h` o custom globbing
2. Manejar `*`, `?`, `[...]` patterns
3. Aplicar solo en argumentos sin comillas
4. Expandir en orden alfabético

Tiempo estimado: 3-5 días para implementación completa de wildcards.
