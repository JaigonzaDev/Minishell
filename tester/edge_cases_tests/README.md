# Edge Cases Tests

Tests comprehensivos de casos límite (edge cases) para el minishell, basados en la documentación de casos extremos.

## Archivos

### Scripts de Tests
- **test_wildcards.sh**: Tests de wildcards y patrones (`*`, `.*`, `*.txt`, etc.)
- **test_redirections.sh**: Tests de redirecciones y pipes complejas
- **run_all_tests.sh**: 🎯 **Master runner** que ejecuta todos los tests

## Uso

```bash
cd tester/edge_cases_tests

# Ejecutar TODOS los tests
./run_all_tests.sh

# O ejecutar tests individuales
./test_wildcards.sh
./test_redirections.sh
```

## 🐛 Bugs Identificados

Ver informe completo en: **`tester/INFORME_BUGS.md`**

### 🔴 BUG #2: Wildcards No Se Expanden (CRÍTICO)
- **Afecta**: 5/7 tests en `test_wildcards.sh`
- **Problema**: Wildcards se imprimen literalmente sin expandir
- **Ejemplos**:
  - `echo *` → minishell: `*` ❌ | bash: `Makefile bin build...` ✅
  - `echo .*` → minishell: `.*` ❌ | bash: `.git .vscode` ✅
- **Nota**: ⚠️ Verificar si wildcards son obligatorios en el subject de minishell

## Casos de Prueba

### Wildcards (2/7 pasando - 28%)
- `echo .*` - Archivos ocultos (`.gitignore`, `.vscode`, etc.) ❌
- `echo *` - Archivos normales ❌
- `echo .*.` - Directorio padre (`..`) ❌
- `echo *.txt` - Archivos con extensión específica ❌
- `echo *.xyz` - Patrón sin coincidencias ❌
- `************M*******a******k*****` - Comando con wildcards (debe dar error 127) ✅

### Redirecciones y Pipes (9/10 pasando - 90%)
- `cat < in` - Redirección de entrada
- `echo test > out` - Redirección de salida
- `echo test >> out` - Redirección append
- `echo hello | cat` - Pipe simple
- `echo test | cat | cat` - Pipes múltiples
- `ls | head -5` - Pipe con comandos externos
- `cat < in > out` - Redirección entrada y salida
- `nonexistent_cmd > out` - Redirección con comando inexistente

## Características del Tester

1. **Comparación con Bash**: Cada test se ejecuta primero en bash para obtener el comportamiento esperado
2. **Entorno Aislado**: Usa directorios temporales para evitar contaminar el workspace
3. **Filtrado Robusto**: Elimina output de sanitizer, debug, etc.
4. **Verificación Múltiple**: Verifica output, exit codes y archivos generados
5. **Limpieza Automática**: Elimina archivos temporales después de cada ejecución

## Notas

- Los tests crean archivos temporales en `/tmp` y los limpian automáticamente
- Se compara el output con el de bash real para verificar compatibilidad
- No modifica el código del minishell, solo lo prueba
- Diseñado para evitar falsos negativos causados por el propio tester
